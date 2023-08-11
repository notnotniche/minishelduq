/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:01:37 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/11 19:01:55 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++))
        ;
    return dest;
}

char *ft_strcat(char *dest, const char *src) {
    char *d = dest;
    while (*d)
        d++;
    while ((*d++ = *src++))
        ;
    return dest;
}





