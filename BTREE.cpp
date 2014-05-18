/*
David Stancu
Data Structures and Algorithms: Binary Trees
dstancu@nyu.edu

Polytechnic Institute of New York University
*/

#include <iostream>
using std::cout;

template <class Object>
struct TreeNode
{
	Object data;
	TreeNode* left;
	TreeNode* right;
	TreeNode(const Object& data, TreeNode* left, TreeNode* right) : data(data), left(left), right(right) {}
};

template <class Object>
class BTree
{
private:
	TreeNode<Object>* root;
public:
	BTree() : root(NULL) {}
	BTree(const BTree<Object>& newrt) 
	{ 
		if (!newrt.root) root = NULL;
		// This could have been done in the initialization list, however, it's best to check if an end-user tries to pass us a tree with a NULL root. 
		root = new TreeNode<Object>(newrt.root->data, NULL, NULL);
		duplicate(newrt.root, root); 
	}
	~BTree() { makeEmpty(root); }

	// This is just pre-order traversal, except we're actually doing something as we traverse the tree
	void duplicate(TreeNode<Object>* newtree, TreeNode<Object>* mytree)
	{
		if (!newtree || !mytree) return; 
		if (newtree->left) mytree->left = new TreeNode<Object>(newtree->left->data, NULL, NULL);
		if (newtree->right) mytree->right = new TreeNode<Object>(newtree->right->data, NULL, NULL);
		duplicate(newtree->left, mytree->left);
		duplicate(newtree->right, mytree->right);
	}

	// This is just post-order traversal; it makes sense since we should recurse fully before getting rid of things!
	void makeEmpty(TreeNode<Object>* node)
	{
		if (!node) return;
		makeEmpty(node->left);
		makeEmpty(node->right);
		delete node;
	}
	void makeEmpty() { makeEmpty(root); }

	void printPreOrder(TreeNode<Object>* node)
	{
		// Print, recurse left right
		cout << node->data << " ";
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
	void printPreOrder() { printPreOrder(root;) }

	void printPostOrder(TreeNode<Object>* node)
	{
		// Recurse left right, print
		if (!node) return;
		printPostOrder(node->left);
		printPostOrder(node->right);
		cout << node->data << " ";
	}
	void printPostOrder() { printPostOrder(root); }

	void printInOrder(TreeNode<Object>* node)
	{
		// Recurse left, print, recurse right
		if (!node) return;
		printInOrder(node->left);
		cout << node->data << " ";
		printInOrder(node->right);
	}
	void printInOrder() { printInOrder(root); }

	void insert(const Object& data)
	{
		if (!root) root = new TreeNode<Object>(data, NULL, NULL);
		else
		{
			for (TreeNode<Object>* dummy = root;;)
			{
				if (!dummy->left && !dummy->right)
				{
					(data > dummy->data) ? (dummy->right = new TreeNode<Object>(data, NULL, NULL)) : (dummy->left = new TreeNode<Object>(data, NULL, NULL));
					break;
				}
				if (data > dummy->data && dummy->right) dummy = dummy->right;
				else if (data > dummy->data && !dummy->right)
				{
					dummy->right = new TreeNode<Object>(data, NULL, NULL);
					break;
				}
				if (data < dummy->data && dummy->left) dummy = dummy->left;
				else if (data < dummy->data && !dummy->left)
				{
					dummy->left = new TreeNode<Object>(data, NULL, NULL);
					break;
				}
			}
		}
	}
};

int main(void)
{
	BTree<int> tree;
	tree.insert(5);
	tree.insert(3);
	tree.insert(11);
	tree.insert(44);
	tree.insert(9);

	BTree<int> t2(tree);

	tree.printInOrder();
	tree.printPostOrder();
	tree.printPreOrder();

	return 0;
}
