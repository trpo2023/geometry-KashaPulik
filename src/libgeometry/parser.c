#include <libgeometry/interface.h>
#include <libgeometry/lexer.h>
#include <libgeometry/listnode.h>
#include <libgeometry/parser.h>

listnode* count_instersects(
        listnode* intersects,
        circle* circles,
        unsigned int number,
        unsigned int count)
{
    for (unsigned int i = 0; i < count; i++) {
        if (i == number)
            continue;
        if (pow(circles[i].radius - circles[number].radius, 2)
                    <= (pow(circles[i].centre.x - circles[number].centre.x, 2)
                        + pow(circles[i].centre.y - circles[number].centre.y,
                              2))
            && (pow(circles[i].centre.x - circles[number].centre.x, 2)
                + pow(circles[i].centre.y - circles[number].centre.y, 2))
                    <= pow(circles[i].radius + circles[number].radius, 2))
            push_back(&intersects, i + 1);
    }
    return intersects;
}

void read_line(
        char* str,
        unsigned int* line,
        unsigned int* count,
        _Bool key,
        circle** circles,
        unsigned int* buffer_size)
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
    if (buffer_count == *buffer_size) {
        *buffer_size *= 2;
        *circles = realloc(*circles, *buffer_size * sizeof(circle));
    }
    buffer_count++;
    (*circles)[buffer_count - 1] = current_circle;
    *count = buffer_count;
    buffer_line++;
    *line = buffer_line;
}

void stdin_read()
{
    char str[256];
    unsigned int line = 1, count = 0, buffer_size = 8;
    circle* circles = (circle*)malloc(buffer_size * sizeof(circle));
    while (1) {
        printf("Введите данные о фигуре в формате WKT или 'q' для выхода\n");
        printf("Введите 'x' чтобы вывести информацию о фигурах\n");
        fgets(str, 255, stdin);
        if (there_is_symbol(str, 0, 'q'))
            return;
        if (there_is_symbol(str, 0, 'x'))
            break;
        read_line(str, &line, &count, 0, &circles, &buffer_size);
    }
    circles_output(count, circles);
    free(circles);
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
    unsigned int line = 1, count = 1, buffer_size = 1;
    circle* circles = (circle*)malloc(buffer_size * sizeof(circle));
    while (!feof(file)) {
        fgets(str, 255, file);
        read_line(str, &line, &count, 1, &circles, &buffer_size);
    }
    fclose(file);
    circles_output(count, circles);
    free(circles);
}