/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:59:07 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 20:00:23 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_space(char *s1, char *s2, t_init *init)
{
	char	*result;

	if (!s1)
		return (s2);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	lstaddback_malloc(init, lstnew_malloc(result));
	ft_strcpy(result, s1);
	ft_strcat(result, " ");
	ft_strcat(result, s2);
	return (result);
}

int	ft_scmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
			i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	echo_n_option(char **line, int i)
{
	int	j;

	j = 0;
	if (size_double_tab(line) == 0)
		return (1);
	if (line[i][j] == '-' && line[i][j + 1] == 'n')
	{
		j += 1;
		while (line[i][j] == 'n')
			j ++;
		if (line[i][j] == '\0')
			return (0);
	}
	return (1);
}
