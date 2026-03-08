#include "main.h"

/* 
 * main.c
 * -------
 * menu driven program for inverted search database
 * calls create, display, search, update, save functions
 * handles user input and menu operations
 */

int main(int argc, char *argv[])
{
    MAIN_NODE *hash_table[TABLE_SIZE] = {NULL};
    FILE_LIST *valid_files = NULL;

    int choice;
    char word[SIZE];
    char filename[SIZE];

    /* ---------------- alidation ---------------- */
    if (validate_files(argc, argv, &valid_files) == FAILURE)
    {
        printf("No valid files to create database\n");
        return FAILURE;
    }

    /* ---------------- Create Database ---------------- */
    create_database(hash_table, valid_files);

    /* ---------------- Menu Driven Operations ---------------- */
    while (1)
    {
        printf("\n--------------- INVERTED SEARCH MENU ---------------\n");
        printf("1. Display Database\n");
        printf("2. Search Word\n");
        printf("3. Update Database\n");
        printf("4. Save Database\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                display_database(hash_table);
                break;

            case 2:
                printf("Enter word to search: ");
                scanf("%s", word);
                search_database(hash_table, word);
                break;

            case 3:
                printf("Enter filename to update: ");
                scanf("%s", filename);

                /* Update assumes validation already done */
                if (update_database(hash_table, filename) == SUCCESS)
                    printf("Update successful\n");
                else
                    printf("Update failed\n");
                break;

            case 4:
                save_database(hash_table);
                break;

            case 5:
                printf("Exiting program...\n");
                return SUCCESS;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return SUCCESS;
}
