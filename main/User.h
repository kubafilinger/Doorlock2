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
	User(char *);
	~User();
	int login(char *);
	void logout();
	void setName(char *);
	char *getName();
	char *getCode();
	void setCode(char *);
	int isLogged();
	Roles getRole();
	char *getStringRole();
	void setStringRole(char *);
	void setRole(Roles);
	char *toString(char *);
	int getId();
};

#endif //__USER_H__
