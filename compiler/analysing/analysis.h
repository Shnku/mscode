#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "token.h"

#define MAX_TRACKED_LINES 256
#define MAX_IDENTIFIERS 256
#define MAX_PREPROCESSOR 64
#define MAX_NUMBERS 256
#define MAX_STRINGS 256

/* Generic token statistics entry */
typedef struct {
    char name[64];          // lexeme
    char typeName[32];      // data type (for identifiers, constants, etc.)
    char scope[32];         // scope (global, function name, block)
    int address;            // simulated address/offset
    int isFunction;         // 1 if identifier is a function
    char value[64];         // literal value for constants / strings
    int frequency;          // occurrence count
    int lines[MAX_TRACKED_LINES];   // line numbers
    int columns[MAX_TRACKED_LINES]; // column numbers (parallel to lines)
    int numberOfLines;      // number of stored occurrences
    char extra[128];        // additional attributes (e.g., param list)
} TokenStat;

typedef struct {
    /* Keywords */
    TokenStat keywords[14];
    int keywordCount;

    /* Operators */
    TokenStat operators[17];
    int operatorCount;

    /* Identifiers */
    TokenStat identifiers[MAX_IDENTIFIERS];
    int identifierCount;

    /* Preprocessor directives */
    TokenStat preprocessor[MAX_PREPROCESSOR];
    int preprocessorCount;

    /* Numeric constants */
    TokenStat numbers[MAX_NUMBERS];
    int numberCount;

    /* String literals */
    TokenStat strings[MAX_STRINGS];
    int stringCount;

    /* Summary counters (backward compatible) */
    int preprocessorDirectives;
    int constantCount;
    int stringLiteralCount;
    int totalTokens;
} AnalysisStats;

void init_analysis(AnalysisStats *stats);
void record_token_analysis(AnalysisStats *stats, const Token *token);
void run_analysis_on_source(AnalysisStats *stats, const char *source);
void print_analysis_report(const AnalysisStats *stats);

#endif /* ANALYSIS_H */