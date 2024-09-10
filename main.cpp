#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int STR_LEN = 48;
const int STR_COUNT = 14;

void read_oneg(char oneg[STR_COUNT][STR_LEN], FILE* pointer_to_onegin);
int my_strcmp(const char* s1, const char* s2);
void str_bubble_sort(char arr[STR_COUNT][STR_LEN]);
void swap(char* p1, char* p2);
void print_oneg(char oneg[STR_COUNT][STR_LEN]);

int main()
{
    char oneg[STR_COUNT][STR_LEN] = {};

    FILE* pointer_to_onegin = fopen("parsed_oneg_1.txt", "r");
    char s1[STR_LEN] = "abc";
    char s2[STR_LEN] = "def";
    char ch;

    read_oneg(oneg, pointer_to_onegin);

    str_bubble_sort(oneg);

    print_oneg(oneg);
}

void read_oneg(char oneg[STR_COUNT][STR_LEN], FILE* pointer_to_onegin)
{
    for (int i = 0; i < STR_COUNT; i++)
    {
        fgets(oneg[i], STR_LEN, pointer_to_onegin);
    }
}

int my_strcmp(const char* s1, const char* s2)
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

void str_bubble_sort(char arr[STR_COUNT][STR_LEN])
{
    for (int i = 0; i < STR_COUNT - 1; i++)
    {
        for (int j = 0; j < STR_COUNT - 1; j++)
        {
            if (my_strcmp(arr[j], arr[j+1]) > 0)
                swap(arr[j], arr[j+1]);
        }
    }
}

void swap(char* p1, char* p2)
{
    char t;
    for (int i = 0; i < STR_LEN; i++)
    {
        t = *(p1 + i);
        *(p1 + i) = *(p2 + i);
        *(p2 + i) = t;
    }
}

void print_oneg(char oneg[STR_COUNT][STR_LEN])
{
    for (int i = 0; i < STR_COUNT; i++)
    {
        fputs(oneg[i], stdout);
    }
}
