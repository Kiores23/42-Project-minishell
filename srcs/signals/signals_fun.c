/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:17:42 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 15:39:15 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	sign_newline(int n)
{
	(void)n;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_rerror[0] = 256;
}

void	sign_shield(int n)
{
	(void)n;
	ft_putstr_fd("\n", 1);
	g_rerror[1] = 130 * 256;
}

void	sign_ignore(int n)
{
	(void)n;
}

void	sign_kill(int n)
{
	(void)n;
	ft_putstr_fd("Quit : 3\n", 1);
	g_rerror[1] = 131 * 256;
}
