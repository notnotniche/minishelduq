/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 00:58:33 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 02:30:02 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void sh_lvl_manager(t_init *init)
{
	int	sh_lvl;
	char *free_itoa;
	
	sh_lvl = ft_atoi(get_env_value("SHLVL", init));
	sh_lvl++;
	if (sh_lvl > 1000)
	{
		printf("warning: shell level (1000) too high, resetting to 1");
		sh_lvl = 1;
	}
	free_itoa = ft_itoa(sh_lvl);
	change_env_value("SHLVL", free_itoa, init);
	free(free_itoa);
}