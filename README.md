# treemap in C++

A (generic) treemap written in C++ with the use of templates based on the example on https://www.geeksforgeeks.org/avl-tree-set-1-insertion/.
Like the link says, the tree uses the AVL algorithm to sort itself after insertion and deletion,
so an access time of O(log n) is guaranteed.

### Prerequisites

boost library is needed for the <boost/optional/optional_io.hpp header>. 
(I use GCC-6.3.0-1 and boost 1.69.0).

### How to use

1. create a new tree_map:
````````
tree_map<key_type, value_type>* root = nullptr;
````````
2. insert elements :
````````
root = insert(root, a_key, a_value);
root = insert(root, another_key, another_value);
...
````````

3. delete elements : 
````````
root = delete_node(root, another_key);
...
````````

4. printing the tree (pre-order)
````````
std::cout << root->to_string() << std::endl;
````````
5. Accessing elements
through
template <class K, class V>
boost::optional<V> tree_map<K,V>::getValue(const K& key) const;

````````
// example : 
tree_map<int, string>* int_string_map = nullptr;
// insert elements
// ....
std::cout << "Value with key 3377 = " << int_string_map->getValue(3377).value_or("NULL") << std::endl;

````````

custom key_types should implement the operators
<, > and << for correct comparison and printing.

(in public area of class : 
````````
	bool operator < (const my_key_type& other) const; 
````````
etc..)

custom value_types should implement the operator
<< for correct printing.



## Authors

* **Etienne Onasch** - *Initial work* - [etienne0n](https://github.com/etienne0n)


