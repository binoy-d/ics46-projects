#ifndef __PROJ_FOUR_AVL_HPP
#define __PROJ_FOUR_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>
#include <iostream>


const bool DEBUG = false;


class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};

template<typename Key, typename Value>
struct Node {
	Key key;
	Value val;
	Node* left;
	Node* right;
	size_t height;
	Node(Key k, Value v){
		key = k;
		val = v;
		left = nullptr;
		right = nullptr;
		height = 1;
	}
	~Node(){
		if(left) delete left;
		if(right) delete right;
	}
};


template<typename Key, typename Value>
class MyAVLTree
{
private:
	
	// fill in private member data here
	// If you need to declare private functions, do so here too.
	size_t sz;
	Node<Key, Value>* rootNode;
	bool containsHelper(const Node<Key, Value>* n,const Key &k) const;
	void inOrderHelper(const Node<Key, Value>* n, std::vector<Key> &out) const;
	void preOrderHelper(const Node<Key, Value>* n, std::vector<Key> &out) const;
	void postOrderHelper(const Node<Key, Value>* n, std::vector<Key> &out) const;
	Node<Key, Value>* insertHelper(Node<Key, Value>* n, const Key & k, const Value & v);
	size_t height(const Node<Key, Value>* n) const;
	int getBalanceFactor(const Node<Key, Value>* n) const;
	void updateHeight( Node<Key, Value>* n);
	Node<Key, Value>* leftRotate( Node<Key, Value>* n);
	Node<Key, Value>* rightRotate( Node<Key, Value>* n);
	
public:
	MyAVLTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required. 
	~MyAVLTree()
	{
		delete rootNode;
	}

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;

};


template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree():
	sz{0}
{
	rootNode = nullptr;
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{
	return sz; // stub
}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return sz == 0; // stub
}


template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{

	Node<Key, Value>* current = rootNode;
	while(current!=nullptr){
		Key nodeKey = current->key;
		if(DEBUG) std::cout<<"current key = "<<nodeKey<<std::endl;
		if(k>nodeKey){
			current = current->right;
			
		}else if(k<nodeKey){
			current = current->left;
		}else{
			return true;
		}
	}
	return false;


	//return containsHelper(rootNode, k);
}


template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::containsHelper(const Node<Key, Value>* n, const Key &k) const
{
	if(n == nullptr){
		if(DEBUG) std::cout<<"nullptr"<<std::endl;
		return false;
	}
	Key nodeKey = *(n->key);
	if(nodeKey == k){
		if(DEBUG) std::cout<<"found key: "<<*(n->key)<<std::endl;
		return true; 
	}
	//if too big, check left
	if(k < nodeKey){
		if(DEBUG) std::cout<<"key "<<nodeKey<<"is too big, checking left"<<std::endl;
		return containsHelper(n->left, k);
	}
	//if too small, check right
	if(k < nodeKey){
		if(DEBUG) std::cout<<"key "<<nodeKey<<"is too small, checking right"<<std::endl;
		return containsHelper(n->right, k);
	}
	if(DEBUG) std::cout<<"Something has gone terribly wrong"<<std::endl;
	return false; //shouldn't happen
}


template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
	Node<Key, Value>* current = rootNode;
	Key nodeKey = current->key;
	while(current!=nullptr){
		if(nodeKey<k){
			current = current->right;
		}else if(nodeKey>k){
			current = current->left;
		}else{
			return  current->val;
		}
		nodeKey = current->key;
	}
	return current->val;
}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
	Node<Key, Value>* current = rootNode;
	Key nodeKey = current->key;
	while(current!=nullptr){
		if(nodeKey<k){
			current = current->right;
		}else if(nodeKey>k){
			current = current->left;
		}else{
			return  current->val;
		}
		nodeKey = current->key;
	}
	return current->val;
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
	rootNode = insertHelper(rootNode, k, v);
	sz++;
}


template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::insertHelper(Node<Key, Value>* n, const Key & k, const Value & v){
	//normal bst insert
	if(DEBUG) std::cout<<"Inserting key : "<<k<<std::endl;
	if(n == nullptr){
		return new Node<Key, Value>(k, v);;
	}else{
		if(k<n->key){
			n->left = insertHelper(n->left, k, v);
		}else if(k>n->key){
			n->right = insertHelper(n->right, k, v);
		}
	}

	//update height
	updateHeight(n);
	//rotation time lmao
	int balanceFactor = getBalanceFactor(n);
	if(DEBUG) std::cout<<"Got balance factor: "<<balanceFactor<<std::endl;

	//4 cases:
	if(balanceFactor>1 && k<n->left->key){//left left
		//right rotate n
		return rightRotate(n);
	}else if(balanceFactor<-1 && k>n->right->key){//right right
		//left rotate n
		return leftRotate(n);
	}else if(balanceFactor>1 && k>n->left->key){//left right
		//left rotate n->left
		n->left = leftRotate(n->left);
		//right rotate n
		return rightRotate(n);

	}else if(balanceFactor<-1 && k<n->right->key){//right left
		//right rotate n->right
		n->right = rightRotate(n->right);
		//left rotate n
		return leftRotate(n);
	}
	return n;
}


template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::leftRotate( Node<Key, Value>* n){
	Node<Key, Value>* ogRight = n->right;
	Node<Key, Value>* ogRightLeft = ogRight->left;

	ogRight->left = n;
	n->right = ogRightLeft;

	//update heights
	updateHeight(n);
	updateHeight(ogRight);

	return ogRight;//new rootNode
}

template<typename Key, typename Value>
Node<Key, Value>* MyAVLTree<Key, Value>::rightRotate( Node<Key, Value>* n){
	Node<Key, Value>* ogLeft = n->left;
	Node<Key, Value>* ogLeftRight = ogLeft->right;

	ogLeft->right = n;
	n->left = ogLeftRight;

	//update heights
	updateHeight(n);
	updateHeight(ogLeft);

	return ogLeft;//new rootNode
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::updateHeight( Node<Key, Value>* n){
	size_t leftHeight = height(n->left);
	size_t rightHeight = height(n->right);
	n->height = 1 + leftHeight>rightHeight?leftHeight:rightHeight; 
}



template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::height(const Node<Key, Value>* n) const{
	return n==nullptr?0:n->height;
}


template<typename Key, typename Value>
int MyAVLTree<Key, Value>::getBalanceFactor(const Node<Key, Value>* n) const{
	return n==nullptr?0:height(n->left)-height(n->right);
}



template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	std::vector<Key> out;
	inOrderHelper(rootNode, out); 
	return out;
}


template<typename Key, typename Value>
void MyAVLTree<Key, Value>::inOrderHelper(const Node<Key, Value>* n, std::vector<Key> &out) const
{
	if(n == nullptr){
		return;
	}
	inOrderHelper(n->left, out);
	out.push_back(n->key);
	inOrderHelper(n->right, out);
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	std::vector<Key> out;
	preOrderHelper(rootNode, out); 
	return out;
}


template<typename Key, typename Value>
void MyAVLTree<Key, Value>::preOrderHelper(const Node<Key, Value>* n, std::vector<Key> &out) const
{
	if(n == nullptr){
		return;
	}
	out.push_back(n->key);
	preOrderHelper(n->left, out);
	preOrderHelper(n->right, out);
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	std::vector<Key> out;
	postOrderHelper(rootNode, out); 
	return out;
}



template<typename Key, typename Value>
void MyAVLTree<Key, Value>::postOrderHelper(const Node<Key, Value>* n, std::vector<Key> &out) const
{
	if(n == nullptr){
		return;
	}
	postOrderHelper(n->left, out);
	postOrderHelper(n->right, out);
	out.push_back(n->key);
	
}




#endif 