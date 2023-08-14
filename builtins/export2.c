/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:03:08 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 20:04:55 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_double_tab(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
		i++;
	return (i);
}

int	valid_first_letter(char *str, int i)
{
	if (ft_isalpha(str[i]) == 0)
		return (0);
	else
		return (1);
}

int	valid_only_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (1);
}

int	valid_until_equal(char *str)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
