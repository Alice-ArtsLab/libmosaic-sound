#ifndef list_H
#define list_H

    typedef struct LIST t_list;

    // Generic list
    struct LIST {
            void *data;
            t_list *next;
    };



    typedef int (*list_compare)(
            const void * data1,
            const void * data2
            );

    t_list * list_create(void);

    void list_add_element(
            t_list **list,
            void * data
            );

    int list_contains(
            t_list **list,
            void * data,
            list_compare compare_function
            );

    void list_add_unique_element(
            t_list **list,
            void * data,
            list_compare compare_function
            );

    void * list_remove_element(t_list **list,
                               const void * data,
                               list_compare compare_function
                               );

    void list_free(
            t_list * list
            );

    int list_lenght(t_list *list);
    
#endif /* list.h */
