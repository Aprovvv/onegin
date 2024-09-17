#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include "text_funcs.h"

const int STR_SIZE = 500;
const int HTML_SHIT = 25;

int main()
{
    struct text_t onegin = read_text_from_file("onegin.html");
    int count = onegin.str_count;
    free(onegin.index_array_p);
    free(onegin.text_p);

    FILE* original_fp = fopen("onegin.html", "r");
    FILE* parsed_fp = fopen("parsed_onegin.txt", "w");
    char string[STR_SIZE] = "";
    char* shit_pointer = NULL;
    struct stat data = {};
    char temp[100] = "";

    for (int i = 0; i < count; i++)
    {
        fgets(string, STR_SIZE, original_fp);
        //printf("%s\n", string);
        while (string[0] == ' ')
        {
            strcpy(temp, shit_pointer + 1);
            strcpy(shit_pointer, temp);
        }
        while ((shit_pointer = strchr(string + HTML_SHIT, '<')) != NULL)
        {
            int j = 0;
            while (*(shit_pointer + j) != '>')
                j++;
            if (*(shit_pointer + 1) == 's' && *(shit_pointer + 2) == 'u' && *(shit_pointer + 3) == 'p')
            {
                j++;
                while (*(shit_pointer + j) != '>')
                    j++;
            }
            strcpy(temp, shit_pointer + j + 1);
            strcpy(shit_pointer, temp);
        }
        while ((shit_pointer = strchr(string + HTML_SHIT, '&')) != NULL)
        {
            int j = 0;
            while (*(shit_pointer + j) != ';')
                j++;
            strcpy(temp, shit_pointer + j + 1);
            strcpy(shit_pointer, temp);
        }
        if (strlen(string) < 10 + HTML_SHIT)
            continue;
        fputs(string + HTML_SHIT, parsed_fp);
    }
    fputc('\n', parsed_fp);
    fclose(original_fp);
    fclose(parsed_fp);
}
