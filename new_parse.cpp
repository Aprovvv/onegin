#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

const int STR_SIZE = 500;
const int HTML_SHIT = 25;

int main()
{
    FILE* original_fp = fopen("onegin.html", "r");
    FILE* parsed_fp = fopen("parsed_onegin.txt", "w");
    char string[STR_SIZE] = "";
    char* shit_pointer = NULL;
    struct stat data = {};
    stat("onegin.txt", &data);

    for (int i = 0; i < 50; i++)
    {
        fgets(string, STR_SIZE, original_fp);
        //printf("%s\n", string);
        if (strlen(string) < 10 + HTML_SHIT)
            continue;
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
            strcpy(shit_pointer, shit_pointer + j + 1);
        }
        fputs(string + HTML_SHIT, parsed_fp);
    }
    fputc('\n', parsed_fp);
    fclose(original_fp);
    fclose(parsed_fp);
}
