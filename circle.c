#include<stdio.h>

#define RED_COLOR "\x1b[31m"
#define DEFOLT_COLOR "\x1b[0m"

typedef struct point{
	int x;
	int y;
}point;

typedef struct circle{
	struct point centre;
	int radius;
}circle;

