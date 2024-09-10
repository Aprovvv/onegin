#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SWAP(a, b) swap(a, b, sizeof(a))

const int STR_LEN = 48;
const int STR_COUNT = 14;

static void read_oneg(char oneg[STR_COUNT][STR_LEN], FILE* pointer_to_onegin);
static void sort_oneg(char oneg[STR_COUNT][STR_LEN]);
void swap(void* a, void* b, size_t size);
static void print_oneg(char oneg[STR_COUNT][STR_LEN]);
static void parse_string(char* str, size_t size);
static int my_strcmp(const char* s1, const char* s2);

int main()
{
    char oneg[STR_COUNT][STR_LEN] = {};

    FILE* pointer_to_onegin = fopen("parsed_oneg_1.txt", "r");
    read_oneg(oneg, pointer_to_onegin);
    sort_oneg(oneg);
    print_oneg(oneg);
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
            if (my_strcmp(s1, s2) > 0)
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
    char t;
    char* char_p1 = (char*)p1;
    char* char_p2 = (char*)p2;
    for (size_t i = 0; i < size; i++)
    {
        t = char_p1[i];
        char_p1[i] = char_p2[i];
        char_p2[i] = t;
    }
}

static void print_oneg(char oneg[STR_COUNT][STR_LEN])
{
    for (int i = 0; i < STR_COUNT; i++)
    {
        fputs(oneg[i], stdout);
    }
}

static int my_strcmp(const char* s1, const char* s2)
{
    int code_1 = 0, code_2 = 0, i = 0;

    do {
        code_1 = tolower(s1[i]);
        code_2 = tolower(s2[i]);
        i++;
        if (code_1 == 0 && code_2 ==0)
            return 0;
    } while (code_1 - code_2 == 0);
    return (code_1 - code_2);
}
