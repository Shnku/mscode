#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    // End of file / Error
    TOKEN_EOF,
    TOKEN_ERROR,

    // Preprocessor Directive
    TOKEN_PREPROCESSOR,

    // Literals & Identifiers
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,

    // Keywords (14 keywords matching analysis_program)
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_CHAR,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_DO,
    TOKEN_SWITCH,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_RETURN,
    TOKEN_LONG,
    TOKEN_DOUBLE,

    // Operators
    TOKEN_PLUS,          // +
    TOKEN_PLUS_PLUS,     // ++
    TOKEN_PLUS_EQUAL,    // +=
    TOKEN_MINUS,         // -
    TOKEN_MINUS_MINUS,   // --
    TOKEN_MINUS_EQUAL,   // -=
    TOKEN_STAR,          // *
    TOKEN_SLASH,         // /
    TOKEN_EQUAL,         // =
    TOKEN_EQUAL_EQUAL,   // ==
    TOKEN_BANG_EQUAL,    // !=
    TOKEN_AND_AND,       // &&
    TOKEN_PIPE_PIPE,     // ||
    TOKEN_LESS,          // <
    TOKEN_LESS_EQUAL,    // <=
    TOKEN_GREATER,       // >
    TOKEN_GREATER_EQUAL, // >=

    // Delimiters
    TOKEN_LPAREN,        // (
    TOKEN_RPAREN,        // )
    TOKEN_LBRACE,        // {
    TOKEN_RBRACE,        // }
    TOKEN_LBRACKET,      // [
    TOKEN_RBRACKET,      // ]
    TOKEN_COMMA,         // ,
    TOKEN_SEMICOLON      // ;
} TokenType;

typedef struct
{
    TokenType type;
    const char *start;
    int length;
    int line;
    int column;
} Token;

const char *token_type_to_string(TokenType type);

#endif /* TOKEN_H */
