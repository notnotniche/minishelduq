/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:32:41 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/09 16:06:36 by nklingsh         ###   ########.fr       */
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

// void print_env_value(char *name, char *value, t_init *init)
// {
// 	t_env_list *tmp;

// 	tmp = init->lst_env;
// 	while (tmp)
// 	{
// 		if (ft_strsame(tmp->name, name))
// 			printf("%s=%s\n",name, value);
// 		else
				
// 	}
	
// }

// void ft_print_env(char **arguments, t_init *init)
// {
// 	int i;
// 	char **str;

// 	i = 1;
// 	str=ft_split(arguments[0], '=');
// 	{
		
// 	}	
// }


void the_real_env(char **arguments, t_init *init)
{
	if (size_double_tab(arguments) == 1)
		print_lst_env(init->lst_env);
	else if (size_double_tab(arguments) > 1)
	{
		if (check_if_all_args_are_good(arguments))
		{
			print_lst_env(init->lst_env);
			
		}
	}	
}