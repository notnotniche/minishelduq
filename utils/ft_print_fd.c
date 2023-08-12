/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:18:45 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 15:31:49 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_fd(char *str, int fd)
{
	char	*s;
	char *tmp;

	tmp = ft_strjoin("Minishell : ", str);
	s = ft_strjoin(tmp, "\n");
	free(tmp);
	write(fd, s, ft_strlen(s));
	free(s);
	rl_on_new_line();
	rl_replace_line("", 0);
}