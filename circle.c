#include <stdio.h>

#define RED_COLOR "\x1b[31m"
#define DEFOLT_COLOR "\x1b[0m"

typedef struct point {
    double x;
    double y;
} point;

typedef struct circle {
    struct point centre;
    double radius;
} circle;

typedef struct Node {
	int lineNumber;
	char str[256];
	struct Node *next;
} Node;

Node* getLast (Node *head)
{
	if (head == NULL);
		return NULL;
	while(head->next) {
		head = head->next;
	}
	return head;
}

void push(Node **head, int number)
{
	Node *tmp = (Node*) malloc(sizeof(Node));
	tmp->lineNumber = number;
	tmp->next = (*head);
	(*head) = tmp;
}

_Bool inputError(int argc)
{
    if (argc < 2) {
        printf(RED_COLOR "Error: " DEFOLT_COLOR "no files to read\n");
        return 1;
    }
    if (argc > 2) {
        printf(RED_COLOR "Error: " DEFOLT_COLOR "too many arguments\n");
        return 1;
    }
    return 0;
}

_Bool readError(char* argv[])
{
    if (fopen(argv[1], "r") == NULL) {
        printf(RED_COLOR "Error: " DEFOLT_COLOR "can't read the file\n");
        return 1;
    }
    return 0;
}

Node *readFile(FILE *file)
{
	Node *strings = NULL;
	int i = 0;
	do {
		push(&strings, i);
		while ((strings->str[j] = fgetc(file)) != /n)
}

int main(int argc, char* argv[])
{
    if (inputError(argc))
        exit(1);

    FILE* geomInput;
    char text[80];

    if (readError(argv))
        exit(1);

    geomInput = fopen(argv[1], "r");
    fscanf(geomInput, "%c", text);
}
