/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:33:10 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 20:49:44 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_same_name(t_env_list *env, char *name)
{
	return (ft_strsame(env->name, name));
}

void	modify_env(t_env_list *tmp, char *new_val, int flag)
{
	free(tmp->value);
	if (new_val)
	{
		tmp->value = ft_strdup(new_val);
		tmp->i = 0;
	}
	else
	{
		if (flag == VALID)
			tmp->i = VALID;
		tmp->value = NULL;
	}
}

void	update_env_or_export(char *name, char *new_val, t_init *init, int flag)
{
	t_env_list	*current;
	char		*val_to_add;

	current = init->lst_env;
	while (current)
	{
		if (is_same_name(current, name))
		{
			modify_env(current, new_val, flag);
			return ;
		}
		current = current->next;
	}
	if (new_val)
		val_to_add = ft_strdup(new_val);
	else
		val_to_add = NULL;
	lstadd_back_env(&init->lst_env, lstnew_env(ft_strdup(name), val_to_add));
}
