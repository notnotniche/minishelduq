/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:14:13 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 15:16:44 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *is_pathabs(t_init *init, char *str)
{
	if ((str[0] == '/' || str[0] == '.') && access(str, F_OK) == 0)
	{
		// printf("lkjfslkgweklfgwlelgjweljgwejlgjlkwe");
		if (check_if_directory(str))
			exit(1);
		if (file_exec(str) == 1)
			return (str);
		else
			exit(1);
	}
	else if ((str[0] == '/' || str[0] == '.') && access(str, F_OK) == -1)
		exit(1);
	return (NULL);
	init->lst_token->token = 1;
}

char *path_res(t_init *init,t_str_list *cmd)
{
	char *res;
	
	if (ft_strlen(cmd->str_list) == 0)
		exit(1);
	// printf("\n cmd->str_list : %s \n",cmd->str_list);
	res = is_pathabs(init, cmd->str_list);
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

char *path_maker(t_init *init, t_str_list *cmd, char *path)
{
	char *res;
	char *tmp;
	char **splittos;
	int i;
	
	i = 0;
	res = path_res(init, cmd);
	if (res)
		return (printf("--> path_res %s res \n",res), res);
	if (!path)
		exit(1);
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
	return (NULL);
}