# LightWave Client - Okta Client Credentials Flow
This is a sample application that illustrates how to retrieve, validate, and revoke OAuth 2 access tokens using the [Okta Identity Service](www.okta.com). The sample application is a C program that retrieves a new token, validates it, and revokes it.

The sample API illustrates how to manage access tokens withing the OAuth 2 Client Credentials Flow. A LightWave Client application might use this flow in the following scenario:
   
 + A Web service uses the OAuth 2 access tokens to authorize access to the service. The web service client is required to provide the access token via the HTTP Authorization header.
 + A mapping for the "Authorization" header is added to the API definition for the LightWave Client application, for those operations that require it.
 + The LightWave Client application uses the Okta API to request an access token from the authorization server. The token is returned as a Base64 encoded string, for example:
 ```
 eyJraWQiOiJCNlE5c ..... Kg5NtjFLNeAQ
 ```
 + The LightWave Client application constructs the Authorization header value by prefixing the token string with "Bearer" and sets it as the value of the Authorization header field in the CLIENT process request IPM. The CLIENT process includes the header with the Bearer token in the request to the service, for example:
 ```
 Authorization: Bearer eyJraWQiOiJCNlE5c ..... Kg5NtjFLNeAQ
 ```

 The access token response from the authorization server includes an expiration time. The LightWave Client application must track the expiration time of the token and request a new token when the timer expires, or if the token is explicitely revoked.

Note that although this sample was developed specifically for the Okta service, this API may be adapted for authorization servers provided by other identity providers or custom authorization servers.

## Prerequisites

+ NonStop C Compiler
+ [LightWave Client](https://docs.nuwavetech.com/display/LWCLIENT)
+ An Okta Identity Service account. For information on implementing the Client Credentials Flow on Okta, see [Implement the Client Credentials Flow](https://developer.okta.com/docs/guides/implement-client-creds/overview/).

The following Okta configuruation values must be copied from the Okta Developer Console to the SETUP TACL macro after installation of the sample:

+ base-url - The URL of the Okto authorization server. This value is shown under *Issuer URI* in the authorization server list in the Okta Console. See [Create an Authorization Server](https://developer.okta.com/docs/guides/customize-authz-server/overview/). 
+ scope - One or more scopes configured in the authorization server.
+ client-id / client-secreat - The client credentials for the Okta application. See [Find your application credentials](https://developer.okta.com/docs/guides/find-your-app-credentials/overview/).

## Install & Build

The application must be built from source. The source files are present in the repository for convenient viewing. 
In addition, a PAK archive containing all of the source files is available for transfer to your NonStop system.

| Repository File | NonStop File |
| -- | -- |
| macros/build.txt | build |
| macros/loadddl.txt | loadddl |
| macros/logcfg.txt | logcfg |
| resources/occfapi.json | occfapi |
| resources/occfddl.txt | occfddl |
| occfpak.bin | occfpak |
| src/oktaccf.c | oktaccfc |
| macros/setenv.txt | setenv |
| macros/startpw.txt | startpw |
| macros/startpw.txt | stoppw |
| macros/setenv.txt | unsetenv |

#### Upload the PAK archive

Download `occfpak.bin` from this repository to your local system, then upload to your NonStop server using binary transfer mode.

Note: to download the PAK file, click `occfpak.bin` in the file list to display the file details, then click the *Download* button.

Logon to TACL on your NonStop system to peform the installation and build steps.

#### Unpak the PAK archive
```
TACL > UNPAK OCCFPAK ($*.*.*), VOL $your-volume.your-subvolume.*, LISTALL, MYID
```

#### Build the application 
```
TACL > RUN LOADDDL
TACL > RUN BUILD
```
## Running the application
Customize the SETENV macro for your environment and run it to set the required PARAMs.
```
TACL> T/EDIT SETENV
TACL> RUN SETENV
```
Start the LightWave Client Pathway
```
TACL > RUN STARTPW
```
Run the application
```
TACL > RUN OKTACCF
```
Assistance is available through the [NuWave Technologies Support Center](http://support.nuwavetech.com).

