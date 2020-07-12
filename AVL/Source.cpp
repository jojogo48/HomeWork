#include <iostream>
#include <string>
using namespace std;



typedef struct {
	string ID="";
	string Item_class;
	string Item;
	int    price;
} element;

typedef struct node {
	node* left;
	node* right;
	int   bf;
	element* data;
} node;

class AVL
{
	public:
		void insert(element*);	
		const element* search(string ID);
		void print();
	private:
		void insert_recursive(node*& parent, element* data, bool* unbanlanced);
		void left_rotation(node*& parent, bool* unbanlanced);
		void right_rotation(node*& parent, bool* unbanlanced);
		void traversal_recrusive(node* root, int space);
		node* root = NULL;
};
void AVL::print()
{
	this->traversal_recrusive(this->root, 0);
}

int main()
{
	AVL tree;
	element temp[10];
	temp[0].ID = "A";
	temp[1].ID = "B";
	temp[2].ID = "C";
	temp[3].ID = "D";
	temp[4].ID = "E";
	temp[5].ID = "F";
	temp[6].ID = "G";
	temp[7].ID = "H";
	temp[8].ID = "I";
	temp[9].ID = "J";
	tree.insert(&temp[0]);
	tree.insert(&temp[1]);
	tree.insert(&temp[2]);
	tree.insert(&temp[3]);
	tree.insert(&temp[4]);
	tree.insert(&temp[5]);
	tree.insert(&temp[6]);
	tree.insert(&temp[7]);
	tree.insert(&temp[8]);
	tree.insert(&temp[9]);

	tree.print();

	const element* a = tree.search("c");
	if(a)
		cout << a->ID << endl;

}


void AVL::insert(element* a)
{
	bool* unbanlanced = new bool();
	*unbanlanced = false;
	this->insert_recursive(this->root, a, unbanlanced);
}
const element* AVL::search(string ID)
{
	node* temp = root;
	while (temp)
	{
		if (temp->data->ID < ID)
		{
			temp = temp->right;
		}
		else if (temp->data->ID > ID)
		{
			temp = temp->left;
		}
		else
		{
			break;
		}
	}
	if (temp)
	{
		cout << "find";
		return (temp->data);

	}
	cout << "not found" << endl;
	return NULL;
}


void AVL::insert_recursive(node*& parent,element* data,bool* unbanlanced)
{
	if (!parent)
	{
		parent = new node();
		parent->data = new element;
		parent->bf = 0;	
		parent->data->ID			= data->ID;
		parent->data->Item			= data->Item;
		parent->data->Item_class	= data->Item_class;
		parent->data->price			= data->price;
		parent->left = parent->right = NULL;
		*unbanlanced = true;
	}
	else if (data->ID < (parent->data)->ID)
	{
		this->insert_recursive(parent->left, data, unbanlanced);
		if (*unbanlanced) 
		{
			switch (parent->bf)
			{
			case -1:
				parent->bf = 0;
				*unbanlanced = false;
				break;
			case 0:
				
				parent->bf = 1;
				break;
			case 1:
				this->left_rotation(parent, unbanlanced);

			}
		}
	}
	else if (data->ID > (parent->data)->ID)
	{
		this->insert_recursive(parent->right, data, unbanlanced);
		if (*unbanlanced)
		{
			switch (parent->bf)
			{
			case 1:
				parent->bf = 0;
				*unbanlanced = false;
				break;
			case 0:
				parent->bf = -1;
				break;
			case -1:
				this->right_rotation(parent, unbanlanced);
			}
		}
	}
	else
	{
		*unbanlanced = false;
		cout << " this key is already in the tree";
	}
}

void AVL::left_rotation(node*& parent, bool* unbanlanced)
{
	node* grandchild; 
	node* child;
	child = parent->left;
	if (child->bf == 1)//LL
	{
		parent->left = child->right;
		child->right = parent;
		parent->bf = 0;
		parent = child;
	}
	else //LR
	{
		grandchild = child->right;
		child->right = grandchild->left;
		grandchild->left = child;
		parent->left = grandchild->right;
		grandchild->right = parent;

		switch (grandchild->bf)
		{
			case 1:
				parent->bf = -1;
				child->bf = 0;
				break;
			case 0:
				parent->bf = 0;
				child->bf = 0;
				break;
			case -1:
				parent->bf = 0;
				child->bf = 1;
				break;
		}
		parent = grandchild;
	}
	parent->bf = 0;
	*unbanlanced = false;
}


void AVL::right_rotation(node*& parent, bool* unbanlanced)
{
	node* grandchild;
	node* child;
	child = parent->right;
	if (child->bf == -1)//RR
	{
		parent->right = child->left;
		child->left = parent;
		parent->bf = 0;
		parent = child;
	}
	else//RL
	{
		grandchild = child->left;
		child->left = grandchild->right;
		grandchild->right = child;
		parent->right = grandchild->left;
		grandchild->left = parent;

		switch (grandchild->bf)
		{
		case -1:
			parent->bf = 1;
			child->bf = 0;
			break;
		case 0:
			parent->bf = 0;
			child->bf = 0;
			break;
		case 1:
			parent->bf = 0;
			child->bf = -1;
			break;
		}
		parent = grandchild;
	}
	parent->bf = 0;
	*unbanlanced = false;

}

void AVL::traversal_recrusive(node* root,int space)
{
	if (root)
	{	
		space +=5;
		traversal_recrusive(root->left,space);
		
		for (int i = 5; i < space; i++)
			cout << " ";
		cout << root->data->ID<<root->bf<< endl;
		traversal_recrusive(root->right,space);

	}
}
