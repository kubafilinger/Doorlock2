#ifndef __MENU_H__
#define __MENU_H__

enum Values {
	NO_OPTIONS,
	CHANGE_CODE,
	CHANGE_DATE,
	ADD_USER,
	LOGOUT
};

class Menu
{
	Values fields[4] = { ADD_USER, CHANGE_DATE, CHANGE_CODE, LOGOUT };
	char *langs[4] = { "1. Dodaj usera", "2. Zmien date", "3. Zmien pin", "4. Wyloguj sie" };
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
	void reset();
};

#endif //__MENU_H__
