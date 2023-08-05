/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:08 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/03 15:22:27 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_env(char **str, char **result, t_init *init)
{
	char *env_name;
	char *env_value;
	
	(*str)++;
	env_name = env_name_expander(*str);
	if (!env_name)
		exit(1);
	if (ft_strsame(env_name, "?"))
	{
		env_value = ft_itoa(g_status_exit_code);
		lstaddback_malloc(init, lstnew_malloc(env_value));
	}
	else
	{
		env_value = get_env_value(env_name, init);
	}
	if (ft_strlen(env_value) != 0)
	{
		*result = ft_strjoin(*result, env_value);
		lstaddback_malloc(init, lstnew_malloc(*result));
	}
	end_env_name(str);
	free(env_name);
}

char	*expand_env_and_quote(char *str,t_init *init)
{
	t_quote quote;
	char *result;

	result = "";
	quote.quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && quote.quote == 0)
		{
			quote.quote = *str;
			str++;
		}
		else if (*str == quote.quote && quote.quote != 0)
		{
			quote.quote = 0;
			str++;
		}
		else if (quote.quote != '\'' && is_env(str))
		{
			expand_env(&str, &result, init);
		}
		else
			result = ft_join_str_in_init(init, *str++, result);
	}
	return (result);
}

void	expander_expanding(t_init *init)
{
	t_lex_list *l_list;
	
	l_list = init->lst_lex;
	while (l_list)
	{
		if (l_list->operator == HERE_DOC)
			l_list = l_list->next;
		if (l_list->operator == WORD)
		{
			l_list->word = expand_env_and_quote(l_list->word, init);
		}
		
		l_list = l_list->next;
	}
}