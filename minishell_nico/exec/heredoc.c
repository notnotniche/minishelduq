/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:54:28 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/10 17:41:21 by nklingsh         ###   ########.fr       */
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
    if (!filename)
        ft_print_fd("Malloc error\n", 2);
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC , 0777);
    //if (fd == -1)
    //error?

    while (1)
    {
        line = readline("> ");
        if (ft_strcmp(delimiteur, line) == 0)
            return ;
        else
        {
            write(fd, line, ft_strlen(line));
            write(fd, "\n", 1);
        }
    }
    close (fd);
    fd = open(filename, O_RDONLY);
    unlink(filename);
    if (filename)
        free(filename);
    if (line)
        free(line);
}


