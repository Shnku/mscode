#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "sets_structure.c"
#include "valid_cnf.c"

typedef struct Productiones {
    Rule rule[100];
    int rule_count;
} Productions;

void print_grammer(Productions P)
{
    for (int i = 0; i < P.rule_count; i++) {
        printf("%c->%s", P.rule[i].left, P.rule[i].right);
        printf("\n");
    }
}
// ================ Clean CYK Algorithm  ==================
bool cyk(const char* word, const Rule grammar[], int rule_count, char start_symbol)
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
    printf("\n--- Level 1: Substrings of length 1 (Terminals) ---\n");
    for (int P = 1; P <= n; P++) {
        table[P][1] = get_terminal_lhs(word[P - 1], grammar, rule_count);
        printf("P=%d: char '%c' -> T[%d][1] = ", P, word[P - 1], P);
        print_set(table[P][1]);
        printf("\n");
    }

    // Levels 2 to N: Building up the pyramid
    for (int L = 2; L <= n; L++) // Loop 1: Length
    {
        printf("\n--- Level %d: Substrings of length %d ---\n", L, L);
        for (int P = 1; P <= n - L + 1; P++) // Loop 2: Position
        {
            printf("\nCalculating T[%d][%d] for substring \"%.*s\":\n", P, L, L, word + P - 1);
            for (int k = 1; k < L; k++) // Loop 3: Split point
            {
                // Matches your exact formula:
                Set LeftSet = table[P][k];
                Set RightSet = table[P + k][L - k];

                Set matches = get_matching_lhs(LeftSet, RightSet, grammar, rule_count);
                table[P][L] = set_union(table[P][L], matches);

                printf("  split k=%d: T[%d][%d] ", k, P, k);
                print_set(LeftSet);
                printf("  x  T[%d][%d] ", P + k, L - k);
                print_set(RightSet);
                printf("  ->  matches: ");
                print_set(matches);
                printf("\n");
            }
            printf("  => Combined T[%d][%d] = ", P, L);
            print_set(table[P][L]);
            printf("\n");
        }
    }

    // Print the final table (from apex down to bottom row)
    printf("\nCYK Parse Table (Position, Length):\n");
    for (int L = n; L >= 1; L--) {
        printf("Level %d (L=%d): ", L, L);
        for (int P = 1; P <= n - L + 1; P++) {
            printf("T[%d][%d]=", P, L);
            print_set(table[P][L]);
            printf("  ");
        }
        printf("\n");
    }

    // Word is accepted if Start Symbol is in T[1][n] (starts at 1, length n)
    return set_contains(table[1][n], start_symbol);
}

/******************************************************************/
/****************** run/test this file only... ********************/
#ifndef CYK_NO_MAIN
/* ============================ Main ============================= */
int main(void)
{
    Productions grammar = {
        .rule = {
            { 'S', "AB" }, { 'S', "BC" }, { 'A', "BA" }, { 'A', "a" },
            { 'B', "CC" }, { 'B', "b" }, { 'C', "AB" }, { 'C', "a" } },
        .rule_count = 8
    };

    printf("\nThe grammar is::\n");
    print_grammer(grammar);

    // 1. Check if the grammar is in valid CNF before running CYK
    printf("\nValidating grammar: %s\n",
        is_cnf_grammer(grammar.rule, grammar.rule_count) ? "[PASS] Valid CNF" : "[FAIL] Invalid CNF");

    if (!is_cnf_grammer(grammar.rule, grammar.rule_count)) {
        printf("Error: Grammar is not in valid Chomsky Normal Form (CNF)!\n");
        return 1;
    }

    // 2. Test word
    char word[100] = "baaba";

    printf("\nTesting word: \"%s\"\n", word);
    if (cyk(word, grammar.rule, grammar.rule_count, 'S')) {
        printf("\nResult: Word \"%s\" is ACCEPTED by the grammar.\n", word);
    } else {
        printf("\nResult: Word \"%s\" is REJECTED by the grammar.\n", word);
    }

    return 0;
}
#endif

/** output...

❯ gcc cyk.c -o cyk && ./cyk

The grammar is::
S->AB
S->BC
A->BA
A->a
B->CC
B->b
C->AB
C->a

Validating grammar: [PASS] Valid CNF

Testing word: "baaba"

--- Level 1: Substrings of length 1 (Terminals) ---
P=1: char 'b' -> T[1][1] = { B }
P=2: char 'a' -> T[2][1] = { A C }
P=3: char 'a' -> T[3][1] = { A C }
P=4: char 'b' -> T[4][1] = { B }
P=5: char 'a' -> T[5][1] = { A C }

--- Level 2: Substrings of length 2 ---

Calculating T[1][2] for substring "ba":
  split k=1: T[1][1] { B }  x  T[2][1] { A C }  ->  matches: { A S }
  => Combined T[1][2] = { A S }

Calculating T[2][2] for substring "aa":
  split k=1: T[2][1] { A C }  x  T[3][1] { A C }  ->  matches: { B }
  => Combined T[2][2] = { B }

Calculating T[3][2] for substring "ab":
  split k=1: T[3][1] { A C }  x  T[4][1] { B }  ->  matches: { C S }
  => Combined T[3][2] = { C S }

Calculating T[4][2] for substring "ba":
  split k=1: T[4][1] { B }  x  T[5][1] { A C }  ->  matches: { A S }
  => Combined T[4][2] = { A S }

--- Level 3: Substrings of length 3 ---

Calculating T[1][3] for substring "baa":
  split k=1: T[1][1] { B }  x  T[2][2] { B }  ->  matches: { }
  split k=2: T[1][2] { A S }  x  T[3][1] { A C }  ->  matches: { }
  => Combined T[1][3] = { }

Calculating T[2][3] for substring "aab":
  split k=1: T[2][1] { A C }  x  T[3][2] { C S }  ->  matches: { B }
  split k=2: T[2][2] { B }  x  T[4][1] { B }  ->  matches: { }
  => Combined T[2][3] = { B }

Calculating T[3][3] for substring "aba":
  split k=1: T[3][1] { A C }  x  T[4][2] { A S }  ->  matches: { }
  split k=2: T[3][2] { C S }  x  T[5][1] { A C }  ->  matches: { B }
  => Combined T[3][3] = { B }

--- Level 4: Substrings of length 4 ---

Calculating T[1][4] for substring "baab":
  split k=1: T[1][1] { B }  x  T[2][3] { B }  ->  matches: { }
  split k=2: T[1][2] { A S }  x  T[3][2] { C S }  ->  matches: { }
  split k=3: T[1][3] { }  x  T[4][1] { B }  ->  matches: { }
  => Combined T[1][4] = { }

Calculating T[2][4] for substring "aaba":
  split k=1: T[2][1] { A C }  x  T[3][3] { B }  ->  matches: { C S }
  split k=2: T[2][2] { B }  x  T[4][2] { A S }  ->  matches: { A }
  split k=3: T[2][3] { B }  x  T[5][1] { A C }  ->  matches: { A S }
  => Combined T[2][4] = { A C S }

--- Level 5: Substrings of length 5 ---

Calculating T[1][5] for substring "baaba":
  split k=1: T[1][1] { B }  x  T[2][4] { A C S }  ->  matches: { A S }
  split k=2: T[1][2] { A S }  x  T[3][3] { B }  ->  matches: { C S }
  split k=3: T[1][3] { }  x  T[4][2] { A S }  ->  matches: { }
  split k=4: T[1][4] { }  x  T[5][1] { A C }  ->  matches: { }
  => Combined T[1][5] = { A C S }

CYK Parse Table (Position, Length):
Level 5 (L=5): T[1][5]={ A C S }
Level 4 (L=4): T[1][4]={ }  T[2][4]={ A C S }
Level 3 (L=3): T[1][3]={ }  T[2][3]={ B }  T[3][3]={ B }
Level 2 (L=2): T[1][2]={ A S }  T[2][2]={ B }  T[3][2]={ C S }  T[4][2]={ A S }
Level 1 (L=1): T[1][1]={ B }  T[2][1]={ A C }  T[3][1]={ A C }  T[4][1]={ B }  T[5][1]={ A C }

Result: Word "baaba" is ACCEPTED by the grammar.

**/