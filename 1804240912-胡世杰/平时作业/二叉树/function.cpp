#include"head.h"

//创建二叉树
BiTree* createTree(BiTree* root)
{
	char ch;
	ch = getchar();                            
	root = (BiTree*)malloc(sizeof(BiTree));
	if (ch == '#')  return NULL;                   //'#'表示没有孩子，指针赋空
	else {
		root->data = ch;                           //根左右，先序创建二叉树
		root->lchild = createTree(root->lchild);
		root->rchild = createTree(root->rchild);
		return root;
	}
}

//中序遍历二叉树（递归）
void rec_Midorder(BiTree* root)
{
	if (root)                                      //递归循环的基本条件——根节点不为空
	{
		rec_Midorder(root->lchild);                //左根右中序递归遍历二叉树
		printf("%c ", root->data);
		rec_Midorder(root->rchild);
	}
}

//中序遍历二叉树（非递归——栈）
void Midorder(BiTree* root)
{
	stack<BiTree*> s;                              //创建一个存放BiTree指针类型的栈
	while (root || !s.empty())                     //循环的结束条件——指针为空并且栈为空
	{
		if (root)                                  //指针不为空的时候，把指针存进栈内
		{                                          //并且，往树的左边走
			s.push(root);
			root = root->lchild;
		}
		else                                      //如果指针为空，证明已经走到了最左边，可以开始输出了
		{                               
			root = s.top();                       //取栈顶的元素并打印
			printf("%c ", root->data);            
			root = root->rchild;                  //左边整完了，自己也输出了，开始往右走走          
			s.pop();                              //把栈顶元素删除      
		}
	}
}


//线索二叉树的创建
ThreadBi* createThreatBiTree(ThreadBi* root)
{
	char ch;
	ch = getchar();
	root = (ThreadBi*)malloc(sizeof(ThreadBi));
	if (ch == '#') return NULL;
	else {
		root->data = ch;
		root->ltag = Link;                   //先序创建二叉树并做标记
		root->rtag = Link;
		root->lchild = createThreatBiTree(root->lchild);
		root->rchild = createThreatBiTree(root->rchild);
	}
	return root;
}

//线索二叉树的线索化全过程
ThreadBi* all_Thread(ThreadBi* root)
{
	ThreadBi* top;
	ThreadBi* pre;
	top = (ThreadBi*)malloc(sizeof(ThreadBi));
	pre = top;                                    //top节点的初始化
	top->ltag = Link;   top->rtag = Thread;
    top->rchild = top;
	if (!root)  top->lchild = top;                //根节点为空，top节点左孩子指向自己
	else {
		top->lchild = root;
		pre = rec_Thread(root, pre);					  //线索化过程
		pre->rtag = Thread;                       
		pre->rchild = top;                        //中序遍历的最后一个节点的线索为top节点
		top->rchild = pre;
	}
	return top;
}

//线索二叉树的线索化(非首尾结点的中序遍历)
ThreadBi* rec_Thread(ThreadBi* root, ThreadBi* pre)     //pre是根节点的中序序列的前驱结点
{
	if(root)
	{
		pre = rec_Thread(root->lchild, pre);
		if (!root->lchild) {                            //当前的根节点如果没有左孩子，那么就建立前驱
			root->ltag = Thread;
			root->lchild = pre;
		}
		if (!pre->rchild) {                             //当前根节点的前驱节点如果没有右孩子，建立后继
			pre->rtag = Thread;
			pre->rchild = root;
		}
		pre = root;                                     //前驱节点跟上根节点
		pre = rec_Thread(root->rchild, pre);            
		return pre;
	}
	else {
		return pre;
	}
	
}

//线索二叉树的中序遍历
void order_Thread(ThreadBi* top)
{
	ThreadBi* p;
	p = top->lchild;
	while (p != top)
	{
		while (p->ltag == Link)  p = p->lchild;         //向左走到头
		printf("%c ", p->data);                         //输出当前子树最左节点（左）
		while (p->rtag == Thread && p->rchild != top)   //当p不是中序序列最后一个节点的时候
		{                                               //通过线索找到当前节点的中序后继
			p = p->rchild;
			printf("%c ", p->data);                     //输出后继节点（根）
		}
		p = p->rchild;                                  //进入右子树（右）
	}
}


//创建静态三叉链表（左右孩子，双亲），构建哈夫曼树,输出哈夫曼编码
void TriArr_Huffmantree(){
	int m, n, i;
	printf("请输入权值的个数:\n");
	scanf("%d", &n);
	if (n <= 1) printf("编码为0或1\n");
	else
	{
		m = 2 * n - 1;
		Arr_Huffmantree* p;
		p = (Arr_Huffmantree*)malloc((m+1) * sizeof(Arr_Huffmantree));
		printf("请输入权值:\n");                  //分配足够空间的三叉链表去接收权值
		for (i = 1; i <= n; i++) {
			p[i] = {0,0,0,0};
			scanf("%d", &p[i].weight);
		}
		for (i = n + 1; i <= m; i++) {
			p[i] = {0,0,0,0};
		}                                         //对三叉链表进行叶子和非叶子节点的初始化
		build_Huffmantree(p, n + 1, m);               //调用函数进行哈夫曼树结构搭建
		print_code(p, n);
	}
}

//（↑的调用函数）在静态三叉链表（左右孩子，双亲）内进行结构搭建
void build_Huffmantree(Arr_Huffmantree* &p,int mark,int max)
{
	while (mark <= max)                     
	{
		int s1, s2;
		find_min(s1,s2,mark-1,p);             //调用函数找到两个无双亲的最小叶子节点的下标
		p[s1].parent = mark; p[s2].parent = mark;
		p[mark].lchild = s1; p[mark].rchild = s2;
		p[mark].weight = p[s1].weight + p[s2].weight;
		mark++;                               //两个最小叶子节点拼接出他们的双亲，mark指针后移一位
	}
}

//↑的调用函数（寻找两个最小并且没有双亲的的叶子节点的下标s1和s2）
void find_min(int& s1, int& s2,int end,Arr_Huffmantree* &p)
{
	int i = 1;                              //s1为最小，s2为第二小
	s1 = s2 = 0;                            //利用0下标给s1,s2的权值赋为最大
	p[0].weight = 99999;
	for (i = 1; i <= end; i++)              //从1开始到end进行依次比较
	{
		if (!p[i].parent)                   //跳过有双亲的节点
		{
			if (p[i].weight < p[s1].weight) //如果i的权值比s1要小
			{
				s2 = s1;
				s1 = i;                     //同时更新两个最小值
			}
			else if (p[i].weight < p[s2].weight)  s2 = i;
		}                                    //如果i的权值比s1大但是却比s2小，那么单独更新s2
	}
}

//引用函数（求得并输出哈夫曼编码）
void print_code(Arr_Huffmantree* p,int n)
{
	char** code;
	code = (char**)malloc(sizeof(char*) * (n + 1));  //动态分配二维数组存放编码 
	char* save;
	save = (char*)malloc((n+1) * sizeof(char));    //动态分配一维数组存放当前进行的编码 
	save[n] = '\0';                //分配停止符 
	int child = 0 , parent = 0 , start = 0;
	int i, j;
	for (i = 1; i <= n; i++) {
		start = n;
		child = i;
		for (parent = p[child].parent; parent != 0; parent = p[parent].parent)
		{
			if (child == p[parent].lchild)  save[--start] = '0';
			else if (child == p[parent].rchild) save[--start] = '1';
			child = parent;       //左0右1进行编码 
		}
		code[i] = (char*)malloc((n+1-start) * sizeof(char));   //分配数组内存 
		memcpy(code[i], &save[start], n+ 1 - start);   //将save中的编码拷贝进code里 
		printf("第%d个权值对应的编码为:", i);
		j = 0;
		while (code[i][j])
		{
			printf("%c ", code[i][j]);  //编码输出 
			j++;
		}
		printf("\n");
	}
}



void menu(BiTree* &root,ThreadBi* &Thread_root, ThreadBi*& top)
{
	int opt;
	int flag = 0;
	while (flag == 0) 
	{
		printf("********************************************\n");
		printf("*******  1.二叉树的建立               ******\n");
		printf("*******  2.二叉树的中序遍历（递归）   ******\n");
		printf("*******  3.二叉树的中序遍历（非递归） ******\n");
		printf("*******  4.线索二叉树的建立与遍历     ******\n");
		printf("*******  5.输出哈夫曼编码             ******\n");
		printf("*******  0.退出程序                   ******\n");
		printf("********************************************\n");
		printf("请输入您想实现的功能:\n");
		scanf("%d",&opt);

		switch (opt)
		{
		case 1:
			getchar();
			printf("请输入您想构造的二叉树的先序序列，以#表示空:\n");
			root = createTree(root);
			printf("二叉树建立完成，可执行选项2和3！\n");
			break;

		case 2:
			if (!root) printf("您还未创建二叉树，请优先进行第一步操作！\n");
			else
			{
				printf("用递归算法中序遍历此二叉树的结果为:");
				rec_Midorder(root);
			}
			printf("\n");
			break;
		
		case 3:
			if (root)
			{
				printf("用非递归算法中序遍历此二叉树的结果为:");
				Midorder(root);
				printf("\n");
			}
			else printf("您还未创建二叉树，请优先进行第一步操作！\n");
			break;
		
		case 4:
			getchar();
			printf("请输入您想构造的线索二叉树的先序序列，以#表示空:\n");
			Thread_root = createThreatBiTree(Thread_root);
			top = all_Thread(Thread_root);
			printf("线索二叉树创建完毕，中序遍历线索二叉树的结果为:\n");
			order_Thread(top);
			printf("\n");
			break;

		case 5:
			TriArr_Huffmantree();
			break;

		case 0:
			flag = 1;
			break;

		default:
			printf("您的输入有误，请重新输入\n");
			break;
		}
	} 
}
