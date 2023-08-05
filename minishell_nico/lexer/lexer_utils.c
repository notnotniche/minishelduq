/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:18:29 by nklingsh          #+#    #+#             */
/*   Updated: 2023/07/27 19:32:06 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex_list *lstnew_lex(char *word, int operator, t_init *init)
{
	t_lex_list *result;

	lstaddback_malloc(init, lstnew_malloc(word));
	result = malloc(sizeof(t_lex_list));	
	lstaddback_malloc(init, lstnew_malloc(result));
	result->word = word;
	result->operator = operator;
	result->next = NULL;
	return (result); 
}

t_lex_list *lstlast_lex(t_lex_list *list)
{
	t_lex_list *head;

	if (list == NULL)
		return (0);
	head = list;
	while (head->next)
		head = head->next;
	return (head);
}

void lstadd_back_lex(t_lex_list **list, t_lex_list *new)
{
	t_lex_list *last;

	if (*list)
	{
		last = lstlast_lex(*list);
		last->next = new;
	}
	else
		*list = new;
}

void print_lst_lex(t_lex_list *list)
{
	while (list)
	{
		printf(" %d  --> %s \n", list->operator, list->word);
		list = list->next;
	}
}