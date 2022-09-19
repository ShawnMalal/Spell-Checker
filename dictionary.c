// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
   char word[LENGTH + 1];
   struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 66000;

// Hash table
node *table[N];

// Declare words to count the words in the dictionary
int dic_size = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
   unsigned int hash = 0;

   for (int i = 0, n = strlen(word); i < n; i++){

       hash = (hash << 2) ^ word[i];

   }
   return hash % N;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
   int len = strlen(word);

   char newWord[len + 1];
   for (int i = 0; i < len; i++){
       newWord[i] = tolower(word[i]);

   }
   newWord[len] = '\0';

   int hash_code = hash(newWord);

   node *tmp = table[hash_code];
   while (tmp != NULL) {

       if (strcmp(tmp->word, newWord) != 0){
           tmp = tmp->next;
       }
       else {
          return true;
       }
   }
   return false;
}




// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
   FILE *input_dictionary = fopen(dictionary, "r");
   char *dicword = malloc(LENGTH + 1);

   while (fscanf(input_dictionary, "%s", dicword) != EOF){
       node *n = malloc(sizeof(node));
       n->next = NULL;

       if (n == NULL){
           return false;
       }

       strcpy(n->word, dicword);

       dic_size++;

       n->next = table[hash(dicword)];

       table[hash(dicword)] = n;
   }
   fclose(input_dictionary);
   free(dicword);
   return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
   return dic_size;

}
void destroy(node *head)
{
   if (head->next != NULL)
   {
       destroy(head->next);
   }
   free(head);
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
   for (int i = 0; i < N - 1; i++){
       if (table[i] != NULL) {
           destroy(table[i]);

       }
   }
    return true;
}
