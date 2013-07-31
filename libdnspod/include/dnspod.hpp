#ifndef DNSPOD_H_
#define DNSPOD_H_
#define DNSPOD_STRINGSIZE 64
#define DNSPOD_BUFFERSIZE 4 * 1024

#include <map>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <json/json.h>


class dnspod {
public:
	/*
	 * All functions' result will in response
	 *
	 */
	Json::Value response;


	dnspod(const char* loginEmail, const char* loginPassword);
	virtual ~dnspod();

	/*
	 *	Function:		getApiVersion()
	 *	Description:	Get the Api version
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/info.html#id4
	 *	Url:			https://dnsapi.cn/Info.Version
	 *
	 */
	void getApiVersion();

	/*
	 *	Function:		getUserDetail()
	 *	Description:	Get the user detail
	 *	Params:			None(depends on login_email and login_password)
	 *	Refer:			https://www.dnspod.cn/docs/accounts.html#id2
	 *	Url:			https://dnsapi.cn/User.Detail
	 *
	 */
	void getUserDetail();

	/*
	 *	Function:		modifyUser()
	 *	Description:	Modify the user's detail
	 *	Params:			userinfo	std::map<const char*, const char*>
	 *	Refer:			https://www.dnspod.cn/docs/accounts.html#id3
	 *	Url:			https://dnsapi.cn/User.Modify
	 *	Example:
	 *					std::map<const char*, const char*> info;
	 *					info.insert(std::pair<const char*, const char*>("real_name", "Foo"));
	 *					dp->modifyUser(info);
	 */
	void modifyUser(std::map<const char*, const char*>userinfo);

	/*
	 *	Function:		modifyUserpassword()
	 *	Description:	Modify the user's password
	 *	Params:			new_password	const char*
	 *	Refer:			https://www.dnspod.cn/docs/accounts.html#id4
	 *	Url:			https://dnsapi.cn/Userpasswd.Modify
	 *
	 */
	void modifyUserpassword(const char* new_password);

	/*
	 *	Function:		modifyUseremail()
	 *	Description:	Modify the user's email address
	 *	Params:			new_email	const char*
	 *	Refer:			https://www.dnspod.cn/docs/accounts.html#id5
	 *	Url:			https://dnsapi.cn/Useremail.Modify
	 *
	 */
	void modifyUseremail(const char* new_email);

	/*
	 *	Function:		getTelephoneverifyCode()
	 *	Description:	Get telephone verify code
	 *	Params:			telephone	const char*
	 *	Refer:			https://www.dnspod.cn/docs/accounts.html#id6
	 *	Url:			https://dnsapi.cn/Telephoneverify.Code
	 *
	 */
	void getTelephoneverifyCode(const char* telephone);

	/*
	 *	Function:		getUserLog()
	 *	Description:	Get user's log
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/accounts.html#id7
	 *	Url:			https://dnsapi.cn/User.Log
	 *
	 */
	void getUserLog();

	/*
	 *  !IMPORTANT
	 *
	 *	Function:		setDomain()
	 *	Description:	Set domain name or id.
	 *					This function is NECESSARY to be set
	 *					before calling the Api which needs
	 *					domain or domain_id as a param
	 *	Params:			domain_id	int
	 *					domain		const char*
	 *	Refer:			None
	 *	Url:			None
	 *
	 */
	void setDomain(int domain_id);
	void setDomain(const char* domain);

	/*
	 *	Function:		createDomain()
	 *	Description:	Create a domain
	 *					You should call setDomain() first
	 *	Params:			group_id	int				-1 for not use
	 *					is_mark		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id2
	 *	Url:			https://dnsapi.cn/Domain.Create
	 *
	 */
	void createDomain(int group_id = -1, const char* is_mark = "no");

	/*
	 *	Function:		getDomainList()
	 *	Description:	Get user's domain list
	 *	Params:			type		const char*
	 *					offset		int
	 *					length		int				-1 for not use
	 *					group_id	int				-1 for not use
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id3
	 *	Url:			https://dnsapi.cn/Domain.List
	 *
	 */
	void getDomainList(const char* type = "all", int offset = 0, int length = -1, int group_id = -1);

	/*
	 *	Function:		removeDomain()
	 *	Description:	Remove a domain
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id4
	 *	Url:			https://dnsapi.cn/Domain.Remove
	 *
	 */
	void removeDomain();

	/*
	 *	Function:		setDomainStatus()
	 *	Description:	Set domain's status
	 *					You should call setDomain() first
	 *	Params:			status		const char*		"enable" or "disable"
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id5
	 *	Url:			https://dnsapi.cn/Domain.Status
	 *
	 */
	void setDomainStatus(const char* status);

	/*
	 *	Function:		getDomainInfo()
	 *	Description:	Get domain's info
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id6
	 *	Url:			https://dnsapi.cn/Domain.Info
	 *
	 */
	void getDomainInfo();

	/*
	 *	Function:		getDomainLog()
	 *	Description:	Get domain's log
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id7
	 *	Url:			https://dnsapi.cn/Domain.Log
	 *
	 */
	void getDomainLog();

	/*
	 *	Function:		setDomainSearchenginepush()
	 *	Description:	Set domain search engine push
	 *					You should call setDomain() first
	 *	Params:			status		const char*		"yes" or "no"
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id8
	 *	Url:			https://dnsapi.cn/Domain.Searchenginepush
	 *
	 */
	void setDomainSearchenginepush(const char* status);

	/*
	 *	Function:		createDomainshare()
	 *	Description:	Create domain share
	 *					You should call setDomain() first
	 *	Params:			email		const char*
	 *					mode		const char*		"r" or "rw"
	 *					sub_dmain	const char*		optional
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id9
	 *	Url:			https://dnsapi.cn/Domainshare.Create
	 *
	 */
	void createDomainshare(const char* email, const char* mode = "r", const char* sub_domain = NULL);

	/*
	 *	Function:		getDomainshareList()
	 *	Description:	Get user's domain share list
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id10
	 *	Url:			https://dnsapi.cn/Domainshare.List
	 *
	 */
	void getDomainshareList();

	/*
	 *	Function:		modifyDomainshare()
	 *	Description:	Modify the domain's share
	 *					You should call setDomain() first
	 *	Params:			email			const char*
	 *					mode			const char*		"r" or "rw"
	 *					old_sub_domain	const char*		optional
	 *					new_sub_domain	const char*		optional
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id11
	 *	Url:			https://dnsapi.cn/Domainshare.Modify
	 *
	 */
	void modifyDomainshare(const char* email, const char* mode, const char* old_sub_domain = NULL, const char* new_sub_domain = NULL);

	/*
	 *	Function:		removeDomainshare()
	 *	Description:	Remove domain's share
	 *					You should call setDomain() first
	 *	Params: 		email		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id12
	 *	Url:			https://dnsapi.cn/Domainshare.Remove
	 *
	 */
	void removeDomainshare(const char* email);

	/*
	 *	Function:		transferDomain()
	 *	Description:	Transfer the domain to other
	 *					You should call setDomain() first
	 *	Params:			email		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id13
	 *	Url:			https://dnsapi.cn/Domain.Transfer
	 *
	 */
	void transferDomain(const char* email);

	/*
	 *	Function:		lockDomain()
	 *	Description:	Lock the domain
	 *					You should call setDomain() first
	 *	Params:			days		int
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id14
	 *	Url:			https://dnsapi.cn/Domain.Lock
	 *
	 */
	void lockDomain(int days);

	/*
	 *	Function:		getDomainLockstatus()
	 *	Description:	Get domain's lock status
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id15
	 *	Url:			https://dnsapi.cn/Domain.Lockstatus
	 *
	 */
	void getDomainLockstatus();

	/*
	 *	Function:		unlockDomain()
	 *	Description:	Unlock the domain
	 *					You should call setDomain() first
	 *	Params:			lock_code		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id16
	 *	Url:			https://dnsapi.cn/Domain.Unlock
	 *
	 */
	void unlockDomain(const char* lock_code);

	/*
	 *	Function:		getDomainaliasList()
	 *	Description:	Get domain's alias list
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id17
	 *	Url:			https://dnsapi.cn/Domainalias.List
	 *
	 */
	void getDomainaliasList();

	/*
	 *	Function:		createDomainalias()
	 *	Description:	Create domain alias
	 *					You should call setDomain() first
	 *	Params:			domain		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id18
	 *	Url:			https://dnsapi.cn/Domainalias.Create
	 *
	 */
	void createDomainalias(const char* domain);

	/*
	 *	Function:		removeDomainalias()
	 *	Description:	Remove domain's alias
	 *					You should call setDomain() first
	 *	Params:			alias_id		int
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id19
	 *	Url:			https://dnsapi.cn/Domainalias.Remove
	 *
	 */
	void removeDomainalias(int alias_id);

	/*
	 *	Function:		getDomaingroupList()
	 *	Description:	Get domain's group list
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id20
	 *	Url:			https://dnsapi.cn/Domaingroup.List
	 *
	 */
	void getDomaingroupList();

	/*
	 *	Function:		createDomaingroup()
	 *	Description:	Create a domain group
	 *	Params:			group_name		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id21
	 *	Url:			https://dnsapi.cn/Domaingroup.Create
	 *
	 */
	void createDomaingroup(const char* group_name);

	/*
	 *	Function:		modifyDomaingroup()
	 *	Description:	Modify the domain group
	 *	Params:			group_id		int
	 *					group_name		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id22
	 *	Url:			https://dnsapi.cn/Domaingroup.Modify
	 *
	 */
	void modifyDomaingroup(int group_id, const char* group_name);

	/*
	 *	Function:		removeDomaingroup()
	 *	Description:	Remove a domain group
	 *	Params:			group_id		int
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id23
	 *	Url:			https://dnsapi.cn/Domaingroup.Remove
	 *
	 */
	void removeDomaingroup(int group_id);

	/*
	 *	Function:		setDomainGroup()
	 *	Description:	Set a domain to a group
	 *					You should call setDomain() first
	 *	Params:			group_id		int
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id24
	 *	Url:			https://dnsapi.cn/Domain.Changegroup
	 *
	 */
	void setDomainGroup(int group_id);

	/*
	 *	Function:		setDomainIsmark()
	 *	Description:	Set a domain to be marked status or not marked
	 *					You should call setDomain() first
	 *	Params:			is_mark		const char*		"yes" or "no"
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id25
	 *	Url:			https://dnsapi.cn/Domain.Ismark
	 *
	 */
	void setDomainIsmark(const char* is_mark);

	/*
	 *	Function:		setDomainRemark()
	 *	Description:	Set domain's remark
	 *					You should call setDomain() first
	 *	Params:			remark		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id26
	 *	Url:			https://dnsapi.cn/Domain.Remark
	 *
	 */
	void setDomainRemark(const char* remark);

	/*
	 *	Function:		getDomainPurview()
	 *	Description:	Get domain's purview
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id27
	 *	Url:			https://dnsapi.cn/Domain.Purview
	 *
	 */
	void getDomainPurview();

	/*
	 *	Function:		getDomainAcquire()
	 *	Description:	Get domain's acquire
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id28
	 *	Url:			https://dnsapi.cn/Domain.Acquire
	 *
	 */
	void getDomainAcquire();

	/*
	 *	Function:		getDomainAcquiresend()
	 *	Description:	Get domain's acquire send
	 *	Params:			email		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id29
	 *	Url:			https://dnsapi.cn/Domain.Acquiresend
	 *
	 */
	void getDomainAcquiresend(const char* email);

	/*
	 *	Function:		getDomainAcquirevalidate()
	 *	Description:	Get domain's acquire validate
	 *					You should call setDomain() first
	 *	Params:			code 		const char*
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id30
	 *	Url:			https://dnsapi.cn/Domain.Acquirevalidate
	 *
	 */
	void getDomainAcquirevalidate(const char* code);

	/*
	 *	Function:		getRecordType()
	 *	Description:	Get allowed record's type
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id31
	 *	Url:			https://dnsapi.cn/Record.Type
	 *
	 */
	void getRecordType();

	/*
	 *	Function:		getRecordLine()
	 *	Description:	Get allowed record's line
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/domains.html#id32
	 *	Url:			https://dnsapi.cn/Record.Line
	 *
	 */
	void getRecordLine();

	/*
	 *	Function:		createRecord()
	 *	Description:	Create a ns record
	 *					You should call setDomain() first
	 *	Params:			sub_domain		const char*
	 *					record_type		const char*
	 *					record_line		const char*
	 *					value			const char*
	 *					ttl				int
	 *					mx				int				-1 for not use
	 *	Refer:			https://www.dnspod.cn/docs/records.html#id2
	 *	Url:			https://dnsapi.cn/Record.Create
	 *
	 */
	void createRecord(std::map<const char*, const char*> params);

	/*
	 *	Function:		getRecordList()
	 *	Description:	Get domain's records list
	 *					You should call setDomain() first
	 *	Params:			offset			int
	 *					length			int				-1 for not use
	 *					sub_domain		const char*		NULL for not use
	 *	Refer:			https://www.dnspod.cn/docs/records.html#id3
	 *	Url:			https://dnsapi.cn/Record.List
	 *
	 */
	void getRecordList(int offset = 0, int length = -1, const char* sub_domain = NULL);

	/*
	 *	Function:		modifyRecord()
	 *	Description:	Modify record
	 *					You should call setDomain() first
	 *	Params:			record_id		int
	 *					params			std::map<const char*, const char*>		build this map accord to Refer description
	 *	Refer:			https://www.dnspod.cn/docs/records.html#id4
	 *	Url:			https://dnsapi.cn/Record.Modify
	 *
	 */
	void modifyRecord(int record_id, std::map<const char*, const char*> params);

	/*
	 *	Function:		removeRecord()
	 *	Description:	Remove a record
	 *					You should call setDomain() first
	 *	Params:			record_id		int
	 *	Refer:			https://www.dnspod.cn/docs/records.html#id5
	 *	Url:			https://dnsapi.cn/Record.Remove
	 *
	 */
	void removeRecord(int record_id);

	/*
	 *	Function:		updateDdnsRecord()
	 *	Description:	Update Ddns record
	 *					You should call setDomain() first
	 *	Params:			record_id		int
	 *					sub_domain		const char*
	 *					record_line		const char*
	 *					value			const char*
	 *	Refer:			https://www.dnspod.cn/docs/records.html#dns
	 *	Url:			https://dnsapi.cn/Record.Ddns
	 *
	 */
	void updateDdnsRecord(int record_id, const char* sub_domain, const char* record_line, const char* value);

	/*
	 *	Function:		setRecordRemark()
	 *	Description:	Set record's remark
	 *					You should call setDomain() first
	 *	Params:			record_id		int
	 *					remark			const char*
	 *	Refer:			https://www.dnspod.cn/docs/records.html#id6
	 *	Url:			https://dnsapi.cn/Record.Remark
	 *
	 */
	void setRecordRemark(int record_id, const char* remark);

	/*
	 *	Function:		getRecordInfo()
	 *	Description:	Get record's info
	 *					You should call setDomain() first
	 *	Params:			record_int		int
	 *	Refer:			https://www.dnspod.cn/docs/records.html#id7
	 *	Url:			https://dnsapi.cn/Record.Info
	 *
	 */
	void getRecordInfo(int record_id);

	/*
	 *	Function:		getRecordStatus()
	 *	Description:	Get record's status
	 *					You should call setDomain() first
	 *	Params:			record_id		int
	 *					status			const char*		"enable" or "disable"
	 *	Refer:			https://www.dnspod.cn/docs/records.html#id8
	 *	Url:			https://dnsapi.cn/Record.Status
	 *
	 */
	void getRecordStatus(int record_id, const char* status);

	/*
	 *	Function:		getMonitorListsubdomain()
	 *	Description:	Get the list of the subdomains which contain A record
	 *					You should call setDomain() first
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#a
	 *	Url:			https://dnsapi.cn/Monitor.Listsubdomain
	 *
	 */
	void getMonitorListsubdomain();

	/*
	 *	Function:		getMonitorListsubvalue()
	 *	Description:	Get the A record of subdomain
	 *					You should call setDomain() first
	 *	Params:			subdomain		const char*
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id1
	 *	Url:			https://dnsapi.cn/Monitor.Listsubvalue
	 *
	 */
	void getMonitorListsubvalue(const char* subdomain);

	/*
	 *	Function:		getMonitorList()
	 *	Description:	Get monitor list
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id2
	 *	Url:			https://dnsapi.cn/Monitor.List
	 *
	 */
	void getMonitorList();

	/*
	 *	Function:		createMonitor()
	 *	Description:	Create a monitor
	 *					You should call setDomain() first
	 *	Params:			params		std::map<const char*, const char*>		Build this map accord to the Refer
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id3
	 *	Url:			https://dnsapi.cn/Monitor.Create
	 *
	 */
	void createMonitor(std::map<const char*, const char*> params);

	/*
	 *	Function:		modifyMonitor()
	 *	Description:	Modify a monitor
	 *	Params:			params		std::map<const char*, const char*>		Build this map accord to the Refer
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id4
	 *	Url:			https://dnsapi.cn/Monitor.Modify
	 *
	 */
	void modifyMonitor(std::map<const char*, const char*> params);

	/*
	 *	Function:		removeMonitor()
	 *	Description:	Remove a monitor
	 *	Params:			monitor_id		int
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id5
	 *	Url:			https://dnsapi.cn/Monitor.Remove
	 *
	 */
	void removeMonitor(int monitor_id);

	/*
	 *	Function:		getMonitorInfo()
	 *	Description:	Get monitor's info
	 *	Params:			monitor_id		int
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id6
	 *	Url:			https://dnsapi.cn/Monitor.Info
	 *
	 */
	void getMonitorInfo(int monitor_id);

	/*
	 *	Function:		setMonitorStatus()
	 *	Description:	Set monitor's status
	 *	Params:			monitor_id		int
	 *					status			const char*		"enabled" or "disabled"
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id7
	 *	Url:			https://dnsapi.cn/Monitor.Setstatus
	 *
	 */
	void setMonitorStatus(int monitor_id, const char* status);

	/*
	 *	Function:		getMonitorHistory()
	 *	Description:	Get monitor's history
	 *	Params:			monitor_id		int
	 *					hours			int		optional, -1 for not use
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id8
	 *	Url:			https://dnsapi.cn/Monitor.Gethistory
	 *
	 */
	void getMonitorHistory(int monitor_id, int hours = -1);

	/*
	 *	Function:		getMonitorUserdesc()
	 *	Description:	Get monitor description
	 *	Params:			None
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id9
	 *	Url:			https://dnsapi.cn/Monitor.Userdesc
	 *
	 */
	void getMonitorUserdesc();

	/*
	 *	Function:		getMonitorDowns()
	 *	Description:	Get monitor's warning
	 *	Params:			offset		int
	 *					length		int		-1 for not use
	 *	Refer:			https://www.dnspod.cn/docs/d-monitor.html#id10
	 *	Url:			https://dnsapi.cn/Monitor.Getdowns
	 *
	 */
	void getMonitorDowns(int offset = 0, int length = -1);





	/*
	 * setters and getters
	 */
	char* getLoginEmail() const {
		return login_email;
	}

	void setLoginEmail(const char* loginEmail) {
		sprintf(login_email, "%s", loginEmail);
	}

	char* getCallUrl() const {
		return call_url;
	}

	void setCallUrl(const char* callUrl) {
		sprintf(call_url, "%s", callUrl);
	}

	char* getErrorOnEmpty() const {
		return error_on_empty;
	}

	void setErrorOnEmpty(const char* errorOnEmpty) {
		sprintf(error_on_empty, "%s", errorOnEmpty);
	}

	char* getFormat() const {
		return format;
	}

	void setFormat(const char* format) {
		sprintf(this->format, "%s", format);
	}

	char* getLang() const {
		return lang;
	}

	void setLang(const char* lang) {
		sprintf(this->lang, "%s", lang);
	}

	char* getLoginPassword() const {
		return login_password;
	}

	void setLoginPassword(const char* loginPassword) {
		sprintf(login_password, "%s", loginPassword);
	}

	char* getUserId() const {
		return user_id;
	}

	void setUserId(const char* userId) {
		sprintf(user_id, "%s", userId);
	}

	char* getDomain() const {
		return domain;
	}

	/*
	 * callApi() uses curl to contact with DNSPOD
	 * the result will be a json string and be parsed in curlWrite() function
	 * the parsed result will in this->response
	 *
	 */
	void callApi();
	void callApi(std::map<const char*, const char*> params);
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

	char *domain, *domain_id_type;
	/*
	 * To build a post data string
	 */
	char *buildPostString();
	char *buildPostString(std::map<const char*, const char*> params);


	char* getDomainIdType() const {
		return domain_id_type;
	}

	void setDomainIdType(char* domainIdType) {
		domain_id_type = domainIdType;
	}

};

#endif /* DNSPOD_H_ */



















