/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:25:51 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 20:25:28 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_env(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '$' || !str[i + 1])
		return (0);
	if (!ft_isalnum(str[i + 1]) && ft_isitenv(str[i + 1] == 1))
		return (0);
	return (1);
}

char	*env_name_expander(char *str)
{
	int		i;
	char	*env_name;

	i = -1;
	if (str[0] == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (ft_strdup(""));
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
	}
	env_name = malloc((i + 1) * sizeof(char));
	if (!env_name)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		env_name[i] = str[i];
	}
	env_name[i] = 0;
	return (env_name);
}

void	end_env_name(char **str)
{
	if (**str == '?')
	{
		(*str)++;
		return ;
	}
	if (!ft_isalpha(**str) && **str != '_')
	{
		(*str)++;
		return ;
	}
	while (**str)
	{
		if (!ft_isalnum(**str) && **str != '_')
			break ;
		(*str)++;
	}
}

void	add_back_env(t_init *init, char *name, char *new_value)
{
	char	*duplicated_name;
	char	*duplicated_value;

	duplicated_name = ft_strdup(name);
	if (new_value)
		duplicated_value = ft_strdup(new_value);
	else
		duplicated_value = NULL;
	lstadd_back_env(&init->lst_env, \
		lstnew_env(duplicated_name, duplicated_value));
}
