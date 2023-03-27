#include <libgeometry/interface.h>
#include <libgeometry/lexer.h>

void print_arrow(unsigned int column)
{
    while (column > 1) {
        printf(" ");
        column--;
    }
    printf("^\n");
}

void default_error_output(
        char* str, unsigned int line, unsigned int column, _Bool key)
{
    column++;
    if (key) {
        printf("%s", str);
        if (this_is_the_end(str))
            printf("\n");
    }

    print_arrow(column);

    printf(RED_COLOR "Error" DEFOLT_COLOR " at line %d, column %d: ",
           line,
           column);
}

void input_error()
{
    printf(RED_COLOR "Error: " DEFOLT_COLOR "too many arguments\n");
}

void read_error()
{
    printf(RED_COLOR "Error: " DEFOLT_COLOR "can't read the file\n");
}

void circle_error(char* str, unsigned int line, unsigned int column, _Bool key)
{
    default_error_output(str, line, column, key);
    printf("expected 'circle'\n\n");
}

void bracket_error(
        char* str,
        unsigned int line,
        unsigned int column,
        unsigned int number,
        _Bool key)
{
    number--;
    char brackets[3] = "()";
    default_error_output(str, line, column, key);
    printf("expected '%c'\n\n", brackets[number]);
}

void comma_error(char* str, unsigned int line, unsigned int column, _Bool key)
{
    default_error_output(str, line, column, key);
    printf("expected comma\n\n");
}

void double_error(char* str, unsigned int line, unsigned int column, _Bool key)
{
    default_error_output(str, line, column, key);
    printf("expected '<double>'\n\n");
}

void unexpected_token_error(
        char* str, unsigned int line, unsigned int column, _Bool key)
{
    default_error_output(str, line, column, key);
    printf("unexpected token\n\n");
}