/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:54:28 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 01:59:5 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_heredoc(char *delimiteur, t_init *init)
{
    char    *filename;
    int        fd;
    char    *line;
	//printf("%s\n", delimiteur);
	static int i = 1;

	filename = "/tmp/heredoc_tmp";
	filename = ft_strjoin(filename, ft_itoa(i));
	filename = ft_strjoin(filename, ".txt");
	// printf("------filename %s -------\n\n", filename);
	i++;
	init->lst_token->delimeter->str_list2 = ft_strdup(filename);
	if (!filename)
		ft_print_fd("Malloc error\n", 2);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		printf("\n ERROR OPENNING FILE HEREDOC\n");//remove
	// error?
	int retour = fork();

	if (retour == 0)
	{
		signal(SIGINT, heredoc_sigint);
		while (1)
		{
			line = readline("> ");
			if (line == NULL)
				break;
			if (ft_strcmp(delimiteur, line) == 0)
				break;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		if (line)
			free(line);
		if (filename)
			free(filename);
		close(fd);
		exit(0);
	}
	waitpid(retour, NULL, 0);
	close(fd);
	fd = open(filename, O_RDONLY);
	//char *str = malloc(1000);
	//read(fd, str, 100);
	//printf("\n STR = %s \n\n", str);
	unlink(filename);
	if (filename)
		free(filename);
}
