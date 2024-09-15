#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include "text_funcs.h"

struct text_t read_text_from_file(const char* name)
{
    struct text_t answer = {};
    struct stat data = {};
    size_t str_count = 0;

    FILE* file_p = fopen(name, "rb");
    stat(name, &data);
    answer.text_p = (char*)calloc((size_t)data.st_size + 1, 1);
    answer.size = (size_t)data.st_size + 1;
    fread(answer.text_p, 1, answer.size, file_p);
    *(answer.text_p + answer.size - 1) = '\n';

    for (size_t i = 0; i < answer.size - 1; i++)
        if(*(answer.text_p + i) == '\n')
        {
            str_count++;
            *(answer.text_p + i) = '\0';
        }
    answer.str_count = str_count;

    answer.index_array_p = (char**)calloc(str_count, sizeof(char*));
    *answer.index_array_p = answer.text_p;
    size_t current_str_index = 0;
    //fprintf(stderr, "str_count = %lu, answer.size - 1 = %lu\n", str_count, answer.size - 1);
    for (size_t i = 0; i < answer.size - 2; i++)
    {
        //fprintf(stderr, "current_str_index = %lu, answer.text_p + i + 1 = %lu; символ %c\n", current_str_index, i + 1, *(answer.text_p + i + 1));
        if (*(answer.text_p + i) == '\0')
        {
            //fprintf(stderr, "зашел в if\n");
            current_str_index++;
            *(answer.index_array_p + current_str_index) = answer.text_p + i + 1;
        }
    }
    //printf("str_count = %d\n", (int)str_count);
    return answer;
}

struct text_t parse_text(struct text_t original)
{
    struct text_t answer = {};
    answer.index_array_p = (char**)calloc(original.str_count, sizeof(char*));
    answer.text_p = (char*)calloc(original.size, 1);
    answer.size = original.size;
    answer.str_count = original.str_count;
    char* orig_p = original.text_p;
    char* copy_p = answer.text_p;
    size_t line_count = 0;

    *(answer.index_array_p) = copy_p;
    //fprintf(stderr, "%p\n", *(answer.index_array_p));
    for(size_t i = 0; i < original.size - 1; i++)
    {
        if (isalnum(*orig_p) || *orig_p == ' ')
            *copy_p = (char)tolower(*orig_p);
        else
        {
            if (*orig_p == '\0' && i < original.size - 2)
            {
                line_count++;
                *copy_p = '\0';
                *(answer.index_array_p + line_count) = copy_p + 1;
                //fprintf(stderr, "%p\n", *(answer.index_array_p + line_count));
            }
            else
            {
                copy_p--;
            }
        }
        orig_p++;
        copy_p++;
    }
    return answer;
}
