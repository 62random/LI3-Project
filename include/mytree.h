#ifndef __MYTREE_H__
#define __MYTREE_H__

#import <stdio.h>
#import <string.h>
#import <stdlib.h>
#import <math.h>

typedef struct AVBin * AVL;

typedef struct tree * TREE;

int TREE_balance(TREE tre);

TREE insere_tree(TREE gl, void * key, void * data);

TREE createTREE(void * f_compare,void * destroy_key,void * destroy_data);

void freeTREE_AVL(TREE tre);

void * search_AVL(TREE tree, void * key,int * valid);

int test_TREE_PROP(TREE tree);

#endif
