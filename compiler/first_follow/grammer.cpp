#include <cstdio>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct production {
    string rhs;
    char lhs;

    // Construct a production from "A->BC" [0=lhs,1,2, 3---=rhs]
    production(const string& rule)
    {
        lhs = rule[0];
        rhs = rule.substr(3);
    }

    // print the production rule...
    void print_production() { cout << lhs << "->" << rhs << ", "; }
};

struct grammar {
    set<char> nonTerminals;
    set<char> Terminals;
    char StartSymbol;
    vector<production> Rules;

    // construct the grammer from the input productions
    grammar() { }
    // terminal,nonterminal,start are determined automatically from Rules
    grammar(const vector<string>& input)
    {
        // the first production's lhs will be the start symbol..
        StartSymbol = input[0][0];
        // create productions for ecan rule and insert them ..
        for (const string& rule : input)
            Rules.push_back(production(rule));
        // Collect nonTerminals from LHS
        for (const auto& p : Rules)
            nonTerminals.insert(p.lhs);
        // Infer symbol types from RHS
        for (const auto& p : Rules) {
            for (char c : p.rhs) {
                if (c >= 'A' && c <= 'Z')
                    nonTerminals.insert(c);
                else
                    Terminals.insert(c);
            }
        }
    }

    // check set participations...
    // check for Terminals returns count = 0 or 1
    bool is_terminal(char c) { return Terminals.count(c); }
    // check for non-Terminals returns count = 0 or 1
    bool is_non_terminal(char c) { return nonTerminals.count(c); }

    // print production rules only...
    void print_production_Rules()
    {
        cout << "{ ";
        for (production p : Rules)
            p.print_production();
        cout << "}\n";
    }

    // print the whole grammer...
    void print_the_whole_grammer()
    {
        string nt = "{ ";
        for (char c : nonTerminals) {
            nt += c;
            nt += ", ";
        }
        nt += "}";

        string t = "{ ";
        for (char c : Terminals) {
            t += c;
            t += ", ";
        }
        t += "}";

        string r = "{ ";
        for (const auto& p : Rules) {
            r += p.lhs;
            r += "->";
            r += p.rhs;
            r += ", ";
        }
        r += "}";

        int width = (int)r.length() + 25;

        string eq_border = "+" + string(width, '=') + "+";
        string dash_border = "+" + string(width, '-') + "+";

        printf("\n%s\n", eq_border.c_str());
        printf("|%*s%*s|\n", width / 2, "THE GRAMMAR", width / 2, "");
        printf("%s\n", eq_border.c_str());
        printf("| Non-Terminals    : %-*s|\n", width - 21, nt.c_str());
        printf("| Terminals        : %-*s|\n", width - 21, t.c_str());
        printf("| Start symbol     : %-*c|\n", width - 21, StartSymbol);
        printf("| Production Rules : %-*s|\n", width - 21, r.c_str());
        printf("%s\n\n", dash_border.c_str());
    }
};

// Test/Run this file only
// use g++ -DRUN_MAIN grammer.cpp
#ifdef RUN_MAIN

int main()
{
    grammar g({ "A->BC", "B->C", "A->a", "C->b", "B->#" });
    cout << g.Rules.size() << " -> rules count..." << endl;
    cout << g.is_terminal('a') << g.is_non_terminal('A') << endl;
    cout << g.is_terminal('f') << g.is_non_terminal('f') << endl;
    g.print_the_whole_grammer();
}

#endif // RUN_MAIN