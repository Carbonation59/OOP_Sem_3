#include "T_NTreeItem.h"
#include <iostream>

using namespace std;

T_NTreeItem::T_NTreeItem(const Romb& romb) {
	this->romb = romb;
	this->next_bro = nullptr;
	this->first_child = nullptr;
}
 
T_NTreeItem::T_NTreeItem(const T_NTreeItem& orig) {
	this->romb = orig.romb;
	this->next_bro = orig.next_bro;
	this->first_child = orig.first_child;
}
 
Romb T_NTreeItem::get_value(){
	return romb;
}

T_NTreeItem*& T_NTreeItem::get_first_child(){
	return first_child;
}

T_NTreeItem*& T_NTreeItem::get_next_bro(){
	return next_bro;
}
 
void T_NTreeItem::set_first_child(T_NTreeItem*& child){
	this->first_child = child;
	return;
}

void T_NTreeItem::set_next_bro(T_NTreeItem*& bro){
	this->next_bro = bro;
	return;
}
 
T_NTreeItem::~T_NTreeItem() {
	delete next_bro;
	delete first_child;
}
 
std::ostream& operator<<(std::ostream& os, T_NTreeItem& obj) {
	os << obj.get_value() << "\n";
	return os;
}
