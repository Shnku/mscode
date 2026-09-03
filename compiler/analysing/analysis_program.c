#include <stdio.h>
#include <string.h>

struct token
{
    char name[20];
    int frequency;
    int lines[100];
    int numberOfLines;
};

struct token identifiers[100];
int identifierCount = 0;

struct token operators[] = {{"++", 0, {0}, 0}, {"--", 0, {0}, 0}, {"+", 0, {0}, 0},  {"-", 0, {0}, 0},
                            {"*", 0, {0}, 0},  {"/", 0, {0}, 0},  {"+=", 0, {0}, 0}, {"-=", 0, {0}},
                            {"=", 0, {0}, 0},  {"&&", 0, {0}, 0}, {"<", 0, {0}, 0},  {">", 0, {0}, 0},
                            {"<=", 0, {0}, 0}, {">=", 0, {0}, 0}};
// list of keywords in C
struct token keywords[] = {{"int", 0, {0}, 0},    {"float", 0, {0}, 0}, {"char", 0, {0}, 0},     {"if", 0, {0}, 0},
                           {"else", 0, {0}, 0},   {"while", 0, {0}, 0}, {"for", 0, {0}, 0},      {"do", 0, {0}, 0},
                           {"switch", 0, {0}, 0}, {"break", 0, {0}, 0}, {"continue", 0, {0}, 0}, {"return", 0, {0}, 0},
                           {"long", 0, {0}, 0},   {"double", 0, {0}, 0}};

// to check a single charecter
int isnumber(char p)
{
    if (p >= '0' && p <= '9')
    {
        return 1;
    }
    return 0;
}
int isletter(char p)
{
    if (p >= 65 && p <= 90)
    {
        return 1;
    }
    else if (p >= 97 && p <= 122)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isoperator(char p)
{
    if (p == '*' || p == '+' || p == '-' || p == '/' || p == '=' || p == '>' || p == '<' || p == '|' || p == '&')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int isdelimeter(char p)
{
    if (p == '(' || p == ')' || p == '{' || p == '}' || p == '[' || p == ']' || p == ',')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int iskeyword(char str[100], int ln)
{
    int j;
    for (j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++)
    {
        if (strcmp(str, keywords[j].name) == 0)
        {
            keywords[j].frequency++;
            keywords[j].lines[keywords[j].numberOfLines] = ln;
            keywords[j].numberOfLines++;
            return;
        }
    }
    return 0;
}
int finaloperator(char str[100], int ln)
{
    int j;
    for (j = 0; j < sizeof(operators) / sizeof(operators[0]); j++)
    {
        if (strcmp(str, operators[j].name) == 0)
        {
            operators[j].frequency++;
            operators[j].lines[operators[j].numberOfLines] = ln;
            operators[j].numberOfLines++;
            return 1;
        }
    }
    return 0;
}

int isidentifier(char str[100])
{
    int j, f = 0, c = 0;
    // check is the token is a keyword
    for (j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++)
    {
        if (strcmp(str, keywords[j].name) == 0)
        {
            return 0;
        }
    }
    // check if it is a identifier
    if (isletter(str[0]))
    {
        c++;
        while (str[c] != '\0')
        {
            if (isletter(str[c]) || isnumber(str[c]))
            {
                f = 1;
            }
            else
            {
                break;
            }
            c++;
        }
    }
    if (f == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void countIdentifier(char str[100], int ln)
{
    int j, f = 0;
    if (identifierCount == 0)
    {
        strcpy(identifiers[0].name, str);
        identifiers[0].frequency = 1;
        identifiers[0].lines[identifiers[0].numberOfLines] = ln;
        identifiers[0].numberOfLines++;
        identifierCount++;
    }
    else
    {
        for (j = 0; j < identifierCount; j++)
        {
            if (strcmp(str, identifiers[j].name) == 0)
            {
                identifiers[j].frequency++;
                identifiers[j].lines[identifiers[j].numberOfLines] = ln;
                identifiers[j].numberOfLines++;
                f = 0;
                break;
            }
            else
            {
                f = 1;
            }
        }
        if (f == 1)
        {
            strcpy(identifiers[identifierCount].name, str);
            identifiers[identifierCount].frequency = 1;
            identifiers[identifierCount].lines[identifiers[identifierCount].numberOfLines] = ln;
            identifiers[identifierCount].numberOfLines++;
            identifierCount++;
        }
    }
}

int main()
{
    // file open
    FILE *fp;
    fp = fopen("sumprogram.c", "r");
    // checking for file existance
    if (fp == NULL)
    {
        printf("file not found\n");
        return 1;
    }
    // Traverse through file and print lines
    char line[100];
    char tokens[100];
    char singletoken[100];
    int linenumber = 0;
    int i = 0, l = 0;
    char past = ' ';

    // Initialize counter variable
    int strcounter = 0;
    int numcounter = 0;
    int pdcounter = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *p = line;
        linenumber++;
        //		printf("\nline - %d\n",linenumber);
        if (p[0] == '#')
        {
            //			printf("%s\n",p);
            pdcounter++;
            continue;
        }
        while (p[0] != '\n')
        {
            if (isletter(past) && isoperator(p[0]) || isletter(p[0]) && isoperator(past))
            {
                //					counting token
                iskeyword(singletoken, linenumber);
                if (isidentifier(singletoken))
                {
                    countIdentifier(singletoken, linenumber);
                }
                // 				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
            else if (isnumber(past) && isoperator(p[0]) || isoperator(past) && isnumber(p[0]))
            {
                //				counting tokens
                finaloperator(singletoken, linenumber);
                // identifying tokens
                printf("%s\n", singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
            else if ((isletter(past) && (p[0] == ' ' || p[0] == '\t')))
            {
                //					counting tokens
                iskeyword(singletoken, linenumber);
                if (isidentifier(singletoken))
                {
                    countIdentifier(singletoken, linenumber);
                }
                //				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = '\0';
                past = p[0];
                p++;
            }
            else if ((past == ' ' || past == '\t') && isletter(p[0]))
            {
                //				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
            else if (isoperator(past) && p[0] == ' ' || p[0] == '\t')
            {
                finaloperator(singletoken, linenumber);
                //				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = '\0';
                past = p[0];
                p++;
            }
            else if ((isdelimeter(past) && p[0] == ' ' || p[0] == '\t'))
            {
                //				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = '\0';
                past = p[0];
                p++;
            }
            else if (isletter(past) && isdelimeter(p[0]) || isdelimeter(past) && isletter(p[0]))
            {
                //					counting tokens
                iskeyword(singletoken, linenumber);
                if (isidentifier(singletoken))
                {
                    countIdentifier(singletoken, linenumber);
                }
                // identifying
                //				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
            else if ((isdelimeter(p[0]) && past == '"'))
            {
                // identifying tokens
                //				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
            else if ((isdelimeter(past) && p[0] == '"'))
            {
                // identify tokens
                //				printf("%s\n",singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
                while (p[0] != '"')
                {
                    singletoken[i] = p[0];
                    singletoken[i + 1] = '\0';
                    i++;
                    p++;
                }
                strcounter++;
            }
            else if (p[0] == ';')
            {
                //				counting tokens
                iskeyword(singletoken, linenumber);
                if (isidentifier(singletoken))
                {
                    countIdentifier(singletoken, linenumber);
                }
                finaloperator(singletoken, linenumber);

                // identifying tokens
                printf("%s\n", singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
            else if (isnumber(p[0]))
            {
                numcounter++;
                // identifying tokens
                printf("%s\n", singletoken);
                i = 0;
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
            else
            {
                singletoken[i] = p[0];
                singletoken[i + 1] = '\0';
                i++;
                past = p[0];
                p++;
            }
        }
    }
    // printing numeric figures
    int m, j, sum = 0;
    printf("\n\n\tKeywords - frequency\n");
    for (j = 0; j < sizeof(keywords) / sizeof(keywords[0]); j++)
    {
        if (keywords[j].frequency > 0)
        {
            sum += keywords[j].frequency;
            printf("\n\t'%s' - %d", keywords[j].name, keywords[j].frequency);
            printf("  lines: ");
            for (m = 0; m < keywords[j].numberOfLines; m++)
            {
                printf("%d,", keywords[j].lines[m]);
            }
        }
    }
    printf("\n");

    printf("\tTotal keywords - %d\n", sum);
    sum = 0;

    printf("\n\tOperators - frequency\n");
    for (j = 0; j < sizeof(operators) / sizeof(operators[0]); j++)
    {
        if (operators[j].frequency > 0)
        {
            sum += operators[j].frequency;
            printf("\n\t'%s' - %d", operators[j].name, operators[j].frequency);
            printf("  lines: ");
            for (m = 0; m < operators[j].numberOfLines; m++)
            {
                printf("%d,", operators[j].lines[m]);
            }
        }
    }
    printf("\n\tTotal operators - %d\n", sum);
    sum = 0;
    printf("\n\tIdentifiers - frequency\n");
    for (j = 0; j < identifierCount; j++)
    {
        sum += identifiers[j].frequency;
        printf("\n\t'%s' - %d", identifiers[j].name, identifiers[j].frequency);
        printf("  lines: ");
        for (m = 0; m < identifiers[j].numberOfLines; m++)
        {
            printf("%d,", identifiers[j].lines[m]);
        }
    }
    printf("\n\tTotal identifiers - %d\n", sum);
    sum = 0;
    printf("\n\tNo. of Preprocessor directives- %d", pdcounter);
    printf("\n\tNo. of Constants- %d", numcounter);
    printf("\n\tNO. of Strings - %d", strcounter);
    // file close
    fclose(fp);
}
