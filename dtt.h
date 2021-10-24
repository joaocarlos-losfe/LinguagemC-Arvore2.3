#ifndef _23T_H_
#define _23T_H_

typedef struct DTT * DTT;
#include "dtt_node.h"

struct DTT
{
    DTNode root;
    int total_infos;
};

DTT dttStart();
void dttPrint(DTNode root);
void getTotalNodes(DTNode root, int *count);
DTNode dttSeach(DTNode node, int key);
DTNode insertNode(DTNode root, int key, DTNode new);
DTNode explodeNode(DTNode *root, DTNode new_node, int key, int *key_cen);
DTNode ddtInsert(DTNode parent, DTNode *root, int key, int *info_cen);
int dttDelete(DTNode *parent, DTNode *root, int key);


#endif