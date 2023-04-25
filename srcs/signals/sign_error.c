/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:24:13 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 17:25:07 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	*init_tab(void)
{
	g_rerror[0] = 0;
	g_rerror[1] = 0;
	g_rerror[2] = 0;
	return (g_rerror);
}

void	sign_error(void)
{
	if (g_rerror[0] == 10)
	{
		ft_putstr_fd("\e[1;31mBus error: 10\e[0m\n", 2);
		g_rerror[0] = 138 * 256;
	}
	if (g_rerror[0] == 11)
	{
		ft_putstr_fd("\e[1;31mSegmentation fault: 11\e[0m\n", 2);
		g_rerror[0] = 139 * 256;
	}
}
