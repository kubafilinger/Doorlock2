#ifndef __USER_H__
#define __USER_H__

class User
{
	int id;
	char *name;
	char *code;
	int logged;
	

public:
	User();
	~User();
	int login(char *);
	void logout();
	void remove();
	void setName(char *);
	char *getName();
	void setCode(char *);
	int isLogged();	
};

#endif //__USER_H__
