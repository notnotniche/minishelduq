/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:18:29 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 19:20:21 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote_ends(char *str)
{
	int		i;
	t_quote	quote;

	quote.quote_bool = 0;
	quote.quote = 0;
	i = 0;
	while (str[i])
	{
		if ((is_quote(str[i]) && quote.quote_bool == 0))
		{
			quote.quote = str[i];
			quote.quote_bool++;
		}
		else if (str[i] == quote.quote && quote.quote_bool == 1)
		{
			quote.quote_bool = 0;
			quote.quote = 0;
		}
		i++;
	}
	if (quote.quote_bool != 0)
		return (ft_print_fd("Subject syntax error", 2), 1);
	return (0);
}
