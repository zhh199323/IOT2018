#include<stdio.h>
#include<malloc.h>

typedef struct AVLNode {
	int data;
	int balance_factor;
	struct AVLNode* lchild, * rchild, * parent;
}AVLNode;


void clockwise_rotate(AVLNode* &parent, AVLNode* &root);
void counter_clockwise_rotate(AVLNode* &parent, AVLNode* &root);
void counter_and_clock(AVLNode* &parent, AVLNode* &root);
void clock_and_counter(AVLNode* &parent, AVLNode* &root);
AVLNode* Insert(AVLNode* root, int key);
void dele(int key, AVLNode*& root);
void delete_rotate(AVLNode* &p, AVLNode*& root);
void deleteNode(AVLNode* p, AVLNode* root);
void Midorder(AVLNode* root);
void destory_AVL(AVLNode* root); 
void menu();

