#include "grammer.cpp"
#include <cstdio>
#include <iostream>
#include <map>
#include <stdbool.h>
using namespace std;

// defining first and follow set structure
struct symbolSet {
    set<char> term;
    bool add(char c)
    {
        auto status = term.insert(c);
        return status.second;
    }
    bool add(symbolSet& s)
    {
        int old_size = term.size();
        term.insert(s.term.begin(), s.term.end());
        return old_size != term.size();
    }
    bool add_all_except(symbolSet& s, char except = ' ')
    {
        int size = term.size();
        for (char it : s.term) {
            if (it == except)
                continue;
            term.insert(it);
        }
        return (size != term.size());
    }
    bool contains(char c) { return term.count(c); }
    // print
    void print()
    {
        for (auto it : term)
            printf("%c, ", it);
    }
};

typedef map<char, symbolSet> FIRST, FOLLOW;

void print_set(map<char, symbolSet> f, string msg, string name = "FOLLOW")
{
    printf(":::%s::", msg.c_str());
    for (auto it : f) {
        printf("%s(%c)->{ ", name.c_str(), it.first);
        it.second.print();
        printf("}, ");
    }
    printf("\n");
}

void print_first_set(FIRST f, string msg = "first set") { print_set(f, msg, "FIRST"); }
void print_follow_set(FOLLOW f, string msg = "follow set") { print_set(f, msg, "FOLLOW"); }

FIRST find_first(grammar g)
{
    FIRST first;
    // For each terminal 'a', FIRST(a) = {a}
    // for (char X : g.Terminals)
    //     first[X].add(X);
    // print_set(first);

    // For each non-terminal A:- Initialize FIRST(A) = ∅
    for (char X : g.nonTerminals)
        first[X] = { };
    print_first_set(first);

    // Repeat the firstollowing steps until no more changes occur:
    bool changed;
    do {
        printf("\n<===========================>running passes<===========================>\n");
        changed = false;

        // For each production X->alpha:
        for (auto production : g.Rules) {
            char X = production.lhs;
            string alpha = production.rhs;

            // Epsilon Production : X->ε, FIRST(X) u {ε}
            if (alpha == "#") {
                if (first[X].add('#'))
                    changed = true;
                print_first_set(first);
                continue;
            }

            // for X->alpha , where alpha = Y1Y2...Yk
            for (char Y : alpha) {
                print_first_set(first);
                // for terminal Y1 = terminal FIRST(X) u {Y1}
                printf("processing: %c<%s> => ", Y, alpha.c_str());
                if (g.is_terminal(Y)) {
                    printf("terminal => FIRST(%c)u{%c}\n", X, Y);
                    if (first[X].add(Y))
                        changed = true;
                    break;
                } else {
                    // Yi = non-terminal, {FIRST(Yi)\{ε}} u FIRST(X)
                    printf("non-terminal => add first(%c)\\{ε} to first(%c)\n", Y, X);
                    if (first[X].add_all_except(first[Y], '#'))
                        changed = true;
                    // If ε ∈ FIRST(Yi), continue to next symbol in α
                    if (first[Y].contains('#')) {
                        printf("ε ∈ FIRST(%c) => continue to next symbol in α\n", Y);
                        continue;
                    } else // Else, break
                        break;
                }
            }
        }
    } while (changed);
    printf("\n\n<===#################First calculation done#################=>\n\n");
    return first;
}

symbolSet find_first_of_string(string alpha, grammar g, FIRST first)
{
    // alpha = ABC
    // FA(alpha)=FA(A)
    // if ε ∈ FA(A), then {FA(A)-{ε}} u FA(alpha) = FA(alpha)
    // if ε ∈ FA(B), then {FA(B)-{ε}} u FA(alpha) = FA(alpha)
    // if ε ∈ FA(C), then {FA(C)-{ε}} u FA(alpha) = FA(alpha)
    // if # ∈ FA(alpha)

    string X = alpha;
    symbolSet F;
    bool al_empty = false;
    for (char Y : alpha) {
        // for terminal Y1 = terminal FIRST(X) u {Y1}
        // printf("processing__%c__:__%s__ => ", Y, alpha.c_str());
        if (g.is_terminal(Y)) {
            // printf("Yi = terminal => FIRST(%c) u {%c}\n", X, Y);
            F.add(Y);
            // print_set(first, "First set\n");
            break;
        } else {
            // Yi = non-terminal, {FIRST(Yi)\{ε}} u FIRST(X)
            // printf("Yi = non-terminal => add first(%c)-{ε} to first(%c)\n", Y, X);
            F.add_all_except(first[Y], '#');
            // If ε ∈ FIRST(Yi), continue to next symbol in α
            if (first[Y].contains('#')) {
                // printf("ε ∈ FIRST(%c) => continue to next symbol in α\n", Y);
                al_empty = true;
                continue;
            } else // Else, break
                break;
        }
    }
    if (al_empty)
        F.add('#');
    return F;
}

FOLLOW find_follow(grammar g, FIRST first)
{
    FOLLOW follow;

    // initiate the follow set
    for (auto it : g.nonTerminals)
        follow[it] = { };

    // For start symbol : $ ∈ FOLLOW(S)
    follow[g.StartSymbol].add('$');
    print_set(follow, "Initial follow set");

    // Repeat until no more changes occur:
    bool changed;
    do {
        printf("\n<===========================>running passes<===========================>\n");
        changed = false;

        // For each production A->αBβ:
        for (auto production : g.Rules) {
            char A = production.lhs;
            string alpha_B_beta = production.rhs;

            // For each non-terminal B in α:
            for (int i = 0; i < alpha_B_beta.size(); i++) {
                char B = alpha_B_beta[i];
                string beta = alpha_B_beta.substr(i + 1);
                if (g.is_non_terminal(B) && !beta.empty()) {
                    printf("Seperation of production:: %c -> %s (NT:%c | beta:%s)\n", A, alpha_B_beta.c_str(), B, beta.c_str());
                    // If there is a production A->αBβ, then  FOLLOW(B) = FIRST(β)\ε
                    // β=ABCDEF..., so FIRST(β)
                    symbolSet betaFirst = find_first_of_string(beta, g, first);
                    printf(">>>>>finding FIRST of beta:: FIRST(%s) = { ", beta.c_str());
                    betaFirst.print();
                    printf("}\n");
                    printf("production A->αBβ => FOLLOW(%c)=FIRST(%s)\\{ε}\n", B, beta.c_str());
                    if (follow[B].add_all_except(betaFirst, '#'))
                        changed = true;

                    // if there is a production A->αB or A->αBβ and ε ∈ FIRST(β), then FOLLOW(B) = FOLLOW(A)
                    if (betaFirst.contains('#')) {
                        printf("production A->αB or A->αBβ and ε ∈ FIRST(%s) => FOLLOW(%c)=FOLLOW(%c)\n", beta.c_str(), B, A);
                        if (follow[B].add(follow[A]))
                            changed = true;
                    }
                }
                print_follow_set(follow);
            }
        }
    } while (changed);

    return follow;
}

int main()
{
    grammar g;

#if 1
    g = grammar({ "A->BC", "A->#" });
    g.print_the_whole_grammer();
    find_first(g);
    g = grammar({ "A->BCDEF", "B->#", "C->#", "D->#", "F->#", "E->#" });
    g.print_the_whole_grammer();
    find_first(g);

#endif

#if 1
    g = grammar({ "S->SBC", "C->#", "B->bB" });
    g.print_the_whole_grammer();

    FIRST f = find_first(g);
    find_follow(g, f);
    return 0;

#endif
}