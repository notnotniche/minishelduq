/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:23:13 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 19:25:24 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_disallowed_op(t_lex_list *lst_lex)
{
	int	ops[5];
	int	i;
	int	size;

	ops[0] = PIPE;
	ops[1] = REDIR_IN;
	ops[2] = REDIR_OUT;
	ops[3] = HERE_DOC;
	ops[4] = APP_OUT;
	i = 0;
	size = sizeof(ops) / sizeof(ops[0]);
	while (i < size)
	{
		if (lst_lex->operator == ops[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_word_after_operator(t_init *init)
{
	t_lex_list	*lst_lex;

	lst_lex = init->lst_lex;
	while (lst_lex->operator != PIPE
		&& lst_lex->operator != REDIR_IN && lst_lex->operator != REDIR_OUT
		&& lst_lex->operator != HERE_DOC && lst_lex->operator != APP_OUT)
	{
		if (lst_lex->next)
			lst_lex = lst_lex->next;
		else
			break ;
	}
	if (lst_lex->operator == PIPE
		|| lst_lex->operator == REDIR_IN || lst_lex->operator == REDIR_OUT
		|| lst_lex->operator == HERE_DOC || lst_lex->operator == APP_OUT)
	{
		if (lst_lex->next == NULL || lst_lex->next->operator != WORD)
		{
			change_env_value("?", "2", init);
			return (ft_print_fd("syntax error \
near unexpected token `newline'", 2), g_status_exit_code = 2, 1);
		}
	}
	return (0);
}

static int	increment_pipe_count(t_lex_list *lst_lex)
{
	int	i;

	i = 0;
	while (lst_lex && lst_lex->operator == PIPE)
	{
		i++;
		lst_lex = lst_lex->next;
	}
	return (i);
}

static int	handle_heredoc_error(t_init *init)
{
	change_env_value("?", "2", init);
	ft_print_fd("syntax error near unexpected token", 2);
	g_status_exit_code = 2;
	return (1);
}

static int	syntax_error(int count, t_init *init)
{
	if (count >= 2)
	{
		change_env_value("?", "2", init);
		ft_print_fd("syntax error near unexpected token `||'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	if (count == 1)
	{
		change_env_value("?", "2", init);
		ft_print_fd("syntax error near unexpected token `|'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	return (0);
}
