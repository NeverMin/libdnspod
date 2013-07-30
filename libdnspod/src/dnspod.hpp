#ifndef DNSPOD_H_
#define DNSPOD_H_
#define DNSPOD_BUFFERSIZE 4 * 1024

#include <map>
#include <string>
#include <curl/curl.h>
#include <json/json.h>


class dnspod {
public:
	/*
	 * All functions' result will in response
	 *
	 */
	Json::Value response;


	dnspod(char* login_email, char* login_password);
	virtual ~dnspod();

	void getApiVersion();

	/*
	 * The following functions are for user account
	 * https://www.dnspod.cn/docs/accounts.html
	 *
	 */
	void getUserDetail();
	void modifyUser(std::map<char*, char*>userinfo);
	void modifyUserpassword(char* new_password);
	void modifyUseremail(char* new_email);
	void getTelephoneverifyCode(char* telephone);
	void getUserLog();








	/*
	 * setters and getters
	 */
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

	/*
	 * callApi() uses curl to contact with DNSPOD
	 * the result will be a json string and be parsed in curlWrite() function
	 * the parsed result will in this->response
	 *
	 */
	void callApi();
	void callApi(std::map<char*, char*> params);
	void callApi(char *postString);
	static size_t curlWrite(void* ptr, size_t size, size_t nmemb, void* usrptr);

private:
	/*
	 * login_email and login_password are necessary params to DNSPOD api
	 */
	char *login_email, *login_password;

	/*
	 * format is "json"; "xml" is not supported now
	 * lang can be "en" or "cn"
	 * error_on_empty and user_id are not necessary, and not used
	 */
	char *format, *lang, *error_on_empty, *user_id;
	char *call_url;

	/*
	 * To build a post data string
	 */
	char *buildPostString();
	char *buildPostString(std::map<char*, char*> params);


};

#endif /* DNSPOD_H_ */



















