#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define LEN 50

int production_count, set_size;
char productions[MAX][LEN], set[256];
int visited_follow[256], visited_first[256];

void first(char c);
void follow(char c);

int is_nonterminal(char c)
{
    return isupper((unsigned char)c);
}

void add_to_set(char c)
{
    int i;

    for (i = 0; i < set_size; i++)
        if (set[i] == c)
            return;

    set[set_size++] = c;
}

void print_set(char name[], char c)
{
    printf("%s(%c) = { ", name, c);

    for (int i = 0; i < set_size; i++)
        printf("%c ", set[i]);

    printf("}\n");
}

void first(char c)
{
    int i;
    unsigned char ch = (unsigned char)c;

    if (!is_nonterminal(c))
    {
        add_to_set(c);
        return;
    }

    if (visited_first[ch])
        return;

    visited_first[ch] = 1;

    for (i = 0; i < production_count; i++)
    {
        if (productions[i][0] == c)
        {
            if (!is_nonterminal(productions[i][2]))
                add_to_set(productions[i][2]);
            else
                first(productions[i][2]);
        }
    }

    visited_first[ch] = 0;
}

void follow(char c)
{
    int i, j, len;
    unsigned char ch = (unsigned char)c;

    if (visited_follow[ch])
        return;

    visited_follow[ch] = 1;

    if (productions[0][0] == c)
        add_to_set('$');

    for (i = 0; i < production_count; i++)
    {
        len = strlen(productions[i]);

        for (j = 2; j < len; j++)
        {
            if (productions[i][j] == c)
            {
                if (j + 1 < len)
                {
                    char next = productions[i][j + 1];

                    if (!is_nonterminal(next))
                        add_to_set(next);
                    else
                        first(next);
                }
                else if (productions[i][0] != c)
                {
                    follow(productions[i][0]);
                }
            }
        }
    }

    visited_follow[ch] = 0;
}

int main(void)
{
    int i, j, nonterminal_count = 0;
    char elements[MAX];

    printf("ENTER THE NUMBER OF PRODUCTIONS: ");

    scanf("%d", &production_count);

    printf("ENTER THE PRODUCTIONS:\n");

    for (i = 0; i < production_count; i++)
    {
        scanf("%49s", productions[i]);

        for (j = 0; j < nonterminal_count; j++)
            if (elements[j] == productions[i][0])
                break;

        if (j == nonterminal_count)
            elements[nonterminal_count++] = productions[i][0];
    }

    printf("\nFIRST AND FOLLOW SETS:\n");

    for (i = 0; i < nonterminal_count; i++)
    {
        char c = elements[i];

        set_size = 0;
        memset(visited_first, 0, sizeof(visited_first));

        first(c);

        printf("\n");
        print_set("FIRST", c);

        set_size = 0;
        memset(visited_follow, 0, sizeof(visited_follow));

        follow(c);

        print_set("FOLLOW", c);
    }

    return 0;
}