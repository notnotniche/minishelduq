/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:25:56 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 16:46:11 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_command_builtin(char *str)
{
	if (ft_strsame(str, "echo"))
		return (1);
	if (ft_strsame(str, "pwd"))
		return (1);
	if (ft_strsame(str, "cd"))
		return (1);
	if (ft_strsame(str, "export"))
		return (1);
	if (ft_strsame(str, "unset"))
		return (1);
	if (ft_strsame(str, "env"))
		return (1);
	if (ft_strsame(str, "exit"))
		return (1);
	return (0);
}

int builtin_manage(t_init *init, char *str, char **all_args)
{
	if (ft_strsame(str, "echo"))
		text_to_print(all_args);
	if (ft_strsame(str, "pwd"))
		the_real_pwd(init);
	if (ft_strsame(str, "export"))
		the_real_export(all_args, init);
	if (ft_strsame(str, "env"))
		the_real_env(all_args, init);
	if (ft_strsame(str, "unset"))
		the_real_unset(all_args, init);
	if (ft_strsame(str, "cd"))
	{
		the_real_cd(all_args, env_to_str(init, init->lst_env, ft_size_env(init->lst_env)), init);
	}
	return (0);
}