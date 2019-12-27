#include"head.h"


//权值是按照深度“右减左”来计算的
//LL旋转发生时，parent权值为-2,进行顺时针旋转
void clockwise_rotate(AVLNode* &parent, AVLNode* &root)
{
	AVLNode* subL = parent->lchild;                //四个节点的结构关系搭建好
	AVLNode* subLR = subL->rchild;
	AVLNode* pparent = parent->parent;

	parent->lchild = subLR;                        //肯定要做的几步关系重置
	parent->parent = subL;
	subL->rchild = parent;

	if (subLR)  subLR->parent = parent;         //parent的左孩子有右枝，那么parent的左枝接上这个“右枝”
	if (pparent)                                  //如果parent不是根节点
	{
		if (parent == pparent->lchild)  pparent->lchild = subL;
		else  pparent->rchild = subL;	          //根据parent是他双亲的左枝或右枝来决定subL接在左边还是右边
		subL->parent = pparent;                   //subL的双亲变成了parent原来的双亲
	}
	else 
	{
		subL->parent = NULL;
		root = subL; 
	}                            //如果parent是根节点，那么subL直接变成根节点

	parent->balance_factor = 0;                   //权值重置
	subL->balance_factor = 0;
}


//RR旋转发生时，parent权值为2，进行逆时针旋转
void counter_clockwise_rotate(AVLNode* &parent, AVLNode* &root)
{
	AVLNode* subR = parent->rchild;
	AVLNode* subRL = subR->lchild;
	AVLNode* pparent = parent->parent;

	parent->rchild = subRL;
	parent->parent = subR;
	subR->lchild = parent;

	if (subRL)  subRL->parent = parent;
	if (pparent)
	{
		if (parent == pparent->lchild)  pparent->lchild = subR;
		else  pparent->rchild = subR;
		subR->parent = pparent;
	}
	else
	{
		subR->parent = NULL;
		root = subR;
	}

	parent->balance_factor = 0;
	subR->balance_factor = 0;
}


//LR旋转发生时，parent权值为-2
//subL的权值为1，subLR的权值为1（在subLR的右边插入）           
//或者，subL的权值为1，subLR的权值为-1(在sublR的左边插入)
void counter_and_clock(AVLNode* &parent, AVLNode* &root)
{
	AVLNode* subL = parent->lchild;
	AVLNode* subLR = subL->rchild;
	int subLR_bf = subLR->balance_factor;

	counter_clockwise_rotate(subL, root);
	clockwise_rotate(parent, root);

	if (subLR_bf == -1)  parent->balance_factor = 1;
	else if (subLR_bf == 1) subL->balance_factor = -1;
}


void clock_and_counter(AVLNode* &parent, AVLNode* &root)
{
	AVLNode* subR = parent->rchild;
	AVLNode* subRL = subR->lchild;
	int subRL_bf = subRL->balance_factor;

	clockwise_rotate(subR, root);
	counter_clockwise_rotate(parent, root);

	if (subRL_bf == 1)  parent->balance_factor = -1;
	else if (subRL_bf == -1)  subR->balance_factor = 1;
}


AVLNode* Insert(AVLNode* root, int key)
{
	int flag = 1;
	AVLNode* p;
	p = (AVLNode*)malloc(sizeof(AVLNode));
	AVLNode* parent;
	parent = root;
	if (!root) {                                                 //如果在空树上插入节点，那他就是根节点
		p->data = key;
		p->balance_factor = 0;
		p->parent = NULL;
		p->lchild = NULL;
		p->rchild = NULL;
		root = p;
		printf("插入成功！\n");
	}
	else {                                                       //插入在树中
		while(1)
		{
			if (key < parent->data)                              //比当前结点小
			{
				if (parent->lchild == NULL)                             
				{
					p->data = key;                               //没有就直接插入
					p->balance_factor = 0;
					p->parent = parent;
					parent->lchild = p;
					p->lchild = NULL;
					p->rchild = NULL;
					printf("成功插入！\n");
					break;
				}
				else { parent = parent->lchild; }                //有左枝就往左枝走
			}
			else if (key > parent->data)                         //比当前结点大
			{
				if ( parent->rchild == NULL )		
				{
					p->data = key;                               //没有右枝就直接插入
					p->balance_factor = 0;
					p->parent = parent;
					parent->rchild = p;
					p->lchild = NULL;
					p->rchild = NULL;
					printf("成功插入！\n");
					break;
				}
				else { parent = parent->rchild; }                 //有右枝就往右边走
			}
			else {                                                //如果跟跟当前结点值相同，不插入
				printf("这个数字在树中已经存在！\n");
				flag = 0;                                         //标记变为0，不执行平衡因子修改和旋转步骤，直接退出函数
				break;
			}
		}
	}

	if (flag == 1)                                                  //成功插入之后,修改平衡因子
	{
		while (parent)
		{
			if (p == parent->lchild)  parent->balance_factor--;
			else if (p == parent->rchild)  parent->balance_factor++;

			if (parent->balance_factor == 1 || parent->balance_factor == -1)   //如果插入之后平衡因子为0（构建了平衡），那么很好，不用操作
			{                                                                  //如果插入之后平衡因子从0变到了1或-1（平衡被破坏），那么往上修改平衡因子
				p = parent;                                                    //直到把根节点修改完  或者  “这个破坏反而让某个节点平衡”为止
				parent = parent->parent;
			}
			else if (parent->balance_factor == 2 || parent->balance_factor == -2)
			{                                                                  //修改平衡因子的时候，如果出现bf为2或者-2，,根据情况进行对应的旋转
				if (parent->balance_factor == 2 && p->balance_factor == 1)  counter_clockwise_rotate(parent, root);
				else if (parent->balance_factor == 2 && p->balance_factor == -1) clock_and_counter(parent, root);
				else if (parent->balance_factor == -2 && p->balance_factor == 1) counter_and_clock(parent, root);
				else if (parent->balance_factor == -2 && p->balance_factor == -1) clockwise_rotate(parent, root);
			}
			else if (parent->balance_factor == 0)  break;
		}
	}
	return root;
}


void dele(int key, AVLNode*& root)
{
	AVLNode* p = root;
	int flag = 0;
	while (p)
	{
		if (key < p->data)   p = p->lchild;                                                 //找到要删除的位置
		else if (key > p->data)  p = p->rchild;
		else if (key == p->data)
		{
			delete_rotate(p, root);
			deleteNode(p, root);
			flag = 1;
			break;
		}
	}
	if (flag != 1) printf("树中没有您想删除的节点！\n");
	else if (flag == 1)  printf("删除成功！\n");
}

void delete_rotate(AVLNode* &p, AVLNode*& root)
{
	AVLNode* q = p->parent;
	AVLNode* r = p;
	
	int flag = 0;
	while (q)
	{
		if (r == q->lchild)  q->balance_factor++;
		else if (r == q->rchild)  q->balance_factor--;

		if (q->balance_factor == 1 || q->balance_factor == -1 || q->balance_factor == 0)
		{
			r = q;
			q = q->parent;
		}
		else if (q->balance_factor == 2)
		{
			r = q->parent;
			if (q == r->lchild)  flag = 0;
			else if (q == r->rchild)  flag = 1;
			counter_clockwise_rotate(r, root);
			q = r;
			if (flag == 0)  r = q->lchild;
			else if (flag == 1) r = q->rchild;
		}
		else if (q->balance_factor == -2)
		{
			r = q->parent;
			if (q == r->lchild)  flag = 0;
			else if (q == r->rchild)  flag = 1;
			clockwise_rotate(r, root);
			q = r;
			if (flag == 0)  r = q->lchild;
			else if (flag == 1) r = q->rchild;
		}
	}
}

void deleteNode(AVLNode* p, AVLNode* root)
{
	AVLNode* q;
	if (!p->lchild && !p->rchild)
	{
		if (p == p->parent->lchild)  p->parent->lchild = NULL;
		else if (p == p->parent->rchild)  p->parent->rchild = NULL;
		delete p;
	}
	else if (!p->lchild && p->rchild)
	{
		q = p;
		p = q->rchild;
		p->parent = q->parent;
		if (q == q->parent->lchild) q->parent->lchild = p;
		else if (q == q->parent->rchild)  q->parent->rchild = p;
		delete q;
	}
	else if (p->lchild && !p->rchild)
	{
		q = p;
		p = q->lchild;
		p->parent = q->parent;
		if (q == q->parent->lchild) q->parent->lchild = p;
		else if (q == q->parent->rchild)  q->parent->rchild = p;
		delete q;
	}
	else {
		q = p->rchild;
		while (q->lchild)  q = q->lchild;
		p->data = q->data;
		deleteNode(q, root);
	}
}


void Midorder(AVLNode* root)
{
	if (root)
	{
		Midorder(root->lchild);
		printf("%d ", root->data);
		printf("平衡因子为%d\n", root->balance_factor);
		Midorder(root->rchild);
	}
}

void destory_AVL(AVLNode* root)
{
	if(root)
	{
		destory_AVL(root->lchild);
		destory_AVL(root->rchild);
		delete root;
	}
}

void menu()
{
	int op, key;
	int flag = 0;
	AVLNode* root = NULL;
	while (1)
	{
		if (flag == 1)  break;
		printf("*************************************************\n");
		printf("***********    1.在AVL中插入数据     ************\n");
		printf("***********    2.在AVL中删除数据     ************\n");
		printf("***********    3.中序遍历AVL         ************\n");
		printf("***********    4.销毁AVL             ************\n");
		printf("***********    0.退出程序            ************\n");
		printf("*************************************************\n");
		printf("请输入您想执行的操作的序号:\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
		{
			printf("请输入您想要插入的值:\n");
			scanf("%d", &key);
			root = Insert(root, key);
			break;
		}
		case 2:
		{
			printf("请输入您想要删除的值:\n");
			scanf("%d", &key);
			dele(key, root);
			break;
		}
		case 3:
		{
			if (!root)  printf("树为空！\n");
			else {
				printf("中序遍历AVL的结果为:\n");
				Midorder(root);
				printf("\n");
			}
			break;
		}
		case 4:
		{
			destory_AVL(root);
			root = NULL;
			printf("AVL以被销毁!\n");
			break;	
		}
		case 0:
		{
			flag = 1;
			break;
		}
		default: printf("序号错误，请重新输入:\n");
		}
	}
}
