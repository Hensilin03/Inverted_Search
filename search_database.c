#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

/* 
 * search_database.c
 * -----------------
 * searches for a given word in the database
 * prints which files contain the word and how many times
 */

int search_database(MAIN_NODE *hash_table[], char *search_word)
{
    int index;
    char word[SIZE];

    /* convert input word to lowercase */
    strcpy(word, search_word);
    for (int i = 0; word[i]; i++)
        word[i] = tolower(word[i]);

    /* calculate hash index */
    index = word[0] % 97;

    /* if index empty */
    if (hash_table[index] == NULL)
    {
        printf("Word '%s' not found in database\n", word);
        return FAILURE;
    }

    SUB_NODE *stemp = hash_table[index]->sub_link;

    /* search word node */
    while (stemp)
    {
        if (strcmp(stemp->word, word) == 0)
        {
            printf("\nWord found!\n");
            printf("[%d] %s: %d file(s) | ",
                   index,
                   stemp->word,
                   stemp->file_count);

            F_NODE *ftemp = stemp->f_link;

            /* display file list */
            while (ftemp)
            {
                printf("File: %s: %d time(s)",
                       ftemp->fname,
                       ftemp->word_count);

                ftemp = ftemp->f_link;

                if (ftemp)
                    printf("; ");
            }
            printf("\n");
            return SUCCESS;
        }
        stemp = stemp->sub_link;
    }

    /* word not found */
    printf("Word '%s' not found in database\n", word);
    return FAILURE;
}
