/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:18:29 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 13:35:37 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex_list	*lstnew_lex(char *word, int operator, t_init *init)
{
	t_lex_list	*result;

	lstaddback_malloc(init, lstnew_malloc(word));
	result = malloc(sizeof(t_lex_list));
	lstaddback_malloc(init, lstnew_malloc(result));
	result->word = word;
	result->operator = operator;
	result->must_split = 0;
	result->next = NULL;
	return (result);
}

t_lex_list	*lstlast_lex(t_lex_list *list)
{
	t_lex_list	*head;

	if (list == NULL)
		return (0);
	head = list;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_lex(t_lex_list **list, t_lex_list *new)
{
	t_lex_list	*last;

	if (*list)
	{
		last = lstlast_lex(*list);
		last->next = new;
	}
	else
		*list = new;
}

void	print_lst_lex(t_lex_list *list)
{
	while (list)
	{
		printf(" %d  --> %s \n", list->operator, list->word);
		list = list->next;
	}
}

void	delete_last_node_lex(t_lex_list **list)
{
	t_lex_list	*tmp;
	t_lex_list	*prev;

	tmp = *list;
	if (*list == NULL)
		return ;
	if (tmp->next == NULL)
	{
		*list = NULL;
		return ;
	}
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	free(tmp);
}
