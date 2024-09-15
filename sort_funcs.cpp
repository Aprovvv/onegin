#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sort_funcs.h"

typedef int(*cf)(int a, int b);

void swap(void* p1, void* p2, size_t size)
{
    int64_t* int64_p1 = (int64_t*)p1;
    int64_t* int64_p2 = (int64_t*)p2;
    int64_t int64_temp = 0;
    //printf("p1 = %p, p2 = %p\n", p1, p2);
    if (size >= 8)
        for (; size >= 8; size -= 8)
        {
            int64_temp = *int64_p1;
            *int64_p1 = *int64_p2;
            *int64_p2 = int64_temp;
            int64_p1++;
            int64_p2++;
        }
    //printf("int64_p1 = %p, int64_p2 = %p\n", int64_p1, int64_p2);
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
    //printf("int32_p1 = %p, int32_p2 = %p\n", int32_p1, int32_p2);
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
    //printf("char_p1 = %p, char_p2 = %p\n", char_p1, char_p2);
}

void my_sort(int* data, size_t size, cf compare)
{
    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t j = 0; j < size - 1; j++)
        {
            if (compare(data[j], data[j + 1]) > 0)
            {
                //printf("%d %d //",data[j], data[j + 1]);
                swap(data+j, data+j + 1, sizeof(int));
                //printf("%d %d\n", data[j], data[j + 1]);
            }
        }
    }
}

int compar_int(int a, int b)
{
    return a-b;
}
