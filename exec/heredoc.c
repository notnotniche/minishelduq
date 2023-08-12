/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:54:28 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 14:55:53 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_heredoc(char *delimiteur, t_init *init)
{
    char    *filename;
    int        fd;
    char    *line;
	char	*stock_itoa_i;
	printf("%s\n", delimiteur);
	static int i = 1;

	filename = "/tmp/heredoc_tmp";
	stock_itoa_i = ft_itoa(i);
	filename = ft_strjoin(filename, stock_itoa_i);
	lstaddback_malloc(init, lstnew_malloc(filename));
	filename = ft_strjoin(filename, ".txt");
	lstaddback_malloc(init, lstnew_malloc(filename));
	printf("------filename %s -------\n\n", filename);
	i++;
	init->lst_token->delimeter->str_list2 = ft_strdup(filename);
	lstaddback_malloc(init, lstnew_malloc(init->lst_token->delimeter->str_list2));	
	printf("filename strdup %s \n", init->lst_token->delimeter->str_list2);
	free(stock_itoa_i);
    if (!filename)
        ft_print_fd("Malloc error\n", 2);
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC , 0777);
	if (fd == -1)
		return ((void)perror(filename));
	signal(SIGINT, handle_sigint);
    while (1)
    {
		line = readline("> ");
		if (line == NULL) //msg erreur --> prompt: warning: here-document at line n delimited by end-of-file (wanted `EOF')
			break;
        if (ft_strcmp(delimiteur, line) == 0)
        {
			close(fd);
			return ;
		}
        else
        {
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
        }
		free(line);
    }
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


