/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:21:16 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 19:25:33 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_syntax_error(t_init *init)
{
	change_env_value("?", "2", init);
	ft_print_fd("syntax error near unexpected token", 2);
	g_status_exit_code = 2;
	return (1);
}

static int	redir_in_error(int count, t_init *init)
{
	change_env_value("?", "2", init);
	if (count >= 5)
	{
		ft_print_fd("syntax error near unexpected token `<<'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	if (count >= 1 && count <= 3)
	{
		ft_print_fd("syntax error near unexpected token `newline'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	if (count == 4)
	{
		ft_print_fd("syntax error near unexpected token `<'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	return (0);
}

static int	increment_redir_in_count(t_lex_list *lst_lex)
{
	int	i;

	i = 0;
	while (lst_lex && lst_lex->operator == REDIR_IN)
	{
		i++;
		lst_lex = lst_lex->next;
	}
	return (i);
}

static int	redir_out_error(int count, t_init *init)
{
	change_env_value("?", "2", init);
	if (count >= 4)
	{
		ft_print_fd("syntax error near unexpected token `>>'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	if (count == 1 || count == 2)
	{
		ft_print_fd("syntax error near unexpected token `newline'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	if (count == 3)
	{
		ft_print_fd("syntax error near unexpected token `>'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	return (0);
}

static int	increment_redir_out_count(t_lex_list *lst_lex)
{
	int	i;

	i = 0;
	while (lst_lex && lst_lex->operator == REDIR_OUT)
	{
		i++;
		lst_lex = lst_lex->next;
	}
	return (i);
}
