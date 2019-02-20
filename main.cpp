/*
 * main.cpp
 *
 *  Created on: 19.02.2019
 *      Author: Etienne Onasch
 */

#include <string>
#include <iostream>
#include <vector>
#include <cmath>

#include "tree_map.hpp"




int main(){

	std::vector<double> dvec{0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12};
	std::vector<long> lvec{1,2,3,4,5,6,7,8,9,10,11,12};
	std::vector<std::string> svec{"Eins", "Zwei", "Drei", "Vier", "Fuenf", "Sechs", "Sieben", "Acht", "Neun", "Zehn", "Elf", "Zwoelf"};


	tree_map<long, std::string>* long_root = nullptr;
	tree_map<std::string, long>* string_root = nullptr;
	tree_map<double, std::string>* double_root = nullptr;

	for (unsigned int i = 0; i < lvec.size(); i++) {
		long_root = insert(long_root, lvec[i], svec[i]);
		string_root = insert(string_root, svec[i], lvec[i]);
		double_root = insert(double_root, dvec[i], svec[i]);
	}

	std::cout << "Tree with long value as key: " << std::endl;
	std::cout << long_root->toString() << std::endl;

	std::cout << "Tree with double value as key: " << std::endl;
	std::cout << double_root->toString() << std::endl << std::endl;
	std::cout << "Value with key 0.07 : " << double_root->getValue(0.07).value_or("nicht gefunden") << std::endl;
	std::cout << "Value with key 9999.99 : " << double_root->getValue(9999.99).value_or("nicht gefunden") << std::endl << std::endl;


	std::cout << "Tree with string value as key: " << std::endl;
	std::cout << string_root->toString() << std::endl;

	delete long_root; delete string_root; delete double_root;



}
