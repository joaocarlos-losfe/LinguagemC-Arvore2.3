#include <stdio.h>
#include <stdlib.h>

#include "dtt.h"

int main()
{
    
    DTT tree = dttStart();
    tree->root = NULL;

    int var_temp;

    ddtInsert(NULL, &tree->root, 400, &var_temp);
    ddtInsert(NULL, &tree->root, 200, &var_temp);
    ddtInsert(NULL, &tree->root, 300, &var_temp);
    ddtInsert(NULL, &tree->root, 1000, &var_temp);
    ddtInsert(NULL, &tree->root, 1, &var_temp);
    ddtInsert(NULL, &tree->root, 500, &var_temp);
    ddtInsert(NULL, &tree->root, 600, &var_temp);
    ddtInsert(NULL, &tree->root, 30, &var_temp);
    ddtInsert(NULL, &tree->root, 3, &var_temp);
    ddtInsert(NULL, &tree->root, 5, &var_temp);
    ddtInsert(NULL, &tree->root, 2, &var_temp);
    ddtInsert(NULL, &tree->root, 10, &var_temp);
    ddtInsert(NULL, &tree->root, 0, &var_temp);

    dttDelete(NULL, &tree->root, 100);


    int count = 0;

    getTotalNodes(tree->root, &count);

    dttPrint(tree->root);    
    
    DTNode node = dttSeach(tree->root, 4);

    if (node != NULL)
    {
        printf("\nencontrado: ");
        dtNodePrint(node);
    }
    else
    {
        printf("\nNAO encontrado\n");
    }


    printf("\ncompilado... total de nos: %d", count);
    
    return 0;
}

