/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:08:59 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 20:26:31 by itahani          ###   ########.fr       */
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

int	at_least_oneisspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	*sep_init(char *sep)
{
	sep[1] = 9;
	sep[2] = 10;
	sep[3] = 11;
	sep[4] = 12;
	sep[5] = 13;
	sep[6] = 32;
	return (sep);
}

char	**split_for_expand(t_init *init, char *str)
{
	char	**splittos;
	char	*sep;

	sep = NULL;
	sep = sep_init(sep);
	(void)init;
	splittos = ft_split_piscine(str, sep);
	lstaddback_malloc(init, lstnew_malloc(splittos));
	return (splittos);
}

void	change_env_value(char *name, char *new_value, t_init *init)
{
	t_env_list	*tmp;

	tmp = init->lst_env;
	while (tmp)
	{
		if (ft_strsame(tmp->name, name))
		{
			set_value(tmp, new_value);
			return ;
		}
		tmp = tmp->next;
	}
	add_back_env(init, name, new_value);
}
