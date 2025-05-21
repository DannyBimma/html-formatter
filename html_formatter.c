#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void display_usage(char *program_name);
void write_header(FILE *output);
void write_footer(FILE *output);
void parse_file(FILE *input, FILE *output);
int formatter_check(FILE *input, FILE *output, char first_char);

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

void display_usage(char *program_name)
{
    fprintf(stderr, "Usage: %s <input_file>\n", program_name);
    fprintf(stderr, "The program will create a new .html file with the same name.\n");
}

void write_header(FILE *output)
{
    fputs("<!DOCTYPE html>\n", output);
    fputs("<html lang=\"en\">\n", output);
    fputs("<head>\n", output);
    fputs("    <meta charset=\"UTF-8\">\n", output);
    fputs("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n", output);
    fputs("    <title>Blog Content</title>\n", output);
    fputs("</head>\n", output);
    fputs("<body>\n", output);
}

void write_footer(FILE *output)
{
    fputs("</body>\n", output);
    fputs("</html>\n", output);
}

// Process input file and write to output file
void parse_file(FILE *input, FILE *output)
{
    int c;
    int body_flag = 0; // Flag to check if loop is within body tag

    write_header(output);

    while ((c = fgetc(input)) != EOF)
    {
        /* Check if current character is start of formatter string */
        if (c == 'h' || c == 'p' || c == 's' || c == 'e')
        {
            /* Check for formatter string */
            if (formatter_check(input, output, (char)c) == 0)
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

    write_footer(output);
}

int formatter_check(FILE *input, FILE *output, char first_char)
{
    long file_pos;
    char buffer[5]; // 4 charater formatter + null terminator
    int i, c;

    // Save current file position
    file_pos = ftell(input);

    buffer[0] = first_char;

    // Check for body formatter sequence
    if (first_char == 's' || first_char == 'e')
    {
        for (i = 1; i <= 3; i++)
        {
            c = fgetc(input);
            if (c == EOF)
            {
                // Can't read any more chars, not a body formatter
                fseek(input, file_pos, SEEK_SET);
                return 0;
            }
            buffer[i] = (char)c;
        }
        buffer[4] = '\0'; // Terminate string

        // Already done by write_header() and write_footer()
        if (strcmp(buffer, "s..s") == 0)
        {
            return 1;
        }
        else if (strcmp(buffer, "e..e") == 0)
        {
            return 1;
        }
    }
    // Check for heading formatter sequence
    else if (first_char == 'h')
    {
        for (i = 1; i <= 3; i++)
        {
            c = fgetc(input);
            if (c == EOF)
            {
                // Can't read any more chars, not heading formatter
                fseek(input, file_pos, SEEK_SET);
                return 0;
            }
            buffer[i] = (char)c;
        }
        buffer[4] = '\0';

        if (strcmp(buffer, "h1-o") == 0)
        {
            fputs("<h1>", output);
            return 1;
        }
        else if (strcmp(buffer, "h1-c") == 0)
        {
            fputs("</h1>", output);
            return 1;
        }
        else if (strcmp(buffer, "h2-o") == 0)
        {
            fputs("<h2>", output);
            return 1;
        }
        else if (strcmp(buffer, "h2-c") == 0)
        {
            fputs("</h2>", output);
            return 1;
        }
        else if (strcmp(buffer, "h3-o") == 0)
        {
            fputs("<h3>", output);
            return 1;
        }
        else if (strcmp(buffer, "h3-c") == 0)
        {
            fputs("</h3>", output);
            return 1;
        }
        else if (strcmp(buffer, "h4-o") == 0)
        {
            fputs("<h4>", output);
            return 1;
        }
        else if (strcmp(buffer, "h4-c") == 0)
        {
            fputs("</h4>", output);
            return 1;
        }
        else if (strcmp(buffer, "h5-o") == 0)
        {
            fputs("<h5>", output);
            return 1;
        }
        else if (strcmp(buffer, "h5-c") == 0)
        {
            fputs("</h5>", output);
            return 1;
        }
    }
    // Paragraph formatter
    else if (first_char == 'p')
    {
        for (i = 1; i <= 2; i++)
        {
            c = fgetc(input);
            if (c == EOF)
            {
                // Can't read any more chars, not a paragraph formatter
                fseek(input, file_pos, SEEK_SET);
                return 0;
            }
            buffer[i] = (char)c;
        }
        buffer[3] = '\0'; // Terminate string

        if (strcmp(buffer, "p-o") == 0)
        {
            fputs("<p>", output);
            return 1;
        }
        else if (strcmp(buffer, "p-c") == 0)
        {
            fputs("</p>", output);
            return 1;
        }
    }

    fseek(input, file_pos, SEEK_SET);
    printf("No formatters found for %s\n", buffer);

    return 0;
}