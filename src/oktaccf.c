
/**
 *
 *  Copyright (c) 2019 NuWave Technologies, Inc. All rights reserved.
 *
 */

#pragma nolist
#include <cextdecs>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tal.h>
#include <time.h>
#pragma list

#include "occf.h"

static const char* getEnvValue(const char* name);
static void printErrorResponse(const lightwave_rp_header_def* header,
                               const error_response_def* error);
static void printSendError(void);
static void printToken(const char* token);

int main(int argc, char** argv, char** env) {
  int rc;
  const char* pathmon_name;
  const char* server_class;
  const char* scope;
  long long start_time;
  long long end_time;
  int reply_len;

  get_token_rq_def get_token_rq;
  introspect_token_rq_def introspect_token_rq;
  revoke_token_rq_def revoke_token_rq;

  union {
    lightwave_rp_header_def header;
    get_token_200_rp_def reply_200;
    get_token_other_rp_def reply_other;
  } get_token_rp;

  union {
    lightwave_rp_header_def header;
    introspect_token_200_rp_def reply_200;
    introspect_token_other_rp_def reply_other;
  } introspect_token_rp;

  union {
    lightwave_rp_header_def header;
    revoke_token_200_rp_def reply_200;
    revoke_token_other_rp_def reply_other;
  } revoke_token_rp;

  printf("\nLightWave Client(tm) - Okta Client Credentials Flow "
         "- Test Driver - 29JUL2019\n");

  /* Get variables from the environment. These are set by the SETENV macro. */
  if ((pathmon_name = getEnvValue("PATHMON-NAME")) == NULL) {
    return 0;
  }

  if ((server_class = getEnvValue("SERVER-CLASS")) == NULL) {
    return 0;
  }

  if ((scope = getEnvValue("SCOPE")) == NULL) {
    return 0;
  }

  /* Initialize and send a get token request. */
  printf("\nSending a get access token request ... ");

  memset(&get_token_rq, 0, sizeof(get_token_rq));
  get_token_rq.lightwave_rq_header.rq_code = rq_get_token;
  strncpy(get_token_rq.scope, scope, sizeof(get_token_rq.scope));

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_(
      (char*)pathmon_name, (short)strlen(pathmon_name), (char*)server_class,
      (short)strlen(server_class), (char*)&get_token_rq, (char*)&get_token_rp,
      sizeof(get_token_rq), sizeof(get_token_rp), &reply_len);

  end_time = JULIANTIMESTAMP();

  if (rc != 0) {
    printSendError();
    return 0;
  }

  if (get_token_rp.header.http_status != 200) {
    printErrorResponse(&get_token_rp.header,
                       &get_token_rp.reply_other.error_response);
    return 0;
  }

  printf("completed in %g seconds.\n",
         (double)(end_time - start_time) / 1000000.0);

  printf("\n");
  printf("The access token is:\n\n");
  printToken(get_token_rp.reply_200.token_response.access_token);
  printf("\n");
  printf("Scope:      %s\n", get_token_rp.reply_200.token_response.scope);
  printf("Expires In: %d\n", get_token_rp.reply_200.token_response.expires_in);

  /* Initialize and send an introspect request. */
  printf("\nSending an introspection request ... ");

  memset(&introspect_token_rq, 0, sizeof(introspect_token_rq));
  introspect_token_rq.lightwave_rq_header.rq_code = rq_introspect_token;
  strncpy(introspect_token_rq.token,
          get_token_rp.reply_200.token_response.access_token,
          sizeof(introspect_token_rq.token));

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_(
      (char*)pathmon_name, (short)strlen(pathmon_name), (char*)server_class,
      (short)strlen(server_class), (char*)&introspect_token_rq,
      (char*)&introspect_token_rp, sizeof(introspect_token_rq),
      sizeof(introspect_token_rp), &reply_len);

  end_time = JULIANTIMESTAMP();

  if (rc != 0) {
    printSendError();
    return 0;
  }

  if (introspect_token_rp.header.http_status != 200) {
    printErrorResponse(&introspect_token_rp.header,
                       &introspect_token_rp.reply_other.error_response);
    return 0;
  }

  printf("completed in %g seconds.\n",
         (double)(end_time - start_time) / 1000000.0);

  printf("\n");
  printf("Token active: %s\n",
         (introspect_token_rp.reply_200.introspect_response.active ? "true"
                                                                   : "false"));

  if (introspect_token_rp.reply_200.introspect_response.active != 0) {
    time_t t;

    t = (time_t)introspect_token_rp.reply_200.introspect_response.iat;
    printf("  Issued:  %s", ctime(&t));
    t = (time_t)introspect_token_rp.reply_200.introspect_response.exp;
    printf("  Expires: %s", ctime(&t));
    printf("\n");
  }

  /* Initialize and send an introspect request. */
  printf("Sending a revoke request ... ");

  memset(&revoke_token_rq, 0, sizeof(revoke_token_rq));
  revoke_token_rq.lightwave_rq_header.rq_code = rq_revoke_token;
  strncpy(revoke_token_rq.token,
          get_token_rp.reply_200.token_response.access_token,
          sizeof(revoke_token_rq.token));

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_((char*)pathmon_name, (short)strlen(pathmon_name),
                          (char*)server_class, (short)strlen(server_class),
                          (char*)&revoke_token_rq, (char*)&revoke_token_rp,
                          sizeof(revoke_token_rq), sizeof(revoke_token_rp),
                          &reply_len);

  end_time = JULIANTIMESTAMP();

  if (rc != 0) {
    printSendError();
    return 0;
  }

  if (revoke_token_rp.header.http_status != 200) {
    printErrorResponse(&revoke_token_rp.header,
                       &revoke_token_rp.reply_other.error_response);
    return 0;
  }

  printf("completed in %g seconds.\n",
         (double)(end_time - start_time) / 1000000.0);

  /* Re-send the introspection request to check the token state. */
  printf("\nSending an introspection request ... ");

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_(
      (char*)pathmon_name, (short)strlen(pathmon_name), (char*)server_class,
      (short)strlen(server_class), (char*)&introspect_token_rq,
      (char*)&introspect_token_rp, sizeof(introspect_token_rq),
      sizeof(introspect_token_rp), &reply_len);

  end_time = JULIANTIMESTAMP();

  if (rc != 0) {
    printSendError();
    return 0;
  }

  if (introspect_token_rp.header.http_status != 200) {
    printErrorResponse(&introspect_token_rp.header,
                       &introspect_token_rp.reply_other.error_response);
    return 0;
  }

  printf("completed in %g seconds.\n",
         (double)(end_time - start_time) / 1000000.0);

  printf("\n");
  printf("Token active: %s\n",
         (introspect_token_rp.reply_200.introspect_response.active ? "true"

                                                                   : "false"));
  printf("\nDone.\n");

  return 0;
}

static const char* getEnvValue(const char* name) {
  const char* v = getenv(name);
  if (v == NULL) {
    printf("PARAM \"%s\" not set. Did you run SETENV?\n", name);
  }
  return v;
}

static void printErrorResponse(const lightwave_rp_header_def* header,
                               const error_response_def* error) {

  printf("The service returned HTTP status %d:\n", header->http_status);
  printf("  error:       %s\n", error->error_rw);
  printf("  description: %s\n", error->error_description);
  printf("\n");
}

static void printSendError(void) {
  short prc;
  short frc;

  SERVERCLASS_SEND_INFO_(&prc, &frc);

  printf("\n\nSERVERCLASS_SEND_ error %hd:%hd occurred.\n\n", prc, frc);
  switch (frc) {
  case 14:
    printf("Did you start the pathway by running STARTPW?\n\n");
    break;
  default:
    break;
  }

  return;
}

static void printToken(const char* token) {
  int width = 70;
  size_t i;
  size_t len;

  for (i = 0, len = strlen(token); i < len; i += width) {
    printf("%.*s\n", width, &token[i]);
  }
}

/* End of file. */