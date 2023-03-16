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

_Bool is_this_the_end(char* str)
{
    while (1) {
        if (*str == '\n')
            return 0;

        if ((*str == EOF) || (*str == '\0')) {
            return 1;
        }
        str++;
    }
}

void circle_output(int number, char* str, circle current_circle)
{
    printf("%d. circle(%f %f, %f)",
           number,
           current_circle.centre.x,
           current_circle.centre.y,
           current_circle.radius);

    if (!is_this_the_end(str))
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
            lineError(line);
        column++;
    }
    return column;
}

int read_double(char* str, int line, int column)
{
    int check = column;
    while ((str[column] == '.') || (isdigit(str[column]))) {
        if (column == 79)
            lineError(line);
        column++;
    }
    if (column == check)
        doubleError(str, line, column);
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
            lineError(line);
        }

        if (!is_circle(str)) {
            circleError(str, line, column + 1);
        }

        column = 6;

        column = skip_space(str, line, column);

        if (str[column] != '(')
            bracketError(str, line, column, 0);

        column++;

        column = skip_space(str, line, column);

        end = read_double(str, line, column);

        if (str[end] != ' ')
            doubleError(str, line, column);

        if (is_double(str, column, end)) {
            circle.centre.x = string_to_double(str, column, end);
        } else {
            doubleError(str, line, column);
        }

        column = skip_space(str, line, end);

        end = read_double(str, line, column);

        if ((str[end] != ' ') && (str[end] != ','))
            commaError(str, line, end);

        if (is_double(str, column, end)) {
            circle.centre.y = string_to_double(str, column, end);
        } else {
            doubleError(str, line, column);
        }

        if (str[end] == ',') {
            end++;
            column = skip_space(str, line, end);
        } else {
            column = skip_space(str, line, end);
            if (str[column] != ',')
                commaError(str, line, column - 1);
            if (str[column] == ',')
                column++;
            if (str[column] == ' ')
                column = skip_space(str, line, column + 1);
        }

        end = read_double(str, line, column);

        if ((str[end] != ' ') && (str[end] != ')'))
            bracketError(str, line, end, 1);

        if (is_double(str, column, end)) {
            circle.radius = string_to_double(str, column, end);
        } else {
            doubleError(str, line, column);
        }

        column = skip_space(str, line, end);
        if (str[column] != ')')
            bracketError(str, line, column, 1);

        column = skip_space(str, line, column + 1);
        if ((str[column] != '\n') && (str[column] != '\0')
            && (str[column] != EOF))
            unTokError(str, line, column + 1);
        circle_output(line, str, circle);
        line++;
    }
}