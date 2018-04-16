#ifndef __USER_H__
#define __USER_H__

class User
{
	int id;
	char *name;
	int code;
	int logged;
	

public:
	User();
	~User();
	int login(int);
	void logout();
	void remove();
	void setName(char *);
	char *getName();
	void setCode(int);
	int isLogged();	
};

#endif //__USER_H__
