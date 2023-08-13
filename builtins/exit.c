/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:04:31 by itahani           #+#    #+#             */
/*   Updated: 2023/08/13 14:10:10 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_str_or_int(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] >= 48 && arg[i] <= 57)
			i++;
		else
			return (1); //str
	}
	return (0); //int
}

void the_real_exit(char **all_args, t_init *init)
{
	if (size_double_tab(all_args) == 1)
	{
		free_s_init(init);
		free_env_list(init->lst_env);	
		printf("exit\n");
		exit(0);
	}
	if (size_double_tab(all_args) > 2)
	{
		ft_print_fd("exit: too many arguments", 2);
		g_status_exit_code = 1;
		return ;
	}
	if (is_str_or_int(all_args[1]) == 1)
	{
		init->err_msg = ft_strjoin("exit: ", all_args[1]);
		lstaddback_malloc(init, lstnew_malloc(init->err_msg));
		init->err_msg = ft_strjoin(init->err_msg, ": numeric argument required");
		lstaddback_malloc(init, lstnew_malloc(init->err_msg));
		ft_print_fd(init->err_msg, 2);
		free_s_init(init);
		free_env_list(init->lst_env);	
		printf("exit\n");
		exit(2);
	}
	if (is_str_or_int(all_args[1]) == 0)
	{
		free_s_init(init);
		free_env_list(init->lst_env);
		printf("exit\n");
		exit(ft_atoi(all_args[1])); 
	}
}