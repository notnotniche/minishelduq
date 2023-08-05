/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:17:53 by nklingsh          #+#    #+#             */
/*   Updated: 2023/07/27 17:26:17 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *str, char *str2)
{
	int i;
	int	compteur;

	i = 0;
	compteur = 0;
	if (ft_strlen(str) > ft_strlen(str2))
		return (1);
	if (ft_strlen(str) < ft_strlen(str2))
		return (-1);
	while(str[i] && str2[i])
	{
		compteur = compteur + str[i] - str2[i];
		i++;
	}
	return (compteur);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}