#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

double string_to_double(char* str, int start, int end)
{
    char doublestr[16];
    int i, j = 0;
    for (i = start; i <= end; i++) {
        doublestr[j] = str[i];
        j++;
    }
    return atof(doublestr);
}

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

int skip_space(char* str, int line, int column)
{
    while (str[column] == ' ') {
        if (column == 79)
            line_error(line);
        column++;
    }
    return column;
}

int skip_double(char* str, int line, int column)
{
    int check = column;
    while ((str[column] == '.') || (isdigit(str[column]))) {
        if (column == 79)
            line_error(line);
        column++;
    }
    if (column == check)
        double_error(str, line, column);
    return column;
}

void read_file(FILE* file)
{
    char str[256];
    int line = 1;
    int column;
    int end;
    circle circle;
    while (!feof(file)) {
        column = 0;

        if (fgets(str, 255, file) == NULL) {
            line_error(line);
        }
        if (empty_string(str)) {
            line++;
            continue;
        }
        if (!is_circle(str)) {
            circle_error(str, line, column + 1);
        }

        column = 6;

        column = skip_space(str, line, column);

        if (!there_is_symbol(str, column, '('))
            bracket_error(str, line, column, 0);

        column++;

        column = skip_space(str, line, column);

        end = skip_double(str, line, column);

        if (!there_is_symbol(str, end, ' '))
            double_error(str, line, column);

        if (is_double(str, column, end)) {
            circle.centre.x = string_to_double(str, column, end);
        } else {
            double_error(str, line, column);
        }

        column = skip_space(str, line, end);

        end = skip_double(str, line, column);

        if (!there_is_symbol(str, end, ' ') && !there_is_symbol(str, end, ','))
            comma_error(str, line, end);

        if (is_double(str, column, end)) {
            circle.centre.y = string_to_double(str, column, end);
        } else {
            double_error(str, line, column);
        }

        if (there_is_symbol(str, end, ',')) {
            end++;
            column = skip_space(str, line, end);
        } else {
            column = skip_space(str, line, end);
            if (!there_is_symbol(str, column, ','))
                comma_error(str, line, column - 1);
            if (there_is_symbol(str, column, ','))
                column++;
            if (there_is_symbol(str, column, ' '))
                column = skip_space(str, line, column + 1);
        }

        end = skip_double(str, line, column);

        if (!there_is_symbol(str, end, ' ') && !there_is_symbol(str, end, ')'))
            bracket_error(str, line, end, 1);

        if (is_double(str, column, end)) {
            circle.radius = string_to_double(str, column, end);
        } else {
            double_error(str, line, column);
        }

        column = skip_space(str, line, end);
        if (!there_is_symbol(str, column, ')'))
            bracket_error(str, line, column, 1);

        column = skip_space(str, line, column + 1);
        if (!there_is_symbol(str, column, '\n')
            && !there_is_symbol(str, column, '\0')
            && !there_is_symbol(str, column, EOF))
            unexpected_token_error(str, line, column + 1);
        circle_output(line, circle);
        line++;
    }
}