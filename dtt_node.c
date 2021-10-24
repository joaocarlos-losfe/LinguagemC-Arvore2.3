#include "dtt_node.h"

DTNode dttCreateNode(int key, DTNode left, DTNode cen)
{
	DTNode new_node = malloc(sizeof(struct DTNode));
	
	new_node->key_left = key;
	new_node->key_right = 0;
	new_node->left = left;
	new_node->cen = cen;
	new_node->right = NULL;

	new_node->total_keys = 1;
	return new_node;
	
}


bool isLeaf(DTNode node)
{
	if (node->left == NULL && node->cen == NULL && node->right == NULL)
		return true;
	
	return false;	
}

void dtNodePrint(DTNode node)
{
	printf("%d %d total de infos: %d\n", node->key_left, node->key_right, node->total_keys);

}