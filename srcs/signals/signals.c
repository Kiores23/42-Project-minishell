/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:14:34 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 15:23:43 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	receive_signal(void)
{
	t_termios	term;

	signal(SIGINT, sign_newline);
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag |= ICANON;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}

int	receive_signal_2(void)
{
	signal(SIGINT, sign_shield);
	signal(SIGQUIT, sign_kill);
	return (0);
}

int	receive_signal_3(void)
{
	signal(SIGINT, sign_ignore);
	signal(SIGQUIT, sign_ignore);
	return (0);
}

int	receive_signal_4(void)
{
	t_termios	term;

	signal(SIGINT, SIG_DFL);
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag |= ICANON;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}

void	choice_signal(t_stack *s)
{
	char	*str;
	char	*start;

	if (s->next || !s->cmd_final[0])
	{
		receive_signal_2();
		return ;
	}
	str = ft_strdup(s->cmd_final[0]);
	start = str;
	while (ft_strchr(str, '/'))
	{
		str = ft_strchr(str, '/') + 1;
	}
	if (!ft_strcmp(str, "minishell"))
		receive_signal_3();
	else
		receive_signal_2();
	free(start);
}
