#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

/* 
 * create_database.c
 * -----------------
 * creates the inverted search database from valid text files
 * uses hash table (main nodes) and linked lists (sub nodes + file nodes)
 */


int create_database(MAIN_NODE *hash_table[], FILE_LIST *head)
{
    FILE *fp;
    char word[SIZE], filename[SIZE];
    int i, index;

    /* initializing hash table with null so no garbage values */
    for (i = 0; i < TABLE_SIZE; i++)
        hash_table[i] = NULL;

    /* pointer to traverse validated file list */
    FILE_LIST *temp = head;

    /* loop through all valid files */
    while (temp)
    {
        strcpy(filename, temp->fname);   // copy filename from list

        /* open the file */
        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            /* file might be deleted later, so skip */
            temp = temp->link;
            continue;
        }

        /* read each word from file till eof */
        while (fscanf(fp, "%s", word) != EOF)
        {
            /* convert word into lowercase for uniformity */
            for (int j = 0; word[j]; j++)
                word[j] = tolower(word[j]);

            /* find index using hashing logic */
            index = word[0] % 97;

            /* if index is empty create main node */
            if (hash_table[index] == NULL)
            {
                hash_table[index] = malloc(sizeof(MAIN_NODE));
                hash_table[index]->index = index;
                hash_table[index]->sub_link = NULL;
            }

            /* traverse sub node list to find word */
            SUB_NODE *stemp = hash_table[index]->sub_link;
            SUB_NODE *sprev = NULL;

            while (stemp)
            {
                if (strcmp(stemp->word, word) == 0)
                    break;

                sprev = stemp;
                stemp = stemp->sub_link;
            }

            /* word not present, create new word node */
            if (stemp == NULL)
            {
                SUB_NODE *new_word = malloc(sizeof(SUB_NODE));
                if (new_word == NULL)
                    return FAILURE;

                strcpy(new_word->word, word);
                new_word->file_count = 1;     // first file for this word
                new_word->f_link = NULL;
                new_word->sub_link = NULL;

                /* create file node */
                F_NODE *new_file = malloc(sizeof(F_NODE));
                if (new_file == NULL)
                    return FAILURE;

                strcpy(new_file->fname, filename);
                new_file->word_count = 1;
                new_file->f_link = NULL;

                /* link file node to word node */
                new_word->f_link = new_file;

                /* attach word node to main list */
                if (sprev == NULL)
                    hash_table[index]->sub_link = new_word;
                else
                    sprev->sub_link = new_word;
            }
            else /* word already exists */
            {
                F_NODE *ftemp = stemp->f_link;
                F_NODE *fprev = NULL;

                /* check if same file already present */
                while (ftemp)
                {
                    if (strcmp(ftemp->fname, filename) == 0)
                        break;

                    fprev = ftemp;
                    ftemp = ftemp->f_link;
                }

                if (ftemp)   // same word same file
                {
                    ftemp->word_count++;
                }
                else        // same word but different file
                {
                    F_NODE *new_file = malloc(sizeof(F_NODE));

                    strcpy(new_file->fname, filename);
                    new_file->word_count = 1;
                    new_file->f_link = NULL;

                    fprev->f_link = new_file;   // attach file node
                    stemp->file_count++;        // increase file count
                }
            }
        }

        fclose(fp);          // close current file
        temp = temp->link;   // move to next file
    }

    printf("database created successfully\n");
    return SUCCESS;
}
