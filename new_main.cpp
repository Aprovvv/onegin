#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "text_funcs.h"
#include "sort_funcs.h"

static void pr(struct text_t* t, FILE* stream);
int cmpstr(const void* a, const void* b);
int back_cmpstr(const void* a, const void* b);

int main()
{
    struct text_t* onegin = t_read_from_file("parsed_onegin.txt");
    FILE* output = fopen("sorted_onegin.txt", "w");

    my_sort(t_str_arr_p(onegin), t_str_count(onegin), sizeof(struct string), cmpstr);
    pr(onegin, output);

    fputc('\n', output);

    my_sort(t_str_arr_p(onegin), t_str_count(onegin), sizeof(struct string), back_cmpstr);
    pr(onegin, output);

    t_destruct(onegin);
}

static void pr(struct text_t* t, FILE* stream)
{
    for (size_t i = 0; i < t_str_count(t); i++)
    {
        fputs((t_str_arr_p(t) + i)->index, stream);
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

int back_cmpstr(const void* a, const void* b)
{
    const struct string* real_a = (const struct string*)a;
    const struct string* real_b = (const struct string*)b;
    const char* a_p = (*real_a).index + (*real_a).len - 1;
    const char* b_p = (*real_b).index + (*real_b).len - 1;
    //fprintf(stderr, "THERE: %d\n", *a_p);
    while(!isalnum(*a_p))
        a_p--;
    while(!isalnum(*b_p))
        b_p--;
    while (a_p >= (*real_a).index && b_p >= (*real_b).index)
    {
        while(!isalnum(*a_p) && *a_p != ' ')
            a_p--;
        while(!isalnum(*b_p) && *b_p != ' ')
            b_p--;
        if (tolower(*a_p) != tolower(*b_p))
        {
            //fprintf(stderr, "HERE: %d %d\n", tolower(*a_p), tolower(*b_p));
            return tolower(*a_p) - tolower(*b_p);
        }
        else
        {
            a_p--;
            b_p--;
        }
    }
    return *a_p - *b_p;
}
