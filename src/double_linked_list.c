#include "double_linked_list.h"
#include <stdlib.h>

static void	*ft_memdup(const void *data, size_t data_size)
{
	char *new_data;
	char *new_data_pointer;
	char *old_data_pointer;

	if (!(new_data = (char *)malloc(data_size)) || !data)
		return (NULL);
	new_data_pointer = new_data;
	old_data_pointer = (char *)data;
	while (data_size--)
	{
		*new_data_pointer = *old_data_pointer;
		old_data_pointer++;
		new_data_pointer++;
	}
	return (new_data);
}

t_double_linked_list *double_ll_new(void *content, size_t size, void(*create_function)(void*, void*))
{
    t_double_linked_list *lst;

    lst = malloc(sizeof(t_double_linked_list));
    lst->content = ft_memdup(content, size);
    lst->content_size = size;
    lst->previous = NULL;
    lst->next = NULL;
    if(create_function != NULL)
        create_function(content, lst->content);
    return (lst);
}

void double_ll_destroy_whole(t_double_linked_list **lst, void(*destroy_function)(void*))
{
    t_double_linked_list *next_lst;
    while(*lst)
    {
        if (destroy_function != NULL)
            destroy_function((*lst)->content);
        free((*lst)->content);
        next_lst = (*lst)->next;
        free((*lst));
        (*lst) = next_lst;
    }
}

void double_ll_destroy_single(t_double_linked_list *lst, void(*destroy_function)(void*))
{
    if (destroy_function != NULL)
        destroy_function(lst->content);
    free(lst->content);
    free(lst);
}

t_double_linked_list *double_ll_copy_whole(t_double_linked_list *lst, void(*create_function)(void*from, void*to))
{
    t_double_linked_list *new_list;

    new_list = NULL;
    lst = double_ll_back(lst);
    while(lst != NULL)
    {
        double_ll_push_front(lst->content, lst->content_size, &new_list, create_function);
        lst = lst->next;
    }
    return (double_ll_back(new_list));
}

void double_ll_push_front(void *content, size_t size, t_double_linked_list **lst, void(*create_function)(void*, void*))
{
    t_double_linked_list *new_lst;
    t_double_linked_list *iter;

    if(lst == NULL)
        return;
    new_lst = double_ll_new(content, size, create_function);
    if(*lst == NULL)
    {
        *lst = new_lst;
        return;
    }
    iter = double_ll_front(*lst);
    iter->next = new_lst;
    new_lst->previous = iter;
    *lst = double_ll_back(*lst);
}

void double_ll_push_back(void *content, size_t size, t_double_linked_list **lst, void(*create_function)(void*, void*))
{
    t_double_linked_list *new_lst;
    t_double_linked_list *iter;

    if(lst == NULL)
        return;
    new_lst = double_ll_new(content, size, create_function);
    if(*lst == NULL)
    {
        *lst = new_lst;
        return;
    }
    iter = double_ll_back((*lst));
    iter->previous = new_lst;
    new_lst->next = iter;
    *lst = new_lst;
}

void double_ll_pop_front(t_double_linked_list **lst, void(*destroy_function)(void*))
{
    t_double_linked_list *forward;
    t_double_linked_list *previous;

    if(lst == NULL || *lst == NULL)
        return;
    forward = double_ll_front(*lst);
    if(forward->previous == NULL)
    {
        double_ll_destroy_single(*lst, destroy_function);
        (*lst) = NULL;
        return;
    }
    previous = forward->previous;
    double_ll_destroy_single(forward, destroy_function);
    previous->next = NULL;
    if(forward == *lst)
        *lst = previous;
}

void double_ll_pop_back(t_double_linked_list **lst, void(*destroy_function)(void*))
{
    t_double_linked_list *back;
    t_double_linked_list *next;

    if(lst == NULL || *lst == NULL)
        return;
    back = double_ll_back(*lst);
    if(back->next == NULL)
    {
        double_ll_destroy_single(*lst, destroy_function);
        *lst = NULL;
        return;
    }
    next = back->next;
    double_ll_destroy_single(back, destroy_function);
    next->previous = NULL;
    if(back == *lst)
        *lst = next;
}

t_double_linked_list *double_ll_front(t_double_linked_list *lst)
{
    const t_double_linked_list *first_element = lst;


    if(lst == NULL)
        return (NULL);
    while(lst->next != NULL)
    {
        lst = lst->next;
        if(lst == first_element)
            break;
    }
    return lst;
}

t_double_linked_list *double_ll_back(t_double_linked_list *lst)
{
    const t_double_linked_list *first_element = lst;

    if(lst == NULL)
        return (NULL);
    while(lst->previous != NULL)
    {
        lst = lst->previous;
        if(lst == first_element)
            break;
    }

    return lst;
}

size_t double_ll_len(t_double_linked_list *lst)
{
    size_t i;
    t_double_linked_list *first_element;

    i = 1;
    if(lst == NULL)
        return (0);
    lst = double_ll_back(lst);
    first_element = lst;
    while(1)
    {
        if(lst->next == NULL)
            break;
        lst = lst->next;
        i++;
        if(lst == first_element)
            break;
    }
    return (i);
}

int double_ll_is_there(t_double_linked_list *lst, void *compare_content, int(*condition)(void *lst, void *compare))
{
    while(lst != NULL)
    {
        if(condition(lst->content, compare_content))
            return (1);
        lst = lst->next;
    }
    return (0);
}