/*
 * tree_map_decl.h
 *
 *  Created on: 19.02.2019
 *      Author: Etienne Onasch
 */

#ifndef TREE_MAP_DECL_HPP_
#define TREE_MAP_DECL_HPP_

#include <iostream>
#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>

/*
 * class K and class V must override << operator
 */
template <class K, class V>
class tree_map{
private:
	K key;
	V value;
	tree_map<K,V>* left = nullptr;
	tree_map<K,V>* right = nullptr;
	int height = 1;
public:
	/**
	 * Construction / Destruction
	 */
	tree_map();
	tree_map(const K&, const V&);
	~tree_map();

	/*
	 * Getter methods
	 */
	K getKey() const;
	V getValue() const;
	boost::optional<V> getValue(const K&) const;
	tree_map<K,V>* getLeft() const;
	tree_map<K,V>* getRight() const;



	int getHeight() const;

	/*
	 * Setter methods
	 */

	void setKey(const K&);
	void setValue(const V&);
	void setLeft(tree_map<K,V>*);
	void setRight(tree_map<K,V>*);
	void setHeight(const int&);
	void updateHeight();

	/*
	 * other methods
	 */

	friend std::ostream& operator << (std::ostream& os, tree_map<K,V>* tm){
			os << tm->toString() << std::endl;
			return os;
	}

	std::string toString() const;

};



#endif /* TREE_MAP_DECL_HPP_ */
