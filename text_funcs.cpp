#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include "text_funcs.h"

struct text_t {
    size_t size;
    size_t str_count;
    char* text_p;
    struct string* string_array_p;
};

struct text_t* read_text_from_file(const char* name)
{
    struct text_t* answer = (struct text_t*)calloc(1, sizeof(struct text_t));
    struct stat data = {};
    size_t str_count = 0;

    FILE* file_p = fopen(name, "rb");
    stat(name, &data);
    answer->text_p = (char*)calloc((size_t)data.st_size + 1, 1);
    answer->size = (size_t)data.st_size + 1;
    fread(answer->text_p, 1, answer->size, file_p);
    *(answer->text_p + answer->size - 1) = '\n';

    for (size_t i = 0; i < answer->size - 1; i++)
        if(*(answer->text_p + i) == '\n')
        {
            str_count++;
            *(answer->text_p + i) = '\0';
        }
    answer->str_count = str_count;

    answer->string_array_p = (struct string*)calloc(str_count, sizeof(struct string));
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
            //fprintf(stderr, "Строка %d, len = %d, strlen = %d\n",
            //current_str_index - 1, answer->string_array_p[current_str_index - 1].len, strlen(answer->string_array_p[current_str_index - 1].index);
        }
    }
    answer->string_array_p[current_str_index].len = answer->size - 3 - (size_t)prev_i;
    //fprintf(stderr, "Строка %d, len = %d, strlen = %d\n",
    //current_str_index, answer->string_array_p[current_str_index].len, strlen(answer->string_array_p[current_str_index].index));
    fclose(file_p);
    return answer;
}

void destruct(struct text_t* struct_p)
{
    free(struct_p->text_p);
    free(struct_p->string_array_p);
    free(struct_p);
}

/*struct text_t {
    size_t size;
    size_t str_count;
    char* text_p;
    struct string* string_array_p;
};*/

size_t text_t_size(struct text_t* struct_p)
{
    return(struct_p->size);
}

size_t text_t_str_count(struct text_t* struct_p)
{
    return(struct_p->str_count);
}

char* text_t_text_p(struct text_t* struct_p)
{
    return(struct_p->text_p);
}

struct string* text_t_str_arr_p(struct text_t* struct_p)
{
    return(struct_p->string_array_p);
}
