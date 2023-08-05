/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:55:17 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/01 15:41:04 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token_list *lst_new_token(t_init *init)
{
	t_token_list *result;
	
	result = malloc(sizeof(t_token_list));
	lstaddback_malloc(init, lstnew_malloc(result));
	result->arguments = NULL;
	result->delimeter = NULL;
	result->in_file = NULL;
	result->out_file = NULL;
	result->i_fd = 0;
	result->token = 1000;
	result->o_fd = 1;
	result->next = NULL;
	return (result);
}

t_token_list *lstlast_token(t_token_list *lst)
{
	t_token_list *head;

	if (lst == NULL)
	{
		return (0);
	}
	head = lst;
	while (head->next)
	{
		head = head->next;
	}
	return (head);
}

void lstaddback_token(t_token_list **lst, t_token_list *new)
{
	t_token_list *last;

	if (*lst)
	{
		last = lstlast_token(*lst);
		last->next = new;
	}
	else
	{
		*lst = new;
	}
}

void print_all_token(t_token_list *lst)
{
	t_token_list *head;
	int		i;

	i = 0;
	head = lst;
	while(head)
	{
		print_str(head->arguments, "arguments");
		print_str(head->in_file, "in_file");
		print_str(head->out_file, "out_file");
		print_str(head->delimeter, "delimiter");
		printf("index = %d  %d \n", i , head->o_fd);
		printf("index = %d  %d \n", i, head->i_fd);
		head = head->next;
	}
}