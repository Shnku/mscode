#include "analysis.h"
#include "scanner_helper.h"
#include "tokenize.h"

#include <stdio.h>
#include <string.h>

void init_analysis(AnalysisStats *stats)
{
    if (stats == NULL)
        return;

    memset(stats, 0, sizeof(AnalysisStats));

    const char *initial_keywords[] = {
        "int", "float", "char", "if", "else", "while", "for",
        "do", "switch", "break", "continue", "return", "long", "double"
    };
    stats->keywordCount = sizeof(initial_keywords) / sizeof(initial_keywords[0]);
    for (int i = 0; i < stats->keywordCount; i++)
    {
        strncpy(stats->keywords[i].name, initial_keywords[i], sizeof(stats->keywords[i].name) - 1);
        stats->keywords[i].frequency = 0;
        stats->keywords[i].numberOfLines = 0;
    }

    const char *initial_operators[] = {
        "++", "--", "+", "-", "*", "/", "+=", "-=",
        "==", "=", "!=", "&&", "||", "<=", "<", ">=", ">"
    };
    stats->operatorCount = sizeof(initial_operators) / sizeof(initial_operators[0]);
    for (int i = 0; i < stats->operatorCount; i++)
    {
        strncpy(stats->operators[i].name, initial_operators[i], sizeof(stats->operators[i].name) - 1);
        stats->operators[i].frequency = 0;
        stats->operators[i].numberOfLines = 0;
    }
}

static void add_line_number(TokenStat *stat, int line)
{
    if (stat->numberOfLines < MAX_TRACKED_LINES)
    {
        stat->lines[stat->numberOfLines++] = line;
    }
}

void record_token_analysis(AnalysisStats *stats, const Token *token)
{
    if (stats == NULL || token == NULL)
        return;

    stats->totalTokens++;

    char lexeme[64];
    int len = token->length < 63 ? token->length : 63;
    strncpy(lexeme, token->start, (size_t)len);
    lexeme[len] = '\0';

    switch (token->type)
    {
        case TOKEN_PREPROCESSOR:
            stats->preprocessorCount++;
            break;

        case TOKEN_NUMBER:
            stats->constantCount++;
            break;

        case TOKEN_STRING:
            stats->stringCount++;
            break;

        case TOKEN_INT:
        case TOKEN_FLOAT:
        case TOKEN_CHAR:
        case TOKEN_IF:
        case TOKEN_ELSE:
        case TOKEN_WHILE:
        case TOKEN_FOR:
        case TOKEN_DO:
        case TOKEN_SWITCH:
        case TOKEN_BREAK:
        case TOKEN_CONTINUE:
        case TOKEN_RETURN:
        case TOKEN_LONG:
        case TOKEN_DOUBLE:
            for (int i = 0; i < stats->keywordCount; i++)
            {
                if (strcmp(lexeme, stats->keywords[i].name) == 0)
                {
                    stats->keywords[i].frequency++;
                    add_line_number(&stats->keywords[i], token->line);
                    break;
                }
            }
            break;

        case TOKEN_IDENTIFIER:
        {
            int found = 0;
            for (int i = 0; i < stats->identifierCount; i++)
            {
                if (strcmp(lexeme, stats->identifiers[i].name) == 0)
                {
                    stats->identifiers[i].frequency++;
                    add_line_number(&stats->identifiers[i], token->line);
                    found = 1;
                    break;
                }
            }
            if (!found && stats->identifierCount < MAX_IDENTIFIERS)
            {
                snprintf(stats->identifiers[stats->identifierCount].name,
                         sizeof(stats->identifiers[stats->identifierCount].name),
                         "%s", lexeme);
                stats->identifiers[stats->identifierCount].frequency = 1;
                stats->identifiers[stats->identifierCount].numberOfLines = 0;
                add_line_number(&stats->identifiers[stats->identifierCount], token->line);
                stats->identifierCount++;
            }
            break;
        }

        case TOKEN_PLUS:
        case TOKEN_PLUS_PLUS:
        case TOKEN_PLUS_EQUAL:
        case TOKEN_MINUS:
        case TOKEN_MINUS_MINUS:
        case TOKEN_MINUS_EQUAL:
        case TOKEN_STAR:
        case TOKEN_SLASH:
        case TOKEN_EQUAL:
        case TOKEN_EQUAL_EQUAL:
        case TOKEN_BANG_EQUAL:
        case TOKEN_AND_AND:
        case TOKEN_PIPE_PIPE:
        case TOKEN_LESS:
        case TOKEN_LESS_EQUAL:
        case TOKEN_GREATER:
        case TOKEN_GREATER_EQUAL:
            for (int i = 0; i < stats->operatorCount; i++)
            {
                if (strcmp(lexeme, stats->operators[i].name) == 0)
                {
                    stats->operators[i].frequency++;
                    add_line_number(&stats->operators[i], token->line);
                    break;
                }
            }
            break;

        default:
            break;
    }
}

void run_analysis_on_source(AnalysisStats *stats, const char *source)
{
    if (stats == NULL || source == NULL)
        return;

    init_analysis(stats);

    Scanner scanner;
    init_scanner(&scanner, source);

    while (1)
    {
        Token token = scan_token(&scanner);
        if (token.type == TOKEN_EOF)
            break;
        record_token_analysis(stats, &token);
    }
}

void print_analysis_report(const AnalysisStats *stats)
{
    if (stats == NULL)
        return;

    int total_kw = 0;
    printf("\n======================================================\n");
    printf("                LEXICAL ANALYSIS REPORT               \n");
    printf("======================================================\n");

    printf("\n--- Keywords Frequency ---\n");
    for (int i = 0; i < stats->keywordCount; i++)
    {
        if (stats->keywords[i].frequency > 0)
        {
            total_kw += stats->keywords[i].frequency;
            printf("  %-12s | Count: %-4d | Lines: ", stats->keywords[i].name, stats->keywords[i].frequency);
            for (int m = 0; m < stats->keywords[i].numberOfLines; m++)
            {
                printf("%d%s", stats->keywords[i].lines[m], (m + 1 < stats->keywords[i].numberOfLines) ? ", " : "");
            }
            printf("\n");
        }
    }
    printf("  Total Keywords: %d\n", total_kw);

    int total_op = 0;
    printf("\n--- Operators Frequency ---\n");
    for (int i = 0; i < stats->operatorCount; i++)
    {
        if (stats->operators[i].frequency > 0)
        {
            total_op += stats->operators[i].frequency;
            printf("  %-12s | Count: %-4d | Lines: ", stats->operators[i].name, stats->operators[i].frequency);
            for (int m = 0; m < stats->operators[i].numberOfLines; m++)
            {
                printf("%d%s", stats->operators[i].lines[m], (m + 1 < stats->operators[i].numberOfLines) ? ", " : "");
            }
            printf("\n");
        }
    }
    printf("  Total Operators: %d\n", total_op);

    int total_id = 0;
    printf("\n--- Identifiers Frequency ---\n");
    for (int i = 0; i < stats->identifierCount; i++)
    {
        total_id += stats->identifiers[i].frequency;
        printf("  %-12s | Count: %-4d | Lines: ", stats->identifiers[i].name, stats->identifiers[i].frequency);
        for (int m = 0; m < stats->identifiers[i].numberOfLines; m++)
        {
            printf("%d%s", stats->identifiers[i].lines[m], (m + 1 < stats->identifiers[i].numberOfLines) ? ", " : "");
        }
        printf("\n");
    }
    printf("  Total Identifiers: %d (Unique: %d)\n", total_id, stats->identifierCount);

    printf("\n--- Additional Metrics ---\n");
    printf("  Preprocessor Directives : %d\n", stats->preprocessorCount);
    printf("  Numeric Constants       : %d\n", stats->constantCount);
    printf("  String Literals         : %d\n", stats->stringCount);
    printf("  Total Tokens Processed  : %d\n", stats->totalTokens);
    printf("======================================================\n\n");
}
