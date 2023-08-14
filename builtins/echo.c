/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:25:02 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 21:06:52 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

static int	skip_echo(char **line)
{
	int		i;

	i = 0;
	while (ft_scmp(line[i], "echo") != 0)
		i++;
	if (ft_scmp(line[i], "echo") == 0)
		i++;
	return (i);
}

static int	check_echo_option(char **line, int i)
{
	int		n;

	n = 0;
	while (echo_n_option(line, i) == 0)
	{
		i++;
		n++;
	}
	return (n);
}

static char	*get_res(char **line, int i, t_init *init)
{
	char	*res;

	res = NULL;
	while (line[i] && (ft_scmp(line[i], "|") != 0 && ft_scmp(line[i], "<") != 0
			&& ft_scmp(line[i], ">") != 0 && ft_scmp(line[i], "<<") != 0
			&& ft_scmp(line[i], ">>") != 0))
	{
		res = ft_strjoin_space(res, line[i], init);
		i++;
	}
	return (res);
}

void	text_to_print(char **line, t_init *init)
{
	int		i;
	int		n;
	char	*res;

	if (size_double_tab(line) == 1)
	{
		printf("\n");
		return ;
	}
	i = skip_echo(line);
	n = check_echo_option(line, i);
	res = get_res(line, i + n, init);
	if (n == 0)
		printf("%s\n", res);
	else
		printf("%s", res);
}
