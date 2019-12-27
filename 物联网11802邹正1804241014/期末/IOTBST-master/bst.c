#include "bst.h"
#include <stdlib.h>

struct node *newNode(int n)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (p == NULL)
    {
        printf("Error!\n");
        exit(-1);
    }
    p->key = n;
    p->left = p->right = NULL;
    return p;
}

struct node *insert(struct node *root, int n)
{
    if (root == NULL)
    {
        return newNode(n);
    }
    if (root->key > n)
    {
        root->left = insert(root->left, n);
    }
    else if (root->key < n)
    {
        root->right = insert(root->right, n);
    }
    else
    {
        return root;
    }
}

void inOrder(struct node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void preOrder(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

struct node *maxValue(struct node *root)
{
    struct node *p;
    if(root == NULL){
        return root;
    }
    p = root;
    while (p->right)
    {
        p = p->right;
    }
    return p;  
    
    
}


struct node *delete(struct node *root, int n)
{
    if (root == NULL)
    {
        return root;
    }
    if (n < root->key)
    {
        root->left = delete(root->left, n);
    }
    else if (n > root->key)
    {
        root->right = delete(root->right, n);
    }
    else
    {
        if(root->left == NULL){
            struct node *tmp = root->right;
            free(root);
            return tmp;
        }
        if(root->right == NULL){
            struct node *tmp = root->left;
            free(root);
            return tmp;
        }

        struct node *tmp = maxValue(root->left);
        root->key = tmp->key;
        root->left = delete(root->left, tmp->key);
    }
    return root; 
}
