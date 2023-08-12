/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_piscine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:34:46 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/12 16:42:44 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_charset(char c, char *charset)
{
    int    j;

    j = 0;
    while (charset[j] != '\0')
    {
        if (c == charset[j])
            return (1);
        j++;
    }
    return (0);
}

char    *make_a_malloc(char *str, char *charset)
{
    char    *tempstr;
    int        i;

    i = 0;
    while (str[i] && is_charset(str[i], charset) == 0)
        i++;
    tempstr = malloc(sizeof(*tempstr) * (i + 1));
    if (tempstr == NULL)
        return (NULL);
    i = 0;
    while (str[i] && is_charset(str[i], charset) == 0)
    {
        tempstr[i] = str[i];
        i++;
    }
    tempstr[i] = '\0';
    return (tempstr);
}

int    ft_nb_words(char *str, char *charset)
{
    int    count;
    int    i;

    count = 0;
    i = -1;
    while (str[++i])
    {
        if (str[i] && (!is_charset(str[i], charset)
                && (i == 0 || is_charset(str[i - 1], charset))))
            count++;
    }
    return (count);
}

char    **ft_split_piscine(char *str, char *charset)
{
    int        i;
    int        k;
    char    **res;

    i = 0;
    k = 0;
    res = malloc (sizeof(*res) * (ft_nb_words(str, charset) + 1));
    if (res == NULL)
        return (NULL);
    while (str[i])
    {
        while (str[i] && is_charset(str[i], charset) == 1)
            i++;
        if (str[i] && k < ft_nb_words(str, charset)
            && (!is_charset(str[i], charset)
                && (i == 0 || is_charset(str[i - 1], charset))))
        {
            res[k] = make_a_malloc(&str[i], charset);
            k++;
        }
        i++;
    }
    res[k] = 0;
    return (res);
}