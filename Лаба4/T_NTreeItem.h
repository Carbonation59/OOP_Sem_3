#ifndef T_NTREEITEM_H
#define 	T_NTREEITEM_H
 
#include "Romb.h"

class T_NTreeItem {
public:
	T_NTreeItem(const Romb& romb);
	T_NTreeItem(const T_NTreeItem& orig);
	friend std::ostream& operator<<(std::ostream& os, T_NTreeItem& obj);
	Romb get_value();
	T_NTreeItem*& get_first_child();
	T_NTreeItem*& get_next_bro();
	void set_first_child(T_NTreeItem*& child);
	void set_next_bro(T_NTreeItem*& bro);
	virtual ~T_NTreeItem();
private:
	Romb romb;
	T_NTreeItem *first_child;
	T_NTreeItem *next_bro;
};
 
#endif  	
