/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:23:48 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/01 17:02:32 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_quote_ends(char *str)
{
	int i;
	t_quote quote;

	quote.quote_bool = 0;
	quote.quote = 0;
	i = 0;
	while (str[i])
	{
		if ((is_quote(str[i]) && quote.quote_bool == 0))
		{
			quote.quote = str[i];	
			quote.quote_bool++;
		}
		else if (str[i] == quote.quote && quote.quote_bool == 1)
		{
			quote.quote_bool = 0;
			quote.quote = 0;
		}
		i++;
	}
	if (quote.quote_bool != 0)
		return (ft_print_fd("error quote", 2), 1);
	return (0);
}

int is_redir_good(t_lex_list *lst_lex)
{
	if (!lst_lex->next)
		return (ft_print_fd("no word after redir",2),1);
	if (lst_lex->next->operator != WORD)
		return (ft_print_fd("no word after redir check syntax", 2), 1);
	return (0);
}

int is_pipe_good(t_lex_list *lst_lex)
{
	if (!lst_lex->next)
		return (ft_print_fd("no word after redir",2),1);
	if (lst_lex->next->operator == REDIR_OUT)
		return (ft_print_fd("no word after redir check synta ", 2), 1);
	return (0);
}

int check_error(t_lex_list *lst_lex)
{
	if (lst_lex->operator == REDIR_OUT)
		return (ft_print_fd("parse error near '|'", 2), g_status_exit_code = 2, 1);
	while (lst_lex)
	{
		if (lst_lex->operator == REDIR_OUT)
		{
			if (is_pipe_good(lst_lex))
				return (g_status_exit_code = 1, 1);
		}
		if (lst_lex->operator != REDIR_OUT && lst_lex->operator != WORD)
		{
			if (is_redir_good(lst_lex))
				return (g_status_exit_code = 2, 1);
		}
		else if (lst_lex->operator == WORD)
		{
			if (check_quote_ends(lst_lex->word))
				return (g_status_exit_code = 2, 1);
		}
		lst_lex = lst_lex->next;
	}
	return (0);
}