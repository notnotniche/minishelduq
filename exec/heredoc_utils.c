/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:14:56 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 17:43:59 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_name(char *delimiteur, t_init *init)
{
	char		*filename;
	static int	i = 1;
	char		*stock_itoa;

	printf("HEREDOC\n");
	filename = "/tmp/heredoc_tmp";
	stock_itoa = ft_itoa(i);
	filename = ft_strjoin(filename, stock_itoa);
	lstaddback_malloc(init, lstnew_malloc(filename));
	filename = ft_strjoin(filename, ".txt");
	lstaddback_malloc(init, lstnew_malloc(filename));
	i++;
	delimiteur = ft_strdup(filename);
	lstaddback_malloc(init, lstnew_malloc(delimiteur));
	init->lst_token->delimeter->str_list2 = delimiteur;
	free(stock_itoa);
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (filename);
}

void	closer_totally_spies(int fd, int oui, char *line)
{
	close(fd);
	dup2(oui, 0);
	close(oui);
	free(line);
}

void	closer_the_magasine(int fd, char *filename, int oui, t_init *init)
{
	(void)fd;
	printf("warning: here-document delimited by end-of-file\n");
	close(oui);
	unlink(filename);
	init->here_doc_tinker = 1;
}

void	the_writer(int fd, char *str, int size_str)
{
	write(fd, str, size_str);
	write(fd, "\n", 1);
}
