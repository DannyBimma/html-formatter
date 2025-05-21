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
        return 2;
    }

    // Write output file name
    strcpy(output_filename, argv[1]);
    strcat(output_filename, ".html");

    // Open output
    output_file = fopen(output_filename, "w");
    if (!output_file)
    {
        fprintf(stderr, "Error: Could not create output file.\n Please check file permissions! %s\n", output_filename);
        fclose(input_file);
        return 3;
    }

    parse_file(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    printf("HTML successfully formatted! \nOutput has been written to %s.\n", output_filename);

    return 0;
}

// Process input file and write to output file
void parse_file(FILE *input, FILE *output)
{
    int c;
    int body_flag = 0; // Flag to check if loop is within body tag

    write_header(output); // TODO: Define

    while ((c = fgetc(input)) != EOF)
    {
        /* Check if current character is start of formatter string */
        if (c == 'h' || c == 'p' || c == 's' || c == 'e')
        {
            /* Check for formatter string */
            if (check_formatter(input, output, (char)c) == 0)
            {
                /* If not, write current character */
                fputc(c, output);
            }
        }
        else
        {
            /* Write current character to output file */
            fputc(c, output);
        }
    }

    write_footer(output); // TODO: Define
}