/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:52:24 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/06 19:30:24 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_list *copy_env_list(t_env_list *original)
{
	if (original == NULL)
		return (NULL);
	t_env_list *new_env_list;
	
	new_env_list = (t_env_list*)(malloc(sizeof(t_env_list)));
	if (!new_env_list)
		exit(EXIT_FAILURE);
	new_env_list->name = ft_strdup(original->name);
	new_env_list->value=ft_strdup(original->value);
	new_env_list->next = copy_env_list(original->next);
	return (new_env_list);
}

void free_env_list(t_env_list* list)
{
    while (list != NULL) {
        t_env_list* temp = list;
        list = list->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

char *add_to_str(char *str, char c)
{
	int i;
	char *new_str;
	
	new_str = malloc(sizeof(char) * ft_strlen(str) + 2);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	i++;
	new_str[i] = '\0';
	return (new_str);
}

int quote_then_alnum(char *str, int i)
{
	if (str[i] == '=')
		i++;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			i++;
		else
			return(0);
	}
	return (1);
}

int	size_double_tab(char **arguments)
{
	int i;

	i = 0;
	while (arguments[i])
		i++;
	return (i);
}

void initalize_export(t_export_list *export_list, char **new_str)
{
	new_str = NULL;
	export_list->value = 0;
	export_list->name = 0;	
}

t_export_list check_if_export_possible(char **arguments)
{
	int i;
	char *new_str;
	t_export_list export_list;

	i = 0;
	initalize_export(&export_list, &new_str);
	while(ft_isalnum(arguments[1][i]))
	{
		new_str = add_to_str(new_str, arguments[1][i]);
		i++;
	}
	if (arguments[1][i] == '\0')
	{
		export_list.name=new_str;
		printf("--\n--\n--");
		return export_list;
	}
	free(new_str);
	new_str = NULL;
	if (quote_then_alnum(arguments[1], i))
	{
		i++;
		while(ft_isalnum(arguments[1][i]))
		{
			new_str = add_to_str(new_str, arguments[1][i]);
			i++;
		}
	}
	if (arguments[1][i] == '\0')
		export_list.value=new_str;
	return export_list;
}

void the_real_export(char **arguments, t_init *init)
{
	t_export_list export_list;

	if (size_double_tab(arguments) == 1)
		print_lst_env(init->lst_env);
	else
	{
		export_list = check_if_export_possible(arguments);
		lstadd_back_env(&init->lst_env, lstnew_env(export_list.name, export_list.value));
	}
	print_lst_env(init->lst_env);
}