#ifndef SCANNER_HELPER_H
#define SCANNER_HELPER_H

typedef struct
{
    const char *start;
    const char *current;
    int line;
    int column;
} Scanner;

void init_scanner(Scanner *scanner, const char *source);
char peek_current_char(const Scanner *scanner);
char peek_next_char(const Scanner *scanner);
char advance_char(Scanner *scanner);
int match_char(Scanner *scanner, char expected);
int is_at_end_position(const Scanner *scanner);
void skip_whitespace_and_comments(Scanner *scanner);

#endif /* SCANNER_HELPER_H */
