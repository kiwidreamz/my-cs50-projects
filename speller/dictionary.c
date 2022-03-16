// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Global variable to count words loaded in dictionary
int global_dictionary_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    int hash_number = hash(word);

    node *temp = table[hash_number];
    while (temp != NULL)
    {
        int i = strcasecmp(word, temp -> word);
        if (i == 0)
        {
            return true;
        }
        else
        {
            temp = temp -> next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    /*
        int value = 0;

        int value_checker = (toupper(word[0] - 64) * toupper(word[1]) - 64);
        if (value_checker < 0)
        {
            value = (toupper(word[0]) + toupper(word[1])) - 65;
        }
        else
        {
            value = value_checker;
        }
    */

    int value = 0;

    for (int i = 0; word[i] != '\0'; i++)
    {
        value += tolower(word[i]);
    }

    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        //printf("Error in file opening\n");
        return false;
    }

    for (int z = 0; z < N; z++)
    {
        table[z] = NULL;
    }

    char temp_word[LENGTH + 1];

    while (fscanf(file, "%s\n", temp_word) != EOF)
    {
        node *current = malloc(sizeof(node));

        if (current == NULL)
        {
            printf("Memory allocation failed");
            return false;
        }

        strcpy(current -> word, temp_word);

        int hash_number = hash(temp_word);

        if (table[hash_number] == NULL)
        {
            current -> next = NULL;
            table[hash_number] = current;
        }
        else
        {
            current -> next = table[hash_number];
            table[hash_number] = current;
        }
        global_dictionary_count++;


    }
    //free(word);

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return global_dictionary_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        node *temp = table[i];

        while (temp != NULL)
        {
            node *cursor = temp;
            temp = temp -> next;
            free(cursor);
            // temp = cursor -> next;
        }
        table[i] = NULL;
    }


    return true;

}
