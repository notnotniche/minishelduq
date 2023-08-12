/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:12:35 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 23:53:57 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	y = 0;
	if (!str2)
		return (NULL);
	str = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (str1[i])
		str[y++] = str1[i++];
	i = 0;
	while (str2[i])
		str[y++] = str2[i++];
	str[y] = '\0';
	return (str);
}
