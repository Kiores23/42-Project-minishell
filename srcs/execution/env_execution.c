/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:41:39 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 17:34:05 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	i_redir(t_stack *s, t_env **env, int cmd)
{
	static t_exe	e;

	if (cmd == 0)
	{
		e.paths = NULL;
		e.envp = NULL;
		e.in_fd = -1;
		e.out_fd = -1;
		g_rerror[1] = env_redir(s, *env, &e);
		if (g_rerror[1])
			return (0);
	}
	else if (cmd == 1)
	{
		if (e.in_fd > 2)
			close(e.in_fd);
		if (e.out_fd > 2)
			close(e.out_fd);
		if (g_rerror[1])
			g_rerror[0] = g_rerror[1] * 256;
		g_rerror[1] = 0;
	}
	return (1);
}

void	std_save(int i)
{
	static int	std_in = 0;
	static int	std_out = 1;

	if (i == 0)
	{
		std_in = dup(0);
		std_out = dup(1);
	}
	else if (i == 1)
	{
		if (dup2(std_in, 0) == -1)
			g_rerror[1] = 1;
		else if (dup2(std_out, 1) == -1)
			g_rerror[1] = 1;
	}
	else if (i == 2)
	{
		close(std_in);
		close(std_out);
	}
}

int	env_execution(t_stack *s, t_env **env, char *line)
{
	if (s->next || !s->cmd_final[0])
		return (0);
	if (!ft_strcmp(to_down(s->cmd_final[0]), "unset") && i_redir(s, env, 0))
		g_rerror[0] = unset_env_var(env, s->cmd_final);
	else if (!ft_strcmp(to_down(s->cmd_final[0]), "export")
		&& i_redir(s, env, 0))
	{
		if (s->cmd_final[1] && !export_env(env, s->cmd_final))
			g_rerror[0] = g_rerror[1];
		else if (!s->cmd_final[1])
			g_rerror[0] = print_export(env);
		g_rerror[1] = 0;
	}
	else if (!ft_strcmp(to_down(s->cmd_final[0]), "cd") && i_redir(s, env, 0))
		g_rerror[0] = changedirectory(s->cmd_final, *env);
	else if (!ft_strcmp(to_down(s->cmd_final[0]), "exit")
		&& i_redir(s, env, 0))
		g_rerror[0] = ft_exit(s->cmd_final, s, *env, line);
	else if (g_rerror[1] && i_redir(s, env, 1))
		return (1);
	else if (i_redir(s, env, 1))
		return (0);
	g_rerror[0] *= 256;
	return (1);
}
