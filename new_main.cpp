#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define SWAP(a, b) swap(a, b, sizeof(a))

struct text_t {
    size_t size;
    size_t max_str_len;
    size_t str_count;
    char* text_p;
    char** index_array_p;
};

struct text_t read_text_from_file(const char* name);
//static char** parse_buffer(char* str, size_t size);
void swap(void* p1, void* p2, size_t size);
static void pr(struct text_t a);


int main()
{
    struct stat onegin_data = {};

    struct text_t onegin = read_text_from_file("parsed_oneg_1.txt");
    pr(onegin);

    free(onegin.text_p);
    free(onegin.index_array_p);
}

struct text_t read_text_from_file(const char* name)
{
    struct text_t answer = {};
    struct stat data = {};
    size_t str_count = 1;

    FILE* file_p = fopen(name, "rb");
    stat(name, &data);
    answer.text_p = (char*)calloc((size_t)data.st_size + 1, 1);
    answer.size = (size_t)data.st_size + 1;
    fread(answer.text_p, 1, answer.size, file_p);
    *(answer.text_p + answer.size - 1) = '\n';

    for (size_t i = 0; i < answer.size; i++)
        if(*(answer.text_p + i) == '\n')
            str_count++;
    answer.str_count = str_count;

    answer.index_array_p = (char**)calloc(str_count, sizeof(char**));
    size_t current_str_index = 0;
    //fprintf(stderr, "str_count = %lu, answer.size - 1 = %lu\n", str_count, answer.size - 1);
    for (size_t i = 0; i < answer.size - 1; i++)
    {
        //fprintf(stderr, "current_str_index = %lu, answer.text_p + i + 1 = %lu; символ %c\n", current_str_index, i + 1, *(answer.text_p + i + 1));
        if (*(answer.text_p + i) == '\n')
        {
            //fprintf(stderr, "зашел в if\n");
            *(answer.index_array_p + current_str_index) = answer.text_p + i + 1;
            current_str_index++;
        }
    }

    size_t len = 0;
    for (size_t i = 0; i < answer.str_count - 1; i++)
    {
        len = (size_t)(*(answer.index_array_p + i + 1) - *(answer.index_array_p + i));
        if (len > answer.max_str_len)
            answer.max_str_len = len;
    }
    return answer;
}

/*static char** parse_buffer(struct text_t)
{
    //char** parsed_buf_p = (char**)calloc
    return 0;
}*/

static void pr(struct text_t a)
{
    for (size_t i = 0; i < a.size; i++)
        putchar(*(a.text_p+i));
}

void swap(void* p1, void* p2, size_t size)
{
    int64_t* int64_p1 = (int64_t*)p1;
    int64_t* int64_p2 = (int64_t*)p2;
    int64_t int64_temp = 0;
    for (; size >= 8; size -= 8)
    {
        int64_temp = *int64_p1;
        *int64_p1 = *int64_p2;
        *int64_p2 = int64_temp;
        int64_p1++;
        int64_p2++;
    }

    int32_t* int32_p1 = (int32_t*)int64_p1;
    int32_t* int32_p2 = (int32_t*)int64_p1;
    int32_t int32_temp = 0;
    for (; size >= 4; size -= 4)
    {
        int32_temp = *int32_p1;
        *int32_p1 = *int32_p2;
        *int32_p2 = int32_temp;
        int32_p1++;
        int32_p2++;
    }

    char* char_p1 = (char*)int32_p1;
    char* char_p2 = (char*)int32_p2;
    char char_temp = 0;
    for (; size > 0; size--)
    {
        char_temp = *char_p1;
        *char_p1 = *char_p2;
        *char_p2 = char_temp;
        char_p1++;
        char_p2++;
    }
}
