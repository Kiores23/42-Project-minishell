/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_execution_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:08:17 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 13:52:47 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	dup_in_env(t_stack *s, t_exe *e, int i)
{
	if (e->in_fd != -1)
	{
		if (s->prec)
			close(e->pipe_fd[i - 1][0]);
		if (dup2(e->in_fd, 0) == -1)
			return (return_error("dup2", NULL, strerror(errno), 1));
	}
	else if (s->prec)
	{
		if (dup2(e->pipe_fd[i - 1][0], 0) == -1)
			return (return_error("dup2", NULL, strerror(errno), 1));
		close(e->pipe_fd[i - 1][1]);
	}
	return (0);
}

int	dup_out_env(t_stack *s, t_exe *e, int i)
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
	return (0);
}

int	infile_env(t_stack *s, t_exe *e, int i_heredoc, int *place)
{
	while (s->in && *place == s->in->order && (*place)++)
	{
		if (s->in->doubles)
		{
			e->in_fd = e->heredoc_fd[i_heredoc][0];
			if (e->in_fd == -1)
				return (return_error("open", s->in->doubles, strerror(errno),
						1));
		}
		else if (s->in->simple)
		{
			e->in_fd = open(s->in->simple, O_RDONLY, 0644);
			if (e->in_fd == -1)
				return (return_error("open", s->in->simple, strerror(errno),
						1));
			if (s->in->next)
				close(e->in_fd);
		}
		s->in = s->in->next;
	}
	return (0);
}

int	outfile_env(t_stack *s, t_exe *e)
{
	if (s->out->simple)
	{
		e->out_fd = open(s->out->simple, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (e->out_fd == -1)
			return (return_error("open", s->out->simple, strerror(errno), 1));
	}
	else if (s->out->doubles)
	{
		e->out_fd = open(s->out->doubles, O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (e->out_fd == -1)
			return (return_error("open", s->out->doubles, strerror(errno), 1));
	}
	if (s->out->next)
		close(e->out_fd);
	s->out = s->out->next;
	return (0);
}

int	env_redir(t_stack *s, t_env *lst_env, t_exe *e)
{
	int		place;
	t_file	*start_in;
	t_file	*start_out;

	if (init_heredoc(s, e, lst_env) || g_rerror[1])
		return (1);
	place = 1;
	start_in = s->in;
	start_out = s->out;
	while (s->in || s->out)
	{
		if (s->in && infile_env(s, e, 0, &place))
			return (1);
		if (s->out && outfile_env(s, e))
			return (1);
		place++;
	}
	s->in = start_in;
	s->out = start_out;
	if (dup_in_env(s, e, 0))
		return (1);
	if (dup_out_env(s, e, 0))
		return (1);
	return (0);
}
