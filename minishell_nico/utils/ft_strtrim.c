/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:03:00 by nklingsh          #+#    #+#             */
/*   Updated: 2023/07/21 17:25:25 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strtrim(char *str, int i , int y)
{
	char *trimmed;
	int x;

	x = 0;
	trimmed = malloc (sizeof(char) * y - i + 1);
	if (!trimmed)
		return (free(trimmed), NULL);
	while (i <= y)
	{
		trimmed[x] = str[i];
		x++;
		i++;
	}
	trimmed[x] = '\0';
	return (trimmed);
}