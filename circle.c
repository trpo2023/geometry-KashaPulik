#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

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

_Bool isCircle(char *str)
{
    char circleStr[7] = "circle";
    char testStr[256];
    int i = 0;

    while(1) {

        if((str[i] == ' ') || (str[i] == '('))
            break;

        if(i == 79)
            return 0;

        testStr[i] = tolower(str[i]);
        i++;
    }

    i--;

    if(i > 5)
        return 0;
    
    for(i = 0; i <= 5; i++){
        if(circleStr[i] != testStr[i])
            return 0;
    }

    return 1;
}

_Bool isDouble(char *str, int start, int end)
{
    if(start == end)
        return 0;

    char testString[256];
    int j, i = 0;

    for(j = start; j < end; j++) {
        testString[i] = str[j];
        i++;
    }

    testString[i] = '\0';
    j = 0;

    while(1)
    {
        if(!isdigit(testString[j]))
            break;
        j++;
    }

    if(j == 0)
        return 0;

    if(testString[j] == '\0')
        return 1;

    if(testString[j] == '.') {
        j++;
        if(testString[j] == '\0')
            return 0;
    } else {
        return 0;
    }

    while(1)
    {
        if(!isdigit(testString[j])){
            if(testString[j] == '\0')
                return 1;
            return 0;
        }
        j++;
    }
}

void circleError(char *str, int line, int column)
{
    _Bool flag = 0;
    int i = 0;
    while(1) {
        if(str[i] == '\n')
            break;

        if((str[i] == EOF) || (str[i] == '\0')) {
            flag = 1;
            break;
        }

        i++;
    }

    printf("%s", str);

    if(flag)
        printf("\n");

    for(i = 1; i < column; i++)
        printf(" ");

    printf("^\n");

    printf(RED_COLOR "Error" DEFOLT_COLOR " at line %d, column %d: expected 'circle'\n", line, column);
    exit(1);
}

void lineError(int line)
{
    printf(RED_COLOR "Error" DEFOLT_COLOR " at line %d: cannot read the line\n", line);
    exit(1);
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
