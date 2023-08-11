/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:33:54 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 15:58:43 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_list *lstnew_env(char *name, char *value)
{
	t_env_list *result;

	result = malloc(sizeof(t_env_list));
	result->name = name;
	result->value = value;
	result->next = NULL;
	return (result);
}

t_env_list *lstlast_env(t_env_list *list)
{
	t_env_list *head;

	if (list == NULL)
		return (0);
	head = list;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_env(t_env_list **list, t_env_list *new)
{
	t_env_list *last;
	
	if (*list)
	{
		last = lstlast_env(*list);
		last->next = new;
	}
	else
		*list = new;
}

void print_lst_env(t_env_list *list)
{
	while (list)
	{
		printf("%s=",list->name);
		if (list->value)
			printf("\"%s\"\n", list->value);
		else
			printf("\"\"\n");
		list = list->next;
	}
}

void free_env_list(t_env_list *head) {
    t_env_list *current = head;
    while (current != NULL) 
	{
        t_env_list *temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
}