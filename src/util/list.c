#include "include/list.h"
#include <stdlib.h>

// Generic list

/* -----------------------------------------------------------------------------
   LIST CREATE
   ---------------------------------------------------------------------------*/
mscsound_list_t *mscsound_list_create(void) { return NULL; }

/* -----------------------------------------------------------------------------
   LIST FREE
   ---------------------------------------------------------------------------*/
void mscsound_list_free(mscsound_list_t *list) {
  mscsound_list_t *temp = list;
  while (temp) {
    mscsound_list_t *temp2 = temp->next;
    free(temp);
    temp = temp2;
  }
}

/* -----------------------------------------------------------------------------
   LIST ADD ELEMENT
   ---------------------------------------------------------------------------*/
void mscsound_list_add_element(mscsound_list_t **list, void *data) {
  if (*list == NULL) {
    *list = malloc(sizeof(mscsound_list_t));
    (*list)->data = data;
    (*list)->next = NULL;
    return;
  }

  mscsound_list_t *last = *list;
  while (last && last->next) { // Find last element
    last = last->next;
  }
  mscsound_list_t *current = malloc(sizeof(mscsound_list_t));
  current->data = data;
  current->next = NULL;
  last->next = current;
}

/* -----------------------------------------------------------------------------
   LIST ADD UNIQUE ELEMENT
   ---------------------------------------------------------------------------*/
void mscsound_list_add_unique_element(
    mscsound_list_t **list, void *data,
    mscsound_list_compare compare_function) {
  if (mscsound_list_contains(list, data, compare_function) == 0)
    mscsound_list_add_element(list, data);
}

/* -----------------------------------------------------------------------------
   LIST CONTAINS ELEMENT
   ---------------------------------------------------------------------------*/
int mscsound_list_contains(mscsound_list_t **list, void *data,
                              mscsound_list_compare compare_function) {
  if (data == NULL || *list == NULL)
    return 0;

  mscsound_list_t *last = *list;
  while (last) { // Find last element
    if (compare_function(data, last->data) == 1)
      return 1;
    last = last->next;
  }
  return 0;
}

/* -----------------------------------------------------------------------------
   LIST REMOVE ELEMENT
   ---------------------------------------------------------------------------*/
void *
mscsound_list_remove_element(mscsound_list_t **list, const void *data,
                                mscsound_list_compare compare_function) {
  mscsound_list_t *current = NULL, *previous = NULL;

  if (list == NULL)
    return NULL;

  for (current = *list; current != NULL;
       previous = current, current = current->next) {
    // check value
    if (compare_function(current->data, data)) {
      if (previous == NULL) // remove first
        *list = current->next;
      else
        previous->next = current->next;

      return current->data;
    }
  }

  return NULL;
}

/* -----------------------------------------------------------------------------
   LIST LENGHT
   ---------------------------------------------------------------------------*/
int mscsound_list_lenght(mscsound_list_t *list) {
  int lenght = 0;

  mscsound_list_t *temp = list;
  while (temp) {
    lenght++;
    mscsound_list_t *temp2 = temp->next;
    temp = temp2;
  }

  return lenght;
}
/*----------------------------------------------------------------------------*/
