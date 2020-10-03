/***************************************************************************
*
*  Project           _        __
*					(_)_ __  / _| ___
*					| | '_ \| |_ / _ \
*					| | | | |  _| (_) |
*					|_|_| |_|_|  \___/
*				  ___ ___  _ __ ___  _ __   __ _
*				 / __/ _ \| '__/ _ \| '_ \ / _` |
*				| (_| (_) | | | (_) | | | | (_| |
*				 \___\___/|_|  \___/|_| |_|\__,_|
*
* Copyright (C) 2020, Momos, <https://twitter.com/fadhlimomos_>, et al.
* Copyright (C) 2020, Fray117, <fray117@exploiter.id>, et al.
*
* This software is unlicensed, you may distribute this Software as you
* wish and editing this program is allowed in many ways.
*
* You may opt to use, copy, modify, merge, publish, distribute and/or sell
* copies of the Software, and permit persons to whom the Software is
* furnished to do so, under the terms of the COPYING file.
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express or implied.
*
***************************************************************************/
/* <DESC>
 * Crawl Covid-19 Information
 * </DESC>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

struct string {
	char *ptr;
	size_t len;
};

void init_string(struct string *s) {
	s->len = 0;
	s->ptr = malloc(s->len + 1);

	if (s->ptr == NULL) {
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}

	s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
	size_t new_len = s->len + size * nmemb;
	s->ptr = realloc(s->ptr, new_len + 1);

	if (s->ptr == NULL) {
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}

	memcpy(s->ptr + s->len, ptr, size * nmemb);
	s->ptr[new_len] = '\0';
 	s->len = new_len;

	return size * nmemb;
}

int main() {
	// printf() displays the string inside quotation
	CURL *curl;
	CURLcode res;

	struct json_object *parsed_json;
	struct json_object *data;

	struct json_object *name;
	struct json_object *positif;
	struct json_object *sembuh;
	struct json_object *meninggal;
	struct json_object *dirawat;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if(curl) {
		struct string s;
		init_string(&s);

		curl_easy_setopt(curl, CURLOPT_URL, "https://api.kawalcorona.com/indonesia/");

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

		#ifdef SKIP_PEER_VERIFICATION
		/*
		 * If you want to connect to a site who isn't using a certificate that is
		 * signed by one of the certs in the CA bundle you have, you can skip the
		 * verification of the server's certificate. This makes the connection
		 * A LOT LESS SECURE.
		 *
		 * If you have a CA cert for the server stored someplace else than in the
		 * default bundle, then the CURLOPT_CAPATH option might come handy for
		 * you.
		 */
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		#endif

		#ifdef SKIP_HOSTNAME_VERIFICATION
		/*
		 * If the site you're connecting to uses a different host name that what
		 * they have mentioned in their server certificate's commonName (or
		 * subjectAltName) fields, libcurl will refuse to connect. You can skip
		 * this check, but this will make the connection less secure.// cJSON *json = cJSON_Parse(data);// printf("Data: %d\n", res);
		 */
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		#endif

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		/* Check for errors */
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);

		parsed_json = json_tokener_parse(s.ptr);
		data = json_object_array_get_idx(parsed_json, 0);

		json_object_object_get_ex(data, "name", &name);
		json_object_object_get_ex(data, "positif", &positif);
		json_object_object_get_ex(data, "sembuh", &sembuh);
		json_object_object_get_ex(data, "meninggal", &meninggal);
		json_object_object_get_ex(data, "dirawat", &dirawat);

		printf("Statistik Covid-19 Indonesia\n\nPositif: %s\nSembuh: %s\nMeninggal: %s\nDirawat: %s\n", json_object_get_string(positif), json_object_get_string(sembuh), json_object_get_string(meninggal) ,json_object_get_string(dirawat));
		free(s.ptr);
	}

	curl_global_cleanup();
	return 0;
}
