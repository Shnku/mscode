#include "tokenize.h"
#include "string_char_processing.h"

#include <stdio.h>
#include <string.h>

const char *token_type_to_string(TokenType type)
{
    switch (type)
    {
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
        case TOKEN_PREPROCESSOR: return "PREPROCESSOR";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_STRING: return "STRING";
        case TOKEN_INT: return "KEYWORD_INT";
        case TOKEN_FLOAT: return "KEYWORD_FLOAT";
        case TOKEN_CHAR: return "KEYWORD_CHAR";
        case TOKEN_IF: return "KEYWORD_IF";
        case TOKEN_ELSE: return "KEYWORD_ELSE";
        case TOKEN_WHILE: return "KEYWORD_WHILE";
        case TOKEN_FOR: return "KEYWORD_FOR";
        case TOKEN_DO: return "KEYWORD_DO";
        case TOKEN_SWITCH: return "KEYWORD_SWITCH";
        case TOKEN_BREAK: return "KEYWORD_BREAK";
        case TOKEN_CONTINUE: return "KEYWORD_CONTINUE";
        case TOKEN_RETURN: return "KEYWORD_RETURN";
        case TOKEN_LONG: return "KEYWORD_LONG";
        case TOKEN_DOUBLE: return "KEYWORD_DOUBLE";
        case TOKEN_PLUS: return "OP_PLUS";
        case TOKEN_PLUS_PLUS: return "OP_PLUS_PLUS";
        case TOKEN_PLUS_EQUAL: return "OP_PLUS_EQUAL";
        case TOKEN_MINUS: return "OP_MINUS";
        case TOKEN_MINUS_MINUS: return "OP_MINUS_MINUS";
        case TOKEN_MINUS_EQUAL: return "OP_MINUS_EQUAL";
        case TOKEN_STAR: return "OP_STAR";
        case TOKEN_SLASH: return "OP_SLASH";
        case TOKEN_EQUAL: return "OP_EQUAL";
        case TOKEN_EQUAL_EQUAL: return "OP_EQUAL_EQUAL";
        case TOKEN_BANG_EQUAL: return "OP_BANG_EQUAL";
        case TOKEN_AND_AND: return "OP_AND_AND";
        case TOKEN_PIPE_PIPE: return "OP_PIPE_PIPE";
        case TOKEN_LESS: return "OP_LESS";
        case TOKEN_LESS_EQUAL: return "OP_LESS_EQUAL";
        case TOKEN_GREATER: return "OP_GREATER";
        case TOKEN_GREATER_EQUAL: return "OP_GREATER_EQUAL";
        case TOKEN_LPAREN: return "DELIM_LPAREN";
        case TOKEN_RPAREN: return "DELIM_RPAREN";
        case TOKEN_LBRACE: return "DELIM_LBRACE";
        case TOKEN_RBRACE: return "DELIM_RBRACE";
        case TOKEN_LBRACKET: return "DELIM_LBRACKET";
        case TOKEN_RBRACKET: return "DELIM_RBRACKET";
        case TOKEN_COMMA: return "DELIM_COMMA";
        case TOKEN_SEMICOLON: return "DELIM_SEMICOLON";
        default: return "UNKNOWN";
    }
}

static TokenType check_keyword(const char *start, int length)
{
    static const struct
    {
        const char *word;
        TokenType type;
    } keywords[] = {
        {"int", TOKEN_INT},
        {"float", TOKEN_FLOAT},
        {"char", TOKEN_CHAR},
        {"if", TOKEN_IF},
        {"else", TOKEN_ELSE},
        {"while", TOKEN_WHILE},
        {"for", TOKEN_FOR},
        {"do", TOKEN_DO},
        {"switch", TOKEN_SWITCH},
        {"break", TOKEN_BREAK},
        {"continue", TOKEN_CONTINUE},
        {"return", TOKEN_RETURN},
        {"long", TOKEN_LONG},
        {"double", TOKEN_DOUBLE},
    };

    int count = (int)(sizeof(keywords) / sizeof(keywords[0]));
    for (int i = 0; i < count; i++)
    {
        if ((int)strlen(keywords[i].word) == length &&
            strncmp(start, keywords[i].word, (size_t)length) == 0)
        {
            return keywords[i].type;
        }
    }
    return TOKEN_IDENTIFIER;
}

static Token make_token(TokenType type, Scanner *scanner, int start_line, int start_col)
{
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start);
    token.line = start_line;
    token.column = start_col;
    return token;
}

Token scan_token(Scanner *scanner)
{
    skip_whitespace_and_comments(scanner);

    scanner->start = scanner->current;
    int start_line = scanner->line;
    int start_col = scanner->column;

    if (is_at_end_position(scanner))
    {
        return make_token(TOKEN_EOF, scanner, start_line, start_col);
    }

    char c = advance_char(scanner);

    // Preprocessor directive: #...
    if (c == '#')
    {
        while (!is_at_end_position(scanner) && !is_newline(peek_current_char(scanner)))
        {
            advance_char(scanner);
        }
        return make_token(TOKEN_PREPROCESSOR, scanner, start_line, start_col);
    }

    // Identifiers & Keywords
    if (is_alphabet(c))
    {
        while (is_alphanumeric(peek_current_char(scanner)))
        {
            advance_char(scanner);
        }
        int length = (int)(scanner->current - scanner->start);
        TokenType type = check_keyword(scanner->start, length);
        return make_token(type, scanner, start_line, start_col);
    }

    // Numeric constants
    if (is_digit(c))
    {
        while (is_digit(peek_current_char(scanner)))
        {
            advance_char(scanner);
        }
        // Handle fractional part if present
        if (peek_current_char(scanner) == '.' && is_digit(peek_next_char(scanner)))
        {
            advance_char(scanner); // consume '.'
            while (is_digit(peek_current_char(scanner)))
            {
                advance_char(scanner);
            }
        }
        return make_token(TOKEN_NUMBER, scanner, start_line, start_col);
    }

    // String literals
    if (c == '"')
    {
        while (!is_at_end_position(scanner) && peek_current_char(scanner) != '"' && !is_newline(peek_current_char(scanner)))
        {
            if (peek_current_char(scanner) == '\\' && peek_next_char(scanner) != '\0')
            {
                advance_char(scanner); // consume escape backslash
            }
            advance_char(scanner);
        }

        if (peek_current_char(scanner) == '"')
        {
            advance_char(scanner); // consume closing quote
            return make_token(TOKEN_STRING, scanner, start_line, start_col);
        }
        return make_token(TOKEN_ERROR, scanner, start_line, start_col);
    }

    // Character literals
    if (c == '\'')
    {
        while (!is_at_end_position(scanner) && peek_current_char(scanner) != '\'' && !is_newline(peek_current_char(scanner)))
        {
            if (peek_current_char(scanner) == '\\' && peek_next_char(scanner) != '\0')
            {
                advance_char(scanner);
            }
            advance_char(scanner);
        }
        if (peek_current_char(scanner) == '\'')
        {
            advance_char(scanner); // consume closing quote
            return make_token(TOKEN_STRING, scanner, start_line, start_col);
        }
        return make_token(TOKEN_ERROR, scanner, start_line, start_col);
    }

    // Operators and Delimiters
    switch (c)
    {
        // Delimiters
        case '(': return make_token(TOKEN_LPAREN, scanner, start_line, start_col);
        case ')': return make_token(TOKEN_RPAREN, scanner, start_line, start_col);
        case '{': return make_token(TOKEN_LBRACE, scanner, start_line, start_col);
        case '}': return make_token(TOKEN_RBRACE, scanner, start_line, start_col);
        case '[': return make_token(TOKEN_LBRACKET, scanner, start_line, start_col);
        case ']': return make_token(TOKEN_RBRACKET, scanner, start_line, start_col);
        case ',': return make_token(TOKEN_COMMA, scanner, start_line, start_col);
        case ';': return make_token(TOKEN_SEMICOLON, scanner, start_line, start_col);

        // Operators
        case '+':
            if (match_char(scanner, '+')) return make_token(TOKEN_PLUS_PLUS, scanner, start_line, start_col);
            if (match_char(scanner, '=')) return make_token(TOKEN_PLUS_EQUAL, scanner, start_line, start_col);
            return make_token(TOKEN_PLUS, scanner, start_line, start_col);

        case '-':
            if (match_char(scanner, '-')) return make_token(TOKEN_MINUS_MINUS, scanner, start_line, start_col);
            if (match_char(scanner, '=')) return make_token(TOKEN_MINUS_EQUAL, scanner, start_line, start_col);
            return make_token(TOKEN_MINUS, scanner, start_line, start_col);

        case '*': return make_token(TOKEN_STAR, scanner, start_line, start_col);
        case '/': return make_token(TOKEN_SLASH, scanner, start_line, start_col);

        case '=':
            if (match_char(scanner, '=')) return make_token(TOKEN_EQUAL_EQUAL, scanner, start_line, start_col);
            return make_token(TOKEN_EQUAL, scanner, start_line, start_col);

        case '<':
            if (match_char(scanner, '=')) return make_token(TOKEN_LESS_EQUAL, scanner, start_line, start_col);
            return make_token(TOKEN_LESS, scanner, start_line, start_col);

        case '>':
            if (match_char(scanner, '=')) return make_token(TOKEN_GREATER_EQUAL, scanner, start_line, start_col);
            return make_token(TOKEN_GREATER, scanner, start_line, start_col);

        case '!':
            if (match_char(scanner, '=')) return make_token(TOKEN_BANG_EQUAL, scanner, start_line, start_col);
            return make_token(TOKEN_ERROR, scanner, start_line, start_col);

        case '&':
            if (match_char(scanner, '&')) return make_token(TOKEN_AND_AND, scanner, start_line, start_col);
            return make_token(TOKEN_ERROR, scanner, start_line, start_col);

        case '|':
            if (match_char(scanner, '|')) return make_token(TOKEN_PIPE_PIPE, scanner, start_line, start_col);
            return make_token(TOKEN_ERROR, scanner, start_line, start_col);

        default:
            return make_token(TOKEN_ERROR, scanner, start_line, start_col);
    }
}

void print_token(const Token *token)
{
    if (token == NULL)
        return;

    printf("[Line %2d, Col %2d] %-18s '%.*s'\n",
           token->line,
           token->column,
           token_type_to_string(token->type),
           token->length,
           token->start);
}
