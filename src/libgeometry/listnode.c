#include <libgeometry/listnode.h>

int pop(listnode** head)
{
    listnode* prev = NULL;
    unsigned int number;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    number = prev->number;
    (*head) = (*head)->next;
    free(prev);
    return number;
}

listnode* get_last(listnode* head)
{
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void push_back(listnode** head, unsigned int number)
{
    listnode* last = get_last(*head);
    listnode* tmp = (listnode*)malloc(sizeof(listnode));
    tmp->number = number;
    tmp->next = NULL;
    if (last == NULL) {
        *head = tmp;
        return;
    }
    last->next = tmp;
}