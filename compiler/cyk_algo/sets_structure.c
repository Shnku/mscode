#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    char left;
    char right[3];
} Rule;

// Use unsigned int bitmask as the Set data structure (Bit 0 = 'A', Bit 1 = 'B', ...)
typedef unsigned int Set;

// ==========================================
// 1. Core Set Operations
// ==========================================

static inline Set set_empty(void)
{
    return 0;
}

static inline Set set_add(Set s, char non_term)
{
    return s | (1U << (non_term - 'A'));
}

static inline bool set_contains(Set s, char non_term)
{
    return (s & (1U << (non_term - 'A'))) != 0;
}

static inline Set set_union(Set s1, Set s2)
{
    return s1 | s2;
}

void print_set(Set s)
{
    printf("{ ");
    for (char c = 'A'; c <= 'Z'; c++)
    {
        if (set_contains(s, c))
        {
            printf("%c ", c);
        }
    }
    printf("}");
}

// ==========================================
// 2. Grammar Matching & Cartesian Product Operations
// ==========================================

// Base Case: Find all Non-Terminals A where A -> terminal
Set get_terminal_lhs(char terminal, const Rule grammar[], int rule_count)
{
    Set result = set_empty();
    for (int r = 0; r < rule_count; r++)
    {
        if (grammar[r].right[1] == '\0' && grammar[r].right[0] == terminal)
        {
            result = set_add(result, grammar[r].left);
        }
    }
    return result;
}

// Cartesian Product + Grammar Rule Lookup:
// Given LeftSet and RightSet, checks every pair (B, C) in LeftSet x RightSet
// and returns the set of all A such that A -> BC
Set get_matching_lhs(Set left_set, Set right_set, const Rule grammar[], int rule_count)
{
    Set result = set_empty();
    if (left_set == 0 || right_set == 0)
        return result;

    for (int r = 0; r < rule_count; r++)
    {
        // Only consider binary rules A -> BC (length 2)
        if (grammar[r].right[1] != '\0')
        {
            char B = grammar[r].right[0];
            char C = grammar[r].right[1];

            // Cartesian product membership check: B in LeftSet AND C in RightSet
            if (set_contains(left_set, B) && set_contains(right_set, C))
            {
                result = set_add(result, grammar[r].left);
            }
        }
    }
    return result;
}
