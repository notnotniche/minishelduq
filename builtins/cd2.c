/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:57:10 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 19:58:19 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../minishell.h"

// si parsing detecte plusieurs arg apres cd : 
// return (ft_putstr_fd("cd: too many arguments\n", 2), 1);

char	*ft_strjoin_cr(char const *s1, char s2)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof (char) * ((ft_strlen((char *)s1)
					+ 2)));
	if (!res)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s2;
	res[i + 1] = '\0';
	return (res);
}

char	*cd_error_no_access(char *path, t_init *init)
{
	char	*ret_error;

	ret_error = ft_strjoin(" cd: ", path);
	lstaddback_malloc(init, lstnew_malloc(ret_error));
	ret_error = ft_strjoin(ret_error, ": No such file or directory");
	lstaddback_malloc(init, lstnew_malloc(ret_error));
	return (ret_error);
}

char	*get_home_path(char **envp, t_init *init)
{
	int		i;
	int		j;
	char	*home_path;

	i = 0;
	j = 5;
	home_path = "";
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME", 4) == 0)
		{
			while (envp[i][j])
			{
				home_path = ft_strjoin_cr(home_path, envp[i][j]);
				lstaddback_malloc(init, lstnew_malloc(home_path));
				j++;
			}
		}
		i++;
	}
	return (home_path);
}

t_env_list	*v_value(t_init *init)
{
	char		*oldpath;
	t_env_list	*v2;

	v2 = init->lst_env;
	while (v2)
	{
		if (ft_strsame(v2->name, "OLDPWD"))
		{
			oldpath = get_env_value("PWD", init);
			if (oldpath)
				change_env_value("OLDPWD", oldpath, init);
			break ;
		}
		v2 = v2->next;
	}
	return (v2);
}
