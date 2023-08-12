/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:00:25 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 23:35:18 by nklingsh         ###   ########.fr       */
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
	if (check_error(init) == 1)
		return (free_s_init(init),1);
	expander_expanding(init);
	init->lst_token = get_all_token(init);
	head = init->lst_token;
	return (0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_init init;

	if (!ttyname(1) || !ttyname(0))
		return(0);
	init.lst_env = init_env_list(env);
	sh_lvl_manager(&init);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while(1)
		{
			init.read_line = readline("minishell :");
			if (init.read_line == NULL) //ctrl d
			{
				free_env_list(init.lst_env);
				break;
			}
			if (is_only_isspace(init.read_line) == 1 || ft_strlen(init.read_line) == 0)
				;
			else
			{
				add_history(init.read_line);
				if (parsing(&init, init.read_line) == 0)
				{	
					real_exec(&init);
					free_s_init(&init);
					if (!init.read_line)
						free(init.read_line);
				}
		}
	}
	if (init.read_line)
		free(init.read_line);
	printf("\n");
}