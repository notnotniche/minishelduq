/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:22:57 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 13:46:59 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_add_word(t_token_list **token, t_lex_list **lex_lst, t_init *init)
{
	t_str_list	*next;

	next = lstnew_str((*lex_lst)->word, init);
	lstaddback_str(&(*token)->arguments, next);
	*lex_lst = (*lex_lst)->next;
}

void	token_add_redir_in(t_token_list **t, t_lex_list **l, t_init *init)
{
	t_str_list	*next;

	(*t)->i_fd = REDIR_IN;
	*l = (*l)->next;
	next = lstnew_str((*l)->word, init);
	lstaddback_str(&(*t)->in_file, next);
	*l = (*l)->next;
}

void	token_add_redir_out(t_token_list **t, t_lex_list **l, t_init *init)
{
	t_str_list	*next;

	(*t)->o_fd = REDIR_OUT;
	*l = (*l)->next;
	next = lstnew_str((*l)->word, init);
	next->str_list2 = "O_TRUNC";
	lstaddback_str(&(*t)->out_file, next);
	*l = (*l)->next;
}

void	token_add_app_out(t_token_list **t, t_lex_list **l, t_init *init)
{
	t_str_list	*next;

	(*t)->o_fd = APP_OUT;
	*l = (*l)->next;
	next = lstnew_str((*l)->word, init);
	next->str_list2 = "O_APPEND";
	lstaddback_str(&(*t)->out_file, next);
	*l = (*l)->next;
}

void	token_here_doc(t_token_list **t, t_lex_list **l, t_init *init)
{
	t_str_list	*next;

	(*t)->i_fd = HERE_DOC;
	*l = (*l)->next;
	next = lstnew_str((*l)->word, init);
	lstaddback_str(&(*t)->delimeter, next);
	*l = (*l)->next;
}
