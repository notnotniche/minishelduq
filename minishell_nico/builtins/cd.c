/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:19:38 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 17:24:05 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../minishell.h"

// si parsing detecte plusieurs arg apres cd : 
// return (ft_putstr_fd("cd: too many arguments\n", 2), 1);

char    *ft_strjoin_cr(char const *s1, char s2)
{
    char    *res;
    int        i;

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

char    *cd_error_no_access(char *path)
{
    char    *ret_error;

    ret_error = ft_strjoin(" cd: ", path);
    ret_error = ft_strjoin(ret_error, ": No such file or directory\n");
    return (ret_error);
}

char    *get_home_path(char **envp)
{
    int        i;
    int        j;
    char    *home_path;

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
                j++;
            }
        }
        i++;
    }
    return (home_path);
}

void grep_old_pwd_and_new(t_init *init)
{
    t_env_list *v2;
    char *str;
    char buffer[PATH_MAX];

    v2 = init->lst_env;
    str = getcwd(buffer, PATH_MAX);
    
    while (v2)
    {
        if (ft_strsame(v2->name, "OLDPWD"))
        {
            change_env_value("OLDPWD", get_env_value("PWD", init), init);
            break;
        }
        v2 = v2->next;
    }
    v2 = init->lst_env;
    while (v2)
    {
        if (ft_strsame(v2->name, "PWD"))
        {
            change_env_value("PWD", str, init);
            break;
        }
        v2 = v2->next;
    }
}

void 	the_real_cd(char **path, char **envp, t_init *init)
{
    if (size_double_tab(path) == 1 || path[1][0] == '~' )
    {
        if (ft_strcmp(get_home_path(envp), "") == 0)
            return (ft_print_fd("cd : HOME not set\n", 2), free(NULL));
			
        else
		{
            chdir(get_home_path(envp));
			grep_old_pwd_and_new(init);
		}
	}
    else if (access(path[1], F_OK) != 0)
        return (ft_print_fd(cd_error_no_access(path[1]), 2), free(NULL));
    else if (chdir(path[1]) == 0)
        grep_old_pwd_and_new(init);
	
}