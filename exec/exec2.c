/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:04:43 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/14 17:21:12 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	size_str_list(t_str_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	only_here_doc(t_token_list *token_list)
{
	if (size_str_list(token_list->arguments) == 0)
	{
		if (size_str_list(token_list->in_file) == 0)
		{
			if (size_str_list(token_list->out_file) == 0)
			{
				if (size_str_list(token_list->delimeter) != 0)
					return (1);
			}
		}
	}
	return (0);
}

void	real_exec(t_init *init)
{
	t_str_list		*del;
	char			**all_args;

	all_args = args_to_str(init->lst_token->arguments, \
		ft_size_str(init->lst_token->arguments), init);
	del = init->lst_token->delimeter;
	print_all_token(init->lst_token);
	if (here_doc_exist(init) >= 1)
		while_here_doc_exist(init);
	if (init->here_doc_tinker == 0)
	{
		if (only_here_doc(init->lst_token) == 0)
		{
			if (ft_size_token(init->lst_token) == 1 && \
				fork_builtin(init->lst_token->arguments->str_list) == 1)
				builtin_manage(init, all_args[0], all_args);
			else
				exec(init);
		}
		else
			free_s_init(init);
	}
	else
		free_s_init(init);
}
