/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:18:45 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 19:50:27 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_fd(char *str, int fd)
{
	char	*s;

	s = ft_strjoin("minishell : ", str);
	s = ft_strjoin(s, "\n");
	write(fd, s, ft_strlen(s));
	rl_on_new_line();
	rl_replace_line("", 0);
}