#include "dnspod.hpp"

dnspod::dnspod(char* login_email, char* login_password) {
	setLoginEmail(login_email);
	setLoginPassword(login_password);
	setFormat("json");
	setLang("cn");
}

dnspod::~dnspod() {
}

void dnspod::getApiVersion() {
	setCallUrl("https://dnsapi.cn/Info.Version");
	callApi();
}

void dnspod::getUserDetail() {
	setCallUrl("https://dnsapi.cn/User.Detail");
	callApi();
}

void dnspod::modifyUser(std::map<char*, char*>userinfo) {
	setCallUrl("https://dnsapi.cn/User.Modify");
	callApi(userinfo);
}

void dnspod::modifyUserpassword(char* new_password) {
	setCallUrl("https://dnsapi.cn/Userpasswd.Modify");

	std::map<char*, char*> params;
	params.insert(std::pair<char*, char*>("old_password", getLoginPassword()));
	params.insert(std::pair<char*, char*>("new_password", new_password));

	callApi(params);
}

void dnspod::modifyUseremail(char* new_email) {
	setCallUrl("https://dnsapi.cn/Useremail.Modify");

	std::map<char*, char*> params;
	params.insert(std::pair<char*, char*>("old_email", getLoginEmail()));
	params.insert(std::pair<char*, char*>("new_email", new_email));
	params.insert(std::pair<char*, char*>("password", getLoginPassword()));

	callApi(params);
}

void dnspod::getTelephoneverifyCode(char* telephone) {
	setCallUrl("https://dnsapi.cn/Telephoneverify.Code");

	std::map<char*, char*> params;
	params.insert(std::pair<char*, char*>("telephone", telephone));

	callApi(params);
}

void dnspod::getUserLog() {
	setCallUrl("https://dnsapi.cn/User.Log");
	callApi();
}












char* dnspod::buildPostString() {
	std::map<char*, char*> emptyMap;
	return buildPostString(emptyMap);
}

char* dnspod::buildPostString(std::map<char*, char*> params) {
	char *postString = new char[DNSPOD_BUFFERSIZE];
	sprintf(postString, "");

	params.insert(std::pair<char*, char*>("login_email", getLoginEmail()));
	params.insert(std::pair<char*, char*>("login_password", getLoginPassword()));
	params.insert(std::pair<char*, char*>("format", getFormat()));
	params.insert(std::pair<char*, char*>("lang", getLang()));

	std::map<char*, char*>::iterator it;
	for (it = params.begin(); it != params.end(); it++) {
		sprintf(postString, "%s&%s=%s", postString, it->first, it->second);
	}

	return postString;
}

void dnspod::callApi() {
	callApi(buildPostString());
}

void dnspod::callApi(std::map<char*, char*> params) {
	callApi(buildPostString(params));
}

void dnspod::callApi(char*postString) {
	CURL *curl;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, getCallUrl());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postString);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dnspod::curlWrite);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	delete [] postString;
}

size_t dnspod::curlWrite(void* ptr, size_t size, size_t nmemb, void* userp) {
	dnspod *dp = (dnspod *)userp;
	char *content = (char*)ptr;
	int return_size = size * nmemb;

	Json::Reader reader;
	reader.parse(content, dp->response);

	return return_size;
}
