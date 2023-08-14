/* ************************************************************************** */
/*				                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:19:38 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 17:51:07 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	grep_old_pwd_and_new(t_init *init)
{
	t_env_list	*v2;
	char		buffer[PATH_MAX];
	char		*str;
	char		*new_path;

	v2 = init->lst_env;
	v_value(init);
	str = getcwd(buffer, PATH_MAX);
	v2 = init->lst_env;
	while (v2)
	{
		if (ft_strsame(v2->name, "PWD"))
		{
			new_path = ft_strdup(str);
			lstaddback_malloc(init, lstnew_malloc(new_path));
			if (new_path)
				change_env_value("PWD", new_path, init);
			break ;
		}
		v2 = v2->next;
	}
}

char	*get_path_from_home(char *path, char **envp, t_init *init)
{
	char	*pathfh;
	char	*tmp;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (ft_strlen(path) == 0 || (ft_strlen(path) == 1 && path[0] == '~'))
		return (get_home_path(envp, init));
	tmp = malloc(sizeof(char) * (ft_strlen(path)));
	if (!tmp)
		return (NULL);
	if (path[i] == '~')
		i++;
	while (path[i])
	{
		tmp[y] = path[i];
		y++;
		i++;
	}
	tmp[y] = '\0';
	pathfh = ft_strjoin(get_home_path(envp, init), tmp);
	free(tmp);
	lstaddback_malloc(init, lstnew_malloc(pathfh));
	return (pathfh);
}

static int	handle_dash_option(t_init *init)
{
	if (chdir(get_env_value("OLDPWD", init)) == -1)
		return (0);
	grep_old_pwd_and_new(init);
	return (1);
}

static int	handle_home_option(char **p, char **envp, t_init *init, int tilde)
{
	char	*home_path;

	home_path = get_home_path(envp, init);
	if (ft_strcmp(home_path, "") == 0)
	{
		ft_print_fd("cd : HOME not set\n", 2);
		return (0);
	}
	if (tilde == 0)
		chdir(get_path_from_home("~", envp, init));
	else
	{
		home_path = get_path_from_home(p[1], envp, init);
		chdir(home_path);
	}
	grep_old_pwd_and_new(init);
	return (1);
}

void	the_real_cd(char **path, char **envp, t_init *init)
{
	if (path[1] && path[1][0] == '-' && ft_strlen(path[1]) == 1)
	{
		if (!handle_dash_option(init))
			return ;
	}
	else if (size_double_tab(path) == 1
		|| (path[1][0] == '~' && path[1][1] == '/'))
	{
		if (!handle_home_option(path, envp, init, 1))
			return ;
	}
	else if (size_double_tab(path) == 1
		|| (path[1][0] == '~' && ft_strlen(path[1]) == 1))
	{
		if (!handle_home_option(path, envp, init, 0))
			return ;
	}
	else if (access(path[1], F_OK) != 0)
	{
		ft_print_fd(cd_error_no_access(path[1], init), 2);
		return ;
	}
	else if (chdir(path[1]) == 0)
		grep_old_pwd_and_new(init);
}
