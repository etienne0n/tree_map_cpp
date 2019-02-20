/*
 * tree_map.h
 *
 *  Created on: 19.02.2019
 *      Author: Etienne Onasch
 */

#ifndef TREE_MAP_HPP_
#define TREE_MAP_HPP_


#include <string>
#include <iostream>
#include <sstream>
#include <memory>

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include "tree_map_decl.hpp"

/**
 * Construction / Destruction
 */

template <class K, class V>
tree_map<K,V>::tree_map(){}

template <class K, class V>
tree_map<K,V>::tree_map(const K& key, const V& value){
	this->key = key;
	this->value = value;
}

template <class K, class V>
tree_map<K,V>::~tree_map(){
	delete left;
	delete right;
}

/*
 * Getter methods
 */
template <class K, class V>
K tree_map<K, V>::getKey() const {
	return this->key;
}

template <class K, class V>
V tree_map<K, V>::getValue() const{
	return this->value;
}

template <class K, class V>
boost::optional<V> tree_map<K,V>::getValue(const K& key) const{

	if(key < this->key){
		if(this->left == nullptr){
			return boost::none;
		}
		else{

			return this->left->getValue(key);
		}
	}
	else if(key > this->key){
		if(this->right == nullptr){
			return boost::none;
		}
		else{

			return this->right->getValue(key);
		}
	}else{

		return this->getValue();
	}
}

template <class K, class V>
tree_map<K,V>* tree_map<K,V>::getLeft() const{
	return left;
}

template <class K, class V>
tree_map<K,V>* tree_map<K,V>::getRight() const{
	return right;
}

template <class K, class V>
int tree_map<K,V>::getHeight() const{
	return this->height;
}



/*
 * Setter methods
 */
template <class K, class V>
void tree_map<K,V>::setKey(const K& key){
	this->key = key;
}

template <class K, class V>
void tree_map<K,V>::setValue(const V& value){
	this->value = value;
}

template <class K, class V>
void tree_map<K,V>::setLeft(tree_map<K,V>* left){
	this->left = left;
}

template <class K, class V>
void tree_map<K,V>::setRight(tree_map<K,V>* right){
	this->right = right;
}

template <class K, class V>
void tree_map<K,V>::setHeight(const int& height){
	this->height = height;
}


// pre order traversal
template <class K, class V>
std::string tree_map<K,V>::toString()const{
	std::ostringstream oss;

	bool L = left != nullptr;
	bool R = right != nullptr;

	oss.str("");
	oss << "{key = " << key <<", value = " << value << ", left.key = ";

	if(L){
		oss << left->getKey();
	}else{
		oss << "null";
	}
	oss << ", right.key = ";
	if(R){
		oss << right->getKey();
	}
	else{
		oss << "null";
	}
	oss << "}" << std::endl;


	if(L){
		oss << left->toString();
	}
	if(R){
		oss << right->toString();
	}
	return oss.str();

}

//template <class K, class V>
//std::ostream& operator << (std::ostream& os, tree_map<K,V>* tm){
//	os << tm->toString() << std::endl;
//	return os;
//}


/*
 * ################################################################
 * AVL - FUNCTIONS
 * ################################################################
 */


/*
 * MAX OF 2 KEYS
 */
template <class K>
K max(const K& key1, const K& key2){
	return (key1 > key2) ? key1 : key2;
}

/*
 * HEIGHT OF A TREE
 */

template <class K, class V>
int get_height(tree_map<K,V>* tm){
	if(tm == nullptr){return 0;}
	else{
		return tm->getHeight();
	}
}

/*
 * UPDATE HEIGHT
 */

template <class K, class V>
void tree_map<K,V>::updateHeight(){

	int lh = left == nullptr ? 0 : left->getHeight();
	int rh = right == nullptr ? 0 : right->getHeight();

	this->setHeight(
		max(lh, rh)
		+ 1
	);
}

/*
 * BALANCE OF A TREE
 */
template <class K, class V>
int getBalance(tree_map<K,V>* tm){
	if(tm == nullptr){return 0;}
	else{
		return get_height(tm->getLeft()) - get_height(tm->getRight());
	}
}


/**
 * ROTATE RIGHT
 *
 * 		r
 * 	x
 * 		t
 *
 * ---------->
 *
 * 	x
 * 		r
 * 	t
 */
template <class K, class V>
tree_map<K,V>* rot_right(tree_map<K,V>* root){
	auto x = root->getLeft();
	auto t = x->getRight();

	// rotation
	x->setRight(root);
	root->setLeft(t);

	// update heights

	root->updateHeight();
	x->updateHeight();

	return x;
}


/**
 * ROTATE LEFT
 *
 * 	r
 * 		x
 * 	t
 *
 * 	---------->
 *
 * 		x
 * 	r
 * 		t
 *
 */
template <class K, class V>
tree_map<K,V>* rot_left(tree_map<K,V>* root){
	auto x = root->getRight();
	auto* t = x->getLeft();

	//rot
	x->setLeft(root);
	root->setRight(t);

	//update heights
	root->updateHeight();
	x->updateHeight();

	return x;
}

template <class K, class V>
tree_map<K, V>* rotate(tree_map<K, V>* root) {
	int balance = getBalance(root);

	/*
	 * left left case
	 */
	if (balance > 1 && getBalance(root->getLeft()) >= 0) {
		return rot_right(root);
	}
	/*
	 * right right case
	 */
	else if (balance < -1 && getBalance(root->getRight()) <= 0) {
		return rot_left(root);
	}

	/*
	 * left right case
	 */
	else if (balance > 1 && getBalance(root->getLeft()) < 0) {
		root->setLeft(rot_left(root->getLeft()));
		return rot_right(root);
	}

	/*
	 * right left case
	 */
	else if (balance < -1 && getBalance(root->getRight()) > 0) {
		root->setRight(rot_right(root->getRight()));
		return rot_left(root);
	} else {
		return root;
	}
}

template <class K, class V>
tree_map<K,V>* insert(tree_map<K,V>* root, const K& key, const V& value){

	//########################################################################
	// 							regular BST insert
	//########################################################################
	if(root == nullptr){
		std::unique_ptr<tree_map<K,V>> root_ptr(new tree_map<K,V>(key, value));
		return root_ptr.release();
	}
	else if(key < root->getKey()){
		root->setLeft(
			insert(root->getLeft(), key, value)
		);
	}
	else if(key > root->getKey()){
		root->setRight(
			insert(root->getRight(), key, value)
		);
	}else{
		return root;
	}

	//########################################################################
	// 						update height of root
	//########################################################################

	root->setHeight(
		max(get_height(root->getLeft()), get_height(root->getRight()))
		+ 1
	);


	//########################################################################
	// 								rotate
	//########################################################################
	return rotate(root);

}

template <class K, class V>
tree_map<K,V>* min_value(tree_map<K,V>* tm){
	auto current = tm;

	while(current->getLeft() != nullptr){
		current = current->getLeft();
	}
	return current;
}

template <class K, class V>
tree_map<K,V>* delete_node(tree_map<K,V>* root, const K& key){

	//########################################################################
	// 						 Standard BST delete
	//########################################################################
	if(root == nullptr){return root;}

	else if(key < root->getKey()){
		root->setLeft(
			delete_node(root->getLeft(), key)
		);
	}
	else if(key > root->getKey()){
		root->setRight(
			delete_node(root->getRight(), key)
		);
	}

	else if(root->getLeft() == nullptr || root->getRight() == nullptr){
		auto temp = root->getLeft() != nullptr ? root->getLeft() : root->getRight();

		//no child case
		if(temp == nullptr){
			delete root;
			return nullptr;
		}
		//one child case
		else{
			*root = *temp;
			delete temp;
		}
	}
	else{
		/*
		 * node with two children: get the inorder
		 * successor (smallest in the right subtree)
		 */
		tree_map<K,V>* temp = min_value(root->getRight());
		/*
		 * copy the inorder successor data to this node
		 */
		root->setKey(temp->getKey());
		root->setValue(temp->getValue());

		/*
		 * delete the inorder successor
		 */
		root->setRight(
			delete_node(root->getRight(), temp->getKey())
		);
	}
	//########################################################################
	//					update height of current node
	//########################################################################
	root->updateHeight();
	//########################################################################
	// 						 perform rotation
	//########################################################################
	return rotate(root);
}
#endif /* TREE_MAP_HPP_ */
