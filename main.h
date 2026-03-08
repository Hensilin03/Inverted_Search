/* 
 * main.h
 * -------
 * header file for inverted search database project
 * defines all structures, constants, and function prototypes
 */

 #ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1
#define SIZE 50
#define TABLE_SIZE 26

/*File node: tracks occurrences of a word within a specific file*/
typedef struct file_node{

    char fname[SIZE];
    int word_count;
    struct file_node *f_link;
}F_NODE;

/*Sub node: stores unique word, global file count and list of files*/
typedef struct sub_node{
    
    char word[SIZE];
    int file_count;
    F_NODE *f_link;
    struct sub_node *sub_link;
}SUB_NODE;

/*Main node: represents a hash table pointing to a list of words*/
typedef struct main_node{
    
    int index;
    SUB_NODE *sub_link;
} MAIN_NODE;

/* ---------------- Validation list node ---------------- */
typedef struct file_list
{
    char fname[SIZE];
    struct file_list *link;
} FILE_LIST;
 
/* ----------- Function Prototypes ----------- */

int create_database(MAIN_NODE *hash_table[], FILE_LIST *head);
void display_database(MAIN_NODE *hash_table[]);
int search_database(MAIN_NODE *hash_table[], char *word);
int update_database(MAIN_NODE *hash_table[], char *filename);
int save_database(MAIN_NODE *hash_table[]);
int validate_files(int argc, char *argv[], FILE_LIST **head);

#endif