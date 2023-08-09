/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:52:24 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/09 17:39:21 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_double_tab(char **arguments)
{
	int i;

	i = 0;
	while (arguments[i])
		i++;
	return (i);
}

int valid_first_letter(char *str, int i)
{
	if(ft_isalpha(str[i]) == 0)
		return (0);
	else
		return (1);
}

int valid_only_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (1);
}

int valid_until_equal(char *str)
{
	int i;
	int y;

	y = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		printf("---------> %c ", i);
		if (ft_isalnum(str[i]) == 0)
			return (printf("\n cest ciao : %c : --> \n", str[i]), 0);
		i++;
	}
	return (1);
}

int valid_after_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i + 1] != '=')
		i++;
	while (str[i])
		i++;
	return (1);
}

int valid_export(char **arguments)
{
	printf("arguemtns :%s \n", arguments[1]);
	if (valid_first_letter(arguments[1], 0) == 0)
		return (printf("cest pas bon1"),0);
	if (valid_until_equal(arguments[1]) == 0)
		return (printf("cest pas bon2"),0);
	else if (valid_after_equal(arguments[1]) == 0)
		return (printf("cest pas bon3"),0);
	return (1);
}



void export_to_linked_list(t_init *init, char **str)
{
	if (str[1] == NULL)
		change_env_value(str[0], str[1], init);
	else
		change_env_value(str[0],str[1], init);
}

char  **exportator(char *str)
{
	char **splittos;

	splittos = ft_split(str, '=');
	return (splittos);
}

void the_real_export(char **arguments, t_init *init)
{
	char **str;
	
	str = NULL;
	if (size_double_tab(arguments) == 1)
	{
		print_lst_env(init->lst_env);
	}
	else if (size_double_tab(arguments) == 2)
	{
		if (valid_export(arguments) == 1)
		{
		str = exportator(arguments[1]);
		export_to_linked_list(init, str);
		}
		free(str);
	}
}