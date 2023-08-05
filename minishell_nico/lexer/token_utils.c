/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:22:57 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/02 17:28:49 by nklingsh         ###   ########.fr       */
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

void	token_add_redir_in(t_token_list **token, t_lex_list **lex_lst, t_init *init)
{
	t_str_list *next;

	(*token)->i_fd = REDIR_IN;
	*lex_lst = (*lex_lst)->next;
	next = lstnew_str((*lex_lst)->word, init);
	lstaddback_str(&(*token)->in_file, next);
	*lex_lst = (*lex_lst)->next;
}

void	token_add_redir_out(t_token_list **token, t_lex_list **lex_lst, t_init *init)
{
	t_str_list *next;

	(*token)->o_fd = REDIR_OUT;
	*lex_lst = (*lex_lst)->next;
	next = lstnew_str((*lex_lst)->word, init);
	next->str_list2 = "O_TRUNC";
	lstaddback_str(&(*token)->out_file, next);
	*lex_lst = (*lex_lst)->next;
}

void	token_add_app_out(t_token_list **token, t_lex_list **lex_lst, t_init *init)
{
	t_str_list *next;

	(*token)->o_fd = APP_OUT;
	*lex_lst = (*lex_lst)->next;
	next = lstnew_str((*lex_lst)->word, init);
	next->str_list2 = "O_APPEND";
	lstaddback_str(&(*token)->out_file, next);
	*lex_lst = (*lex_lst)->next;
}

void	token_here_doc(t_token_list **token, t_lex_list **lex_lst, t_init *init)
{
	t_str_list *next;

	(*token)->i_fd = HERE_DOC;
	*lex_lst = (*lex_lst)->next;
	next = lstnew_str((*lex_lst)->word, init);
	lstaddback_str(&(*token)->delimeter, next);
	*lex_lst = (*lex_lst)->next;
}