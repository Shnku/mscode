#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "sets_structure.c"
#include "valid_cnf.c"
typedef struct Productiones
{
    Rule rule[100];
    int rule_count;
} Productions;

void print_grammer(Productions P)
{
    for (int i = 0; i < P.rule_count; i++)
    {
        printf("%c->%s", P.rule[i].left, P.rule[i].right);
        printf("\n");
    }
}
// ================ Clean CYK Algorithm  ==================
bool cyk(const char *word, const Rule grammar[], int rule_count, char start_symbol)
{
    int n = strlen(word);
    if (n == 0)
        return false;

    // 1-based indexing: table[Position][Length], size (n+1) x (n+1)
    Set table[n + 1][n + 1];

    for (int p = 0; p <= n; p++)
        for (int l = 0; l <= n; l++)
            table[p][l] = set_empty();

    // Level 1: Bottom row (L = 1)
    for (int P = 1; P <= n; P++)
    {
        table[P][1] = get_terminal_lhs(word[P - 1], grammar, rule_count);
    }

    // Levels 2 to N: Building up the pyramid
    for (int L = 2; L <= n; L++) // Loop 1: Length
    {
        for (int P = 1; P <= n - L + 1; P++) // Loop 2: Position
        {
            for (int k = 1; k < L; k++) // Loop 3: Split point
            {
                // Matches your exact formula:
                Set LeftSet = table[P][k];
                Set RightSet = table[P + k][L - k];

                Set matches = get_matching_lhs(LeftSet, RightSet, grammar, rule_count);
                table[P][L] = set_union(table[P][L], matches);
            }
        }
    }

    // Print the final table (from apex down to bottom row)
    printf("\nCYK Parse Table (Position, Length):\n");
    for (int L = n; L >= 1; L--)
    {
        printf("Level %d (L=%d): ", L, L);
        for (int P = 1; P <= n - L + 1; P++)
        {
            printf("T[%d][%d]=", P, L);
            print_set(table[P][L]);
            printf("  ");
        }
        printf("\n");
    }

    // Word is accepted if Start Symbol is in T[1][n] (starts at 1, length n)
    return set_contains(table[1][n], start_symbol);
}

// ============================ Main =============================
int main(void)
{
    Rule grammar[] = {{'S', "AB"}, {'S', "BC"}, {'A', "BA"}, {'A', "a"},
                      {'B', "CC"}, {'B', "b"},  {'C', "AB"}, {'C', "a"}};
    int rule_count = sizeof(grammar) / sizeof(grammar[0]);

    // user input format ---S=AB parse as 'S' and "AB"
    Productions g2;
    int no;
    printf("enter the rule count: ");
    scanf("%d", &no);
    g2.rule_count = no;

    for (int i = 0; i < no; i++)
    {
        char left;
        char right[3];
        printf("PUT RULE %d: left: ", i);
        scanf(" %c", &left); // use %c for single char, " %c" skips whitespace
        printf("PUT RULE %d: right: ", i);
        scanf("%2s", right); // limit to 2 chars, automatically adds '\0'
        g2.rule[i].left = left;
        strcpy(g2.rule[i].right, right);
    }

    print_grammer(g2);

    // 1. Check if the grammar is in valid CNF before running CYK
    printf("\nValidating grammar: %s\n",
           is_cnf_grammer(grammar, rule_count) ? "[PASS] Valid CNF" : "[FAIL] Invalid CNF");

    if (!is_cnf_grammer(grammar, rule_count))
    {
        printf("\nError: Provided grammar is not in Chomsky Normal Form (CNF).\n");
        return 1;
    }

    // 2. Test word
    const char word[100] = "baaba";
    printf("\n Enter the word to test: ");
    scanf("%s", &word);

    printf("\nTesting word: \"%s\"\n", word);
    if (cyk(word, grammar, rule_count, 'S'))
    {
        printf("\nResult: Word \"%s\" is ACCEPTED by the grammar.\n", word);
    }
    else
    {
        printf("\nResult: Word \"%s\" is REJECTED by the grammar.\n", word);
    }

    return 0;
}

/**
output...

PS C:\Users\ADMIN\mscode-compilers\compiler\cyk_algo> gcc .\cyk.c
PS C:\Users\ADMIN\mscode-compilers\compiler\cyk_algo> .\a.exe
enter the rule count: 5
PUT RULE 0: left: S
PUT RULE 0: right: AB
PUT RULE 1: left: S
PUT RULE 1: right: CA
PUT RULE 2: left: A
PUT RULE 2: right: a
PUT RULE 3: left: B
PUT RULE 3: right: b
PUT RULE 4: left: C
PUT RULE 4: right: c
S->AB
S->CA
A->a
B->b
C->c

Validating grammar: [PASS] Valid CNF

 Enter the word to test: ab

Testing word: "ab"

CYK Parse Table (Position, Length):
Level 2 (L=2): T[1][2]={ C S }
Level 1 (L=1): T[1][1]={ A C }  T[2][1]={ B }

Result: Word "ab" is ACCEPTED by the grammar.
PS C:\Users\ADMIN\mscode-compilers\compiler\cyk_algo> .\a.exe
enter the rule count: 8
PUT RULE 0: left: S
PUT RULE 0: right: AB
PUT RULE 1: left: S
PUT RULE 1: right: BC
PUT RULE 2: left: A
PUT RULE 2: right: BA
PUT RULE 3: left: A
PUT RULE 3: right: a
PUT RULE 4: left: B
PUT RULE 4: right: CC
PUT RULE 5: left: B
PUT RULE 5: right: b
PUT RULE 6: left: C
PUT RULE 6: right: AB
PUT RULE 7: left: C
PUT RULE 7: right: a
S->AB
S->BC
A->BA
A->a
B->CC
B->b
C->AB
C->a

Validating grammar: [PASS] Valid CNF

 Enter the word to test: baaba

Testing word: "baaba"

CYK Parse Table (Position, Length):
Level 5 (L=5): T[1][5]={ A C S }
Level 4 (L=4): T[1][4]={ }  T[2][4]={ A C S }
Level 3 (L=3): T[1][3]={ }  T[2][3]={ B }  T[3][3]={ B }
Level 2 (L=2): T[1][2]={ A S }  T[2][2]={ B }  T[3][2]={ C S }  T[4][2]={ A S }
Level 1 (L=1): T[1][1]={ B }  T[2][1]={ A C }  T[3][1]={ A C }  T[4][1]={ B }  T[5][1]={ A C }

Result: Word "baaba" is ACCEPTED by the grammar.
**/