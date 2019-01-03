#include "include/list.h"
#include <stdlib.h>

// Generic list

/* -----------------------------------------------------------------------------
   LIST CREATE
   ---------------------------------------------------------------------------*/
mosaicsound_list_t *mosaicsound_list_create(void) { return NULL; }

/* -----------------------------------------------------------------------------
   LIST FREE
   ---------------------------------------------------------------------------*/
void mosaicsound_list_free(mosaicsound_list_t *list) {
  mosaicsound_list_t *temp = list;
  while (temp) {
    mosaicsound_list_t *temp2 = temp->next;
    free(temp);
    temp = temp2;
  }
}

/* -----------------------------------------------------------------------------
   LIST ADD ELEMENT
   ---------------------------------------------------------------------------*/
void mosaicsound_list_add_element(mosaicsound_list_t **list, void *data) {
  if (*list == NULL) {
    *list = malloc(sizeof(mosaicsound_list_t));
    (*list)->data = data;
    (*list)->next = NULL;
    return;
  }

  mosaicsound_list_t *last = *list;
  while (last && last->next) { // Find last element
    last = last->next;
  }
  mosaicsound_list_t *current = malloc(sizeof(mosaicsound_list_t));
  current->data = data;
  current->next = NULL;
  last->next = current;
}

/* -----------------------------------------------------------------------------
   LIST ADD UNIQUE ELEMENT
   ---------------------------------------------------------------------------*/
void mosaicsound_list_add_unique_element(
    mosaicsound_list_t **list, void *data,
    mosaicsound_list_compare compare_function) {
  if (mosaicsound_list_contains(list, data, compare_function) == 0)
    mosaicsound_list_add_element(list, data);
}

/* -----------------------------------------------------------------------------
   LIST CONTAINS ELEMENT
   ---------------------------------------------------------------------------*/
int mosaicsound_list_contains(mosaicsound_list_t **list, void *data,
                              mosaicsound_list_compare compare_function) {
  if (data == NULL || *list == NULL)
    return 0;

  mosaicsound_list_t *last = *list;
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
mosaicsound_list_remove_element(mosaicsound_list_t **list, const void *data,
                                mosaicsound_list_compare compare_function) {
  mosaicsound_list_t *current = NULL, *previous = NULL;

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
int mosaicsound_list_lenght(mosaicsound_list_t *list) {
  int lenght = 0;

  mosaicsound_list_t *temp = list;
  while (temp) {
    lenght++;
    mosaicsound_list_t *temp2 = temp->next;
    temp = temp2;
  }

  return lenght;
}
/*----------------------------------------------------------------------------*/
