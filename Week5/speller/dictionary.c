// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;

int size_dict = 0;

// Hash table
node *table[N];
// unload function
void unloader(node *current);
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the word
    // access linked list at that index in the hash table
    int index = hash(word);

    if (table[index] == NULL)
    {
        return false;
    }
    else
    {
        node *cursor = table[index];

        while (cursor != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
            else
            {
                cursor = cursor->next;
            }
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int lon = strlen(word);
    int val = 0;
    if (lon > 2)
    {
        for (int i = 0; i < lon; i++)
        {
            if ((toupper(word[i])) >= 65 && toupper(word[i]) <= 90)
            {
                val = val + (toupper(word[i]) - 'A');
            }
            else if ((int) (word[i]) == 39)
            {
                val = 27;
            }
        }
    }
    else if (lon == 1)
    {
        if (toupper(word[0]) >= 65 && toupper(word[0]) <= 90)
        {
            val = (toupper(word[0]) - 'A');
        }
        else if ((int) (word[0]) == 39)
        {
            val = 27;
        }
    }
    return val % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    // Ask if a dictionary was provide
    FILE *infile = fopen(dictionary, "r");

    if (!infile)
    {
        printf("Error opening Dictionary!\n");
        return false;
    }
    char word_dict[LENGTH + 1];

    while (fscanf(infile, "%s", word_dict) != EOF)
    {
        // Create a new node for hash table and ask for available memory
        node *new = malloc(sizeof(node));

        if (new == NULL)
        {
            fclose(infile);
            return false;
        }
        // values for new node, asigno palabra y luego puntero

        strcpy(new->word, word_dict);

        new->next = NULL;
        // Call hash function to obtain hash value
        int index = hash(word_dict);
        // find the index in a hash matrix

        if (table[index] == NULL)
        {
            table[index] = new;
        }
        else
        {
            new->next = table[index];

            table[index] = new;
        }
        size_dict += 1;
    }
    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_dict;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            unloader(table[i]);
        }
    }
    return true;
}

void unloader(node *current)
{
    node *cursor = current;
    if (cursor->next != NULL)
    {
        unloader(cursor->next);
    }
    free(cursor);
    cursor = NULL;
}
