#ifndef MOSAICSOUND_LIST_H
#define MOSAICSOUND_LIST_H
typedef struct LIST mosaicsound_list_t;

// Generic list
struct LIST {
  void *data;
  mosaicsound_list_t *next;
};

typedef int (*mosaicsound_list_compare)(const void *data1, const void *data2);

mosaicsound_list_t *mosaicsound_list_create(void);

void mosaicsound_list_add_element(mosaicsound_list_t **list, void *data);

int mosaicsound_list_contains(mosaicsound_list_t **list, void *data,
                              mosaicsound_list_compare compare_function);

void mosaicsound_list_add_unique_element(
    mosaicsound_list_t **list, void *data,
    mosaicsound_list_compare compare_function);

void *
mosaicsound_list_remove_element(mosaicsound_list_t **list, const void *data,
                                mosaicsound_list_compare compare_function);

void mosaicsound_list_free(mosaicsound_list_t *list);

int mosaicsound_list_lenght(mosaicsound_list_t *list);

#endif /* list.h */
