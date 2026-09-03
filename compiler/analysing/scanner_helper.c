#include "scanner_helper.h"
#include "string_char_processing.h"

#include <stddef.h>

void init_scanner(Scanner *scanner, const char *source)
{
    if (scanner == NULL)
        return;
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
    scanner->column = 1;
}

char peek_current_char(const Scanner *scanner)
{
    if (scanner == NULL || scanner->current == NULL)
        return '\0';
    return *scanner->current;
}

char peek_next_char(const Scanner *scanner)
{
    if (scanner == NULL || scanner->current == NULL || *scanner->current == '\0')
        return '\0';
    return *(scanner->current + 1);
}

char advance_char(Scanner *scanner)
{
    if (scanner == NULL || scanner->current == NULL || *scanner->current == '\0')
        return '\0';

    char c = *scanner->current;
    scanner->current++;
    if (c == '\n')
    {
        scanner->line++;
        scanner->column = 1;
    }
    else
    {
        scanner->column++;
    }
    return c;
}

int match_char(Scanner *scanner, char expected)
{
    if (scanner == NULL || is_at_end_position(scanner))
        return 0;

    if (*scanner->current != expected)
        return 0;

    advance_char(scanner);
    return 1;
}

int is_at_end_position(const Scanner *scanner)
{
    if (scanner == NULL || scanner->current == NULL)
        return 1;
    return *scanner->current == '\0';
}

void skip_whitespace_and_comments(Scanner *scanner)
{
    if (scanner == NULL)
        return;

    while (!is_at_end_position(scanner))
    {
        char c = peek_current_char(scanner);
        if (is_whitespace(c) || is_newline(c))
        {
            advance_char(scanner);
        }
        else if (c == '/' && peek_next_char(scanner) == '/')
        {
            // Skip single-line comment
            while (!is_at_end_position(scanner) && !is_newline(peek_current_char(scanner)))
            {
                advance_char(scanner);
            }
        }
        else if (c == '/' && peek_next_char(scanner) == '*')
        {
            // Skip multi-line block comment
            advance_char(scanner); // consume '/'
            advance_char(scanner); // consume '*'
            while (!is_at_end_position(scanner))
            {
                if (peek_current_char(scanner) == '*' && peek_next_char(scanner) == '/')
                {
                    advance_char(scanner); // consume '*'
                    advance_char(scanner); // consume '/'
                    break;
                }
                advance_char(scanner);
            }
        }
        else
        {
            break;
        }
    }
}
