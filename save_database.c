#include <stdio.h>
#include "main.h"

/* 
 * save_database.c
 * ----------------
 * saves the current database to a text file (database_backup.txt)
 * preserves word, file counts, and file names
 */


int save_database(MAIN_NODE *hash_table[])
{
    FILE *fp;
    int i;

    fp = fopen("database_backup.txt", "w");
    if (fp == NULL)
    {
        printf("Error: Unable to create backup file\n");
        return FAILURE;
    }

    /* traverse hash table */
    for (i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] != NULL)
        {
            SUB_NODE *stemp = hash_table[i]->sub_link;

            /* traverse sub (word) nodes */
            while (stemp)
            {
                fprintf(fp, "#%d: %s: %d: ",
                        i,
                        stemp->word,
                        stemp->file_count);

                F_NODE *ftemp = stemp->f_link;

                /* Traverse file nodes */
                while (ftemp)
                {
                    fprintf(fp, "%s: %d: ",
                            ftemp->fname,
                            ftemp->word_count);

                    ftemp = ftemp->f_link;
                }

                fprintf(fp, "\n");
                stemp = stemp->sub_link;
            }
        }
    }

    fclose(fp);
    printf("Database saved successfully to database_backup.txt\n");
    return SUCCESS;
}
