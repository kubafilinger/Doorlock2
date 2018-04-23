#ifndef __MENU_H__
#define __MENU_H__

enum Values {
	NO_OPTIONS,
	CHANGE_CODE,
	CHANGE_DATE,
	ADD_USER
};

class Menu
{
	Values fields[3] = { ADD_USER, CHANGE_DATE, CHANGE_CODE };
	char *langs[3] = { "1. Dodaj usera", "2. Zmien date", "3. Zmien pin" };
	int position;
	Values choose;

public:
	Menu();
	~Menu();
	int countFields();
	Values getField();
	void setChoose(Values);
	Values getChoose();
	int getPostion();
	char *getLang();
	int levelUp();
	int levelDown();
};

#endif //__MENU_H__
