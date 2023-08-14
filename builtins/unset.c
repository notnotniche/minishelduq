/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:33:12 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 14:42:43 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	name_exist_in_env(char *str, t_init *init)
{
	t_env_list	*lst;

	lst = init->lst_env;
	while (lst)
	{
		if (ft_strcmp(str, lst->name) == 0)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	remove_node_env_name(t_init *init, char *str)
{
	t_env_list	*now;
	t_env_list	*before;

	now = init->lst_env;
	before = NULL;
	if (now != NULL && ft_strcmp(now->name, str) == 0)
	{
		init->lst_env = now->next;
		free(now);
		return ;
	}
	while (now)
	{
		if (ft_strcmp(str, now->name) == 0)
		{
			before->next = now->next;
			free(now->name);
			free(now->value);
			free(now);
			return ;
		}
			before = now;
			now = now->next;
	}
}

void	the_real_unset(char **arguments, t_init *init)
{
	if (size_double_tab(arguments) == 1)
		;
	else if (size_double_tab(arguments) == 2)
	{
		if (name_exist_in_env(arguments[1], init) == 1)
			remove_node_env_name(init, arguments[1]);
	}
}
