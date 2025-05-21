#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *input_file;
    FILE *output_file;
    char output_filename[256];

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open input
    input_file = fopen(argv[1], "r");
    if (!input_file)
    {
        fprintf(stderr, "Error: Could not open file.\n Please check path or file name! %s\n", argv[1]);
        return 1;
    }
}