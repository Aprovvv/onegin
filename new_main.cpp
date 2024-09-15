#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "text_funcs.h"
#include "sort_funcs.h"

#define SWAP(a, b) swap(a, b, sizeof(a))

static void pr2(struct text_t t);
void sort_text_t(struct text_t orig, struct text_t parsed);

int main()
{
    /*struct text_t onegin = read_text_from_file("parsed_oneg_1.txt");
    pr2(onegin);

    putchar('\n');

    struct text_t parsed_text_p = parse_text(onegin);
    pr2(parsed_text_p);

    putchar('\n');

    sort_text_t(onegin, parsed_text_p);
    pr2(parsed_text_p);
    putchar('\n');
    pr2(onegin);

    free(parsed_text_p.text_p);
    free(parsed_text_p.index_array_p);
    free(onegin.text_p);
    free(onegin.index_array_p);*/

    int arr[] = {152, 84, 95, 45, 12, 68, 2};
    my_sort(arr, 7, compar_int);
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", arr[i]);
    }
}

void sort_text_t(struct text_t orig, struct text_t parsed)
{
    for (size_t i = 0; i < parsed.str_count - 1; i++)
    {
        for (size_t j = 0; j < parsed.str_count - 1; j++)
        {
            if (strcmp(parsed.index_array_p[j], parsed.index_array_p[j + 1]) > 0)
            {
                swap(&orig.index_array_p[j], &orig.index_array_p[j + 1], sizeof(char*));
                swap(&parsed.index_array_p[j], &parsed.index_array_p[j + 1], sizeof(char*));
            }
        }
    }
}

static void pr2(struct text_t t)
{
    for (size_t i = 0; i < t.str_count; i++)
    {
        puts(*(t.index_array_p+i));
    }
}
