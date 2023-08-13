/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:23:48 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/13 22:00:21 by nklingsh         ###   ########.fr       */
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
		return (ft_print_fd("Subject syntax error", 2), 1);
	return (0);
}

int is_redir_good(t_lex_list *lst_lex)
{
	if (!lst_lex->next)
		return (ft_print_fd("no word after redir",2),1);
	if (lst_lex->next->operator != REDIR_IN)
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

int	is_word_after_operator(t_init *init)
{
	t_lex_list *lst_lex;

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
			return (ft_print_fd("syntax error near unexpected token `newline'", 2), g_status_exit_code = 2, 1);
		}
	}
	return (0);
}

int	syntax_pipe(t_init	*init)
{
	t_lex_list *lst_lex;
	int			i;

	i = 0;
	lst_lex = init->lst_lex;
	// printf("lst_lex->operator ==== %d\n", lst_lex->operator);
	if (lst_lex && lst_lex->operator == PIPE)
	{
		while (lst_lex->operator && lst_lex->operator == PIPE)
		{
			i++;
			if (lst_lex->next)
				lst_lex = lst_lex->next;
			else
				break;
		}
		if (!lst_lex->next)
		{
			change_env_value("?", "2", init);
			return (ft_print_fd("syntax error near unexpected token `||'", 2), g_status_exit_code = 2, 1);
		}
		if (i >= 2) //change_env_value to change '?' error code value
		{
			change_env_value("?", "2", init);
			return (ft_print_fd("syntax error near unexpected token `||'", 2), g_status_exit_code = 2, 1);
		}
	}
	if (i == 1)
	{
		change_env_value("?", "2", init);
		return (ft_print_fd("syntax error near unexpected token `|'", 2), g_status_exit_code = 2, 1);
	}
	return (0);
}

int	syntax_redir_out(t_init	*init)
{
	t_lex_list *lst_lex;
	int			i;

	i = 0;
	lst_lex = init->lst_lex;
	if (lst_lex && lst_lex->operator == REDIR_OUT)
	{
		while (lst_lex->operator && (lst_lex->operator == REDIR_OUT))
		{
			i++;
			if (lst_lex->next)
				lst_lex = lst_lex->next;
			else
				break;
		}
		if (i >= 4) //change_env_value to change '?' error code value
			return (ft_print_fd("syntax error near unexpected token `>>'", 2), g_status_exit_code = 2, 1);
	}
	if (i == 1 || i == 2)
	{
		change_env_value("?", "2", init);
		return (ft_print_fd("syntax error near unexpected token `newline'", 2), g_status_exit_code = 2, 1);
	}
	if (i == 3)
	{
		change_env_value("?", "2", init);
		return (ft_print_fd("syntax error near unexpected token `>'", 2), g_status_exit_code = 2, 1);
	}
	return (0);
}

int syntax_append(t_init *init)
{
	t_lex_list *lst_lex;

	lst_lex = init->lst_lex;
	if (lst_lex->operator == APP_OUT)
		return (1);
	return (0);
}

int	syntax_redir_in(t_init	*init)
{
	t_lex_list *lst_lex;
	int			i;

	i = 0;
	lst_lex = init->lst_lex;
	if (lst_lex && (lst_lex->operator == REDIR_IN))
	{
		while (lst_lex->operator && (lst_lex->operator == REDIR_IN))
		{
			i++;
			if (lst_lex->next)
				lst_lex = lst_lex->next;
			else
				break;
		}
		if (i >= 5) //change_env_value to change '?' error code value
		{
			change_env_value("?", "2", init);
			return (ft_print_fd("syntax error near unexpected token `<<'", 2), g_status_exit_code = 2, 1);
		}
	}
	if (i >= 1 && i <= 3)
	{
		change_env_value("?", "2", init);
		return (ft_print_fd("syntax error near unexpected token `newline'", 2), g_status_exit_code = 2, 1);
	}
	if (i == 4)
	{
		change_env_value("?", "2", init);
		return (ft_print_fd("syntax error near unexpected token `<'", 2), g_status_exit_code = 2, 1);
	}
	return (0);
}

int	syntax_heredoc(t_init	*init)
{
	t_lex_list *lst_lex;
	int			i;

	i = 0;
	lst_lex = init->lst_lex;
	if (lst_lex && lst_lex->operator == HERE_DOC)
	{
		if (lst_lex->next)
		{
			lst_lex = lst_lex->next;
			if (lst_lex->operator == PIPE
				|| lst_lex->operator == REDIR_IN || lst_lex->operator == REDIR_OUT 
				|| lst_lex->operator == HERE_DOC || lst_lex->operator == APP_OUT)
			{
				change_env_value("?", "2", init);
				return (ft_print_fd("syntax error near unexpected token", 2), g_status_exit_code = 2, 1);
			}
			if(is_word_after_operator(init) == 1)
				return(2);
		}
		else
		{
			change_env_value("?", "2", init);
			return (ft_print_fd("syntax error near unexpected token", 2), g_status_exit_code = 2, 1);
		}
	}
	return (0);
}

int	syntax_app(t_init	*init)
{
	t_lex_list *lst_lex;
	int			i;

	i = 0;
	lst_lex = init->lst_lex;
	if (lst_lex && lst_lex->operator == APP_OUT)
	{
		if (!lst_lex->next)
		{
			change_env_value("?", "2", init);
			return (ft_print_fd("syntax error near unexpected token", 2), g_status_exit_code = 2, 1);
		}
		if (lst_lex->next)
		{
			lst_lex = lst_lex->next;
			if (lst_lex->operator == PIPE
				|| lst_lex->operator == REDIR_IN || lst_lex->operator == REDIR_OUT 
				|| lst_lex->operator == HERE_DOC || lst_lex->operator == APP_OUT)
				{
				change_env_value("?", "2", init);
				return (ft_print_fd("syntax error near unexpected token", 2), g_status_exit_code = 2, 1);
				}
		}
	}
	return (0);
}

int	check_if_syntax_ok(t_init *init)
{
	t_lex_list *lst_lex;
	int			i;

	i = 0;
	lst_lex = init->lst_lex;
	while (lst_lex)
	{
		if (lst_lex->operator != WORD && (!lst_lex->next->operator || lst_lex->next->operator != WORD))
			return (ft_print_fd("syntax error near unexpected token", 2), g_status_exit_code = 2, 1);
		lst_lex = lst_lex->next;
	}
	return (0);
}

int check_error(t_init *init)
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
	// if (check_if_syntax_ok(init) == 1)
	// 	return (1)7
	return (0);
}