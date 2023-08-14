/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:40:36 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 18:30:06 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenator(t_token_list **t_head, t_token_list **t_next, t_init *init)
{
	lstaddback_token(t_head, *t_next);
	*t_next = lst_new_token(init);
}

t_token_list	*get_all_token(t_init *init)
{
	t_token_list	*token_head;
	t_token_list	*token_next;

	token_head = NULL;
	token_next = lst_new_token(init);
	while (init->lst_lex)
	{
		if (init->lst_lex->operator == PIPE)
		{
			tokenator(&token_head, &token_next, init);
			init->lst_lex = init->lst_lex->next;
		}
		else if (init->lst_lex->operator == REDIR_OUT)
			token_add_redir_out(&token_next, &init->lst_lex, init);
		else if (init->lst_lex->operator == REDIR_IN)
			token_add_redir_in(&token_next, &init->lst_lex, init);
		else if (init->lst_lex->operator == APP_OUT)
			token_add_app_out(&token_next, &init->lst_lex, init);
		else if (init->lst_lex->operator == HERE_DOC)
			token_here_doc(&token_next, &init->lst_lex, init);
		else if (init->lst_lex->operator == WORD)
			token_add_word(&token_next, &init->lst_lex, init);
	}
	lstaddback_token(&token_head, token_next);
	return (token_head);
}
