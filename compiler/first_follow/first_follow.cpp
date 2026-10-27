#include "grammer.cpp"
#include <cstdio>
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
    bool print()
    {
        for (auto it : term)
            printf("%c, ", it);
        return true;
    }
};

typedef map<char, symbolSet> FIRST, FOLLOW;

bool print_set(map<char, symbolSet> f, string msg, string name = "FOLLOW")
{
    printf(":::%s:: [ ", msg.c_str());
    for (auto it : f) {
        printf("%s(%c)->{ ", name.c_str(), it.first);
        it.second.print();
        printf("}, ");
    }
    printf("]\n");
    return true;
}

bool print_first_set(FIRST f, string msg = "first set") { return print_set(f, msg, "FIRST"); }
bool print_follow_set(FOLLOW f, string msg = "follow set") { return print_set(f, msg, "FOLLOW"); }

symbolSet find_first_of_string(string alpha, grammar g, FIRST first, bool log = true)
{
    // alpha = ABC
    // FA(alpha)=FA(A)
    // if ε ∈ FA(A), then {FA(A)-{ε}} u FA(alpha) = FA(alpha)
    // if ε ∈ FA(B), then {FA(B)-{ε}} u FA(alpha) = FA(alpha)
    // if ε ∈ FA(C), then {FA(C)-{ε}} u FA(alpha) = FA(alpha)
    // if # ∈ FA(alpha)

    string X = alpha;
    symbolSet First_of_alpha;

    // for terminal Y1 = terminal;  FIRST(X)u{Y1}
    if (g.is_terminal(X[0])) {
        log ? printf("processing:- %c in <%s> :: ", X[0], alpha.c_str()) : 0;
        log ? printf("terminal => FIRST(%c) u FIRST(%s)\n", X[0], alpha.c_str()) : 0;
        First_of_alpha.add(X[0]);
        return First_of_alpha;
    }

    // Yi = non-terminal; FIRST(X) u {FIRST(Yi)\{ε}}
    bool derive_eplison = true;
    for (char Y : alpha) {
        log ? printf("processing:- %c in <%s> :: ", Y, alpha.c_str()) : 0;
        derive_eplison = false;
        log ? printf("non-terminal => {FIRST(%c)\\{ε}} u FIRST(%s)\n", Y, alpha.c_str()) : 0;
        First_of_alpha.add_all_except(first[Y], '#');

        // If ε ∈ FIRST(Yi), continue to next symbol in α
        if (first[Y].contains('#')) {
            log ? printf("ε ∈ FIRST(%c) => continue to next symbol in α\n", Y) : 0;
            derive_eplison = true;
            continue;
        }
    }

    // if each of yi=>ε then X =>* ε, add ε to FIRST(X)
    if (derive_eplison) {
        log ? printf("<%s> =>* ε, add ε to FIRST(%s)\n", alpha.c_str(), X.c_str()) : 0;
        First_of_alpha.add('#');
    }
    return First_of_alpha;
}

FIRST find_first(grammar g, bool log = true)
{
    FIRST first;
    // For each terminal 'a', FIRST(a) = {a}
    // for (char X : g.Terminals)
    //     first[X].add(X);
    // print_set(first);

    // For each non-terminal A:- Initialize FIRST(A) = ∅
    for (char X : g.nonTerminals)
        first[X] = { };
    log ? print_first_set(first) : 0;

    // Repeat the firstollowing steps until no more changes occur:
    bool changed;
    do {
        log ? printf("\n<===========================>running passes<===========================>\n") : 0;
        changed = false;

        // For each production X->alpha:
        for (auto production : g.Rules) {
            char X = production.lhs;
            string alpha = production.rhs;

            // Epsilon Production : X->ε, FIRST(X) u {ε}
            if (alpha == "#") {
                if (first[X].add('#')) {
                    changed = true;
                    log ? print_first_set(first) : 0;
                }
                continue;
            }

            // for X->alpha , where alpha = Y1Y2...Yk
            symbolSet s = find_first_of_string(alpha, g, first, log);
            if (first[X].add(s)) {
                changed = true;
                log ? print_first_set(first) : 0;
            }
        }
    } while (changed);
    print_first_set(first);
    log ? printf("\n<===################# First calculation done #################=>\n\n\n") : 0;
    return first;
}

FOLLOW find_follow(grammar g, FIRST first, bool log = true)
{
    FOLLOW follow;

    // initiate the follow set
    for (auto it : g.nonTerminals)
        follow[it] = { };

    // For start symbol : $ ∈ FOLLOW(S)
    follow[g.StartSymbol].add('$');
    log ? print_set(follow, "Initial follow set") : 0;

    // Repeat until no more changes occur:
    bool changed;
    do {
        log ? printf("\n<===========================>running passes<===========================>\n") : 0;
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
                    log ? printf("Seperation of production:: %c -> %s where, NT:-%c and ß:-%s\n", A, alpha_B_beta.c_str(), B, beta.c_str()) : 0;
                    // If there is a production A->αBβ, then  FOLLOW(B) = FIRST(β)\ε
                    // β=ABCDEF..., so FIRST(β)
                    symbolSet betaFirst = find_first_of_string(beta, g, first, log);
                    log ? printf(">>>>>finding FIRST of ß:: FIRST(%s) = { ", beta.c_str()) : 0;
                    log ? betaFirst.print() : 0;
                    log ? printf("}\nproduction %c->α%cß => FOLLOW(%c)=FIRST(%s)\\{ε}\n", A, B, B, beta.c_str()) : 0;
                    if (follow[B].add_all_except(betaFirst, '#')) {
                        log ? print_follow_set(follow) : 0;
                        changed = true;
                    }
                    // if there is a production A->αB or A->αBβ and ε ∈ FIRST(β), then FOLLOW(B) = FOLLOW(A)
                    if (betaFirst.contains('#')) {
                        log ? printf("production %c->α%c or %c->α%cß and ε ∈ FIRST(%s) => FOLLOW(%c)=FOLLOW(%c)\n", A, B, A, B, beta.c_str(), B, A) : 0;
                        if (follow[B].add(follow[A])) {
                            log ? print_follow_set(follow) : 0;
                            changed = true;
                        }
                    }
                }
            }
        }
    } while (changed);
    print_follow_set(follow);
    log ? printf("\n\n<===################# Follow calculation done #################=>\n\n") : 0;
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
    find_follow(g, find_first(g, false), false);

#endif

#if 1
    g = grammar({ "S->ABC", "A->a", "A->#", "B->b", "B->#", "C->c", "C->#" });
    g.print_the_whole_grammer();
    find_follow(g, find_first(g));

#endif
}