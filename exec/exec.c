/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:38 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 20:17:33 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_wait_pid(t_exec_init exec_init)
{
	int		i;
	pid_t	tmp;
	int		status;

	(void)exec_init;
	i = 0;
	while (1)
	{
		tmp = wait(&status);
		if (WIFEXITED(status))
			g_status_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_status_exit_code = 128 + WTERMSIG(status);
			if (g_status_exit_code == 130 || g_status_exit_code == 131)
				;
		}
		if (tmp == -1)
			break ;
	}
}

int	here_doc_exist(t_init *init)
{
	t_str_list	*tmp;
	int			i;

	i = 0;
	tmp = init->lst_token->delimeter;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	exec_child_process(t_init *init, int i, t_exec_init exec_init)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exec_all_pid(init, i, exec_init);
}

void	exec_parent_process(t_exec_init *exec_init)
{
	if (signal(SIGINT, SIG_IGN) != SIG_ERR)
		g_status_exit_code = 131;
	if (exec_init->pipetmp)
		close(exec_init->pipetmp);
	exec_init->pipetmp = exec_init->mypipe[0];
	close(exec_init->mypipe[1]);
}

void	initialize_exec(t_init *init, int *i, t_exec_init *exec_init)
{
	if (ft_size_token(init->lst_token) == 0)
		return ;
	*exec_init = init_exec_struct(init);
	*i = 0;
}
