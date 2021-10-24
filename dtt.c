#include "dtt.h"

DTT dttStart()
{
    DTT new_tree = malloc(sizeof(struct DTT));
    new_tree->total_infos = 0;

    return new_tree;
}

void dttPrint(DTNode root)
{
	if (root != NULL)
	{
		printf("%d ", root->key_left);
		if(root->key_right != 0)
			printf("%d\n", root->key_right);
		

		dttPrint(root->left);
		dttPrint(root->cen);
		dttPrint(root->right);
	}
}

void getTotalNodes(DTNode root, int *count)
{
	if (root != NULL)
	{
		*count = *count + root->total_keys;

		getTotalNodes(root->left, count);
		getTotalNodes(root->cen, count);
		getTotalNodes(root->right, count);
	}
}

DTNode dttSeach(DTNode node, int key)
{
	if(node == NULL)
		return NULL;
	if (key == node->key_left || key == node->key_right)
		return node; 

	else if (key < node->key_left)
		return dttSeach(node->left, key);
	else if(key > node->key_left && node->key_right == 0)
		return dttSeach(node->cen, key);
	else if(key > node->key_left && key > node->key_right)
		return dttSeach(node->right, key);
	else 
		return dttSeach(node->cen, key);
	
}

DTNode insertNode(DTNode root, int key, DTNode new)
{
	if (key > root->key_left)
	{
		root->key_right = key;
		root->right = new;
	}
	else
	{
		root->key_right = root->key_left;
		root->key_left = key;
		root->right = root->cen;
		root->cen = new;
	}

	root->total_keys = 2;

	return root;
	
}

DTNode explodeNode(DTNode *root, DTNode new_node, int key, int *key_cen)
{
	DTNode new;

	if (key > (*root)->key_right)
	{
		*key_cen = (*root)->key_right;
		new = dttCreateNode(key, (*root)->right, new_node);
	}
	else if (key < (*root)->key_left)
	{
		*key_cen = (*root)->key_left;
		new = dttCreateNode((*root)->key_right, (*root)->cen, (*root)->right);

		(*root)->key_left = key;
		(*root)->cen = new_node;
	}
	else
	{
		*key_cen = key;
		new = dttCreateNode((*root)->key_right, new_node, (*root)->right);
	}

	(*root)->key_right = 0;
	(*root)->total_keys = 1;
	(*root)->right = NULL;

	return new;
}

DTNode ddtInsert(DTNode parent, DTNode *root, int key, int *info_cen)
{
	DTNode new;
	
	if (*root == NULL)
	{
		*root = dttCreateNode(key, NULL, NULL);
	}
	else
	{
		if (isLeaf(*root))
		{
			if ((*root)->total_keys == 1)
			{
				*root = insertNode(*root, key, NULL);
				new = NULL;
			}
			else
			{
				new = explodeNode(root, NULL, key, info_cen);

				if (parent == NULL)
				{
					*root = dttCreateNode(*info_cen, *root, new);
					new = NULL;
				}
			}
		}
		else
		{
			if (key < (*root)->key_left)
				new = ddtInsert(*root, &(*root)->left, key, info_cen);
			
			else if((*root)->total_keys == 1)
				new = ddtInsert(*root, &(*root)->cen, key, info_cen);
			
			else if(key < (*root)->key_right)
				new = ddtInsert(*root, &(*root)->cen, key, info_cen);
			
			else
				new = ddtInsert(*root, &(*root)->right, key, info_cen);
			
			if(new != NULL)
			{
				if((*root)->total_keys == 1)
				{
					*root = insertNode(*root, *info_cen, new);
					new = NULL;
				}
				else
				{
					new = explodeNode(root, new, *info_cen, info_cen);

					if (parent == NULL)
					{
						*root = dttCreateNode(*info_cen, *root, new);
						new = NULL; 
					}
					
				}
			}
			
		}
		
	}
	
	return new;
}

int contains(DTNode root, int key)
{
	if (key == root->key_left)
		return 1; // se esta na informação da esquerda
	else if(key == root->key_right)
		return 2; // se esta na informação da direita
	
	return 0; // em nenhuma das infos
}

int dttDelete(DTNode *parent, DTNode *root, int key)
{

	if (*root != NULL)
	{
		if (contains(*root, key) != 0)
		{
			if (*parent == NULL && isLeaf(*root))
			{
				if (contains(*root, key) == 1)
					(*root)->key_left = (*root)->key_right;
				
				(*root)->key_right = 0; // deixar vazia

				if((*root)->total_keys == 2)
					(*root)->total_keys = 1;
				else
					*root = NULL;
			}
			else if(*parent == NULL)
			{
				if((*root)->total_keys == 2)
				{
					if(contains(*root, key) == 2 && (*root)->right->total_keys == 2)
					{
						(*root)->key_right = (*root)->right->key_left;
						(*root)->right->key_left = (*root)->right->key_right;
						(*root)->right->key_right = 0;
						(*root)->right->total_keys = 1;
					}
					else if(contains(*root, key) == 2 && (*root)->cen->total_keys ==2)
					{
						(*root)->key_right = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->right->total_keys = 1;
					}
					else if(contains(*root, key) == 2 && (*root)->left->total_keys == 2)
					{
						(*root)->key_right = 0;
						(*root)->total_keys = 1;
						(*root)->cen->key_right = (*root)->right->key_left;
						(*root)->cen->total_keys = 2;
						(*root)->right = NULL;
					}
					else if(contains(*root, key) == 2 && (*root)->left->total_keys == 1)
					{
						(*root)->key_right = 0;
						(*root)->total_keys = 1;
						(*root)->cen->key_right = (*root)->right->key_left;
						(*root)->cen->total_keys = 2;
						(*root)->right = NULL;
					}
					else if(contains(*root, key) == 1 && (*root)->cen->total_keys == 2)
					{
						(*root)->key_left = (*root)->cen->key_left;
						(*root)->cen->key_left = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->cen->total_keys = 1;
					}
					else if(contains(*root, key) == 1 && (*root)->left->total_keys == 2)
					{
						(*root)->key_left = (*root)->left->key_right;
						(*root)->left->key_right = 0;
						(*root)->left->total_keys = 1;
					}
					else if (contains(*root, key) == 1 && (*root)->cen->total_keys == 1)
					{
						(*root)->key_left = (*root)->key_right;
						(*root)->key_right = 0;
						(*root)->total_keys = 1;
						(*root)->left->key_right = (*root)->cen->key_left;
						(*root)->left->total_keys = 2;
						(*root)->cen = NULL;
					}
					else if ((*root)->total_keys == 1)
					{
						if((*root)->cen->total_keys == 2)
						{
							(*root)->key_left = (*root)->cen->key_left;
							(*root)->cen->key_left = (*root)->cen->key_right;
							(*root)->cen->key_right = 0;
							(*root)->cen->total_keys = 1;
						}
						else if((*root)->left->total_keys == 2)
						{
							(*root)->key_left = (*root)->left->key_right;
							(*root)->left->key_right = 0;
							(*root)->left->total_keys = 1;
						}
						else
						{
							(*root)->left->key_right = (*root)->cen->key_left;
							(*root)->left->total_keys = 2;
							(*root)->right = NULL;
							*root = (*root)->left; 
						}
					}	
				}
			}
			else if(*parent != NULL && isLeaf(*root))
			{
				if ((*root)->total_keys == 2)
				{
					if(contains(*root, key) == 1)
						(*root)->key_left = (*root)->key_right;
					
					(*root)->key_right = 0;
					(*root)->total_keys = 1;
				}
				else if ((*parent)->total_keys == 2)
				{
					if (key > (*parent)->key_right && (*parent)->cen->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_right;
						(*parent)->key_right = (*parent)->cen->key_right;
						(*parent)->cen->key_right = 0;
						(*parent)->cen->total_keys = 1;
					}
					else if(key > (*parent)->key_right && (*parent)->cen->total_keys == 1)
					{
						(*parent)->cen->key_right = (*parent)->key_right;
						(*parent)->cen->total_keys = 2;
						(*parent)->key_right = 0;
						(*parent)->total_keys = 1;
						*root = NULL; 
					}
					else if(key > (*parent)->key_left && (*parent)->right->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_right;
						(*parent)->key_right = (*parent)->right->key_left;
						(*parent)->right->key_left = (*parent)->right->key_right;
						(*parent)->right->key_right = 0;
						(*parent)->right->total_keys = 1;
					}
					else if(key > (*parent)->key_left && (*parent)->right->total_keys == 1)
					{
						(*root)->key_left = (*parent)->key_right;
						(*root)->key_right = (*parent)->right->key_left;
						(*root)->total_keys = 2;
						(*parent)->key_right = 0;
						(*parent)->total_keys = 1;
						(*parent)->right = NULL;
					}

					else if(key < (*parent)->key_left && (*parent)->cen->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->cen->key_right;
						(*parent)->cen->key_right = 0;
						(*parent)->cen->total_keys = 1;
					}
					else if (key < (*parent)->key_left && (*parent)->right->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->key_right;
						
						(*parent)->key_right = (*parent)->right->key_left;
						(*parent)->right->key_left = (*parent)->right->key_right;
						(*parent)->right->key_right = 0;
						(*parent)->right->total_keys = 1;
					}
					else
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->key_right;
						(*parent)->key_right = 0;
						(*parent)->total_keys = 1;
						(*parent)->cen->key_right = (*parent)->right->key_left;
						(*parent)->cen->total_keys = 2;
						(*parent)->right = NULL;
					}
				}
				
				else
				{
					if (key > (*parent)->key_left && (*parent)->left->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->left->key_right;
						(*parent)->left->key_right = 0;
						(*parent)->left->total_keys = 1;
					}
					else if (key < (*parent)->key_left && (*parent)->cen->total_keys == 2)
					{
						(*root)->key_left = (*parent)->key_left;
						(*parent)->key_left = (*parent)->cen->key_left;
						(*parent)->cen->key_left = (*parent)->cen->key_right;
						(*parent)->cen->key_right = 0;
						(*parent)->cen->total_keys = 1;
					}
					else if(key < (*parent)->key_left)
					{
						(*root)->key_left = (*parent)->key_left;
						(*root)->key_right = (*parent)->cen->key_left;
						(*root)->total_keys = 2;
						*parent = *root;
					}
					else
					{
						(*parent)->left->key_right = (*parent)->key_left;
						(*parent)->left->total_keys = 2;
						*parent = (*parent)->left;
					}	
				}
			}

			else if(*parent != NULL && !isLeaf(*root))
			{
				if(contains(*root, key) == 2)
				{
					if ((*root)->right->total_keys == 2)
					{
						(*root)->key_right = (*root)->right->key_left;
						(*root)->right->key_left = (*root)->right->key_right;
						(*root)->right->key_right = 0;
						(*root)->right->total_keys = 1;
					}
					else if((*root)->cen->total_keys == 2)
					{
						(*root)->key_right = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->cen->total_keys = 1;
					}
					else
					{
						(*root)->cen->key_right = (*root)->right->key_left;
						(*root)->cen->total_keys = 2;
						(*root)->key_right = 0;
						(*root)->total_keys = 2;
						(*root)->right = NULL;
					}	
				}
				else if (contains(*root, key) == 1)
				{
					if ((*root)->cen->total_keys == 2)
					{
						(*root)->key_left = (*root)->cen->key_left;
						(*root)->cen->key_left = (*root)->cen->key_right;
						(*root)->cen->key_right = 0;
						(*root)->cen->total_keys = 1;
					}
					else if((*root)->left->total_keys == 2)
					{
						(*root)->key_left = (*root)->left->key_right;
						(*root)->left->key_right = 0;
						(*root)->left->total_keys = 1;
					}
					else
					{
						(*root)->key_left = (*root)->cen->key_left;
						(*root)->cen->key_left = (*root)->key_right;
						(*root)->key_right = (*root)->right->key_left;
						(*root)->right->key_left = (*root)->right->key_right;
						(*root)->right->key_right = 0;
						(*root)->right->total_keys = 1;
					}
				}
			}
			
		}
		else if (key < (*root)->key_left)
			dttDelete(root, &(*root)->left, key);
		else if((*root)->total_keys == 1)
			dttDelete(root, &(*root)->cen, key);
		else if(key < (*root)->key_right)
			dttDelete(root, &(*root)->cen, key);
		else
			dttDelete(root, &(*root)->right, key);
		
	}

	
}