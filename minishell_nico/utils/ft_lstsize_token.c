/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:48:48 by nklingsh          #+#    #+#             */
/*   Updated: 2023/07/31 20:08:45 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_size_token(t_token_list *head)
{
	if (head == NULL)
		return (0);
	else
		return (1 + ft_size_token(head->next));
}

int ft_size_env(t_env_list *head)
{
	if (head == NULL)
		return (0);
	else
		return (1 + ft_size_env(head->next));
}

int ft_size_str(t_str_list *head)
{
	if (head == NULL)
		return (0);
	else
		return (1 + ft_size_str(head->next));
}