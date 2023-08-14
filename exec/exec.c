/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:38 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 17:19:45 by nklingsh         ###   ########.fr       */
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

static void	exec_child_process(t_init *init, int i, t_exec_init exec_init)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exec_all_pid(init, i, exec_init);
}

static void	exec_parent_process(t_exec_init *exec_init)
{
	if (signal(SIGINT, SIG_IGN) != SIG_ERR)
		g_status_exit_code = 131;
	if (exec_init->pipetmp)
		close(exec_init->pipetmp);
	exec_init->pipetmp = exec_init->mypipe[0];
	close(exec_init->mypipe[1]);
}

void	exec(t_init *init)
{
	int				i;
	t_exec_init		exec_init;

	if (ft_size_token(init->lst_token) == 0)
		return ;
	exec_init = init_exec_struct(init);
	i = 0;
	while (i < exec_init.nb_command)
	{
		if (pipe(exec_init.mypipe) == -1)
			printf("!233123131311231");
		exec_init.realpid = fork();
		if (exec_init.realpid < 0)
			printf("deuxieme");
		else if (exec_init.realpid == 0)
			exec_child_process(init, i, exec_init);
		else
			exec_parent_process(&exec_init);
		i++;
		init->lst_token = init->lst_token->next;
	}
	my_wait_pid(exec_init);
	if (g_status_exit_code == 130)
		printf("\n");
	else if (g_status_exit_code == 131)
		printf("Quit (core dumped)\n");
	close(exec_init.pipetmp);
	heredoc_supp(init->lst_token);
}
