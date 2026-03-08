#include <stdio.h>
#include "main.h"

/* 
 * display_database.c
 * ------------------
 * displays the contents of the inverted search database
 * shows each word, file count, file names, and word count in each file
 */


void display_database(MAIN_NODE *hash_table[])
{
    int i;

    printf("\n---------------- INVERTED SEARCH DATABASE ----------------\n");

    /* traverse hash table */
    for (i = 0; i < TABLE_SIZE; i++)
    {
        /* if index not empty */
        if (hash_table[i] != NULL)
        {
            SUB_NODE *stemp = hash_table[i]->sub_link;

            /* traverse word nodes */
            while (stemp)
            {
                printf("[%d] %s: %d file(s) | ",
                       i,
                       stemp->word,
                       stemp->file_count);

                F_NODE *ftemp = stemp->f_link;

                /* traverse file nodes */
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
                stemp = stemp->sub_link;
            }
        }
    }

    printf("-----------------------------------------------------------\n");
}
