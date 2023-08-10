/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:31:30 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/10 17:26:49 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int    ft_nbrlen(long int nb)
{
    int    len;

    len = 1;
    if (nb < 0)
    {
        nb *= -1;
        len++;
    }
    while (nb >= 10)
    {
        nb /= 10;
        len++;
    }
    return (len);
}

void    *ft_memset(void *s, int c, size_t n)
{
    long unsigned int    i;
    char                *buffer;

    i = 0;
    buffer = (char *)s;
    while (i != n)
    {
        buffer[i] = c;
        i++;
    }
    return (s);
}

void    ft_bzero(void *s, size_t n)
{
    ft_memset(s, '\0', n);
}

void    *ft_calloc(size_t nmemb, size_t size)
{
    int    *mem;

    mem = malloc(nmemb * size);
        if (!mem)
          return(NULL);
    ft_bzero(mem, nmemb * size);
    return (mem);
}

char    *ft_itoa(int nb)
{
    char    *str;
    int        len;
    long    nbr;

    nbr = (long int) nb;
    len = ft_nbrlen(nbr);
    str = (char *) ft_calloc(sizeof(char), len + 1);
    if (!str)
        return (NULL);
    str[len] = '\0';
    if (nbr < 0)
    {
        nbr *= -1;
        str[0] = '-';
    }
    while (--len >= 0 && !str[len])
    {
        str[len] = (nbr % 10) + '0';
        nbr /= 10;
    }
    return (str);
}