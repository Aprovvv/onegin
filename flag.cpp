/**@file */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "flag.h"

int analyze_flag(const struct flag_struct all_flags[],
                 int flag_count, const char* argv)
{
    if (argv[0] != '-')
        return 0;
    if (strlen(argv) == 2)
        for (int i = 0; i < flag_count; i++)
        {
            if (argv[1] == all_flags[i].short_flag)
                return all_flags[i].short_flag;
        }
    else
        for (int i = 0; i < flag_count; i++)
        {
            if (strcmp(argv+1, all_flags[i].long_flag) == 0)
                return all_flags[i].short_flag;
        }
    return 0;
}
