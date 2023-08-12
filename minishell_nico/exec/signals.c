/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:10 by itahani           #+#    #+#             */
/*   Updated: 2023/08/12 01:46:01 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ctrl+c
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line(); // Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
	rl_replace_line("", 0);
	rl_redisplay(); // Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
	g_status_exit_code = 130;
	return ;
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line(); // Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
	rl_replace_line("", 0);
	rl_redisplay(); // Change what's displayed on the screen to reflect the current contents of rl_line_buffer.
	g_status_exit_code = 130;
	exit(130);
	return ;
}