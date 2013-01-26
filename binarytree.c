/*
Description:二叉查找树，包括建树，查找，最小值，最大值，前驱，后继，插入和删除结点等基本操作
Date:2012/10/09
Author:Roger Liu 
*/

#include <stdio.h> 

struct tree;
typedef struct tree tree;
typedef struct tree *ltree;

struct tree{
    int data;
    ltree parent;
    ltree lchild;
    ltree rchild;      
};

ltree tree_create(void);
ltree tree_search(ltree, int);
ltree tree_maximum(ltree);
ltree tree_minimum(ltree);
ltree tree_predecessor(ltree);
ltree tree_successor(ltree);

void tree_insert(ltree, ltree);
void tree_delete(ltree, ltree); 

int main()
{
    ltree root, x, y;
    
    printf("请输入根节点，0表示NULL:\n");
    root = tree_create();
    root->parent = NULL;
    
    /*printf("最大的结点是：%d\n", tree_maximum(root)->data);
    printf("最小的结点是：%d\n", tree_minimum(root)->data);
    
    x = tree_search(root, 9); 
    printf("结点9的前驱结点是：%d\n", tree_predecessor(x)->data);
    printf("结点9的后继结点是：%d\n", tree_successor(x)->data);     
    */
    
    /*y = (ltree)malloc(sizeof(tree));
    y->data = 13;
    y->lchild = y->rchild = y->parent = NULL;
    tree_insert(root, y);
    
    
    x = tree_search(root, 15); 
    printf("\n\n插入结点13后\n\n");
    printf("结点15的前驱结点是：%d\n", tree_predecessor(x)->data);
    printf("结点15的后继结点是：%d\n", tree_successor(x)->data); 
        
    
    
    x = tree_search(root, 13); 
    tree_delete(root, x);
    x = tree_search(root, 15); 
    printf("\n\n删除结点13后\n\n");
    printf("结点15的前驱结点是：%d\n", tree_predecessor(x)->data);
    printf("结点15的后继结点是：%d\n", tree_successor(x)->data);  
    
    x = tree_search(root, 17); 
    tree_delete(root, x);
    x = tree_search(root, 15); 
    printf("\n\n删除结点17后\n\n");
    printf("结点15的前驱结点是：%d\n", tree_predecessor(x)->data);
    printf("结点15的后继结点是：%d\n", tree_successor(x)->data);      
    
    x = tree_search(root, 18); 
    tree_delete(root, x);
    x = tree_search(root, 15); 
    printf("\n\n删除结点18后\n\n");
    printf("结点15的前驱结点是：%d\n", tree_predecessor(x)->data);
    printf("结点15的后继结点是：%d\n", tree_successor(x)->data); 
    */
    
    system("pause");
    exit(0); 
} 

ltree tree_create(void)
{
    ltree T;
    int a;
    scanf("%d", &a);
    
    if (a == 0){
        T = NULL;   
    }else{
        T = (ltree)malloc(sizeof(tree));
        T->data = a;
        printf("\n请输入结点%d的左子结点:\n", T->data); 
        T->lchild = tree_create();
        if (T->lchild != NULL) 
            T->lchild->parent = T;
        printf("\n请输入结点%d的右子结点:\n", T->data); 
        T->rchild = tree_create();
        if (T->rchild != NULL)
            T->rchild->parent = T;
    }
    
    return T;
}

ltree tree_search(ltree T, int x)
{
    ltree t = T;
    if (t == NULL || t->data == x)
        return t;
    if (x < t->data)
        return tree_search(t->lchild, x);
    else
        return tree_search(t->rchild, x);
}

ltree tree_maximum(ltree x)
{ 
    while (x->rchild != NULL)
        x = x->rchild;
    return x;
}

ltree tree_minimum(ltree x)
{ 
    while (x->lchild != NULL)
        x = x->lchild;
    return x;
}

ltree tree_predecessor(ltree x) 
{
    ltree y;
    
    if (x->lchild != NULL)
        return tree_maximum(x->lchild);
    
    y = x->parent;
    
    while (y != NULL && x == y->lchild){
        x = y;
        y = y->parent;
    }
    
    return y;
}

ltree tree_successor(ltree x)
{
    ltree y; 
    
    if (x->rchild != NULL)
        return tree_minimum(x->rchild);
        
    y = x->parent;
    
    while (y != NULL && x == y->rchild){
        x = y;
        y = y->parent;
    }     
    
    return y;
}

void tree_insert(ltree T, ltree z)
{
    ltree y = NULL;
    ltree x;
    
    x = T;
    
    while (x != NULL){
        y = x;
        if (z->data < x->data)
            x = x->lchild;
        else
            x = x->rchild; 
    } 
    
    z->parent = y;
    if (y == NULL)
        T = z;
    else{
        if (z->data < y->data)
            y->lchild = z;
        else
            y->rchild = z; 
    }
} 

void tree_delete(ltree T, ltree z)
{
    ltree x;
    int y;
     
    if (z->lchild == NULL && z->rchild == NULL)//z has no child 
    {
        x = z->parent;
        if (x == NULL)//z is rooot 
            T = NULL;
        else{
            if (x->lchild == z)
                x->lchild = NULL;
            if (x->rchild == z)
                x->rchild = NULL; 
        }           
    }      
    
    if ((z->lchild == NULL && z->rchild != NULL) || (z->lchild != NULL && z->rchild == NULL))//z has only one child
    {
        if (z->lchild != NULL){
            z->lchild->parent = z->parent; 
            if (z->parent != NULL){//z is not root
                if (z->parent->lchild == z){//z is the left child of its parent
                    z->parent->lchild = z->lchild;        
                }else{
                    z->parent->rchild = z->lchild;
                }
            }else{
                T = z->lchild;     
            }             
        }else{
            z->rchild->parent = z->parent;
            if (z->parent != NULL){
                if (z->parent->lchild == z){
                    z->parent->lchild = z->rchild;
                }else{
                    z->parent->rchild = z->rchild;
                }
            }else{
                T = z->rchild;
            }
        }
    }
    
    if (z->lchild != NULL && z->rchild != NULL)//z has tow children
    {
        x = tree_successor(z);//find z's successor and delete it
        y = x->data;//get data
        tree_delete(T, x);//delete the successor
        z->data = y;
    }
} 
