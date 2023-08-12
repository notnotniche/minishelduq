/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isnumber.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:55:55 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 00:30:13 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	numerical(char c)
{
	if ((c >= 7 && c <= 13) || c == '\0' || c == 32)
		return (0);
	return (1);
}

int	is_quote(char c)
{
	if ((c == '\'') || (c == '\"'))
		return (1);
	return (0);
}

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_only_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_space(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
