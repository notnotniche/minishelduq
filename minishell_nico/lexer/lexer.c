/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:51:54 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/02 13:26:30 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//choisir ici assignation here doc , to	


#include "../minishell.h"

void operator_manager(char **read_line, t_lex_list **lex_list, t_init *init)
{
	if ((*read_line)[1] && (*read_line)[0] == '<' && (*read_line)[1] == '<')
	{
		lstadd_back_lex(lex_list, lstnew_lex(ft_strdup("<<"), HERE_DOC, init));
		(*read_line)++;	
	}
	else if ((*read_line)[1] && (*read_line)[0] == '>' && (*read_line)[1] == '>')
	{
		lstadd_back_lex(lex_list, lstnew_lex(ft_strdup(">>"), APP_OUT, init));
		(*read_line)++;	
	}
	else if ((*read_line)[0] == '|')
		lstadd_back_lex(lex_list, lstnew_lex(ft_strdup("|"), PIPE, init));
	else if ((*read_line)[0] == '<')
		lstadd_back_lex(lex_list, lstnew_lex(ft_strdup("<"), REDIR_IN, init));
	else if ((*read_line)[0] == '>')
		lstadd_back_lex(lex_list, lstnew_lex(ft_strdup(">"), REDIR_OUT, init));
	(*read_line)++;

}

void word_manager(char *read_line, t_lex_list **lex_list, t_init *init)
{
	char *word;
	int		size;

	size = length_word(read_line);
	word = malloc(sizeof(char) * (size + 1));
	lstadd_back_lex(lex_list, lstnew_lex(word, WORD, init));
	write_word(read_line, &word);
}

t_lex_list *lexer_lexing(char *read_line, t_init *init)
{
	t_lex_list *lex_list;

	lex_list = NULL;
	while (*read_line)
	{
		if (ft_is_operator(read_line))
			operator_manager(&read_line, &lex_list, init);
		else if (!ft_is_operator(read_line) && !ft_isspace(*read_line))
		{
			word_manager(read_line, &lex_list, init);
			end_of_word(&read_line);
		}
		else
			read_line++;
	}
	return (lex_list);
}