#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sort_funcs.h"

void swap(void* p1, void* p2, size_t size)
{
    char* char_p1 = (char*)p1;
    char* char_p2 = (char*)p2;
    int64_t int64_temp = 0;
    int32_t int32_temp = 0;
    char char_temp = 0;
    for (; size >= 8; size -= 8)
    {
        memcpy(&int64_temp, char_p1, 8);
        memcpy(char_p1, char_p2, 8);
        memcpy(char_p2, &int64_temp, 8);
        char_p1 += 8;
        char_p2 += 8;
    }
    for (; size >= 4; size -= 4)
    {
        memcpy(&int32_temp, char_p1, 4);
        memcpy(char_p1, char_p2, 4);
        memcpy(char_p2, &int32_temp, 4);
        char_p1 += 4;
        char_p2 += 4;
    }
    for (; size > 0; size--)
    {
        char_temp = *char_p1;
        *char_p1 = *char_p2;
        *char_p2 = char_temp;
        char_p1++;
        char_p2++;
    }
}

void bubble_sort(void* data, size_t nmemb,
                 size_t size, comparator compare)
{
    char* ptr = (char*)data;
    for (size_t i = 0; i < nmemb - 1; i++)
    {
        for (size_t j = 0; j < nmemb - 1; j++)
        {
            if (compare(ptr + j*size, ptr + (j + 1)*size) > 0)
            {
                swap(ptr + j*size, ptr + (j + 1)*size, size);
            }
        }
    }
}

