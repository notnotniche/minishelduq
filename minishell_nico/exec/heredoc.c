/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:54:28 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 03:33:03 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_heredoc(char *delimiteur, t_init *init)
{
    char    *filename;
    int        fd;
    char    *line;
	printf("%s\n", delimiteur);
	static int i = 1;

	filename = "/tmp/heredoc_tmp";
	filename = ft_strjoin(filename, ft_itoa(i));
	filename = ft_strjoin(filename, ".txt");
	printf("------filename %s -------\n\n", filename);
	i++;
	init->lst_token->delimeter->str_list2 = ft_strdup(filename);
	printf("filename strdup %s \n", init->lst_token->delimeter->str_list2);
    if (!filename)
        ft_print_fd("Malloc error\n", 2);
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC , 0777);
    //if (fd == -1)
    //error?
	signal(SIGINT, handle_sigint);
    while (1)
    {
        line = readline("> ");
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
    }
}


