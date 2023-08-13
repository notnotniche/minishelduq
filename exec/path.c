/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:14:13 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/13 18:26:16 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *is_pathabs(t_init *init, char *str, t_exec_init *exec_init)
{
	if ((str[0] == '/' || str[0] == '.') && access(str, F_OK) == 0)
	{
		if (check_if_directory(str))
		{
			init->err_msg = ft_strjoin(str, ": Is a directory");
			lstaddback_malloc(init, lstnew_malloc(init->err_msg));
			ft_print_fd(init->err_msg, 2);
			free_env_list(init->lst_env);
			free_s_init(init);
			close(exec_init->mypipe[1]);
			close(exec_init->mypipe[0]);
			close(exec_init->pipetmp);
			exit(126);
		}
		if (file_exec(str) == 1)
			return (str);
		if (file_exec(str) != 1)
		{
			init->err_msg = ft_strjoin(str, ": Permission denied");
			lstaddback_malloc(init, lstnew_malloc(init->err_msg));
			ft_print_fd(init->err_msg, 2);
			free_env_list(init->lst_env);
			free_s_init(init);
			close(exec_init->mypipe[1]);
			close(exec_init->mypipe[0]);
			close(exec_init->pipetmp);
			exit(126);
		}
		exit(1);
	}
	else if ((str[0] == '/' || str[0] == '.') && access(str, F_OK) == -1)
	{
		init->err_msg = ft_strjoin(str, ": No such file or directory");
		lstaddback_malloc(init, lstnew_malloc(init->err_msg));
		ft_print_fd(init->err_msg, 2);
		free_s_init(init);
		free_env_list(init->lst_env);
		close(exec_init->mypipe[1]);
		close(exec_init->mypipe[0]);
		close(exec_init->pipetmp);
		exit(127);
	}
	return (NULL);
	init->lst_token->token = 1;
}

char *path_res(t_init *init, t_str_list *cmd, t_exec_init *exec_init)
{
	char *res;
	
	if (ft_strlen(cmd->str_list) == 0)
		exit(1);
	// printf("\n cmd->str_list : %s \n",cmd->str_list);
	res = is_pathabs(init, cmd->str_list, exec_init);
	// printf("path res  : --> %s\n", res);
	if (res)
		return (res);
	return (NULL);
}

void free_tab_tab(char **splittos)
{
	int i;
	
	i = 0;
	while (splittos[i])
	{
		free(splittos[i]);
		i++;
	}
	free(splittos);
	return ;
}

char *path_maker(t_init *init, t_str_list *cmd, char *path,t_exec_init *exec_init)
{
	char *res;
	char *tmp;
	char **splittos;
	int i;
	
	i = 0;
	if (ft_strlen(init->lst_token->arguments->str_list) != 0)
	{	
		res = path_res(init, cmd, exec_init);
		// printf("paaaaatah res %s\n", res);
		if (res)
			return (res);
		if (!path)
		{
			init->err_msg = ft_strjoin(cmd->str_list, ": command not found");
			ft_print_fd(init->err_msg, 2);
			free(init->err_msg);
			free(res);
			free_env_list(init->lst_env);
			free_s_init(init);
			close(exec_init->mypipe[0]);
			close(exec_init->mypipe[1]);
			close(exec_init->pipetmp);
			exit(127);
		}
		splittos = ft_split(path, ':');
		while (splittos[i])		
		{
			tmp = ft_strjoin(splittos[i], "/");
			res = ft_strjoin(tmp, cmd->str_list);
			free(tmp);
			// printf("\n%s", res);
			if (file_exec(res) == 1)
				return (ft_strdup(res));
			free(res);
			i++;
		}
		free_tab_tab(splittos);
	}
	init->err_msg = ft_strjoin(cmd->str_list, ": command not found");
	ft_print_fd(init->err_msg, 2);
	free(init->err_msg);
	free_env_list(init->lst_env);
	free_s_init(init);
	close(exec_init->mypipe[0]);
	close(exec_init->mypipe[1]);
	close(exec_init->pipetmp);
	exit(127);	
	return (NULL);
}