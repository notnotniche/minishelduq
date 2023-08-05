/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_str_in_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:31:37 by nklingsh          #+#    #+#             */
/*   Updated: 2023/07/24 19:38:47 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_str_in_init(t_init *init, char c, 	char *src)
{
	char *res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(src) + 2));
	if (!res)
		printf("error mess");
	lstaddback_malloc(init, lstnew_malloc(res));
	while (src[i])
	{
		res[i] = src[i];
		i++;
	}
	res[i++] = c;
	res[i] = 0;
	return (res);
}