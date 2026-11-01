#include "analysis.h"
#include "scanner_helper.h"
#include "tokenize.h"

#include <stdio.h>
#include <string.h>

// ---------- Data structures ----------

// Helper to add occurrence (line & column) to a TokenStat entry
static void add_occurrence(TokenStat *stat, int line, int column)
{
    if (stat->numberOfLines < MAX_TRACKED_LINES)
    {
        stat->lines[stat->numberOfLines] = line;
        stat->columns[stat->numberOfLines] = column;
        stat->numberOfLines++;
    }
}

// Compatibility wrapper (old calls)
static void add_line_number(TokenStat *stat, int line)
{
    add_occurrence(stat, line, 0);
}

// ---------- Initialization ----------

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

    // preprocessor, numbers, strings start empty; counts zero
}

// ---------- Token entry helpers ----------

static int find_or_create_entry(TokenStat *array, int *count, const char *lexeme)
{
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(array[i].name, lexeme) == 0)
            return i;
    }
    if (*count < MAX_PREPROCESSOR) // safe upper bound; same max for all tables
    {
        strncpy(array[*count].name, lexeme, sizeof(array[*count].name) - 1);
        array[*count].frequency = 0;
        array[*count].numberOfLines = 0;
        return (*count)++;
    }
    return -1; // overflow (should not happen)
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
        {
            stats->preprocessorDirectives++;
            int idx = find_or_create_entry(stats->preprocessor, &stats->preprocessorCount, lexeme);
            if (idx >= 0)
                add_occurrence(&stats->preprocessor[idx], token->line, token->column);
            break;
        }
        case TOKEN_NUMBER:
        {
            stats->constantCount++;
            int idx = find_or_create_entry(stats->numbers, &stats->numberCount, lexeme);
            if (idx >= 0)
            {
                add_occurrence(&stats->numbers[idx], token->line, token->column);
                strncpy(stats->numbers[idx].value, lexeme, sizeof(stats->numbers[idx].value) - 1);
                strcpy(stats->numbers[idx].typeName, "numeric");
            }
            break;
        }
        case TOKEN_STRING:
        {
            stats->stringLiteralCount++;
            int idx = find_or_create_entry(stats->strings, &stats->stringCount, lexeme);
            if (idx >= 0)
            {
                add_occurrence(&stats->strings[idx], token->line, token->column);
                strncpy(stats->strings[idx].value, lexeme, sizeof(stats->strings[idx].value) - 1);
                strcpy(stats->strings[idx].typeName, "string");
            }
            break;
        }
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
                    add_occurrence(&stats->keywords[i], token->line, token->column);
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
                    add_occurrence(&stats->identifiers[i], token->line, token->column);
                    found = 1;
                    break;
                }
            }
            if (!found && stats->identifierCount < MAX_IDENTIFIERS)
            {
                // Basic attributes – will be enriched later
                strncpy(stats->identifiers[stats->identifierCount].name, lexeme, sizeof(stats->identifiers[stats->identifierCount].name) - 1);
                stats->identifiers[stats->identifierCount].frequency = 1;
                stats->identifiers[stats->identifierCount].numberOfLines = 0;
                add_occurrence(&stats->identifiers[stats->identifierCount], token->line, token->column);
                strcpy(stats->identifiers[stats->identifierCount].typeName, "int"); // placeholder
                strcpy(stats->identifiers[stats->identifierCount].scope, "global");
                stats->identifiers[stats->identifierCount].address = 0;
                stats->identifiers[stats->identifierCount].isFunction = 0;
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
                    add_occurrence(&stats->operators[i], token->line, token->column);
                    break;
                }
            }
            break;
        default:
            break;
    }
}

// ---------- Attribute enrichment ----------

static void assign_identifier_attributes(AnalysisStats *stats, Token *tokens, int tokenCount)
{
    static int nextAddress = 0;
    for (int i = 0; i < stats->identifierCount; i++)
    {
        TokenStat *id = &stats->identifiers[i];
        // Find first occurrence of this identifier in token stream
        for (int t = 0; t < tokenCount; t++)
        {
            Token tk = tokens[t];
            if (tk.type == TOKEN_IDENTIFIER)
            {
                char curLex[64];
                int l = tk.length < 63 ? tk.length : 63;
                strncpy(curLex, tk.start, (size_t)l);
                curLex[l] = '\0';
                if (strcmp(curLex, id->name) == 0)
                {
                    // Look backward for a type keyword (simple heuristic)
                    if (t > 0)
                    {
                        Token prev = tokens[t-1];
                        switch (prev.type)
                        {
                            case TOKEN_INT:    strcpy(id->typeName, "int"); break;
                            case TOKEN_FLOAT:  strcpy(id->typeName, "float"); break;
                            case TOKEN_CHAR:   strcpy(id->typeName, "char"); break;
                            case TOKEN_DOUBLE: strcpy(id->typeName, "double"); break;
                            case TOKEN_LONG:   strcpy(id->typeName, "long"); break;
                            default: break;
                        }
                    }
                    // Address allocation for variables (skip functions)
                    if (!id->isFunction && id->address == 0)
                    {
                        id->address = nextAddress;
                        nextAddress += 4; // assume 4‑byte slots
                    }
                    // Detect if identifier is a function (look ahead for '(' )
                    if (t+1 < tokenCount && tokens[t+1].type == TOKEN_LPAREN)
                    {
                        id->isFunction = 1;
                        strcpy(id->scope, "global"); // functions are global in this simple model
                        // For functions you could store parameter list etc. in extra
                    }
                    break;
                }
            }
        }
    }
}

// ---------- Symbol table printing ----------

static void print_symbol_table_section(const char *title, TokenStat *entries, int count)
{
    if (count <= 0) return;
    printf("\n--- %s ---\n", title);
    for (int i = 0; i < count; i++)
    {
        if (entries[i].frequency > 0)
        {
            printf("  %-12s | Type: %-8s | Scope: %-8s | Addr: %-4d | Func: %d | Count: %-4d | Lines: ",
                   entries[i].name,
                   entries[i].typeName,
                   entries[i].scope,
                   entries[i].address,
                   entries[i].isFunction,
                   entries[i].frequency);
            for (int m = 0; m < entries[i].numberOfLines; m++)
                printf("%d:%d%s", entries[i].lines[m], entries[i].columns[m], (m + 1 < entries[i].numberOfLines) ? ", " : "");
            printf("\n");
        }
    }
}

static void print_symbol_table(const AnalysisStats *stats)
{
    printf("\n=== Symbol Table (All Tokens) ===\n");
    print_symbol_table_section("Keywords", (TokenStat *)stats->keywords, stats->keywordCount);
    print_symbol_table_section("Operators", (TokenStat *)stats->operators, stats->operatorCount);
    print_symbol_table_section("Identifiers", (TokenStat *)stats->identifiers, stats->identifierCount);
    print_symbol_table_section("Preprocessor Directives", (TokenStat *)stats->preprocessor, stats->preprocessorCount);
    print_symbol_table_section("Numeric Constants", (TokenStat *)stats->numbers, stats->numberCount);
    print_symbol_table_section("String Literals", (TokenStat *)stats->strings, stats->stringCount);
    printf("================================================================\n");
}

// ---------- Main analysis flow ----------

#define MAX_TOKENS 1024

void run_analysis_on_source(AnalysisStats *stats, const char *source)
{
    if (stats == NULL || source == NULL)
        return;

    init_analysis(stats);

    Scanner scanner;
    init_scanner(&scanner, source);

    Token tokens[MAX_TOKENS];
    int tokenCount = 0;

    while (1)
    {
        Token token = scan_token(&scanner);
        if (token.type == TOKEN_EOF)
            break;
        if (tokenCount < MAX_TOKENS)
            tokens[tokenCount++] = token;
        record_token_analysis(stats, &token);
    }

    assign_identifier_attributes(stats, tokens, tokenCount);
}

void print_analysis_report(const AnalysisStats *stats)
{
    if (stats == NULL)
        return;

    int total_kw = 0;
    printf("\n======================================================\n");
    printf("                LEXICAL ANALYSIS REPORT               \n");
    printf("======================================================\n");

    // Keywords
    printf("\n--- Keywords Frequency ---\n");
    for (int i = 0; i < stats->keywordCount; i++)
    {
        if (stats->keywords[i].frequency > 0)
        {
            total_kw += stats->keywords[i].frequency;
            printf("  %-12s | Count: %-4d | Lines: ", stats->keywords[i].name, stats->keywords[i].frequency);
            for (int m = 0; m < stats->keywords[i].numberOfLines; m++)
                printf("%d%s", stats->keywords[i].lines[m], (m + 1 < stats->keywords[i].numberOfLines) ? ", " : "");
            printf("\n");
        }
    }
    printf("  Total Keywords: %d\n", total_kw);

    // Operators
    int total_op = 0;
    printf("\n--- Operators Frequency ---\n");
    for (int i = 0; i < stats->operatorCount; i++)
    {
        if (stats->operators[i].frequency > 0)
        {
            total_op += stats->operators[i].frequency;
            printf("  %-12s | Count: %-4d | Lines: ", stats->operators[i].name, stats->operators[i].frequency);
            for (int m = 0; m < stats->operators[i].numberOfLines; m++)
                printf("%d%s", stats->operators[i].lines[m], (m + 1 < stats->operators[i].numberOfLines) ? ", " : "");
            printf("\n");
        }
    }
    printf("  Total Operators: %d\n", total_op);

    // Identifiers
    int total_id = 0;
    printf("\n--- Identifiers Frequency ---\n");
    for (int i = 0; i < stats->identifierCount; i++)
    {
        total_id += stats->identifiers[i].frequency;
        printf("  %-12s | Count: %-4d | Lines: ", stats->identifiers[i].name, stats->identifiers[i].frequency);
        for (int m = 0; m < stats->identifiers[i].numberOfLines; m++)
            printf("%d%s", stats->identifiers[i].lines[m], (m + 1 < stats->identifiers[i].numberOfLines) ? ", " : "");
        printf("\n");
    }
    printf("  Total Identifiers: %d (Unique: %d)\n", total_id, stats->identifierCount);

    // Preprocessor
    printf("\n--- Preprocessor Directives Frequency ---\n");
    for (int i = 0; i < stats->preprocessorCount; i++)
        if (stats->preprocessor[i].frequency > 0)
            printf("  %-12s | Count: %-4d | Lines: %d\n", stats->preprocessor[i].name, stats->preprocessor[i].frequency, stats->preprocessor[i].lines[0]);

    // Numbers
    printf("\n--- Numeric Constants Frequency ---\n");
    for (int i = 0; i < stats->numberCount; i++)
        if (stats->numbers[i].frequency > 0)
            printf("  %-12s | Count: %-4d | Lines: %d\n", stats->numbers[i].name, stats->numbers[i].frequency, stats->numbers[i].lines[0]);

    // Strings
    printf("\n--- String Literals Frequency ---\n");
    for (int i = 0; i < stats->stringCount; i++)
        if (stats->strings[i].frequency > 0)
            printf("  %-12s | Count: %-4d | Lines: %d\n", stats->strings[i].name, stats->strings[i].frequency, stats->strings[i].lines[0]);

    // Additional Metrics
    printf("\n--- Additional Metrics ---\n");
    printf("  Preprocessor Directives : %d\n", stats->preprocessorDirectives);
    printf("  Numeric Constants       : %d\n", stats->constantCount);
    printf("  String Literals         : %d\n", stats->stringLiteralCount);
    printf("  Total Tokens Processed  : %d\n", stats->totalTokens);
    printf("======================================================\n\n");

    // Unified Symbol Table
    print_symbol_table(stats);
}
