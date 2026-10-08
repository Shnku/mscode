/* Check if the grammar is a valid CNF or not */
#ifndef VALID_CNF_C
#define VALID_CNF_C

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "sets_structure.c"

// rules are like A->a or A->BC
bool is_cnf_rule(char left, const char *right) // left== A,  right== [a], or right==[B,C]
{
    if (!isupper((unsigned char)left))
        return false;

    if (right == NULL || right[0] == '\0')
        return false;

    // for A->a or A->$ how to check the null
    if (right[0] == '$')
    {
        printf("null");
    }
    if (right[1] == '\0')
        return islower(right[0]);
    // for A->BC kind of things
    if (right[2] == '\0')
        return isupper((unsigned char)right[0]) && isupper((unsigned char)right[1]);

    return false; // not CNF (length >= 3 or invalid characters)
}

bool is_cnf_grammer(const Rule grammer[], int rule_count)
{
    if (rule_count <= 0)
        return false;

    for (int i = 0; i < rule_count; i++)
    {
        if (!is_cnf_rule(grammer[i].left, grammer[i].right))
            return false;
    }
    return true;
}

// Testing this file standalone: gcc -DIS_CNF valid_cnf.c -o valid_cnf && ./valid_cnf
#ifdef IS_CNF

int main()
{
    // Input a CNF grammar
    Rule cnf_grammar[] = {{'S', "AB"}, {'S', "BC"}, {'A', "BA"}, {'A', "a"},
                          {'B', "CC"}, {'B', "b"},  {'C', "AB"}, {'C', "a"}};
    int rule_count = sizeof(cnf_grammar) / sizeof(cnf_grammar[0]);

    printf("Check CNF grammar: %s\n", is_cnf_grammer(cnf_grammar, rule_count) ? "yes" : "no");

    // Input a non-CNF grammar (contains 'aB' with lowercase 'a' in binary rule)
    Rule ncnf_grammar[] = {{'S', "aB"}, {'S', "BC"}, {'A', "BA"}, {'A', "a"},
                           {'B', "CC"}, {'B', "b"},  {'C', "AB"}, {'C', "a"}};
    rule_count = sizeof(ncnf_grammar) / sizeof(ncnf_grammar[0]);

    printf("Check Non-CNF grammar: %s\n", is_cnf_grammer(ncnf_grammar, rule_count) ? "yes" : "no");

    return 0;
}

#endif

#endif // VALID_CNF_C