/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:00:25 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 22:40:36 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status_exit_code = 0;

void	sig_process(int sig_num)
{
	if (sig_num == SIGQUIT)
		g_status_exit_code = 131;
	else if (sig_num == SIGINT)
	{
		g_status_exit_code = 130;
	}
}

int	parsing(t_init *init, char *read_line)
{
	t_token_list *head;
	init->lst_mal = NULL;
	lstaddback_malloc(init, lstnew_malloc(read_line));
	init->lst_lex = lexer_lexing(read_line, init);
	// if (check_error(init->lst_lex))
		// return (printf("\nfais ta fonction free connard \n\n\n"), 0);
	expander_expanding(init);
	// print_lst_env(init->lst_env);
	init->lst_token = get_all_token(init);
	head = init->lst_token;
	//print_all_token(init->lst_token);
	
	return (0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_init init;

	init.lst_env = init_env_list(env);
	//signal(SIGINT, routine_start);
	signal(SIGINT, handle_sigint);
	if (signal(SIGQUIT, SIG_IGN) != SIG_ERR)
		g_status_exit_code = 131;
	while(1)
		{
			init.read_line = readline("minishell :");
			if (init.read_line == NULL) //ctrl d
			{
				free_env_list(init.lst_env);
				free_s_init(&init);
				break;
			}
			add_history(init.read_line);
			if (ft_strlen(init.read_line) == 0)
				;
			else
			{
			parsing(&init, init.read_line);
			if (ft_strcmp(init.read_line, "exit") == 0)
				return (free(init.read_line), 0);
			real_exec(&init);
			if (!init.read_line)
				free(init.read_line);
			}
		}
	if (init.read_line)
		free(init.read_line);
	return (printf("finito bizarre"), 0);
}