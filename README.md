# HTML Formatter Documentation

## Overview

This "HTML Formatter" is a program I built in C that converts plain text files, with my own made-up format specifiers, into a HTML file that can be uploaded straight to the web.

A few months ago I started a lil developer blog on GitHub Pages with plain ole HTML, CSS, and JS. I'd like to blog more often, but the process of replacing the content of the HTML page every time is very annoying... the web is annoying, in general. It'll be much easier for me to write my heart's content into a plain text file, throw in my custom format specifiers, and simply have the program shit out a functional HTML page to publish.

This certainly wouldn't be particularly useful for real bloggers and content creators, or anyone else for that matter. I didn't even check to see if a real solution existed before I started building this, so please don't use it, use a real CDN. To be honest, I just wanted an excuse to write a couple hundred lines of C, and now I'm a happy coder boi 🙂

So to surmise: The program reads a text.txt file, identifies special format specifiers/strings, and replaces each of them with the corresponding HTML tags while wrapping the entire content in HTML5 boilerplate code.

## Features

- **Full HTML5 Document Generation**: Creates complete HTML documents with your typical headers, DOCTYPE, meta tags, and structure
- **Multiple Header Levels**: Supports H1 through H5 headings
- **Paragraph Support**: Converts paragraph markers to HTML paragraph tags
- **Content Boundaries**: Uses special markers to define the start and end of blog content
- **Memory Safe**: Written in C89-compliant code with careful memory management
- **Cross-Platform**: Works on my machine and probably any other system with a C compiler... maybe

## Installation

### Prerequisites

- A C compiler (GCC, Clang, or similar)
- Basic command line knowledge

### Compilation

```bash
gcc -o html_formatter html_formatter.c
```

For additional compiler warnings (recommended for development):

```bash
gcc -Wall -Wextra -std=c89 -o html_formatter html_formatter.c
```

## Usage

### Basic Syntax

```bash
./html_formatter <input_file>
```

### Arguments

- `<input_file>`: Path to the text file containing the content with format specifiers/strings

### Output

The program creates a new file with the same name as the input file but with `.html` extension appended to the filename. This could be better but I got tired and settled for good enough.

**Example:**

- Input: `myblog.txt`
- Output: `myblog.txt.html`

## Format Specifier/String Reference

### Content Boundaries

| Formatter | Purpose               | HTML Output                              |
| --------- | --------------------- | ---------------------------------------- |
| `s..s`    | Start of blog content | (Marker removed, content placed in body) |
| `e..e`    | End of blog content   | (Marker removed, content placed in body) |

### Header Tags

| Formatter | Purpose        | HTML Output |
| --------- | -------------- | ----------- |
| `h1-o`    | Opening H1 tag | `<h1>`      |
| `h1-c`    | Closing H1 tag | `</h1>`     |
| `h2-o`    | Opening H2 tag | `<h2>`      |
| `h2-c`    | Closing H2 tag | `</h2>`     |
| `h3-o`    | Opening H3 tag | `<h3>`      |
| `h3-c`    | Closing H3 tag | `</h3>`     |
| `h4-o`    | Opening H4 tag | `<h4>`      |
| `h4-c`    | Closing H4 tag | `</h4>`     |
| `h5-o`    | Opening H5 tag | `<h5>`      |
| `h5-c`    | Closing H5 tag | `</h5>`     |

### Paragraph Tags

| Formatter | Purpose               | HTML Output |
| --------- | --------------------- | ----------- |
| `p-o`     | Opening paragraph tag | `<p>`       |
| `p-c`     | Closing paragraph tag | `</p>`      |

## Example Usage

### Input File (`myblog.txt`)

```
s..s
h1-o Welcome to My Tech Blog h1-c

p-o
Today I want to share some thoughts about programming and software development: AI is good but way too over hyped, Python kinda sucks and I don't know why it persist, and C is the greatest language to ever exist.
p-c

h2-o Why I Chose C for This Project h2-c

p-o
C is a powerful language that gives you direct control over memory management, and it keeps abstraction to a minimal so you can always see what's happening... I call it WYSIWYG programming, here are some key benefits:
p-c

h3-o Performance h3-c
p-o
C programs typically run very fast because they compile to efficient machine code. I know this because, inefficient as I wrote it, this program is still fast AF!!
p-c

h3-o Learning Value h3-c
p-o
Understanding C helps you to either appreciate or absolutely hate higher-level languages and their sea of abstractions. I fell into the latter category 😔
p-c

h2-o Conclusion h2-c
p-o
"In summation, C doesn't know who you're racing because it's already at the finish line with the flag waving." - Jay-Z
p-c

e..e
```

### Generated Output (`myblog.txt.html`)

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Blog Content</title>
  </head>
  <body>
    <h1>Welcome to My Tech Blog</h1>

    <p>
      Today I want to share some thoughts about programming and software
      development: AI is good but way too over hyped, Python kinda sucks and I
      don't know why it persist, and C is the greatest language to ever exist.
    </p>

    <h2>Why I Chose C for This Project</h2>

    <p>
      C is a powerful language that gives you direct control over memory
      management, and it keeps abstraction to a minimal so you can always see
      what's happening... I call it WYSIWYG programming, here are some key
      benefits:
    </p>

    <h3>Performance</h3>
    <p>
      C programs typically run very fast because they compile to efficient
      machine code. I know this because, inefficient as I wrote it, this program
      is still fast AF!!
    </p>

    <h3>Learning Value</h3>
    <p>
      Understanding C helps you to either appreciate or absolutely hate
      higher-level languages and their sea of abstractions. I fell into the
      latter category 😔
    </p>

    <h2>Conclusion</h2>
    <p>
      "In summation, C doesn't know who you're racing because it's already at
      the finish line with the flag waving." - Jay-Z
    </p>
  </body>
</html>
```

## Command Line Examples

### Basic Usage

```bash
# Parse a blog post
./html_formatter my_article.txt

# Parse multiple files (using shell loop)
for file in *.txt; do ./html_formatter "$file"; done
```

### Error Handling Examples

```bash
# No arguments provided
./html_formatter
# Output: Usage: ./html_formatter <input_file>

# Too many arguments
./html_formatter file1.txt file2.txt
# Output: Usage: ./html_formatter <input_file>

# File doesn't exist
./html_formatter nonexistent.txt
# Output: Error: Cannot open file nonexistent.txt for reading.
```

## Technical Implementation Details

### Architecture

I simply used a **character-by-character parsing approach** with the following key components:

1. **Main Function**: Handles command line arguments, file I/O, and program flow
2. **Process File Function**: Reads input char by char to identify potential formatters
3. **Check Formatter Function**: Validates and processes formatter strings
4. **HTML Generation Functions**: Creates full HTML5 boilerplate

### Memory Management

- **Static Allocation**: Fixed-size buffers to avoid malloc/free complexity
- **File Handle Management**: Properly opens and closes all file resources
- **Buffer Safety**: All string operations use appropriate buffer sizes with null termination

### Performance Characteristics

- **Time Complexity**: O(n) where n is the input file size... major skill issues 😔
- **Space Complexity**: O(1) - uses constant memory regardless of file size
- **Suitable for**: Files of any practical size (limited only by available disk space)

## Best Practices for Content Creation

### File Organization

```
project/
├── content/
│   ├── post1.txt
│   ├── post2.txt
│   └── post3.txt
├── html_formatter
└── output/
    ├── post1.txt.html
    ├── post2.txt.html
    └── post3.txt.html
```

### Content Structure Guidelines

1. **Always use content boundaries**:

   ```
   s..s
   [your content here]
   e..e
   ```

2. **Proper heading hierarchy**:

   ```
   h1-o Main Title h1-c
   h2-o Section Title h2-c
   h3-o Subsection h3-c
   ```

3. **Paragraph formatting**:
   ```
   p-o
   Each paragraph should be wrapped in paragraph tags for proper spacing and styling.
   p-c
   ```

### Workflow Automation

Create a shell script to process multiple files:

```bash
#!/bin/bash
# process_blog.sh

for file in content/*.txt; do
    if [ -f "$file" ]; then
        echo "Processing $file..."
        ./html_formatter "$file"
        # Move output to desired directory
        mv "$file.html" output/
    fi
done
echo "All files processed!"
```

## Troubleshooting

### Common Issues

**Problem**: Format specifiers/strings appear in the output file instead of being converted

- **Cause**: Typo in formatter (e.g., `h1-0` instead of `h1-o`)
- **Solution**: Double-check formatter spelling, especially 'o' vs '0'

**Problem**: Program says "Cannot open file for reading"

- **Cause**: File doesn't exist or does not have read permissions
- **Solution**: Check file path and permissions with `ls -la filename.txt`

**Problem**: HTML output looks wrong in browser

- **Cause**: Missing content boundaries (`s..s` and `e..e`)
- **Solution**: Always include the content boundary markers

**Problem**: Compilation errors

- **Cause**: Missing compiler or non-C89 compliant environment
- **Solution**: Ensure GCC is installed: `gcc --version`

### Debugging Tips

1. **Check input file format**:

   ```bash
   cat -n myblog.txt  # Shows line numbers and content
   ```

2. **Verify output**:

   ```bash
   head -n 20 myblog.txt.html  # Check HTML structure
   ```

3. **Test with minimal example**:

   ```
   s..s

   h1-o Test h1-c

   p-o
   Hello world!
   p-c

   e..e
   ```

## Extending the Program

### Adding New Formatters

To add new format specifiers/strings, modify the `check_formatter()` function:

1. Add new condition for the first character
2. Read appropriate number of characters
3. Add string comparison and HTML output
4. Update the character check in `process_file()`

### Example: Adding Bold Text Support

```c
/* In check_formatter(), add this case: */
if (strcmp(buffer, "b-o") == 0) {
    fputs("<strong>", output);
    return 1;
} else if (strcmp(buffer, "b-c") == 0) {
    fputs("</strong>", output);
    return 1;
}
```

## Performance Tips

1. **Process files individually**: Better error handling and memory usage
2. **Use appropriate buffer sizes**: The current 256-character filename buffer handles most cases, because there's always that one a-hole 🙄
3. **Consider file size**: While the program handles large files, extremely large files (>100MB) may be slow

## Related Tools and Integration

### Text Editors

- **Vim/Neovim**: Create syntax highlighting for formatter strings
- **VS Code**: Use snippets for common formatter patterns
- **Emacs**: Create custom mode for blog formatting

### Automation Scripts

The program integrates well with:

- **Make**: For build automation
- **Shell scripts**: For batch processing
- **Git hooks**: For automatic HTML generation on commits

## License and Contributing

This program is designed as a learning tool for it's creator, and an example of C programming best practices. Feel free to modify and extend it for your own needs. Like seriously, just do whatever you want with this code!!

### Learning Resources

- **C Programming**: "The C Programming Language" aka "White Book C" by Kernighan and Ritchie

---

_Happy formatting! Building this was a tonne of fun, I could feel my desire to create my own programming language growing with each line lol_
