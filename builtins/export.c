/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:52:24 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 20:36:02 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_to_linked_list(t_init *init, char **str)
{
	if (str[1] == NULL)
		update_env_or_export(str[0], str[1], init, VALID);
	else
		update_env_or_export(str[0], str[1], init, 0);
}

char	**exportator(char *str)
{
	char	**splittos;

	splittos = ft_split(str, '=');
	return (splittos);
}

void	the_real_export(char **arguments, t_init *init)
{
	char	**str;

	str = NULL;
	if (size_double_tab(arguments) == 1)
		print_lst_env(init->lst_env);
	else if (size_double_tab(arguments) == 2)
	{
		if (valid_export(arguments) == 1)
		{
			str = exportator(arguments[1]);
			export_to_linked_list(init, str);
			free_tab_tab(str);
		}
	}
	else
		printf("error too many arugments");
}
