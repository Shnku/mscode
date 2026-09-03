#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "sets_structure.c"

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

    const char *word = "baaba";

    printf("Testing word: \"%s\"\n", word);
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
