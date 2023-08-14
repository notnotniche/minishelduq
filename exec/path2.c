/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:11:06 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 16:14:09 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	f_msg(t_init *init, char *str, char *err_msg)
{
	init->err_msg = ft_strjoin(str, err_msg);
	lstaddback_malloc(init, lstnew_malloc(init->err_msg));
	ft_print_fd(init->err_msg, 2);
}

int	tinker_path(t_init *init, t_exec_init *exec_init, char *str)
{
	if (check_if_directory(str))
	{
		f_msg(init, str, ": Is a directory");
		free_close_exit(init, exec_init, 126);
	}
	if (file_exec(str) == 1)
		return (1);
	if (file_exec(str) != 1)
	{
		f_msg(init, str, ": Permission denied");
		free_close_exit(init, exec_init, 126);
	}
	return (0);
}

char	*concatenate_strings(char *s1, char *s2)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, "/");
	res = ft_strjoin(tmp, s2);
	free(tmp);
	return (res);
}

char	*execute_from_path(char **splittos, t_str_list *c)
{
	int		i;
	int		file_exec_result;
	char	*res;

	i = -1;
	while (splittos[++i])
	{
		res = concatenate_strings(splittos[i], c->str_list);
		file_exec_result = file_exec(res);
		if (file_exec_result == 1)
			return (ft_strdup(res));
		free(res);
	}
	return (NULL);
}
