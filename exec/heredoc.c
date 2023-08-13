/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:54:28 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/13 20:59:17 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
 
void ft_heredoc(char *delimiteur, t_init *init)
{
    char    *filename;
    char    *line;
	int fd;
	char	*stock_itoa_i;
	static int i = 1;
	int		oui;

	printf("HEREDOC\n");
	filename = "/tmp/heredoc_tmp";
	stock_itoa_i = ft_itoa(i);
	filename = ft_strjoin(filename, stock_itoa_i);
	lstaddback_malloc(init, lstnew_malloc(filename));
	filename = ft_strjoin(filename, ".txt");
	lstaddback_malloc(init, lstnew_malloc(filename));
	i++;
	init->lst_token->delimeter->str_list2 = ft_strdup(filename);
	lstaddback_malloc(init, lstnew_malloc(init->lst_token->delimeter->str_list2));	
	free(stock_itoa_i);
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC , 0777);
	oui = dup(0);
	if (!filename)
        ft_print_fd("Malloc error\n", 2);
    signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (line == NULL) //ctrl d
		{
			//free_env_list(init->lst_env); // mettre les free
			break;
		}
		if (ft_strcmp(delimiteur, line) == 0)
			break;
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
	}
	dup2(oui, 0);
	close(oui);
	free(line);
}

void  while_here_doc_exist(t_init *init)
{
	t_token_list *token;
	t_str_list *head;
	token = init->lst_token;
	while(init->lst_token)
	{
		head = init->lst_token->delimeter;
		while (init->lst_token->delimeter)
		{
			ft_heredoc(init->lst_token->delimeter->str_list, init);
			init->lst_token->delimeter = init->lst_token->delimeter->next;
		}
		init->lst_token->delimeter = head;
		init->lst_token = init->lst_token->next;
	}
	init->lst_token = token;
	print_all_token(init->lst_token);
}

void	heredoc_supp(t_token_list *token_lst)
{
	while (token_lst)
	{
		while(token_lst->delimeter)
		{
			unlink(token_lst->delimeter->str_list2);
			token_lst->delimeter = token_lst->delimeter->next;
		}
		token_lst = token_lst->next;
	}
}
