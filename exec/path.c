/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:14:13 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 16:11:12 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_close_exit(t_init *init, t_exec_init *exec_init, int exittos)
{
	free_env_list(init->lst_env);
	free_s_init(init);
	close(exec_init->mypipe[1]);
	close(exec_init->mypipe[0]);
	close(exec_init->pipetmp);
	exit(exittos);
}

char	*is_pathabs(t_init *init, char *str, t_exec_init *exec_init)
{
	if (str[0] == '~')
		str = get_path_from_home(str, env_to_str(init, init->lst_env, \
			ft_size_env(init->lst_env)), init);
	if ((str[0] == '~' || str[0] == '/' || \
		str[0] == '.') && access(str, F_OK) == 0)
	{
		if (tinker_path(init, exec_init, str) == 1)
			return (str);
	}
	else if ((str[0] == '~' || str[0] == '/' || \
		str[0] == '.') && access(str, F_OK) == -1)
	{
		f_msg(init, str, ": No such file or directory");
		free_close_exit(init, exec_init, 126);
	}
	return (NULL);
}

char	*path_res(t_init *init, t_str_list *cmd, t_exec_init *exec_init)
{
	char	*res;

	if (ft_strlen(cmd->str_list) == 0)
		exit(1);
	res = is_pathabs(init, cmd->str_list, exec_init);
	if (res)
		return (res);
	return (NULL);
}

void	free_tab_tab(char **splittos)
{
	int	i;

	i = 0;
	while (splittos[i])
	{
		free(splittos[i]);
		i++;
	}
	free(splittos);
	return ;
}

char	*path_maker(t_init *init, t_str_list *c, char *path, t_exec_init *e_i)
{
	char	*res;
	char	**splittos;
	int		i;

	i = -1;
	if (ft_strlen(init->lst_token->arguments->str_list) != 0)
	{	
		res = path_res(init, c, e_i);
		lstaddback_malloc(init, lstnew_malloc(res));
		if (res)
			return (res);
		if (!path)
		{
			f_msg(init, c->str_list, ": command not found");
			free_close_exit(init, e_i, 126);
		}
		splittos = ft_split(path, ':');
		if (execute_from_path(splittos, c) != NULL)
			return (execute_from_path(splittos, c));
		free_tab_tab(splittos);
	}
	f_msg(init, c->str_list, ": command not found");
	free_close_exit(init, e_i, 126);
	return (NULL);
}
