#include <libgeometry/interface.h>
#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

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

void circles_output(unsigned int count, circle* circles)
{
    listnode* intersects = NULL;
    for (unsigned int number = 0; number < count; number++) {
        intersects = count_instersects(intersects, circles, number, count);
        circle_output(number, circles[number], &intersects);
    }
}

void circle_output(int number, circle current_circle, listnode** intersects)
{
    printf("%d. circle(%.1f %.1f, %.1f)",
           number + 1,
           current_circle.centre.x,
           current_circle.centre.y,
           current_circle.radius);

    printf("\n");

    printf("    perimetr = %f\n", (2 * M_PI * current_circle.radius));
    printf("    area = %f\n",
           (M_PI * current_circle.radius * current_circle.radius));
    printf("    intersects:\n");
    if (*intersects == NULL) {
        printf("      none\n");
    }
    while (*intersects != NULL) {
        printf("      %d. circle\n", pop(intersects));
    }
    printf("\n");
}
