#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include "text_funcs.h"
#include "color_print/color_print.h"

struct string
{
    char* index;
    size_t len;
};

struct text_t
{
    size_t size;
    size_t str_count;
    char* text_p;
    struct string* string_array_p;
};

struct text_t* text_t_read_from_file(const char* name)
{
    struct text_t* answer =
        (struct text_t*)calloc(1, sizeof(struct text_t));
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR failed to allocate memory "
                      "for struct text_t: %s\n",
                      strerror(errno));
    }
    *answer = {};
    struct stat data = {};
    size_t str_count = 0;
    size_t str_i = 0;
    int prev_i = -1;
    FILE* file_p = fopen(name, "rb");
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR failed to open file %s: %s\n",
                      name, strerror(errno));
        goto error_label;
    }
    stat(name, &data);
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR failed to get information "
                      "about file: %s\n",
                      strerror(errno));
        goto error_label;
    }
    answer->text_p = (char*)calloc((size_t)data.st_size + 1, 1);
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR failed to allocate memory "
                      "for text: %s\n",
                      strerror(errno));
        goto error_label;
    }
    answer->size = (size_t)data.st_size + 1;
    if (0 == fread(answer->text_p, 1, answer->size, file_p))
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR failed to read from file");
        goto error_label;
    }
    *(answer->text_p + answer->size - 1) = '\n';

    for (size_t i = 0; i < answer->size - 1; i++)
    {
        if(*(answer->text_p + i) == '\n')
        {
            str_count++;
            *(answer->text_p + i) = '\0';
        }
    }
    answer->str_count = str_count;

    answer->string_array_p =
        (struct string*)calloc(str_count, sizeof(struct string));
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR failed to allocate memory "
                      "for struct string* array: %s\n",
                      strerror(errno));
        goto error_label;
    }
    answer->string_array_p[0].index = answer->text_p;
    for (size_t i = 0; i < answer->size - 2; i++)
    {
        if (*(answer->text_p + i) == '\0')
        {
            str_i++;
            answer->string_array_p[str_i].index =
                answer->text_p + i + 1;
            answer->string_array_p[str_i - 1].len =
                i - (size_t)prev_i - 1;
            prev_i = (int)i;
        }
    }
    answer->string_array_p[str_i].len =
        answer->size - 3 - (size_t)prev_i;
    fclose(file_p);
    if (errno)
        fprintf_color(stderr, CONSOLE_TEXT_RED,
                      "ERROR failed to close file: %s\n",
                      strerror(errno));
    return answer;
error_label:
    if (file_p != NULL)
        fclose(file_p);
    free(answer->text_p);
    free(answer);
    return NULL;
}

void t_destruct(struct text_t* ptr)
{
    free(ptr->text_p);
    free(ptr->string_array_p);
    free(ptr);
}

size_t text_t_size(const struct text_t* ptr)
{
    return ptr->size;
}

size_t text_t_str_count(const struct text_t* ptr)
{
    return ptr->str_count;
}

char* text_t_text_p(const struct text_t* ptr)
{
    return ptr->text_p;
}

struct string* text_t_string_p(const struct text_t* ptr,
                          size_t string_numb)
{
    return ptr->string_array_p + string_numb;
}

size_t text_t_line_len(const struct text_t* ptr,
                  size_t line_n)
{
    return (ptr->string_array_p + line_n)->len;
}

size_t string_line_len(const struct string* ptr,
                    size_t line_n)
{
    return (ptr + line_n)->len;
}

char* text_t_line_p(const struct text_t* ptr,
               size_t line_n)
{
    return (ptr->string_array_p + line_n)->index;
}

char* string_line_p(const struct string* ptr,
                 size_t line_n)
{
    return (ptr + line_n)->index;
}

size_t string_size(void)
{
    return (sizeof(string));
}
