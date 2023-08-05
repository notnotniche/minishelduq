/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splittos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:12:36 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/01 15:15:26 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stdio.h>

static int	issep(char str, char sep)
{
	if (sep == str)
		return (1);
	return (0);
}

static int	nbword(const char *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (issep(str[i], c) == 0 && str[i])
		{
			while (issep(str[i], c) == 0 && str[i])
				i++;
			words++;
		}
		while (issep(str[i], c) == 1 && str[i])
			i++;
	}
	return (words);
}

static char	*dupdup(char const *str, char sep)
{
	int		len;
	int		i;
	char	*cpy;

	len = 0;
	i = 0;
	while (str[len] && !issep(str[len], sep))
		len++;
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	while (str[i] && !issep(str[i], sep))
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (nbword(s, c) + 1));
	if (!split)
		return (NULL);
	while (s[i] && issep(s[i], c))
		i++;
	while (s[i])
	{
		split[j] = dupdup(&s[i], c);
		while (s[i] && !issep(s[i], c))
			i++;
		while (s[i] && issep(s[i], c))
			i++;
		j++;
	}
	split[j] = 0;
	return (split);
}