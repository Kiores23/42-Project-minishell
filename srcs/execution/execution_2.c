/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:12:39 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 17:42:58 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	child_exit(char *cmd, char *f_name, char *msg, int r)
{
	if (r)
		ft_putstr_fd("\e[1;31m"MN_SHELL": ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (f_name)
	{
		ft_putstr_fd(f_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\e[0m\n", 2);
	exit(r);
}

void	dup_in(t_stack *s, t_exe *e, int i)
{
	if (e->in_fd != -1)
	{
		if (s->prec)
			close(e->pipe_fd[i - 1][0]);
		if (s->cmd_final[0] && dup2(e->in_fd, 0) == -1)
			child_exit("dup2", NULL, strerror(errno), 1);
	}
	else if (s->prec)
	{
		if (dup2(e->pipe_fd[i - 1][0], 0) == -1)
			child_exit("dup2", NULL, strerror(errno), 1);
		close(e->pipe_fd[i - 1][1]);
	}
}

void	dup_out(t_stack *s, t_exe *e, int i)
{
	if (e->out_fd != -1)
	{
		if (s->next)
			close(e->pipe_fd[i][1]);
		if (dup2(e->out_fd, 1) == -1)
			child_exit("dup2", NULL, strerror(errno), 1);
	}
	else if (s->next)
	{
		if (dup2(e->pipe_fd[i][1], 1) == -1)
			child_exit("dup2", NULL, strerror(errno), 1);
		close(e->pipe_fd[i][0]);
	}
}

int	create_pipe_for_heredoc(t_stack *s, t_exe *e)
{
	t_file	*start_in;
	int		i;

	i = -1;
	while (s && ++i >= 0)
	{
		start_in = s->in;
		while (s->in)
		{
			if (s->in->doubles && !s->in->next && pipe(e->heredoc_fd[i]) == -1)
			{
				g_rerror[0] = 1;
				free_paths(e->paths);
				free_paths(e->envp);
				child_exit(NULL, NULL, strerror(errno), 1);
			}
			s->in = s->in->next;
		}
		s->in = start_in;
		s = s->next;
	}
	return (0);
}

int	process_heredoc(t_stack *s, t_exe *e, int i, t_env *env)
{
	int	f_id;

	f_id = fork();
	if (f_id == -1)
	{
		g_rerror[0] = 1;
		free_paths(e->paths);
		free_paths(e->envp);
		return (return_error("fork", NULL, strerror(errno), 1));
	}
	if (f_id == 0)
	{
		if (s->in->doubles && s->in->next)
			free(create_heredoc(s->in->doubles, env));
		if (s->in->doubles && !s->in->next)
			pipe_heredoc(create_heredoc(s->in->doubles, env), e->heredoc_fd[i]);
		exit(0);
	}
	if (s->in->doubles && !s->in->next)
		close(e->heredoc_fd[i][1]);
	waitpid(f_id, &g_rerror[2], 0);
	s->in = s->in->next;
	return (0);
}
