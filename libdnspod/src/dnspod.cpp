#include "dnspod.hpp"

dnspod::dnspod(const char* loginEmail, const char* loginPassword) {
	login_email = new char[DNSPOD_STRINGSIZE];
	login_password = new char[DNSPOD_STRINGSIZE];
	format = new char[DNSPOD_STRINGSIZE];
	lang = new char[DNSPOD_STRINGSIZE];
	error_on_empty = new char[DNSPOD_STRINGSIZE];
	user_id = new char[DNSPOD_STRINGSIZE];
	call_url = new char[DNSPOD_STRINGSIZE];
	domain = new char[DNSPOD_STRINGSIZE];
	domain_id_type = new char[DNSPOD_STRINGSIZE];

	setLoginEmail(loginEmail);
	setLoginPassword(loginPassword);
	setFormat("json");
	setLang("cn");
}

dnspod::~dnspod() {
	delete login_email;
	delete login_password;
	delete format;
	delete lang;
	delete error_on_empty;
	delete user_id;
	delete call_url;
	delete domain;
	delete domain_id_type;
}

void dnspod::getApiVersion() {
	setCallUrl("https://dnsapi.cn/Info.Version");
	callApi();
}

void dnspod::getUserDetail() {
	setCallUrl("https://dnsapi.cn/User.Detail");
	callApi();
}

void dnspod::modifyUser(std::map<const char*, const char*>userinfo) {
	setCallUrl("https://dnsapi.cn/User.Modify");
	callApi(userinfo);
}

void dnspod::modifyUserpassword(const char* new_password) {
	setCallUrl("https://dnsapi.cn/Userpasswd.Modify");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>("old_password", getLoginPassword()));
	params.insert(std::pair<const char*, const char*>("new_password", new_password));

	callApi(params);
}

void dnspod::modifyUseremail(const char* new_email) {
	setCallUrl("https://dnsapi.cn/Useremail.Modify");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>("old_email", getLoginEmail()));
	params.insert(std::pair<const char*, const char*>("new_email", new_email));
	params.insert(std::pair<const char*, const char*>("password", getLoginPassword()));

	callApi(params);
}

void dnspod::getTelephoneverifyCode(const char* telephone) {
	setCallUrl("https://dnsapi.cn/Telephoneverify.Code");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>("telephone", telephone));

	callApi(params);
}

void dnspod::getUserLog() {
	setCallUrl("https://dnsapi.cn/User.Log");
	callApi();
}

void dnspod::createDomain(int group_id, const char* is_mark) {
	setCallUrl("https://dnsapi.cn/Domain.Create");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>("domain", getDomain()));
	params.insert(std::pair<const char*, const char*>("is_mark", is_mark));
	if (group_id != -1) {
		char groupIdBuffer[DNSPOD_STRINGSIZE];
		sprintf(groupIdBuffer, "%d", group_id);
		params.insert(std::pair<const char*, const char*>("group_id", groupIdBuffer));
	}

	callApi(params);
}

void dnspod::getDomainList(const char* type, int offset, int length, int group_id) {
	setCallUrl("https://dnsapi.cn/Domain.List");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>("type", type));

	char offsetBuffer[DNSPOD_STRINGSIZE];
	sprintf(offsetBuffer, "%d", offset);
	params.insert(std::pair<const char*, const char*>("offset", offsetBuffer));
	if (length != -1) {
		char lengthBuffer[DNSPOD_STRINGSIZE];
		sprintf(lengthBuffer, "%d", length);
		params.insert(std::pair<const char*, const char*>("length", lengthBuffer));
	}
	if (group_id != -1) {
		char groupIdBuffer[DNSPOD_STRINGSIZE];
		sprintf(groupIdBuffer, "%d", group_id);
		params.insert(std::pair<const char*, const char*>("group_id", groupIdBuffer));
	}

	callApi(params);
}

void dnspod::setDomain(int domainId) {
	sprintf(domain_id_type, "domain_id");
	sprintf(domain, "%d", domainId);
}
void dnspod::setDomain(const char* domain) {
	sprintf(domain_id_type, "domain");
	sprintf(this->domain, "%s", domain);
}

void dnspod::removeDomain() {
	setCallUrl("https://dnsapi.cn/Domain.Remove");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::setDomainStatus(const char* status) {
	setCallUrl("https://dnsapi.cn/Domain.Status");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("status", status));

	callApi(params);
}

void dnspod::getDomainInfo() {
	setCallUrl("https://dnsapi.cn/Domain.Info");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::getDomainLog() {
	setCallUrl("https://dnsapi.cn/Domain.Log");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::setDomainSearchenginepush(const char* status) {
	setCallUrl("https://dnsapi.cn/Domain.Searchenginepush");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("status", status));

	callApi(params);
}

void dnspod::createDomainshare(const char* email, const char* mode, const char* sub_domain) {
	setCallUrl("https://dnsapi.cn/Domainshare.Create");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("email", email));
	params.insert(std::pair<const char*, const char*>("mode", mode));
	if (sub_domain != NULL)
		params.insert(std::pair<const char*, const char*>("sub_domain", sub_domain));

	callApi(params);
}

void dnspod::getDomainshareList() {
	setCallUrl("https://dnsapi.cn/Domainshare.List");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::modifyDomainshare(const char* email, const char* mode, const char* old_sub_domain, const char* new_sub_domain) {
	setCallUrl("https://dnsapi.cn/Domainshare.Modify");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("email", email));
	params.insert(std::pair<const char*, const char*>("mode", mode));
	if (old_sub_domain != NULL)
		params.insert(std::pair<const char*, const char*>("old_sub_domain", old_sub_domain));
	if (new_sub_domain != NULL)
		params.insert(std::pair<const char*, const char*>("new_sub_domain", new_sub_domain));

	callApi(params);
}

void dnspod::removeDomainshare(const char* email) {
	setCallUrl("https://dnsapi.cn/Domainshare.Remove");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("email", email));

	callApi(params);
}

void dnspod::transferDomain(const char* email) {
	setCallUrl("https://dnsapi.cn/Domain.Transfer");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("email", email));

	callApi(params);
}

void dnspod::lockDomain(int days) {
	setCallUrl("https://dnsapi.cn/Domain.Lock");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	char daysBuffer[DNSPOD_STRINGSIZE];
	sprintf(daysBuffer, "%d", days);
	params.insert(std::pair<const char*, const char*>("days", daysBuffer));

	callApi(params);
}

void dnspod::getDomainLockstatus() {
	setCallUrl("https://dnsapi.cn/Domain.Lockstatus");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::unlockDomain(const char* lock_code) {
	setCallUrl("https://dnsapi.cn/Domain.Unlock");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("lock_code", lock_code));

	callApi(params);
}

void dnspod::getDomainaliasList() {
	setCallUrl("https://dnsapi.cn/Domainalias.List");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::createDomainalias(const char* domain) {
	setCallUrl("https://dnsapi.cn/Domainalias.Create");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("domain", domain));

	callApi(params);
}

void dnspod::removeDomainalias(int alias_id) {
	setCallUrl("https://dnsapi.cn/Domainalias.Remove");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	char aliasIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(aliasIdBuffer, "%d", alias_id);
	params.insert(std::pair<const char*, const char*>("alias_id", aliasIdBuffer));

	callApi(params);
}

void dnspod::getDomaingroupList() {
	setCallUrl("https://dnsapi.cn/Domaingroup.List");

	callApi();
}

void dnspod::createDomaingroup(const char* group_name) {
	setCallUrl("https://dnsapi.cn/Domaingroup.Create");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>("group_name", group_name));

	callApi(params);
}

void dnspod::modifyDomaingroup(int group_id, const char* group_name) {
	setCallUrl("https://dnsapi.cn/Domaingroup.Modify");

	std::map<const char*, const char*> params;
	char groupIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(groupIdBuffer, "%d", group_id);
	params.insert(std::pair<const char*, const char*>("group_id", groupIdBuffer));
	params.insert(std::pair<const char*, const char*>("group_name", group_name));

	callApi(params);
}

void dnspod::removeDomaingroup(int group_id) {
	setCallUrl("https://dnsapi.cn/Domaingroup.Remove");

	std::map<const char*, const char*> params;
	char groupIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(groupIdBuffer, "%d", group_id);
	params.insert(std::pair<const char*, const char*>("group_id", groupIdBuffer));

	callApi(params);
}

void dnspod::setDomainGroup(int group_id) {
	setCallUrl("https://dnsapi.cn/Domain.Changegroup");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	char groupIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(groupIdBuffer, "%d", group_id);
	params.insert(std::pair<const char*, const char*>("group_id", groupIdBuffer));

	callApi(params);
}

void dnspod::setDomainIsmark(const char* is_mark) {
	setCallUrl("https://dnsapi.cn/Domain.Ismark");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("is_mark", is_mark));

	callApi(params);
}

void dnspod::setDomainRemark(const char* remark) {
	setCallUrl("https://dnsapi.cn/Domain.Remark");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("remark", remark));

	callApi(params);
}

void dnspod::getDomainPurview() {
	setCallUrl("https://dnsapi.cn/Domain.Purview");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::getDomainAcquire() {
	setCallUrl("https://dnsapi.cn/Domain.Acquire");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::getDomainAcquiresend(const char* email) {
	setCallUrl("https://dnsapi.cn/Domain.Acquiresend");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("email", email));

	callApi(params);
}

void dnspod::getDomainAcquirevalidate(const char* code) {
	setCallUrl("https://dnsapi.cn/Domain.Acquirevalidate");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("code", code));

	callApi(params);
}

void dnspod::getRecordType() {
	setCallUrl("https://dnsapi.cn/Record.Type");
	callApi();
}

void dnspod::getRecordLine() {
	setCallUrl("https://dnsapi.cn/Record.Line");
	callApi();
}

void dnspod::createRecord(std::map<const char*, const char*> params) {
	setCallUrl("https://dnsapi.cn/Record.Create");
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	callApi(params);
}

void dnspod::getRecordList(int offset, int length, const char* sub_domain) {
	setCallUrl("https://dnsapi.cn/Record.List");

	std::map<const char*, const char*> params;

	char offsetBuffer[DNSPOD_STRINGSIZE];
	sprintf(offsetBuffer, "%d", offset);
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("offset", offsetBuffer));
	if (sub_domain != NULL)
		params.insert(std::pair<const char*, const char*>("sub_domain", sub_domain));
	if (length != -1) {
		char lengthBuffer[DNSPOD_STRINGSIZE];
		sprintf(lengthBuffer, "%d", length);
		params.insert(std::pair<const char*, const char*>("length", lengthBuffer));
	}

	callApi(params);
}

void dnspod::modifyRecord(int record_id, std::map<const char*, const char*> params) {
	setCallUrl("https://dnsapi.cn/Record.Modify");

	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	char recordIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(recordIdBuffer, "%d", record_id);
	params.insert(std::pair<const char*, const char*>("record_id", recordIdBuffer));

	callApi(params);
}

void dnspod::removeRecord(int record_id) {
	setCallUrl("https://dnsapi.cn/Record.Remove");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	char recordIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(recordIdBuffer, "%d", record_id);
	params.insert(std::pair<const char*, const char*>("record_id", recordIdBuffer));

	callApi(params);
}

void dnspod::updateDdnsRecord(int record_id, const char* sub_domain,
		const char* record_line, const char* value) {
	setCallUrl("https://dnsapi.cn/Record.Ddns");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("sub_domain", sub_domain));
	params.insert(std::pair<const char*, const char*>("record_line", record_line));
	params.insert(std::pair<const char*, const char*>("value", value));

	char recordIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(recordIdBuffer, "%d", record_id);
	params.insert(std::pair<const char*, const char*>("record_id", recordIdBuffer));

	callApi(params);
}

void dnspod::setRecordRemark(int record_id, const char* remark) {
	setCallUrl("https://dnsapi.cn/Record.Remark");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("remark", remark));

	char recordIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(recordIdBuffer, "%d", record_id);
	params.insert(std::pair<const char*, const char*>("record_id", recordIdBuffer));

	callApi(params);
}

void dnspod::getRecordInfo(int record_id) {
	setCallUrl("https://dnsapi.cn/Record.Info");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	char recordIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(recordIdBuffer, "%d", record_id);
	params.insert(std::pair<const char*, const char*>("record_id", recordIdBuffer));

	callApi(params);
}

void dnspod::getRecordStatus(int record_id, const char* status) {
	setCallUrl("https://dnsapi.cn/Record.Status");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("status", status));

	char recordIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(recordIdBuffer, "%d", record_id);
	params.insert(std::pair<const char*, const char*>("record_id", recordIdBuffer));

	callApi(params);
}

void dnspod::getMonitorListsubdomain() {
	setCallUrl("https://dnsapi.cn/Monitor.Listsubdomain");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));

	callApi(params);
}

void dnspod::getMonitorListsubvalue(const char* subdomain) {
	setCallUrl("https://dnsapi.cn/Monitor.Listsubvalue");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	params.insert(std::pair<const char*, const char*>("subdomain", subdomain));

	callApi(params);
}

void dnspod::getMonitorList() {
	setCallUrl("https://dnsapi.cn/Monitor.List");
	callApi();
}

void dnspod::createMonitor(std::map<const char*, const char*> params) {
	setCallUrl("https://dnsapi.cn/Monitor.Create");

	params.insert(std::pair<const char*, const char*>(getDomainIdType(), getDomain()));
	callApi(params);
}

void dnspod::modifyMonitor(std::map<const char*, const char*> params) {
	setCallUrl("https://dnsapi.cn/Monitor.Modify");
	callApi(params);
}

void dnspod::removeMonitor(int monitor_id) {
	setCallUrl("https://dnsapi.cn/Monitor.Remove");

	std::map<const char*, const char*> params;

	char monitorIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(monitorIdBuffer, "%d", monitor_id);
	params.insert(std::pair<const char*, const char*>("monitor_id", monitorIdBuffer));

	callApi(params);
}

void dnspod::getMonitorInfo(int monitor_id) {
	setCallUrl("https://dnsapi.cn/Monitor.Info");

	std::map<const char*, const char*> params;

	char monitorIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(monitorIdBuffer, "%d", monitor_id);
	params.insert(std::pair<const char*, const char*>("monitor_id", monitorIdBuffer));

	callApi(params);
}

void dnspod::setMonitorStatus(int monitor_id, const char* status) {
	setCallUrl("https://dnsapi.cn/Monitor.Setstatus");

	std::map<const char*, const char*> params;
	params.insert(std::pair<const char*, const char*>("status", status));

	char monitorIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(monitorIdBuffer, "%d", monitor_id);
	params.insert(std::pair<const char*, const char*>("monitor_id", monitorIdBuffer));

	callApi(params);
}

void dnspod::getMonitorHistory(int monitor_id, int hours) {
	setCallUrl("https://dnsapi.cn/Monitor.Gethistory");

	std::map<const char*, const char*> params;

	char monitorIdBuffer[DNSPOD_STRINGSIZE];
	sprintf(monitorIdBuffer, "%d", monitor_id);
	params.insert(std::pair<const char*, const char*>("monitor_id", monitorIdBuffer));

	if (hours != -1) {
		char hoursBuffer[DNSPOD_STRINGSIZE];
		sprintf(hoursBuffer, "%d", hours);
		params.insert(std::pair<const char*, const char*>("hours", hoursBuffer));
	}

	callApi(params);
}

void dnspod::getMonitorUserdesc() {
	setCallUrl("https://dnsapi.cn/Monitor.Userdesc");
	callApi();
}

void dnspod::getMonitorDowns(int offset, int length) {
	setCallUrl("https://dnsapi.cn/Record.List");

	std::map<const char*, const char*> params;

	char offsetBuffer[DNSPOD_STRINGSIZE];
	sprintf(offsetBuffer, "%d", offset);
	params.insert(std::pair<const char*, const char*>("offset", offsetBuffer));
	if (length != -1) {
		char lengthBuffer[DNSPOD_STRINGSIZE];
		sprintf(lengthBuffer, "%d", length);
		params.insert(std::pair<const char*, const char*>("length", lengthBuffer));
	}

	callApi(params);
}





char* dnspod::buildPostString() {
	std::map<const char*, const char*> emptyMap;
	return buildPostString(emptyMap);
}

char* dnspod::buildPostString(std::map<const char*, const char*> params) {
	char *postString = new char[DNSPOD_BUFFERSIZE];
	sprintf(postString, "1=1");

	params.insert(std::pair<const char*, const char*>("login_email", getLoginEmail()));
	params.insert(std::pair<const char*, const char*>("login_password", getLoginPassword()));
	params.insert(std::pair<const char*, const char*>("format", getFormat()));
	params.insert(std::pair<const char*, const char*>("lang", getLang()));

	std::map<const char*, const char*>::iterator it;
	for (it = params.begin(); it != params.end(); it++) {
		sprintf(postString, "%s&%s=%s", postString, it->first, it->second);
	}

	return postString;
}

void dnspod::callApi() {
	callApi(buildPostString());
}

void dnspod::callApi(std::map<const char*, const char*> params) {
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
