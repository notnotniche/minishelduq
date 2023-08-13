	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   export.c                                           :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2023/08/03 15:52:24 by nklingsh          #+#    #+#             */
	/*   Updated: 2023/08/11 18:45:08 by nklingsh         ###   ########.fr       */
	/*                                                                            */
	/* ************************************************************************** */

	#include "../minishell.h"

	int	size_double_tab(char **arguments)
	{
		int i;

		i = 0;
		while (arguments[i])
			i++;
		return (i);
	}

	int valid_first_letter(char *str, int i)
	{
		if(ft_isalpha(str[i]) == 0)
			return (0);
		else
			return (1);
	}

	int valid_only_str(char *str)
	{
		int i;

		i = 0;
		while (str[i])
		{
			i++;
		}
		return (1);
	}

	int valid_until_equal(char *str)
	{
		int i;
		int y;

		y = 0;
		i = 0;
		while (str[i] && str[i] != '=')
		{
			if (ft_isalnum(str[i]) == 0)
				return (0);
			i++;
		}
		return (1);
	}

	int valid_after_equal(char *str)
	{
		int i;

		i = 0;
		while (str[i] && str[i + 1] != '=')
			i++;
		while (str[i])
			i++;
		return (1);
	}

	int valid_export(char **arguments)
	{
		if (valid_first_letter(arguments[1], 0) == 0)
			return (0);
		if (valid_until_equal(arguments[1]) == 0)
			return (0);
		else if (valid_after_equal(arguments[1]) == 0)
			return (0);
		return (1);
	}

void change_env_value_export(char *name, char *new_value, t_init *init, int i) {
    t_env_list *tmp;

    tmp = init->lst_env;
    while (tmp) {
        if (ft_strsame(tmp->name, name)) {
            // Free the old value
            free(tmp->value);

            if (new_value) {
                tmp->value = ft_strdup(new_value);
				tmp->i = 0; 
            } else {
				if (i == VALID)
					tmp->i = VALID;
                tmp->value = NULL; 
            }
            return; 
        }
        tmp = tmp->next;
    }
    lstadd_back_env(&init->lst_env, lstnew_env(ft_strdup(name), new_value ? ft_strdup(new_value) : NULL));
}

	void export_to_linked_list(t_init *init, char **str)
	{
		if (str[1] == NULL)
			change_env_value_export(str[0], str[1], init, VALID);
		else
			change_env_value_export(str[0],str[1], init, 0);
	}

	char  **exportator(char *str)
	{
		char **splittos;

		splittos = ft_split(str, '=');
		return (splittos);
	}

	void the_real_export(char **arguments, t_init *init)
	{
		char **str;
		
		str = NULL;	
		if (size_double_tab(arguments) == 1)
		{
			print_lst_env(init->lst_env);
		}
		else if (size_double_tab(arguments) == 2)
		{
			if (valid_export(arguments) == 1)
			{
			str = exportator(arguments[1]);
			export_to_linked_list(init, str);
			free_tab_tab(str);
			}
		}
		else 
			printf("error too many arugments");
	}