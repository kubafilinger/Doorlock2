#ifndef __USER_H__
#define __USER_H__

enum Role = {
	SUPER_ADMIN,
	USER
};

class User
{
	int id;
	char *name;
	char *code;
	int logged;
	Role role; 	

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
	Role getRole();
	void setRole(Role)
};

#endif //__USER_H__
