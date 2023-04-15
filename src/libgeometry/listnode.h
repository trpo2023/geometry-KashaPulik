#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct listnode {
    unsigned int number;
    struct listnode* next;
} listnode;

int pop(listnode** head);
listnode* get_last(listnode* head);
void push_back(listnode** head, unsigned int number);