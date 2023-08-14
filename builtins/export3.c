/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:05:03 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 20:05:13 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != '=')
		i++;
	while (str[i])
		i++;
	return (1);
}

int	valid_export(char **arguments)
{
	if (valid_first_letter(arguments[1], 0) == 0)
		return (0);
	if (valid_until_equal(arguments[1]) == 0)
		return (0);
	else if (valid_after_equal(arguments[1]) == 0)
		return (0);
	return (1);
}