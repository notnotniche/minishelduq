/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:44:04 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/07 18:48:46 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_name_size(char *env)
{
	int i;

	i = 0;
	if (ft_strlen(env) == 0)
		return (0);
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	if (env[i - 1] == '+')
		i--;
	return (i);
}

char	*env_name(char *env)
{
	int		i;
	char	*name;

	if (env[0] == '=')
		return (NULL);
	i = env_name_size(env);
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=' || (env[i] == '+' && env[i + 1] == '='))
			break ;
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	if (ft_strlen(name) == 0)
	{
		free(name);
		return (NULL);
	}
	return (name);
}

t_env_list	*init_env_list(char **env)
{
	t_env_list	*env_list;
	char 		*value;
	char 		*name;
	int			i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		name = env_name(env[i]);
		value = ft_strdup(getenv(name));
		lstadd_back_env(&env_list, lstnew_env(name, value));
		i++;
	}
	return (env_list);
}

void	change_env_value(char *name, char *new_value, t_init *init)
{
	t_env_list *tmp;

	tmp = init->lst_env;
	while (tmp)
	{
		if (ft_strsame(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
	lstadd_back_env(&init->lst_env, lstnew_env(ft_strdup(name), new_value));
}

char	*get_env_value(char *name, t_init *init)
{
	t_env_list *env_list;

	env_list = init->lst_env;
	while (env_list)
	{
		if (ft_strsame(name, env_list->name))
			return (env_list->value);
		env_list = env_list->next;
		
	}
	return ("");
}