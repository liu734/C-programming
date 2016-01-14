
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{

    struct lnode * head;
    struct lnode *tail;
    struct lnode * node;
    /* list starts empty */
    head = tail = NULL;

    newNode(&head, &tail, "ONE", 1);
    newNode(&head, &tail, "TWO", 1);
    newNode(&head, &tail, "THREE", 1);


    /* now let's print every node */
    for (node = head; node != NULL; node = nodeGetNext(node)) {
        /* increment its count */
        nodeIncCount(node);

        /* then show it */
        printf("%s: %d %d\n", nodeGetWord(node), nodeGetLine(node), nodeGetCount(node));
    }

    return 0;
}