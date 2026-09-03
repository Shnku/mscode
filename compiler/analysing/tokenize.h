#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "scanner_helper.h"
#include "token.h"

Token scan_token(Scanner *scanner);
void print_token(const Token *token);

#endif /* TOKENIZE_H */
