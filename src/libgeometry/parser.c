#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

void circle_output(int number, circle current_circle)
{
    printf("%d. circle(%f %f, %f)",
           number,
           current_circle.centre.x,
           current_circle.centre.y,
           current_circle.radius);

    printf("\n");

    printf("    perimetr = %f\n", (2 * M_PI * current_circle.radius));
    printf("    area = %f\n",
           (M_PI * current_circle.radius * current_circle.radius));
    printf("\n");
}

void read_line(char* str, unsigned int* line, unsigned int* count, _Bool key)
{
    unsigned int buffer_line = *line;
    unsigned int buffer_count = *count;
    circle current_circle;
    unsigned int column = 0;
    if (empty_string(str, column)) {
        buffer_line++;
        *line = buffer_line;
        return;
    }
    if (!circle_handling(str, &column)) {
        circle_error(str, *line, column, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }
    if (!bracket_handling(str, &column, 1)) {
        bracket_error(str, *line, column, 1, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }

    if (!double_handling(str, &column, &(current_circle.centre.x))) {
        double_error(str, *line, column, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }
    if (!double_handling(str, &column, &(current_circle.centre.y))) {
        double_error(str, *line, column, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }

    if (!comma_handling(str, &column)) {
        comma_error(str, *line, column, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }
    if (!double_handling(str, &column, &(current_circle.radius))) {
        double_error(str, *line, column, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }
    if (!bracket_handling(str, &column, 2)) {
        bracket_error(str, *line, column, 2, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }
    if (!end_handling(str, column)) {
        unexpected_token_error(str, *line, column, key);
        buffer_line++;
        *line = buffer_line;
        return;
    }
    circle_output(*count, current_circle);
    buffer_count++;
    *count = buffer_count;
    buffer_line++;
    *line = buffer_line;
}

void stdin_read()
{
    char str[256];
    unsigned int line = 1, count = 1;
    while (1) {
        printf("Введите данные о фигуре в формате WKT или 'q' для выхода\n");
        fgets(str, 255, stdin);
        if (there_is_symbol(str, 0, 'q'))
            break;
        read_line(str, &line, &count, 0);
    }
}

void file_read(char* file_name)
{
    FILE* file;
    file = fopen(file_name, "r");
    if (file == NULL) {
        read_error();
        exit(1);
    }
    char str[256];
    unsigned int line = 1, count = 1;
    while (!feof(file)) {
        fgets(str, 255, file);
        read_line(str, &line, &count, 1);
    }
    fclose(file);
}