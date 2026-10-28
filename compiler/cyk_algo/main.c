#include <stdbool.h>
#include <stdio.h>

#define CYK_NO_MAIN // skips the main() of `cyk.c`
#include "cyk.c"

int main(void)
{
    Productions P;
    P.rule_count = 0;

    int choice;
    printf("1. Manual user input\n");
    printf("2. Read from file\n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        // 1. Manual user input
        printf("\nEnter number of rules: ");
        scanf("%d", &P.rule_count);

        for (int i = 0; i < P.rule_count; i++) {
            printf("Enter rule %d (e.g. S->AB or A->a): ", i + 1);
            scanf(" %c->%s", &P.rule[i].left, P.rule[i].right);
        }
    } else if (choice == 2) {
        // 2. Read from file
        char filename[100];
        printf("\nEnter filename: (avail: gmr_val.txt, gmr_inval.txt)");
        scanf("%s", filename);

        FILE* fp = fopen(filename, "r");
        if (!fp) {
            printf("Error: Cannot open file '%s'\n", filename);
            return 1;
        }

        while (fscanf(fp, " %c->%s", &P.rule[P.rule_count].left, P.rule[P.rule_count].right) == 2) {
            P.rule_count++;
        }
        fclose(fp);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    // Display the loaded grammar
    printf("\nGrammar rules:\n");
    print_grammer(P);

    // CNF checking
    if (!is_cnf_grammer(P.rule, P.rule_count)) {
        printf("\nError: Grammar is NOT in valid Chomsky Normal Form (CNF)!\n");
        return 1;
    }
    printf("\nGrammar is in valid CNF.\n");

    // Word testing with CYK
    char word[100];
    printf("\nEnter word to test: ");
    scanf("%s", word);

    printf("\nTesting word: \"%s\"\n", word);
    if (cyk(word, P.rule, P.rule_count, 'S')) {
        printf("\nResult: Word \"%s\" is ACCEPTED by the grammar.\n", word);
    } else {
        printf("\nResult: Word \"%s\" is REJECTED by the grammar.\n", word);
    }

    return 0;
}
