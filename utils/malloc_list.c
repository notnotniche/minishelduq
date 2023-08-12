/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:23:59 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 00:00:15 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_malloc	*lstnew_malloc(void *adr)
{
	t_malloc	*result;

	if (!adr)
		return (NULL);
	result = malloc(sizeof(t_malloc));
	if (!result)
		return (NULL);
	result->adr = adr;
	result->next = NULL;
	return (result);
}

t_malloc	*lstlast_malloc(t_malloc *nodes)
{
	t_malloc	*head;

	if (nodes == NULL)
		return (0);
	head = nodes;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstaddback_malloc(t_init *init, t_malloc *new)
{
	t_malloc	*last;

	if (init->lst_mal)
	{
		last = lstlast_malloc(init->lst_mal);
		last->next = new;
	}
	else
		init->lst_mal = new;
}

void	free_lst_malloc(t_malloc *lst)
{
	t_malloc	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->adr);
		free(lst);
		lst = tmp;
	}
}
