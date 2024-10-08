#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "text_funcs.h"
#include "sort_funcs.h"
#include "color_print/color_print.h"
#include "flag.h"

const int flag_count = 2;
const struct flag_struct all_flags[flag_count] = {
    {'o', "o"},
    {'i', "i"}
};

static void pr(struct text_t* t, FILE* stream);
static int cmpstr(const void* a, const void* b);
static int back_cmpstr(const void* a, const void* b);
static int check_names(const char** output_name,
                       const char** onegin_name,
                       int argc, char* argv[]);

int main(int argc, char* argv[])
{
    const char* onegin_name = "parsed_onegin.txt";
    const char* output_name = "sorted_onegin.txt";
    if (check_names(&output_name, &onegin_name, argc, argv) == 1)
        return EXIT_FAILURE;

    struct text_t* onegin = text_t_read_from_file(onegin_name);
    if (onegin == NULL)
        return EXIT_FAILURE;
    FILE* output = fopen(output_name, "w");
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR: failed to open file %s: %s\n",
                      output_name, strerror(errno));
        return EXIT_FAILURE;
    }

    bubble_sort(text_t_string_p(onegin, 0),
                text_t_str_count(onegin),
                string_size(), cmpstr);
    pr(onegin, output);

    fputc('\n', output);

    bubble_sort(text_t_string_p(onegin, 0),
                text_t_str_count(onegin),
                string_size(), back_cmpstr);
    pr(onegin, output);

    t_destruct(onegin);
}

static void pr(struct text_t* t, FILE* stream)
{
    for (size_t i = 0; i < text_t_str_count(t); i++)
    {
        fputs(text_t_line_p(t, i), stream);
        fputc('\n', stream);
    }
}

static int cmpstr(const void* a, const void* b)
{
    const struct string* real_a = (const struct string*)a;
    const struct string* real_b = (const struct string*)b;
    const char* a_p = string_line_p(real_a, 0);
    const char* b_p = string_line_p(real_b, 0);
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

static int back_cmpstr(const void* a, const void* b)
{
    const struct string* real_a = (const struct string*)a;
    const struct string* real_b = (const struct string*)b;
    const char* a_start = string_line_p(real_a, 0);
    const char* b_start = string_line_p(real_b, 0);
    const char* a_p = a_start + string_line_len(real_a, 0) - 1;
    const char* b_p = b_start + string_line_len(real_b, 0) - 1;
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

static int check_names(const char** output_name,
                       const char** onegin_name,
                       int argc, char* argv[])
{
    for (int i = 1; i < argc; i++)
    {
        int flag = analyze_flag(all_flags, flag_count, argv[i]);
        switch (flag)
        {
        case 'o':
            if (i < argc - 1)
            {
                *output_name = argv[i + 1];
                i++;
            }
            else
            {
                fprintf_color(stderr, CONSOLE_TEXT_RED,
                              "ERROR: -o requires name of file\n");
                return 1;
            }
            break;
        case 'i':
            if (i < argc - 1)
            {
                *onegin_name = argv[i + 1];
                i++;
            }
            else
            {
                fprintf_color(stderr, CONSOLE_TEXT_RED,
                              "ERROR: -i requires name of file\n");
                return 1;
            }
            break;
        default:
            fprintf_color(stderr, CONSOLE_TEXT_RED,
                          "ERROR: undefined flag\n");
        }
    }
    return 0;
}
