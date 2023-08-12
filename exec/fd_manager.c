/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:19:03 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/01 15:20:16 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(int fd_nbr, int *fd_array)
{
	int i;

	i = 0;
	while (i < fd_nbr)
	{
		close(fd_array[i]);
		i++;
	}
}