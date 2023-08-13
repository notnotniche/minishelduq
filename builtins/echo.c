// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   echo.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/18 16:54:51 by nklingsh          #+#    #+#             */
// /*   Updated: 2023/07/20 15:09:42 by nklingsh         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../minishell.h"

char *ft_strjoin_space(char *s1, char *s2, t_init *init)
{
    char *result;

	if (!s1)
        return (s2);
    result = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	lstaddback_malloc(init, lstnew_malloc(result)); // +2 for the added space and null terminator
    ft_strcpy(result, s1);
    ft_strcat(result, " ");
    ft_strcat(result, s2);
    return (result);
}

int     ft_scmp(const char *s1, const char *s2)
{
        size_t  i;
        i = 0;
        while (s1[i] && s2[i] && s1[i] == s2[i])
                i++;
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int    echo_n_option(char **line, int i)
{
    int    j;

    j = 0;
	if (size_double_tab(line) == 0)
		return (1);
    if (line[i][j] == '-' && line[i][j + 1] == 'n')
    {
        j += 1;
        while (line[i][j] == 'n')
            j ++;
        if (line[i][j] == '\0')
            return (0);
    }
    return (1);
}

void    text_to_print(char    **line, t_init *init)
{
    int    i;
    int    n;
    char    *res;
	char 	*tmp;

    i = 0;
    n = 0;
    res = NULL;
	tmp = NULL;
    while (line[i])
        i++;
    i = 0;
    while (ft_scmp(line[i], "echo") != 0)
        i++;
    if (ft_scmp(line[i], "echo") == 0)
         i++;
	if (size_double_tab(line) == 1)
	{
		printf("\n");
		return ;
	}
    while (echo_n_option(line, i) == 0)
    {
        i++;
        n++;
    }
    while (line[i] && (ft_scmp(line[i], "|") != 0 && ft_scmp(line[i], "<") != 0
            && ft_scmp(line[i], ">") != 0 && ft_scmp(line[i], "<<") != 0
            && ft_scmp(line[i], ">>") != 0))
    {
        res = ft_strjoin_space(res, line[i], init);
        i++;
    }
	if (n == 0) {
		printf("%s\n", res);
		return;
	} else {
		printf("%s", res);
		return;
	}
}