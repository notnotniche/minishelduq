/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:21:37 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/13 18:24:52 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **env_to_str(t_init *init, t_env_list *env_list, int size_env)
{
	t_env_list *head;
	char **result;
	int i;
	char *content;

	i = 0;
	head = env_list;
	result = malloc(sizeof(char *) * (size_env + 1));
	lstaddback_malloc(init, lstnew_malloc(result));
	while (head)
	{
		content = ft_strjoin(head->name, "=");
		lstaddback_malloc(init, lstnew_malloc(content));
		content = ft_strjoin(content, head->value);
		lstaddback_malloc(init, lstnew_malloc(content));
		result[i++] = content;
		head = head->next;
	}
	result[i] = NULL;
	return (result);
}

char **args_to_str(t_str_list *str, int size_str, t_init *init)
{
	t_str_list *head;
	char **result;
	int i;

	head = str;
	result = malloc(sizeof(char *) * (size_str + 1));
	lstaddback_malloc(init, lstnew_malloc(result));
	i = 0;
	while (head)
	{
		result[i] = head->str_list;
		i++;
		head = head->next;
	} 
	result[i] = NULL;
	return (result);
}

void printalltab(char **tarb, char *arg)
{
	int i;
	
	i = 0;
	printf("---%s----\n",arg);
	while (tarb[i])
	{
		printf("%d ----> %s\n",i, tarb[i]);
		i++;
	}
}

void exit_close(t_init *init, t_exec_init *exec_init , int move2ouf)
{
	(void)init;
	close(exec_init->mypipe[1]);
	close(exec_init->mypipe[0]);
	close(exec_init->pipetmp);
	exit(move2ouf);
}

void	command_manager(t_init *init, t_exec_init *exec_init, int i)
{
	char **all_args;
	char **env;
	char *path;
	
	(void)i;
	path = NULL;
	env = env_to_str(init, init->lst_env, ft_size_env(init->lst_env));
	// printalltab(env, "env");
	all_args = args_to_str(init->lst_token->arguments, ft_size_str(init->lst_token->arguments), init);
	// printalltab(all_args, "all_args");
	if (!is_command_builtin(all_args[0]))
	{
		path = path_maker(init, init->lst_token->arguments, get_env_value("PATH", init), exec_init);
		close(exec_init->mypipe[1]);
		close(exec_init->mypipe[0]);
		close(exec_init->pipetmp);
		execve(path, all_args, env);
	}
	else if (is_command_builtin(all_args[0]))
	{
		close(exec_init->mypipe[1]);
		close(exec_init->mypipe[0]);
		close(exec_init->pipetmp);
		builtin_manage(init, all_args[0], all_args);
		free_env_list(init->lst_env);
		free_s_init(init);
		exit(0);
	}
}