#ifndef __CLASS_MEMBER__
#define __CLASS_MEMBER__

#include<string>
#include<sstream>
#include"iobuffer.h"
#include"delim.h"

#define LENID	15
#define STDMAXBUF 512

using namespace std;

class Member{
private:
	string id;
	string pw;
	string name;
	string phonenum;
	string address;
	string birthday;
	string email;
	string level;
	string key;

public:
	Member();
	Member(const string& id,const string& pw,const string& name,const string& phone,const string& addr,const string& birthday,const string& email,const string& level);
	Member(const Member& p);
	~Member();
 
	Member& operator=(const Member& operand);
	bool operator==(const Member& operand);
	bool operator!=(const Member& operand);

	friend istream & operator>> (istream& is, Member& m);
	friend ostream & operator<< (ostream& os, Member& m);
 
	void setId(const string& id);
	void setPw(const string& pw);
	void setName(const string& name);
	void setPhonenum(const string& phonenum);
	void setAddress(const string& address);
	void setBirthday(const string& birthday);
	void setEmail(const string& email);
	void setLevel(const string& level);
	string getId();
	string getPw();
	string getLevel();

	bool Pack(IOBuffer& Buffer) const;
	bool Unpack(IOBuffer &);

	char *Key();
};

#endif