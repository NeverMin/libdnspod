#include "dnspod.hpp"

dnspod::dnspod(char* login_email, char* login_password) {
	setLoginEmail(login_email);
	setLoginPassword(login_password);
	setFormat("json");
}

dnspod::~dnspod() {
	// TODO Auto-generated destructor stub
}

void dnspod::getApiVersion() {
	setCallUrl("https://dnsapi.cn/Info.Version");
	callApi();
}

void dnspod::getUserDetail() {
	setCallUrl("https://dnsapi.cn/User.Detail");
	callApi();
}

void dnspod::callApi() {
	callApi("");
}

void dnspod::callApi(char *params) {
	char postData[DNSPOD_BUFFERSIZE];
	sprintf(postData, "login_email=%s&login_password=%s&format=%s&%s", getLoginEmail(), getLoginPassword(), getFormat(), params);

	CURL *curl;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, getCallUrl());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dnspod::curlWrite);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

}

size_t dnspod::curlWrite(void *ptr, size_t size, size_t nmemb, void *userp) {
	dnspod *dp = (dnspod *)userp;
	char *content = (char *)ptr;
	int return_size = size * nmemb;

	Json::Reader reader;
	reader.parse(content, dp->response);

	return return_size;
}

