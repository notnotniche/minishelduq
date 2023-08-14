/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:11:06 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 14:32:36 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_err_msg(t_init *init,t_exec_init *exec_init, char *str, char *err_msg, int exittos)
{
	init->err_msg = ft_strjoin(str, err_msg);
	lstaddback_malloc(init, lstnew_malloc(init->err_msg));
	ft_print_fd(init->err_msg, 2);
	free_close_exit(init, exec_init, exittos);
}
