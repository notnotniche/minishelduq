/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:23:48 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 19:27:08 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_pipe(t_init *init)
{
	t_lex_list	*lst_lex;
	int			count;

	lst_lex = init->lst_lex;
	if (!lst_lex || lst_lex->operator != PIPE)
		return (0);
	count = increment_pipe_count(lst_lex);
	if (!lst_lex->next && count > 0)
		return (syntax_error(2, init));
	return (syntax_error(count, init));
}

int	syntax_append(t_init *init)
{
	t_lex_list	*lst_lex;

	lst_lex = init->lst_lex;
	if (lst_lex->operator == APP_OUT)
		return (1);
	return (0);
}

int	syntax_heredoc(t_init	*init)
{
	t_lex_list	*lst_lex;

	lst_lex = init->lst_lex;
	if (lst_lex && lst_lex->operator == HERE_DOC)
	{
		if (lst_lex->next)
		{
			lst_lex = lst_lex->next;
			if (is_disallowed_op(lst_lex))
				return (handle_heredoc_error(init));
			if (is_word_after_operator(init) == 1)
				return (2);
		}
		else
		{
			return (handle_heredoc_error(init));
		}
	}
	return (0);
}

int	syntax_app(t_init *init)
{
	t_lex_list	*lst_lex;

	lst_lex = init->lst_lex;
	if (lst_lex && lst_lex->operator == APP_OUT)
	{
		if (!lst_lex->next)
			return (handle_syntax_error(init));
		lst_lex = lst_lex->next;
		if (is_disallowed_op(lst_lex))
			return (handle_syntax_error(init));
	}
	return (0);
}

int	check_error(t_init *init)
{
	if (check_quote_ends(init->read_line))
		return (1);
	if (is_word_after_operator(init) == 1)
		return (1);
	else if (syntax_pipe(init) == 1)
		return (1);
	else if (syntax_heredoc(init) != 0)
		return (1);
	else if (syntax_redir_out(init) == 1)
		return (1);
	else if (syntax_redir_in(init) == 1)
		return (1);
	else if (syntax_app(init) == 1)
		return (1);
	else if (syntax_append(init) == 1)
		return (1);
	return (0);
}
