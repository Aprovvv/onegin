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

struct string {
    char* index;
    size_t len;
};

struct text_t {
    size_t size;
    size_t str_count;
    char* text_p;
    struct string* string_array_p;
};

struct text_t* t_read_from_file(const char* name)
{
    struct text_t* answer = (struct text_t*)calloc(1, sizeof(struct text_t));
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED, "ERROR failed to allocate memory for struct text_t: %s\n", strerror(errno));
        return NULL;
    }
    struct stat data = {};
    size_t str_count = 0;
    FILE* file_p = fopen(name, "rb");
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED, "ERROR failed to open file %s: %s\n", name, strerror(errno));
        free(answer);
        return NULL;
    }
    stat(name, &data);
    answer->text_p = (char*)calloc((size_t)data.st_size + 1, 1);
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED, "ERROR failed to allocate memory for text: %s\n", strerror(errno));
        free(answer);
        return NULL;
    }
    answer->size = (size_t)data.st_size + 1;
    fread(answer->text_p, 1, answer->size, file_p);
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

    answer->string_array_p = (struct string*)calloc(str_count, sizeof(struct string));
    if (errno)
    {
        fprintf_color(stderr, CONSOLE_TEXT_RED, "ERROR failed to allocate memory for struct string* array: %s\n", strerror(errno));
        free(answer->text_p);
        free(answer);
        return NULL;
    }
    answer->string_array_p[0].index = answer->text_p;
    size_t current_str_index = 0;
    int prev_i = -1;
    for (size_t i = 0; i < answer->size - 2; i++)
    {
        if (*(answer->text_p + i) == '\0')
        {
            current_str_index++;
            answer->string_array_p[current_str_index].index = answer->text_p + i + 1;
            answer->string_array_p[current_str_index - 1].len = i - (size_t)prev_i - 1;
            prev_i = (int)i;
        }
    }
    answer->string_array_p[current_str_index].len = answer->size - 3 - (size_t)prev_i;
    fclose(file_p);
    return answer;
}

void t_destruct(struct text_t* struct_p)
{
    free(struct_p->text_p);
    free(struct_p->string_array_p);
    free(struct_p);
}

size_t t_size(const struct text_t* struct_p)
{
    return struct_p->size;
}

size_t t_str_count(const struct text_t* struct_p)
{
    return struct_p->str_count;
}

char* t_text_p(const struct text_t* struct_p)
{
    return struct_p->text_p;
}

struct string* t_string_p(const struct text_t* struct_p, size_t string_numb)
{
    return struct_p->string_array_p + string_numb;
}

size_t t_line_len(const struct text_t* struct_p, size_t line_number)
{
    return (struct_p->string_array_p + line_number)->len;
}

size_t str_line_len(const struct string* struct_p, size_t line_number)
{
    return (struct_p + line_number)->len;
}

char* t_line_p(const struct text_t* struct_p, size_t line_number)
{
    return (struct_p->string_array_p + line_number)->index;
}

char* str_line_p(const struct string* struct_p, size_t line_number)
{
    return (struct_p + line_number)->index;
}

size_t string_size(void)
{
    return (sizeof(string));
}
