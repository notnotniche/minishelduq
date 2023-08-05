/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:01:09 by nklingsh          #+#    #+#             */
/*   Updated: 2023/07/27 16:44:30 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_str_list	*lstnew_str(char *content, t_init *init)
{
	t_str_list	*result;

	result = malloc(sizeof(t_str_list));
	lstaddback_malloc(init, lstnew_malloc(result));
	result->str_list = content;
	result->str_list2 = NULL;
	result->next = NULL;
	return (result);
}

t_str_list	*lstlast_str(t_str_list *lst)
{
	t_str_list	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstaddback_str(t_str_list **lst, t_str_list *new)
{
	t_str_list	*last;

	if (*lst)
	{
		last = lstlast_str(*lst);
		last->next = new;
	}
	else
		*lst = new;
}


void	print_str(t_str_list *str_list, char *str)
{
	int i;

	i = 0;
	printf("%s : ", str);
	while (str_list)
	{
		printf(" % d : %s ",i , str_list->str_list);
		i++;
		str_list = str_list->next;
	}
	printf("\n");
}
