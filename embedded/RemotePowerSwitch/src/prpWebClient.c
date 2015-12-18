/**
 *  Filename:       prpWebClient.c
 *  Platform(s):    
 *  Project:        RemotePowerSwitch
 *  Created:        Dec 17, 2015
 *  Description:    
 *  Notes:          
 *  Author:         Andreas Isenegger
 *  Copyright:      2014, Bitcontrol GmbH, Switzerland.
 *                  All rights reserved.
 */

#include "prpWebClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cfgGlobal.h>
#include <cfgPlatform.h>

#include <curl/curl.h>

//------------------------------------------------------------------------------
// Symbols and Macros
/** Maximum size of an URI string in bytes. */
#define URI_STR_SIZE_MAX	512

//------------------------------------------------------------------------------
// Types
/** Instance descriptor type. */
typedef struct inst_struct
{
    /** \c TRUE if started, \c FALSE otherwise. */
    BOOL started;

    char webServerURI[URI_STR_SIZE_MAX]; /** URI of the web server. */
} inst_t;

struct string {
  char *buf;
  size_t len;
};

//------------------------------------------------------------------------------
// Constants and Variables
static inst_t sInstDscr; /**< Instance descriptor. */

//------------------------------------------------------------------------------
// Local Functions
/**
 * Initializes the variables of the instance.
 */
static void initInst(void)
{
    // todo Auto-generated function body
    memset(&sInstDscr, 0, sizeof(sInstDscr));
}

static void initString(struct string *s) {
  s->len = 0;
  s->buf = malloc(s->len+1);
  if (s->buf == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->buf[0] = '\0';
}

static size_t fWrite(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->buf = realloc(s->buf, new_len+1);
  if (s->buf == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->buf+s->len, ptr, size*nmemb);
  s->buf[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

//------------------------------------------------------------------------------
// Global Functions
int prpWebClient_start(const char* uri)
{
    CHECK_NOT_STARTED_INT(&sInstDscr, 0);
    CHECK_POINTER_INT(uri);

    initInst();
    strncpy(sInstDscr.webServerURI, uri, sizeof(sInstDscr.webServerURI));

    sInstDscr.started = TRUE;
    return R_SUCCESS;
}

int prpWebClient_stop(void)
{
	// todo Auto-generated function body
	if (sInstDscr.started) {
		sInstDscr.started = FALSE;
	}
	return R_SUCCESS;
}

int prpWebClient_GET_switch(BOOL* value)
{
    CHECK_STARTED_INT(&sInstDscr, 0);
    CHECK_POINTER_INT(value);

	CURL *curl;
	CURLcode res;
	int result = R_ERROR;
	char strURL[URI_STR_SIZE_MAX];

	curl = curl_easy_init();
	if(curl)
	{
	    struct string str;
	    initString(&str);

	    /* Perform a GET request, res will contain the return code. */
	    strcpy(strURL, sInstDscr.webServerURI);
	    strncat(strURL, "switches/1", sizeof(strURL));
	    curl_easy_setopt(curl, CURLOPT_URL, strURL);
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fWrite);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
	    res = curl_easy_perform(curl); // Perform request, synchronous call
	    if(res == CURLE_OK)
	    {
	    	char* pChar = strstr(str.buf, "\"switch\":");
	    	if (pChar != NULL) {
	    		pChar = strstr(pChar, "\"on\"");
	    		if (pChar != NULL)
	    		{
	    			*value = TRUE;
	    		}
	    		else
	    		{
	    			*value = FALSE;
	    		}
				result = R_SUCCESS;
	    	}
		    printf("%s\n", str.buf); // todo For learning, can be deleted; 17-Dec-2015/ais
		    free(str.buf);
	    }
	    else
	    {
	    	fprintf(stderr, "curl_easy_perform() failed: %s\n",
	    			curl_easy_strerror(res));
	    }
	    curl_easy_cleanup(curl);
	}
	return result;
}

int prpWebClient_POST_status(BOOL value)
{
    CHECK_STARTED_INT(&sInstDscr, 0);

	CURL *curl;
	CURLcode res;
	int result = R_ERROR;
	char strURL[URI_STR_SIZE_MAX];

	curl = curl_easy_init();
	if(curl)
	{
	    struct string str;
	    initString(&str);

	    /* Perform a POST request, res will contain the return code. */
	    strcpy(strURL, sInstDscr.webServerURI);
	    strncat(strURL, "status/1/", sizeof(strURL));
		if (value)
		{
			strncat(strURL, "on", sizeof(strURL));
		}
		else
		{
			strncat(strURL, "off", sizeof(strURL));
		}
	    curl_easy_setopt(curl, CURLOPT_URL, strURL);
	    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fWrite);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);
	    res = curl_easy_perform(curl); // Perform request, synchronous call
		if (res == CURLE_OK)
		{
			printf("%s\n", str.buf); // todo For learning, can be deleted; 17-Dec-2015/ais
			free(str.buf);
			result = R_SUCCESS;
		}
		else
		{
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
		}
	    curl_easy_cleanup(curl);
	}
	return result;
}
