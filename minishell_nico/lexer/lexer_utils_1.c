/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:23:26 by nklingsh          #+#    #+#             */
/*   Updated: 2023/07/26 17:52:14 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_operator(char *read_line)
{
	if (read_line[1] && read_line[0] == '<' && read_line[1] == '<')
		return (1);
	else if (read_line[1] && read_line[0] == '>' && read_line[1] == '>')
		return (1);
	else if (read_line[0] == '|')
		return (1);
	else if (read_line[0] == '>')
		return (1);
	else if (read_line[0] == '<')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

int length_word(char *word)
{
	char quotes;
	int quote;
	int i;

	i = 0;
	quote = 0;
	quotes = 0;
	while (*word)
	{
		if (quote == 0 && (ft_is_operator(word) || ft_isspace(*word)))
			break;
		if ((*word == '\'' || (*word) == '\"') && quote == 0)
		{
			quote++;
			quotes = *word;
		}
		else if ((quote == 1) && (*word == quotes))
		{
			quote = 0;
			quotes = 0;
		}
		i++;
		word++;
	}
	return (i);
}

void write_word(char *word, char **result)
{
	char	quote_type;
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	quote_type = 0;
	while (*word)
	{
		if (quote == 0 && (ft_is_operator(word) || ft_isspace(*word)))
			break ;
		if ((*word == '\'' || *word == '\"') && quote == 0)
		{
			quote++;
			quote_type = *word;
		}
		else if (quote == 1 && *word == quote_type)
		{
			quote = 0;
			quote_type = 0;
		}
		(*result)[i++] = *word++;
	}
	(*result)[i] = 0;
}

void end_of_word(char **splittos)
{
	char quotes;
	int quote;

	quote = 0;
	quotes = 0;
	while ((**splittos))
	{
		if (quote == 0 && ft_is_operator(*splittos))
			break;
		if (ft_isspace(**splittos) && quote == 0)
			break;
		if ((**splittos == '\"' || **splittos =='\'') && quote == 0)
		{
			quote++;
			quotes = **splittos;
		}	
		else if (quote == 1 && **splittos == quotes)
		{
			quote++;
			quotes = 0;
		}
		(*splittos)++;
	}
}