/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megafree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:49:24 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 13:44:11 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_s_init(t_init *init)
{
    t_malloc *copy;
    
    while (init->lst_mal)
    {
        copy = init->lst_mal->next;
        if (init->lst_mal->adr)
            free(init->lst_mal->adr);
        free(init->lst_mal);
        init->lst_mal = copy;
    }
}