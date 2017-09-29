#include <stdlib.h>
#include "include/list.h"

// Generic list

/* -----------------------------------------------------------------------------
   LIST CREATE
   ---------------------------------------------------------------------------*/
t_list *list_create(void) { return NULL; }

/* -----------------------------------------------------------------------------
   LIST FREE
   ---------------------------------------------------------------------------*/
void list_free(t_list *list) {
  t_list *temp = list;
  while (temp) {
    t_list *temp2 = temp->next;
    free(temp);
    temp = temp2;
  }
}

/* -----------------------------------------------------------------------------
   LIST ADD ELEMENT
   ---------------------------------------------------------------------------*/
void list_add_element(t_list **list, void *data) {
  if (*list == NULL) {
    *list = malloc(sizeof(t_list));
    (*list)->data = data;
    (*list)->next = NULL;
    return;
  }

  t_list *last = *list;
  while (last && last->next) {  // Find last element
    last = last->next;
  }
  t_list *current = malloc(sizeof(t_list));
  current->data = data;
  current->next = NULL;
  last->next = current;
}

/* -----------------------------------------------------------------------------
   LIST ADD UNIQUE ELEMENT
   ---------------------------------------------------------------------------*/
void list_add_unique_element(t_list **list, void *data,
                             list_compare compare_function) {
  if (list_contains(list, data, compare_function) == 0)
    list_add_element(list, data);
}

/* -----------------------------------------------------------------------------
   LIST CONTAINS ELEMENT
   ---------------------------------------------------------------------------*/
int list_contains(t_list **list, void *data, list_compare compare_function) {
  if (data == NULL || *list == NULL) return 0;

  t_list *last = *list;
  while (last) {  // Find last element
    if (compare_function(data, last->data) == 1) return 1;
    last = last->next;
  }
  return 0;
}

/* -----------------------------------------------------------------------------
   LIST REMOVE ELEMENT
   ---------------------------------------------------------------------------*/
void *list_remove_element(t_list **list, const void *data,
                          list_compare compare_function) {
  t_list *current = NULL, *previous = NULL;

  if (list == NULL) return NULL;

  for (current = *list; current != NULL;
       previous = current, current = current->next) {
    // check value
    if (compare_function(current->data, data)) {
      if (previous == NULL) {  // remove first
        *list = current->next;
      } else {
        previous->next = current->next;
      }
      return current->data;
    }
  }

  return NULL;
}

/* -----------------------------------------------------------------------------
   LIST LENGHT
   ---------------------------------------------------------------------------*/
int list_lenght(t_list *list) {
  int lenght = 0;

  t_list *temp = list;
  while (temp) {
    lenght++;
    t_list *temp2 = temp->next;
    temp = temp2;
  }

  return lenght;
}
/*----------------------------------------------------------------------------*/
