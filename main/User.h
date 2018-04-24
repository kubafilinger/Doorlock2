#ifndef __USER_H__
#define __USER_H__

enum Roles {
	SUPER_ADMIN,
	USER
};

class User
{
	int id;
	char *name;
	char *code;
	int logged;
	Roles role; 	

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
	Roles getRole();
	void setRole(Roles);
	void save();
};

#endif //__USER_H__
