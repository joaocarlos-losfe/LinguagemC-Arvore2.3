#ifndef _23TNODE_H_
#define _23TNODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DTNode * DTNode;

struct DTNode
{
    DTNode left;
	int key_left;
	DTNode cen;
    int key_right;
	DTNode right;
	int total_keys;  
};

DTNode dttCreateNode(int key, DTNode left, DTNode cen);
bool isLeaf(DTNode node);
void dtNodePrint(DTNode node);

#endif