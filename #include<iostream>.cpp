#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<queue>
#include <cassert>
using namespace std;
class node
{
public:
	int item;
	node* right;
	node* left;
	int hight;
	int balance;
	node(int it) :item(it), right(NULL), left(NULL),hight(1),balance(0) {}
	node() {
		right = left = NULL;
	}
	node* operator = (node* r1)
	{
		this->item = r1->item;
		this->right = r1->right;
		this->left = r1->left;
	}
};
class AVL_Tree
{
private:
	node* root;
	void in_order(node*);
	void pre_order(node*);
	void post_order(node*);
	node* insert(node* r, int it);
	node* remove(node* &r, int it);
	node* LL(node*);
	node* RR(node*);
	void clearTree(node*);
public:
	AVL_Tree():root(NULL){}
	void insert(int it) {
		root = insert(root, it);
	}
	void remove(int it) {
		root = remove(root, it);
	}
	void clear()
	{
		clearTree(root);
	}
	void in_order_traversal()
	{
		in_order(root);
	}
	void pre_order_traversal()
	{
		pre_order(root);
	}
	void post_order_traversal()
	{
		post_order(root);
	}
	int hight(node* r)
	{
		if (r == NULL)return 0;
		else if (r->right == NULL && r->left == NULL) return 1;
		else if (r->right == NULL && r->left != NULL) return 1 + hight(r->left);
		else if (r->right != NULL && r->left == NULL) return 1 + hight(r->right);
		else
		{
			return 1 + max(hight(r->left), hight(r->right));
		}

	}
	int balanceFactor(node* r)
	{
		if (r == NULL) return 0;
		return hight(r->left) - hight(r->right);
	}
};
void AVL_Tree::in_order(node* r) {
	if (r != NULL)
	{
		in_order(r->left);
		cout << r->item << "  ";
		in_order(r->right);
	}
}
void AVL_Tree::pre_order(node* r) {
	if (r != NULL)
	{
		cout << r->item << "  ";
		pre_order(r->left);
		pre_order(r->right);
	}
}
void AVL_Tree::post_order(node* r)
{
	if (r != NULL)
	{
		post_order(r->left);
		post_order(r->right);
		cout << r->item << "  ";
	}
}
node* AVL_Tree::remove(node* &r, int it)
{
	
	if (r == NULL)
		return r;
	if (r->item < it)
		r->right = remove(r->right, it);
	else if (r->item > it)
		r->left = remove(r->left, it);
	if (r->item == it)
	{
		if (r->left == NULL && r->right == NULL)// leaf node
		{
			delete r;
			r = NULL;
		}
		else if (r->right != NULL && r->left == NULL)// one child on the right
		{
			node* temp = r;
			r = r->right;
			delete temp;
		}
		else if (r->right == NULL && r->left != NULL)// one child on the left
		{
			node* temp = r;
			r = r->left;
			delete temp;
		}
		else
		{
			node* cur;
			node* parent = NULL;
			cur = r->right;
			while (cur->left != NULL)
			{
				parent = cur;
				cur = cur->left;
			}
			r->item = cur->item;
			if (parent == NULL)
			{
				r->right = cur->right;
			}
			else
			{
				parent->left = cur->right;
			}
			delete cur;
		}
	}
	if (r == NULL)
		return r;
	r->hight = hight(r);
	int balance = balanceFactor(r);
	if (balance > 1 && it < r->left->item)// left left
		return LL(r);
	if (balance < -1 && it > r->right->item)//rr
		return RR(r);
	if (balance > 1 && it > r->left->item)//lr
	{
		r->left = RR(r->left);
		return LL(r);
	}
	if (balance < -1 && it < r->right->item)
	{
		r->right = LL(r->right);
		return RR(r);
	}
	return r;
}
node* AVL_Tree::insert(node*r,int it)
{
	node* newnode = new node(it);
	if (r == NULL)
		r = newnode;
	else {
		if (it > r->item)
			r->right = insert(r->right, it);
		else if (it < r->item)
			r->left = insert(r->left, it);
		else return r;
	}
	r->hight = hight(r);
	int balance = balanceFactor(r);
	if (balance > 1 && it < r->left->item)// left left
		return LL(r);
	if (balance < -1 && it > r->right->item)//rr
		return RR(r);
	if (balance > 1 && it > r->left->item)//lr
	{
		r->left = RR(r->left);
		return LL(r);
	}
	if (balance < -1 && it < r->right->item)
	{
		r->right = LL(r->right);
		return RR(r);
	}
	return r;
}
node* AVL_Tree::LL(node* r)
{
	node* b=r->left;
	node* br=b->right;
	b->right = r;
	r->left = br;
	r->hight = hight(r);
	b->hight = hight(b);
	return b;
}
node* AVL_Tree::RR(node* r)
{
	node* b = r->right;
	node* bl = b->left;
	b->left = r;
	r->right = bl;
	r->hight = hight(r);
	b->hight = hight(b);
	return b;
}
int main()
{
	return 0;
}

