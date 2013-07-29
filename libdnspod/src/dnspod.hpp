#ifndef DNSPOD_H_
#define DNSPOD_H_
#define DNSPOD_BUFFERSIZE 4 * 1024

#include <string>
#include <curl/curl.h>
#include <json/json.h>

class dnspod {
public:
	dnspod(char* login_email, char* login_password);
	virtual ~dnspod();

	void getApiVersion();
	void getUserDetail();

	char* getLoginEmail() const {
		return login_email;
	}

	void setLoginEmail(char* loginEmail) {
		login_email = loginEmail;
	}

	char* getCallUrl() const {
		return call_url;
	}

	void setCallUrl(char* callUrl) {
		call_url = callUrl;
	}

	char* getErrorOnEmpty() const {
		return error_on_empty;
	}

	void setErrorOnEmpty(char* errorOnEmpty) {
		error_on_empty = errorOnEmpty;
	}

	char* getFormat() const {
		return format;
	}

	void setFormat(char* format) {
		this->format = format;
	}

	char* getLang() const {
		return lang;
	}

	void setLang(char* lang) {
		this->lang = lang;
	}

	char* getLoginPassword() const {
		return login_password;
	}

	void setLoginPassword(char* loginPassword) {
		login_password = loginPassword;
	}

	char* getUserId() const {
		return user_id;
	}

	void setUserId(char* userId) {
		user_id = userId;
	}

	void callApi();
	void callApi(char *params);
	static size_t curlWrite(void* ptr, size_t size, size_t nmemb, void *usrptr);
	Json::Value response;

private:
	char *login_email, *login_password, *format, *lang, *error_on_empty, *user_id;
	char *call_url;


};

#endif /* DNSPOD_H_ */
