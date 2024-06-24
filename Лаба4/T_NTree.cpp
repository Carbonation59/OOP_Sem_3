#include "T_NTree.h"
#include <iostream>
#include <string>

using namespace std;
 
T_NTree::T_NTree() : root(nullptr) {
}
 
T_NTree::T_NTree(T_NTree& old) : root(old.get_root()){};

T_NTreeItem*& T_NTree::get_root(){
	return root;
}

bool T_NTree::empty(){
	return root == nullptr;
}

static void print(ostream& os, T_NTreeItem*& tree, int h){
	if(tree == nullptr){
		return;
	}
	for(int i=0;i<h;i++){
		os << "\t";
	}
	(tree->get_value()).print_diagonals();
	print(os, tree->get_first_child(), h+1);
	print(os,tree->get_next_bro(), h);
}

ostream& operator<<(ostream& os, T_NTree& n_tree){
	T_NTreeItem*& root = n_tree.get_root();
	if(root==nullptr){
		cout << "Tree is empty\n";
	} 
	print(os, root, 0);
	return os;
}

void destroy(T_NTreeItem*& tree){
	if(tree == nullptr) return;
	destroy(tree->get_first_child()); 
	destroy(tree->get_next_bro()); 
	delete tree;
	tree = nullptr;
}

T_NTreeItem*& way(T_NTreeItem*& tree, string path){
	if((path != "") && (tree == nullptr)){
		throw invalid_argument("Wrong path!");
	} else if(path == ""){
		return tree;
	} else if(path[0] == 'c'){
		return way((tree)->get_first_child(), path.substr(1));
	} else if(path[0] == 'b'){
		return way((tree)->get_next_bro(), path.substr(1));
	}  else{
		throw invalid_argument("Wrong path!");
	}
}

void T_NTree::insert(string path, Romb value){
	T_NTreeItem*& tree = way(root, path);
	T_NTreeItem* new_node = new T_NTreeItem(value);
	new_node->set_next_bro(tree);
	tree = new_node;
}
void T_NTree::delete_el(string path){
	T_NTreeItem*& tree = way(root, path);
	if(tree == nullptr) throw invalid_argument("Wrong path!");
	T_NTreeItem* tmp = (tree)->get_next_bro();
	destroy((tree)->get_first_child());
	//delete tree;
	tree = tmp;
}

T_NTreeItem*& T_NTree::get_el(string path){
	T_NTreeItem*& tree = way(root, path);
	if(tree==nullptr){
		throw invalid_argument("Wrong path!");
	}
	return tree;
}

T_NTree::~T_NTree() {
	destroy(get_root());
}

