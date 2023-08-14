/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:00:25 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 20:04:50 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status_exit_code = 0;

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
	t_token_list	*head;

	init->lst_mal = NULL;
	lstaddback_malloc(init, lstnew_malloc(read_line));
	init->lst_lex = lexer_lexing(read_line, init);
	if (check_error(init) == 1)
		return (free_s_init(init), 1);
	expander_expanding(init);
	init->lst_token = get_all_token(init);
	head = init->lst_token;
	return (0);
}

void	init_main(t_init *init, char **env)
{
	if (!ttyname(1) || !ttyname(0))
		exit(0);
	init->lst_env = init_env_list(env);
	sh_lvl_manager(init);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	process_input(t_init *init)
{
	add_history(init->read_line);
	if (parsing(init, init->read_line) == 0)
	{
		real_exec(init);
		free_s_init(init);
		if (!init->read_line)
			free(init->read_line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_init	init;

	(void)argv;
	(void)argc;
	init_main(&init, env);
	while (1)
	{
		init.read_line = readline("minishell :");
		init.here_doc_tinker = 0;
		if (!init.read_line)
		{
			free_env_list(init.lst_env);
			break ;
		}
		if (is_only_isspace(init.read_line) == 1
			|| ft_strlen(init.read_line) == 0)
			continue ;
		process_input(&init);
	}
	if (init.read_line)
		free(init.read_line);
	return (0);
}
