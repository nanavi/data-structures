#pragma once
#include <iostream>
#include <string>
#include <fstream>
#define BLACK 0
#define RED 1

typedef int T;
typedef int Color;
//template <class T>
class RB_tree {
public:
	struct Node {
		T key;
		Node* left;
		Node* right;
		Node* p;
		Color color;

		Node(const T& k, Node* l, Node* r, Node* pa, Color c = RED) 
			: key(k), left(l), right(r), p(pa), color(c) {}
		Node(T&& k, Node* l, Node* r, Node* pa, Color c = RED)
			: key(std::move(k)), left(l), right(r), p(pa), color(c) {}
	};
public:
	RB_tree() {
		this->nil = new Node(T(), nullptr, nullptr, nullptr, BLACK);
		this->root = nil;
	}
	void insert(T k) {
		Node* z = new Node(std::forward<T>(k), nil, nil, nil, RED);
		_RB_insert(z);
	}
	Node* search(T k) {
		Node* x = root;
		while (x != nil && k != x->key) {
			if (k < x->key)
				x = x->left;
			else
				x = x->right;
		}
		return x;
	}
	void remove(T k) {
		Node* x = search(k);
		_RB_delete(x);
	}
	void tree_print_dot() {
		using std::cout, std::endl, std::string, std::ofstream;
		string Str = "";
		cout << "digraph tree1 {" << endl;
		Str += "digraph tree1 {\n";
		if (root != nil)
			_tree_print_dot_subtree(-1, nil, 0, root, Str);
		cout << "}" << endl;
		Str += "}";
		ofstream myfile;
		myfile.open("tree.dot");
		myfile << Str;
		myfile.close();
	}

public:
	Node* nil;
	Node* root;

private:
	void update_nil() {
		Node* aux = this->nil;
		aux->p = this->root;
		aux->color = BLACK;
	}
	Node* _Tree_minimum(Node* x) {
		while (x->left != this->nil) {
			x = x->left;
		}
		return x;
	}
	Node* _Tree_maximum(Node* x) {
		while (x->right != this->nil) {
			x = x->right;
		}
		return x;
	}
	void _RB_insert_fixup(Node* z) {					// cases where p is RED 
		while (z->p->color == RED) {					//	while p's color is red  z->p->color == RED
			if (z->p == z->p->p->left) {				//     G
														//	  /	\
														//   P   U
				Node* u = z->p->p->right;					//	 |     u is Uncle of x
				//Node* g = z->p->p;//grandparent
				if (u->color == RED) {					// case where uncle i   (u->color == RED)
					z->p->color = BLACK;
					u->color = BLACK;
					z->p->p->color = RED;
					z = z->p->p;
				}
				else{// u is BLACK 
					if (z == z->p->right) {	//then could be both cases		P
											//								 \
											//								  Z
						z = z->p;			//	we do this line to complement 							  
						_left_rotate(z);	//								  
					}						// case or just 1 single case
					z->p->color = BLACK;
					z->p->p->color = RED;
					_right_rotate(z->p->p);
				}
			}
			else{
				Node* u = z->p->p->left;
				if (u->color == RED) {		//recolor case 1
					z->p->color = BLACK;
					u->color = BLACK;
					z->p->p->color = RED;
					z = z->p->p;
				}
				else {						// R .. 
					if (z == z->p->left) {	// R - L
						z = z->p;
						_right_rotate(z);	//complement R-R, this way z is again at the bottom
					}						// R - R
					z->p->p->color = RED;
					z->p->color = BLACK;
					_left_rotate(z->p->p);
				}
			}
		}
		this->root->color = BLACK;
		this->nil->p = root;
	}
	void _RB_insert(Node* z) {
		Node* y = this->nil;	//nil
		Node* x = this->root;	//root
		while (x != this->nil) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			}
			else if (z->key > x->key) {
				x = x->right;
			}
			else {
				if (x) {
					if (x->key == z->key) {
						delete z;
						z = nullptr;
						goto end;
					}
				}
			}
		}
		z->p = y;
		if (y == this->nil) {
			this->root = z;
			this->nil->p = root;
		}
		else if (z->key < y->key) { //setting y.left or y.right
			y->left = z;
		}
		else {
			y->right = z;
		}
		z->left = this->nil;
		z->right = this->nil;
		z->color = RED;
		_RB_insert_fixup(z);
		end:;
	} 
	void _RB_delete_fixup(Node* x) {
		while (x != this->root && x->color == BLACK) {
			if (x == x->p->left) {
				Node* w = x->p->right;
				if (w->color == RED) {					//case 1
					w->color = BLACK;
					x->p->color = RED;
					this->_left_rotate(x->p);		
					w = x->p->right;					//case 1
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;			//case 2
					x = x->p;			//case 2	
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						this->_right_rotate(w);
						w = x->p->right;
					}
					w->color = x->p->color;
					x->p->color = BLACK;
					w->right->color = BLACK;
					this->_left_rotate(x->p);
					x = this->root;
				}
				
			}
			else {//x == x->p->right     MIRROR
				Node* w = x->p->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->p->color = RED;
					this->_right_rotate(x->p);//this->_left_rotate(x->p);
					w = x->p->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->p;
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						this->_right_rotate(w);
						w = x->p->left;
					}
					w->color = x->p->color;
					x->p->color = BLACK;
					w->right->color = BLACK;  //w->left
					this->_right_rotate(x->p); //leftrotate
					x = this->root;
				}
			}
		}
		x->color = BLACK;
		update_nil();
	}
	void _RB_delete(Node* z) {
	if (z != nil) {//not accepting nils nodes innecesary computation
		Node* y = z;
		Node* x;
		int y_original_color = y->color;
		if (z->left == this->nil) {
			x = z->right;
			this->_RB_transplant(z, z->right);
		}
		else if (z->right == this->nil) {
			x = z->left;
			this->_RB_transplant(z, z->left);
		}
		else {
			y = this->_Tree_minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->p == z) {
				x->p = y;
			}
			else {
				this->_RB_transplant(y, y->right);
				y->right = z->right;
				y->right->p = y;
			}
			this->_RB_transplant(z, y);
			y->left = z->left;
			y->left->p = y;
			y->color = z->color;
		}
		if (y_original_color == BLACK) {
			this->_RB_delete_fixup(x);
		}
	}
	}
	/*TOOLS*/
	void _left_rotate(Node* x) { //Right - Right
		auto y = x->right;			// M :: set y

		x->right = y->left;			// M :: y(left subtree) is now x(right)'s
		if (y->left != this->nil)   // if its NOT nil
			y->left->p = x;
		y->p = x->p;				// M :: change y's p into x's p
		if (x->p == this->nil) {		// Check if x is root
			this->root = y;
			update_nil();
			//this->nil->p = this->root;//mod
		}
		else if (x->p->left == x)   //---
			x->p->left = y;			//	 |__  M :: x.p find if  x is parents.left or parents .right
		else						//	 |    x->p->right == x
			x->p->right = y;		//---
		y->left = x;
		x->p = y;
	}
	void _right_rotate(Node* x) {
		auto y = x->left;

		x->left = y->right;
		if (y->right != this->nil)
			y->right->p = x;
		y->p = x->p;
		if (x->p == this->nil) {
			this->root = y;
			update_nil();
			//this->nil->p = this->root;//mod
		}
		else if (x->p->right == x)
			x->p->right = y;
		else
			x->p->left = y;
		y->left = x;
		x->p = y;
	}
	void _RB_transplant(Node* u, Node* v) {
		if (u->p == this->nil) {
			this->root = v;
		}
		else if (u == u->p->left) {
			u->p->left = v;
		}
		else {
			u->p->right = v;
		}
		v->p = u->p;
	}
	void _tree_print_dot_subtree(int parent_number, Node* parent, int number, Node* node, std::string& Str) {
		using std::cout, std::endl;
		if (node != nil) {
			cout << "x" << number << " [label=<" << node->key << ">" << red_or_black(node->color)+"]" << ";" << endl;
			Str += "x" + std::to_string(number) + " [label=<" + std::to_string(node->key) + ">" + red_or_black(node->color) + "]" + ";\n";
			if (parent != nil) {
				Str += "x" + std::to_string(parent_number) + " -> " + "x" + std::to_string(number) + ";\n";
				cout << "x" << parent_number << " -> " << "x" << number << ";" << endl;
			}
		// dive into left and right subtree
			_tree_print_dot_subtree(number, node, 2 * number + 1, node->left, Str);
			_tree_print_dot_subtree(number, node, 2 * number + 2, node->right, Str);
		}
		else {
			cout << "nil" << number << " [label=nil,fontcolor=gray,shape=none]" << ";" << endl;
			Str += "nil" + std::to_string(number) + " [label=nil,fontcolor=gray,shape=none]" + ";";
			Str += "x" + std::to_string(parent_number) + " -> " + " nil" + std::to_string(number) + ";\n";
			cout << "x" << parent_number << " -> " << " nil" << number << ";" << endl;
		}
	}
	std::string red_or_black(int m) {
		if (m == 0)
			return "style=filled, color=black, fontcolor=white";
		else
			return "style=filled, color=red, fontcolor=white";
	}
};
