#ifndef __USER_H__
#define __USER_H__

class User
{
	int id;
	char *name;
	int code;

public:
	User();
	~User();
	bool login(int);
	void logout();
	void remove();
	void setName(char *);
	char *getName();
	void setCode(int);
	int getCode();
};

#endif //__USER_H__
