#include <libgeometry/lexer.h>

_Bool input_error(int argc)
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

_Bool read_error(char* argv[])
{
    if (fopen(argv[1], "r") == NULL) {
        printf(RED_COLOR "Error: " DEFOLT_COLOR "can't read the file\n");
        return 1;
    }

    return 0;
}

_Bool is_circle(char* str)
{
    char circleStr[7] = "circle";
    char testStr[256];
    int i = 0;

    while (1) {
        if ((str[i] == ' ') || (str[i] == '('))
            break;

        if (i == 79)
            return 0;

        testStr[i] = tolower(str[i]);
        i++;
    }

    i--;

    for (i = 0; i <= 5; i++) {
        if (circleStr[i] != testStr[i])
            return 0;
    }

    if (str[6] == ')')
        return 1;

    if ((str[6] != ' ') && (str[6] != '('))
        return 0;

    return 1;
}

char* copy_part_of_string(char* str, int start, int end)
{
    if (start == end)
        return NULL;
    char* copy = (char*)malloc(256);
    if (copy == NULL)
        return NULL;
    for (int i = start; i < end; i++) {
        copy[i - start] = str[i];
    }
    copy[end] = '\0';
    return copy;
}

unsigned int skip_digits(char* str, unsigned int index)
{
    while (1) {
        if (!isdigit(str[index]))
            return index;
        index++;
    }
}

_Bool there_is_symbol(char* str, unsigned int index, char symbol)
{
    if (str[index] == symbol)
        return 1;
    return 0;
}

_Bool is_double(char* str, int start, int end)
{
    char* test_string;
    unsigned int index = 0;

    test_string = copy_part_of_string(str, start, end);
    if (!test_string)
        return 0;

    if (index == skip_digits(test_string, index))
        return 0;
    index = skip_digits(test_string, index);

    if (there_is_symbol(test_string, index, '\0'))
        return 1;

    if (!there_is_symbol(test_string, index, '.'))
        return 0;
    index++;

    if (there_is_symbol(test_string, index, '\0'))
        return 0;

    if (index == skip_digits(test_string, index))
        return 0;
    index = skip_digits(test_string, index);

    if (there_is_symbol(test_string, index, '\0')) {
        free(test_string);
        return 1;
    }
    free(test_string);
    return 0;
}

void circleError(char* str, int line, int column)
{
    _Bool flag = 0;
    int i = 0;
    while (1) {
        if (str[i] == '\n')
            break;

        if ((str[i] == EOF) || (str[i] == '\0')) {
            flag = 1;
            break;
        }

        i++;
    }

    printf("%s", str);

    if (flag)
        printf("\n");

    for (i = 1; i < column; i++)
        printf(" ");

    printf("^\n");

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " at line %d, column %d: expected 'circle'\n",
           line,
           column);
    exit(1);
}

void lineError(int line)
{
    printf(RED_COLOR "Error" DEFOLT_COLOR " at line %d: cannot read the line\n",
           line);
    exit(1);
}

void bracketError(char* str, int line, int column, int key)
{
    char brackets[3] = "()";
    _Bool flag = 0;
    int i = 0;
    column++;

    while (1) {
        if (str[i] == '\n')
            break;

        if ((str[i] == EOF) || (str[i] == '\0')) {
            flag = 1;
            break;
        }
        i++;
    }

    printf("%s", str);

    if (flag)
        printf("\n");

    for (i = 1; i < column; i++)
        printf(" ");

    printf("^\n");

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " in line %d, column %d: expected '%c'\n",
           line,
           column,
           brackets[key]);
    exit(1);
}

void commaError(char* str, int line, int column)
{
    column++;
    _Bool flag = 0;
    int i = 0;

    while (1) {
        if (str[i] == '\n')
            break;

        if ((str[i] == EOF) || (str[i] == '\0')) {
            flag = 1;
            break;
        }
        i++;
    }

    printf("%s", str);

    if (flag)
        printf("\n");

    for (i = 1; i < column; i++)
        printf(" ");

    printf("^\n");

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " at line %d, column %d: expected comma\n",
           line,
           column);
    exit(1);
}

void doubleError(char* str, int line, int column)
{
    column++;
    _Bool flag = 0;
    int i = 0;

    while (1) {
        if (str[i] == '\n')
            break;

        if ((str[i] == EOF) || (str[i] == '\0')) {
            flag = 1;
            break;
        }
        i++;
    }
    printf("%s", str);

    if (flag)
        printf("\n");

    for (i = 1; i < column; i++)
        printf(" ");

    printf("^\n");

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " in line %d, column %d: expected '<double>'\n",
           line,
           column + 1);
    exit(1);
}

void unTokError(char* str, int line, int column)
{
    _Bool flag = 0;
    int i = 0;

    while (1) {
        if (str[i] == '\n')
            break;

        if ((str[i] == EOF) || (str[i] == '\0')) {
            flag = 1;
            break;
        }
        i++;
    }

    printf("%s", str);

    if (flag)
        printf("\n");

    for (i = 1; i < column; i++)
        printf(" ");

    printf("^\n");

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " in line %d, column %d: unexpected token\n",
           line,
           column + 1);
    exit(1);
}