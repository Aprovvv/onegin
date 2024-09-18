#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "text_funcs.h"
#include "sort_funcs.h"

#define SWAP(a, b) swap(a, b, sizeof(a))

static void pr(struct text_t t, FILE* stream);
void sort_text_t(struct text_t orig, struct text_t parsed);
int cmpstr(const void* a, const void* b);
//int back_cmpstr(const void* a, const void* b);

int main()
{
    struct text_t onegin = read_text_from_file("parsed_onegin.txt");
    FILE* output = fopen("sorted_onegin.txt", "w");

    my_sort(onegin.string_array_p, onegin.str_count, sizeof(struct string), cmpstr);
    pr(onegin, output);

    free(onegin.text_p);
    free(onegin.string_array_p);
}

static void pr(struct text_t t, FILE* stream)
{
    for (size_t i = 0; i < t.str_count; i++)
    {
        fputs(t.string_array_p[i].index, stream);
        fputc('\n', stream);
    }
}

int cmpstr(const void* a, const void* b)
{
    const struct string* real_a = (const struct string*)a;
    const struct string* real_b = (const struct string*)b;
    const char* a_p = (*real_a).index;
    const char* b_p = (*real_b).index;
    while (*a_p != '\0' && *b_p != '\0')
    {
        while(!isalnum(*a_p) && *a_p != ' ')
            a_p++;
        while(!isalnum(*b_p) && *b_p != ' ')
            b_p++;
        if (tolower(*a_p) != tolower(*b_p))
        {
            //fprintf(stderr, "HERE: %d %d\n", tolower(*a_p), tolower(*b_p));
            return tolower(*a_p) - tolower(*b_p);
        }
        else
        {
            a_p++;
            b_p++;
        }
    }
    return *a_p - *b_p;
}

/*int back_cmpstr(const void* a, const void* b)
{
    const char* real_a = *(const char**)a;
    const char* real_b = *(const char**)b;
    const char* a_p = real_a;
    const char* b_p = real_b;
    while (*a_p != '\0' && *b_p != '\0')
    {
        while(!isalnum(*a_p) && *a_p != ' ')
            a_p++;
        while(!isalnum(*b_p) && *b_p != ' ')
            b_p++;
        if (tolower(*a_p) != tolower(*b_p))
        {
            //fprintf(stderr, "HERE: %d %d\n", tolower(*a_p), tolower(*b_p));
            return tolower(*a_p) - tolower(*b_p);
        }
        else
        {
            a_p++;
            b_p++;
        }
    }
    return *a_p - *b_p;
}*/
