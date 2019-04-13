#ifndef mscsound_LIST_H
#define mscsound_LIST_H
typedef struct LIST mscsound_list_t;

// Generic list
struct LIST {
  void *data;
  mscsound_list_t *next;
};

typedef int (*mscsound_list_compare)(const void *data1, const void *data2);

mscsound_list_t *mscsound_list_create(void);

void mscsound_list_add_element(mscsound_list_t **list, void *data);

int mscsound_list_contains(mscsound_list_t **list, void *data,
                              mscsound_list_compare compare_function);

void mscsound_list_add_unique_element(
    mscsound_list_t **list, void *data,
    mscsound_list_compare compare_function);

void *
mscsound_list_remove_element(mscsound_list_t **list, const void *data,
                                mscsound_list_compare compare_function);

void mscsound_list_free(mscsound_list_t *list);

int mscsound_list_lenght(mscsound_list_t *list);

#endif /* list.h */
