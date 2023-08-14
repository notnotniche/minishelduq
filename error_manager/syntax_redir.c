/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:26:41 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 19:27:24 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_redir_in(t_init *init)
{
	t_lex_list	*lst_lex;
	int			count;

	lst_lex = init->lst_lex;
	if (!lst_lex || lst_lex->operator != REDIR_IN)
		return (0);
	count = increment_redir_in_count(lst_lex);
	return (redir_in_error(count, init));
}

int	syntax_redir_out(t_init *init)
{
	t_lex_list	*lst_lex;
	int			count;

	lst_lex = init->lst_lex;
	if (!lst_lex || lst_lex->operator != REDIR_OUT)
		return (0);
	count = increment_redir_out_count(lst_lex);
	return (redir_out_error(count, init));
}
