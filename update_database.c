#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

/* 
 * update_database.c
 * -----------------
 * updates the database by adding a new file
 * processes all words in the new file, updates counts and file list
 */

int update_database(MAIN_NODE *hash_table[], char *filename)
{
    FILE *fp;
    char word[SIZE];
    int index;

    /* open file */
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Unable to open file %s\n", filename);
        return FAILURE;
    }

    /* read words from file */
    while (fscanf(fp, "%s", word) != EOF)
    {
        /* convert word to lowercase */
        for (int i = 0; word[i]; i++)
            word[i] = tolower(word[i]);

        index = word[0] % 97;

        /* if index empty -> create main node */
        if (hash_table[index] == NULL)
        {
            hash_table[index] = malloc(sizeof(MAIN_NODE));
            hash_table[index]->index = index;
            hash_table[index]->sub_link = NULL;
        }

        SUB_NODE *stemp = hash_table[index]->sub_link;
        SUB_NODE *sprev = NULL;

        /* search word */
        while (stemp)
        {
            if (strcmp(stemp->word, word) == 0)
                break;
            sprev = stemp;
            stemp = stemp->sub_link;
        }

        /* word not found -> create new word + file node */
        if (stemp == NULL)
        {
            SUB_NODE *new_word = malloc(sizeof(SUB_NODE));
            strcpy(new_word->word, word);
            new_word->file_count = 1;
            new_word->sub_link = NULL;

            F_NODE *new_file = malloc(sizeof(F_NODE));
            strcpy(new_file->fname, filename);
            new_file->word_count = 1;
            new_file->f_link = NULL;

            new_word->f_link = new_file;

            if (sprev == NULL)
                hash_table[index]->sub_link = new_word;
            else
                sprev->sub_link = new_word;
        }
        else
        {
            /* word found -> search file node */
            F_NODE *ftemp = stemp->f_link;
            F_NODE *fprev = NULL;

            while (ftemp)
            {
                if (strcmp(ftemp->fname, filename) == 0)
                    break;
                fprev = ftemp;
                ftemp = ftemp->f_link;
            }

            /* same word & same file -> ignorer */
            if (ftemp)
                continue;

            /* same word & new file */
            F_NODE *new_file = malloc(sizeof(F_NODE));
            strcpy(new_file->fname, filename);
            new_file->word_count = 1;
            new_file->f_link = NULL;

            fprev->f_link = new_file;
            stemp->file_count++;
        }
    }

    fclose(fp);
    printf("Database updated successfully with %s\n", filename);
    return SUCCESS;
}
