#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "text_funcs.h"
#include "sort_funcs.h"

static void pr(struct text_t* t, FILE* stream);
int cmpstr(const void* a, const void* b);
int back_cmpstr(const void* a, const void* b);

int main()
{
    struct text_t* onegin = t_read_from_file("parsed_onegin.txt");
    if (onegin == NULL)
        return errno;
    FILE* output = fopen("sorted_onegin.txt", "w");
    if (errno)
    {
        printf("ERROR: failed to open file^ %s", strerror(errno));
        return errno;
    }

    my_sort(t_string_p(onegin, 0), t_str_count(onegin), string_size(), cmpstr);
    pr(onegin, output);

    fputc('\n', output);

    my_sort(t_string_p(onegin, 0), t_str_count(onegin), string_size(), back_cmpstr);
    pr(onegin, output);

    t_destruct(onegin);
}

static void pr(struct text_t* t, FILE* stream)
{
    for (size_t i = 0; i < t_str_count(t); i++)
    {
        fputs(t_line_p(t, i), stream);
        fputc('\n', stream);
    }
}

int cmpstr(const void* a, const void* b)
{
    const struct string* real_a = (const struct string*)a;
    const struct string* real_b = (const struct string*)b;
    const char* a_p = str_line_p(real_a, 0);
    const char* b_p = str_line_p(real_b, 0);
    while (*a_p != '\0' && *b_p != '\0')
    {
        while(!isalnum(*a_p) && *a_p != ' ')
            a_p++;
        while(!isalnum(*b_p) && *b_p != ' ')
            b_p++;
        if (tolower(*a_p) != tolower(*b_p))
        {
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
    const char* a_start = str_line_p(real_a, 0);
    const char* b_start = str_line_p(real_b, 0);
    const char* a_p = a_start + str_line_len(real_a, 0) - 1;
    const char* b_p = b_start + str_line_len(real_b, 0) - 1;
    while(!isalnum(*a_p))
        a_p--;
    while(!isalnum(*b_p))
        b_p--;
    while (a_p >= a_start && b_p >= b_start)
    {
        while(!isalnum(*a_p) && *a_p != ' ')
            a_p--;
        while(!isalnum(*b_p) && *b_p != ' ')
            b_p--;
        if (tolower(*a_p) != tolower(*b_p))
        {
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
