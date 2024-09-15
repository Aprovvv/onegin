#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sort_funcs.h"

void swap(void* p1, void* p2, size_t size)
{
    int64_t* int64_p1 = (int64_t*)p1;
    int64_t* int64_p2 = (int64_t*)p2;
    int64_t int64_temp = 0;
    if (size >= 8)
        for (; size >= 8; size -= 8)
        {
            int64_temp = *int64_p1;
            *int64_p1 = *int64_p2;
            *int64_p2 = int64_temp;
            int64_p1++;
            int64_p2++;
        }
    int32_t* int32_p1 = (int32_t*)int64_p1;
    int32_t* int32_p2 = (int32_t*)int64_p2;
    int32_t int32_temp = 0;
    if (size >= 4)
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
    if (size > 0)
        for (; size > 0; size--)
        {
            char_temp = *char_p1;
            *char_p1 = *char_p2;
            *char_p2 = char_temp;
            char_p1++;
            char_p2++;
        }
}

void my_sort(void* data, size_t nmemb, size_t size, cf compare)
{
    for (size_t i = 0; i < nmemb - 1; i++)
    {
        for (size_t j = 0; j < nmemb - 1; j++)
        {
            if (compare((char*)data + j * size, (char*)data + (j + 1) * size) > 0)
            {
                swap((char*)data + j * size, (char*)data + (j + 1) * size, sizeof(int));
            }
        }
    }
}

