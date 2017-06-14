#include <stdio.h>
#include <stdlib.h>
#include "SList.h"
#include <string.h>
int main()
{
    int i;
    SLIST_HEADER * root = createSList();
    for (i=1;i<=3;i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        if (NULL != tmp)
            insertFirst(root, tmp);
    }

    pr_SList(root);

    free(root);

    return EXIT_SUCCESS;
}
