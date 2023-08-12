/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:38 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 02:39:23 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void my_wait_pid(t_exec_init exec_init)
{
	int i;
	pid_t tmp;
	int	status; 
	
	i = 0;
	free(exec_init.pid);
	while (1)
	{
		tmp = wait(&status);
		if (WIFEXITED(status))
            g_status_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_status_exit_code = 128 + WTERMSIG(status);
		if (tmp == -1)
			break;
	}
}

int here_doc_exist(t_init *init)
{
	t_str_list *tmp;
	int i;

	i =0;
	tmp = init->lst_token->delimeter;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	//printf("nb delimeter :%d\n", i);
	return (i);
}


void real_exec(t_init *init)
{
	char **all_args;
	all_args = args_to_str(init->lst_token->arguments, ft_size_str(init->lst_token->arguments), init);

	if (here_doc_exist(init) >= 1)
		ft_heredoc(init->lst_token->delimeter->str_list, init);
	if (ft_size_token(init->lst_token) == 1 && is_command_builtin(init->lst_token->arguments->str_list))
			builtin_manage(init, all_args[0], all_args);
	else 
		exec(init);
}


// void free_int(t_exec_init exec_init)
// {
// 	if (exec_init.realpid != NULL)
// 		free(exec_init.realpid);
// }

void exec(t_init *init)
{
	int i;
	t_exec_init exec_init;
	t_token_list *head;

	i = 0;
	head = init->lst_token;
	if (ft_size_token(init->lst_token) != 0)
		exec_init = init_exec_struct(init);
	//printf("nb_command : %d \n ", exec_init.nb_command);
	while (i < exec_init.nb_command)
	{
		
		if ( pipe(exec_init.mypipe) == -1)
				exit(1);
		exec_init.realpid = fork();
		// printf("%d \n\n", exec_init.realpid);
		if (exec_init.realpid < 0)
				exit(1);
		signal(SIGINT, handle_sigint);
		if (signal(SIGQUIT, SIG_IGN) != SIG_ERR)
			g_status_exit_code = 131;
		if (exec_init.realpid == 0)
				exec_all_pid(init, i, exec_init);
		// printf("exec_init : %d\n",exec_init.pid[i]);
		else
		{
			if (exec_init.pipetmp)
				close(exec_init.pipetmp);
			exec_init.pipetmp = exec_init.mypipe[0];
			close(exec_init.mypipe[1]);
		}
		i++;
		init->lst_token = init->lst_token->next;
	}
	my_wait_pid(exec_init);
	close(exec_init.pipetmp);
	init->lst_token = head;
}
