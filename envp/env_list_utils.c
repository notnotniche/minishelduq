/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:33:54 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 14:48:36 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_list	*lstnew_env(char *name, char *value)
{
	t_env_list	*result;

	result = malloc(sizeof(t_env_list));
	result->name = name;
	result->value = value;
	result->next = NULL;
	return (result);
}

t_env_list	*lstlast_env(t_env_list *list)
{
	t_env_list	*head;

	if (list == NULL)
		return (0);
	head = list;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_env(t_env_list **list, t_env_list *new)
{
	t_env_list	*last;

	if (*list)
	{
		last = lstlast_env(*list);
		last->next = new;
	}
	else
		*list = new;
}

void	print_lst_env(t_env_list *list)
{
	while (list)
	{
		if (list->i == VALID)
		{
			printf("1%s\n", list->name);
		}
		else
			printf("2 %s=\"%s\"\n", list->name, list->value);
		list = list->next;
	}
}

void	free_env_list(t_env_list *head)
{
	t_env_list	*current;
	t_env_list	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}
