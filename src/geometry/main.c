#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        stdin_read();
    }
    if (argc == 2) {
        file_read(argv[1]);
    }
    if (argc > 2) {
        input_error();
        exit(1);
    }
    return 0;
}