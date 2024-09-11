#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

#define SWAP(a, b) swap(a, b, sizeof(a))

const int STR_LEN = 48;
const int STR_COUNT = 14;

static void read_oneg(char oneg[STR_COUNT][STR_LEN], FILE* pointer_to_onegin);
static void sort_oneg(char oneg[STR_COUNT][STR_LEN]);
void swap(void* a, void* b, size_t size);
static void print_oneg(char oneg[STR_COUNT][STR_LEN]);
static void parse_string(char* str, size_t size);

int main()
{
    char oneg[STR_COUNT][STR_LEN] = {};

    FILE* pointer_to_onegin = fopen("parsed_oneg_1.txt", "r");
    read_oneg(oneg, pointer_to_onegin);
    sort_oneg(oneg);
    print_oneg(oneg);
    fclose(pointer_to_onegin);
}

static void read_oneg(char oneg[STR_COUNT][STR_LEN], FILE* pointer_to_onegin)
{
    int ch = 0;
    int i = 0;
    while((ch = fgetc(pointer_to_onegin)) != EOF)
    {
        ungetc(ch, pointer_to_onegin);
        fgets(oneg[i], STR_LEN, pointer_to_onegin);
        i++;
    }
}

static void sort_oneg(char oneg[STR_COUNT][STR_LEN])
{
    for (int i = 0; i < STR_COUNT - 1; i++)
    {
        for (int j = 0; j < STR_COUNT - 1; j++)
        {
            char s1[STR_LEN] = "";
            char s2[STR_LEN] = "";
            memcpy(s1, oneg[j], STR_LEN);
            memcpy(s2, oneg[j+1], STR_LEN);
            parse_string(s1, STR_LEN);
            parse_string(s2, STR_LEN);
            if (strcmp(s1, s2) > 0)
                SWAP(oneg[j], oneg[j+1]);
        }
    }
}

static void parse_string(char* str, size_t size)
{
    size_t length = strlen(str);
    size_t i = 0;
    while (str[i] != 0)
    {
        str[i] = (char)tolower(str[i]);
        if (!isalnum(str[i]) && !isspace(str[i]))
        {
            memmove(str + i, str + i + 1, size - i - 1);
            str[length] = 0;
            length--;
            i--;
        }
        i++;
    }
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

static void print_oneg(char oneg[STR_COUNT][STR_LEN])
{
    for (int i = 0; i < STR_COUNT; i++)
    {
        fputs(oneg[i], stdout);
    }
}
