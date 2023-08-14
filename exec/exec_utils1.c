/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:11:45 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 20:14:34 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_execution(t_init *init, int *i, t_exec_init *exec_init)
{
	if (pipe(exec_init->mypipe) == -1)
		free_s_init(init);
	exec_init->realpid = fork();
	if (exec_init->realpid < 0)
		free_s_init(init);
	else if (exec_init->realpid == 0)
		exec_child_process(init, *i, *exec_init);
	else
		exec_parent_process(exec_init);
	(*i)++;
	init->lst_token = init->lst_token->next;
}

void	exec(t_init *init)
{
	int				i;
	t_exec_init		exec_init;

	initialize_exec(init, &i, &exec_init);
	while (i < exec_init.nb_command)
		handle_execution(init, &i, &exec_init);
	my_wait_pid(exec_init);
	if (g_status_exit_code == 130)
		printf("\n");
	else if (g_status_exit_code == 131)
		printf("Quit (core dumped)\n");
	close(exec_init.pipetmp);
	heredoc_supp(init->lst_token);
}
