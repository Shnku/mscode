#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "token.h"

#define MAX_TRACKED_LINES 256
#define MAX_IDENTIFIERS 256

typedef struct
{
    char name[64];
    int frequency;
    int lines[MAX_TRACKED_LINES];
    int numberOfLines;
} TokenStat;

typedef struct
{
    TokenStat keywords[14];
    int keywordCount;

    TokenStat operators[17];
    int operatorCount;

    TokenStat identifiers[MAX_IDENTIFIERS];
    int identifierCount;

    int preprocessorCount;
    int constantCount;
    int stringCount;
    int totalTokens;
} AnalysisStats;

void init_analysis(AnalysisStats *stats);
void record_token_analysis(AnalysisStats *stats, const Token *token);
void run_analysis_on_source(AnalysisStats *stats, const char *source);
void print_analysis_report(const AnalysisStats *stats);

#endif /* ANALYSIS_H */
