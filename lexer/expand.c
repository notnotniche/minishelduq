/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:08 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 00:05:05 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_env(char **str, char **result, t_init *init)
{
	char	*env_name;
	char	*env_value;

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

int at_least_oneisspace(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	*expand_env_and_quote(char *str, t_init *init)
{
	t_quote	quote;
	char	*result;

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
			if (at_least_oneisspace(result))
				init->lst_lex->must_split = 1;
		}
		else
			result = ft_join_str_in_init(init, *str++, result);
	}
	return (result);
}
	
char **split_for_expand(t_init *init, char *str)
{
	char **splittos;
	(void)init;
	char sep[]={9, 10, 11, 12, 13, 32};
	
	splittos = ft_split_piscine(str, sep);
	lstaddback_malloc(init, lstnew_malloc(splittos));
	return (splittos);
	
}

void	expander_expanding(t_init *init)
{
	t_lex_list	*l_list;
	char		**splittos;

	l_list = init->lst_lex;
	while (l_list)
	{
		if (l_list->operator == HERE_DOC)
			l_list = l_list->next;
		else if (l_list->operator == WORD)
		{
			l_list->word = expand_env_and_quote(l_list->word, init);
			if (l_list->must_split == 1)
			{
				splittos = split_for_expand(init, l_list->word);
				delete_last_node_lex(&init->lst_lex);
                while (*splittos)
                {
                    lstadd_back_lex(&init->lst_lex, lstnew_lex(*splittos, WORD, init));
                    splittos++;
				}
				l_list->must_split = 0;
			}
		}
		l_list = l_list->next;
	}
}
