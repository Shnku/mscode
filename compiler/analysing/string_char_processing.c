#include "string_char_processing.h"

int is_alphabet(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int is_alphanumeric(char c)
{
    return is_alphabet(c) || is_digit(c);
}

int is_whitespace(char c)
{
    return c == ' ' || c == '\r' || c == '\t';
}

int is_newline(char c)
{
    return c == '\n';
}

int is_operator_char(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '=' || c == '<' || c == '>' || c == '!' ||
            c == '&' || c == '|' || c == '%' || c == '^');
}

int is_delimiter_char(char c)
{
    return (c == '(' || c == ')' || c == '{' || c == '}' ||
            c == '[' || c == ']' || c == ',' || c == ';' ||
            c == ':' || c == '.');
}