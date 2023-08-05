/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:56:36 by nklingsh          #+#    #+#             */
/*   Updated: 2023/05/30 15:27:48 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void routine_start(int signum)
{
	if (signum == SIGTERM) {
        printf("\nReceived SIGTERM. Exiting...\n");
        exit(EXIT_SUCCESS);
    }
}