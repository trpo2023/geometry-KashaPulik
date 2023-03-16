#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

int main(int argc, char* argv[])
{
    if (input_error(argc))
        exit(1);

    FILE* geomInput;

    if (read_error(argv))
        exit(1);

    geomInput = fopen(argv[1], "r");
    read_file(geomInput);
}