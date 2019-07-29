/* SCHEMA PRODUCED DATE - TIME : 7/29/2019 - 13:16:53 */
#pragma section lightwave_rp_code_enum
/* Definition LIGHTWAVE-RP-CODE-ENUM created on 07/29/2019 at 13:16 */
enum
{
   lw_rp_success = 0,
   lw_rp_info = 1,
   lw_rp_error = 2
};
typedef short                           lightwave_rp_code_enum_def;
#pragma section lightwave_info_code_enum
/* Definition LIGHTWAVE-INFO-CODE-ENUM created on 07/29/2019 at 13:16 */
enum
{
   lw_info_field_truncated = 100,
   lw_info_array_truncated = 101
};
typedef short                           lightwave_info_code_enum_def;
#pragma section lightwave_error_src_enum
/* Definition LIGHTWAVE-ERROR-SRC-ENUM created on 07/29/2019 at 13:16 */
enum
{
   lw_error_src_lightwave = 1,
   lw_error_src_http = 2,
   lw_error_src_tcpip = 3,
   lw_error_src_ssl = 4
};
typedef short                           lightwave_error_src_enum_def;
#pragma section lightwave_error_enum
/* Definition LIGHTWAVE-ERROR-ENUM created on 07/29/2019 at 13:16 */
enum
{
   lw_error_invalid_license = 1,
   lw_error_invalid_header = 2,
   lw_error_invalid_rq_code = 3,
   lw_error_invalid_type = 4,
   lw_error_serialization_error = 5,
   lw_error_deserialization_error = 6,
   lw_error_request_timeout = 7,
   lw_error_response_not_defined = 12,
   lw_error_internal_error = 500
};
typedef short                           lightwave_error_enum_def;
#pragma section lightwave_rq_header
/* Definition LIGHTWAVE-RQ-HEADER created on 07/29/2019 at 13:16 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_rq_header
typedef struct __lightwave_rq_header
{
   short                           rq_code;
   unsigned short                  rq_version;
   __uint32_t                      rq_timeout;
   char                            reserved[24];
} lightwave_rq_header_def;
#define lightwave_rq_header_def_Size 32
#pragma section lightwave_rp_header
/* Definition LIGHTWAVE-RP-HEADER created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __lightwave_rp_header
typedef struct __lightwave_rp_header
{
   short                           rp_code;
   short                           http_status;
   short                           info_code;
   short                           info_detail;
   char                            reserved[24];
} lightwave_rp_header_def;
#define lightwave_rp_header_def_Size 32
#pragma section lightwave_error_rp
/* Definition LIGHTWAVE-ERROR-RP created on 07/29/2019 at 13:16 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_error_rp
typedef struct __lightwave_error_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   __int32_t                       error_source;
   __int32_t                       error_code;
   __int32_t                       error_subcode;
   char                            error_message[4096];
} lightwave_error_rp_def;
#define lightwave_error_rp_def_Size 4140
#pragma section okta_client_credential_val
/* Definition OKTA-CLIENT-CREDENTIAL-VAL created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __okta_client_credential_val
typedef struct __okta_client_credential_val
{
   short                           rq_introspect_token;
   /*value is 2*/
   short                           rq_revoke_token;
   /*value is 3*/
   short                           rq_get_token;
   /*value is 1*/
} okta_client_credential_val_def;
#define okta_client_credential_val_def_Size 6
#pragma section okta_client_credential_enm
/* Definition OKTA-CLIENT-CREDENTIAL-ENM created on 07/29/2019 at 13:16 */
enum
{
   rq_introspect_token = 2,
   rq_revoke_token = 3,
   rq_get_token = 1
};
typedef short                           okta_client_credential_enm_def;
#pragma section token_response
/* Definition TOKEN-RESPONSE created on 07/29/2019 at 13:16 */
#include <tnsint.h>
#pragma fieldalign shared2 __token_response
typedef struct __token_response
{
   char                            access_token[2048];
   char                            token_type[128];
   __int32_t                       expires_in;
   char                            scope[256];
   char                            refresh_token[256];
   char                            id_token[2048];
} token_response_def;
#define token_response_def_Size 4740
#pragma section error_response
/* Definition ERROR-RESPONSE created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __error_response
typedef struct __error_response
{
   char                            error_rw[256];
   char                            error_description[256];
} error_response_def;
#define error_response_def_Size 512
#pragma section introspect_response
/* Definition INTROSPECT-RESPONSE created on 07/29/2019 at 13:16 */
#include <tnsint.h>
#pragma fieldalign shared2 __introspect_response
typedef struct __introspect_response
{
   __int32_t                       active;
   char                            token_type[32];
   char                            scope[32];
   char                            client_id[32];
   char                            username[32];
   __int32_t                       exp;
   __int32_t                       iat;
   char                            sub[32];
   char                            aud[32];
   char                            iss[52];
   char                            jti[46];
   char                            uid[32];
} introspect_response_def;
#define introspect_response_def_Size 334
#pragma section introspect_token_rq
/* Definition INTROSPECT-TOKEN-RQ created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __introspect_token_rq
typedef struct __introspect_token_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            token[2048];
} introspect_token_rq_def;
#define introspect_token_rq_def_Size 2080
#pragma section introspect_token_200_rp
/* Definition INTROSPECT-TOKEN-200-RP created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __introspect_token_200_rp
typedef struct __introspect_token_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   introspect_response_def         introspect_response;
} introspect_token_200_rp_def;
#define introspect_token_200_rp_def_Size 366
#pragma section introspect_token_other_rp
/* Definition INTROSPECT-TOKEN-OTHER-RP created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __introspect_token_other_rp
typedef struct __introspect_token_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_response_def              error_response;
} introspect_token_other_rp_def;
#define introspect_token_other_rp_def_Size 544
#pragma section revoke_token_rq
/* Definition REVOKE-TOKEN-RQ created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __revoke_token_rq
typedef struct __revoke_token_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            token[2048];
} revoke_token_rq_def;
#define revoke_token_rq_def_Size 2080
#pragma section revoke_token_200_rp
/* Definition REVOKE-TOKEN-200-RP created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __revoke_token_200_rp
typedef struct __revoke_token_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
} revoke_token_200_rp_def;
#define revoke_token_200_rp_def_Size 32
#pragma section revoke_token_other_rp
/* Definition REVOKE-TOKEN-OTHER-RP created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __revoke_token_other_rp
typedef struct __revoke_token_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_response_def              error_response;
} revoke_token_other_rp_def;
#define revoke_token_other_rp_def_Size 544
#pragma section get_token_rq
/* Definition GET-TOKEN-RQ created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __get_token_rq
typedef struct __get_token_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            scope[256];
} get_token_rq_def;
#define get_token_rq_def_Size 288
#pragma section get_token_200_rp
/* Definition GET-TOKEN-200-RP created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __get_token_200_rp
typedef struct __get_token_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   token_response_def              token_response;
} get_token_200_rp_def;
#define get_token_200_rp_def_Size 4772
#pragma section get_token_other_rp
/* Definition GET-TOKEN-OTHER-RP created on 07/29/2019 at 13:16 */
#pragma fieldalign shared2 __get_token_other_rp
typedef struct __get_token_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_response_def              error_response;
} get_token_other_rp_def;
#define get_token_other_rp_def_Size 544