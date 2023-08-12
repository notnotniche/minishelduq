/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:12:21 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 22:36:34 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_out_manager(t_token_list *token_list)
{
	int	fd;
	char *file;

	file = lstlast_str(token_list->out_file)->str_list;
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (token_list->arguments != NULL)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	app_out_manager(t_token_list *token_list)
{
	int	fd;
	char *file;

	file = lstlast_str(token_list->out_file)->str_list;
	//printf("\n append file ---->%s",file);
	fd = open(file, O_APPEND | O_RDWR | O_CREAT, 0666);
	if (token_list->arguments != NULL)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_in_manager(t_token_list *token_list)
{
	int	fd;
	char *file;

	file = lstlast_str(token_list->in_file)->str_list;
	fd = open(file, O_RDONLY);
	if (token_list->arguments != NULL)
		dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_here_doc(t_token_list *token_list)
{
	int	fd;
	t_str_list	*del;

	del = lstlast_str(token_list->delimeter);
	fd = open(del->str_list2, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}