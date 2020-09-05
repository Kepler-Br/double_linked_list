#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <unistd.h>

typedef struct s_double_linked_list
{
    struct s_double_linked_list *previous;
    struct s_double_linked_list *next;
    void *content;
    size_t content_size;
} t_double_linked_list;

t_double_linked_list *double_ll_new(void *content, size_t size, void(*create_function)(void*from, void*to));
void double_ll_destroy_whole(t_double_linked_list **lst, void(*destroy_function)(void*));
void double_ll_destroy_single(t_double_linked_list *lst, void(*destroy_function)(void*));
t_double_linked_list *double_ll_copy_whole(t_double_linked_list *lst, void(*create_function)(void*from, void*to));
void double_ll_push_front(void *content, size_t size, t_double_linked_list **lst, void(*create_function)(void*from, void*to));
void double_ll_push_back(void *content, size_t size, t_double_linked_list **lst, void(*create_function)(void*from, void*to));
void double_ll_pop_front(t_double_linked_list **lst, void(*destroy_function)(void*));
void double_ll_pop_back(t_double_linked_list **lst, void(*destroy_function)(void*));
void double_ll_pop_front_function(t_double_linked_list **lst, void(*fun)(void*));
void double_ll_pop_back_function(t_double_linked_list **lst, void(*fun)(void*));
void double_ll_pop_element(t_double_linked_list **lst, void(*fun)(void*));
t_double_linked_list *double_ll_front(t_double_linked_list *lst);
t_double_linked_list *double_ll_back(t_double_linked_list *lst);
size_t double_ll_len(t_double_linked_list *lst);
int double_ll_is_there(t_double_linked_list *lst, void*compare_content, int(*condition)(void *what, void *compare));

#endif //DOUBLE_LINKED_LIST_H
