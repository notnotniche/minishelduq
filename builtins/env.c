/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:32:41 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/09 17:25:00 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int str_without_equl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int str_with_equal(char *str, int i)
{
	if (i == ft_strlen(str))
		return (1);
	if (ft_strlen(str) > i)
		return (2);
	return (0);
}

int check_if_all_args_are_good(char **arguments)
{
	int i;

	i = 1;
	while (arguments[i])
	{
		if (str_without_equl(arguments[i]) == 0)
			return (0);
		if (str_with_equal(arguments[i], i) == 0)
			return (0);
		i++;
	}
	return (1);
}

void    print_for_env(t_init *init)
{
	
	t_env_list    *suivant;

	suivant =init->lst_env;
    while(suivant)
    {
        if (suivant->name && suivant->value)
            printf("%s=%s\n", suivant->name, suivant->value);
		suivant = suivant->next;
    }
}


void the_real_env(char **arguments, t_init *init)
{
	if (size_double_tab(arguments) == 1)
		print_for_env(init);
}