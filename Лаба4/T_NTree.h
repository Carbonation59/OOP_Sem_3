#ifndef T_NTREE_H
#define 	T_NTREE_H

#include <iostream>
#include <string>
#include "Romb.h"
#include "T_NTreeItem.h"

using namespace std;

class T_NTree {
public:
	T_NTree();
	T_NTree(T_NTree& old);
	T_NTreeItem*& get_root();
	bool empty();
	friend ostream& operator<<(ostream& os, T_NTree& n_tree);
	void insert(string path, Romb value);
	void delete_el(string path);
	T_NTreeItem*& get_el(string path);
	virtual ~T_NTree();
private:
	T_NTreeItem *root;
};

#endif