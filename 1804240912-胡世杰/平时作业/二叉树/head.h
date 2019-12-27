#pragma once
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<iostream>
#include<stack>
using namespace std;


//二叉树所需结构
typedef char ElemType;
typedef struct BiTreeNode{
	ElemType data;
	BiTreeNode* lchild, * rchild;
}BiTree;

//线索二叉树所需结构
enum Pionter{Link , Thread};
typedef struct ThreadNode{
	ElemType data;
	ThreadNode* lchild, * rchild;
	Pionter ltag, rtag;
}ThreadBi;

//哈夫曼编码所需结构
typedef struct Arr_Huffmantree{
	int weight;
	int parent, lchild, rchild;
}Arr_Huffmantree;




//调用函数
BiTree* createTree(BiTree* root);                              //建立二叉树
void rec_Midorder(BiTree* root);                               //递归中序遍历二叉树
void Midorder(BiTree* root);                                   //非递归中序遍历二叉树
 
ThreadBi* createThreatBiTree(ThreadBi* root);                  //建立线索二叉树
ThreadBi* all_Thread(ThreadBi* root);                          //线索二叉树线索化
ThreadBi* rec_Thread(ThreadBi* root, ThreadBi* pre);           //（一级调用函数）线索化过程函数
void order_Thread(ThreadBi* top);                              //中序遍历线索二叉树

void TriArr_Huffmantree();                                     //建立哈夫曼树，输出哈夫曼编码
void build_Huffmantree(Arr_Huffmantree* &p,int mark,int max);  //(一级调用函数)用三叉链表创建哈夫曼树
void find_min(int& s1, int& s2, int end, Arr_Huffmantree* &p); //（二级调用函数）找到最小的两个权值进行组合
void print_code(Arr_Huffmantree* p, int n);                    //（一级调用函数）打印哈夫曼编码
void menu(BiTree* &root, ThreadBi* &Thread_root,ThreadBi* &top);              //菜单


