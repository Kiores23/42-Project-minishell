/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:07:27 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:34:50 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	parent(t_exe *e, int i)
{
	if (i > 0 && e->pipe_fd[i - 1][1] > 2)
		close(e->pipe_fd[i - 1][1]);
	if (i > 1 && e->pipe_fd[i - 2][0] > 2)
		close(e->pipe_fd[i - 2][0]);
}

int	init_heredoc(t_stack *s, t_exe *e, t_env *env)
{
	t_file	*start_in;
	int		i;

	if (create_pipe_for_heredoc(s, e))
		return (1);
	i = -1;
	while (s && ++i >= 0 && !g_rerror[1])
	{
		start_in = s->in;
		while (s->in && !g_rerror[1])
		{
			if (process_heredoc(s, e, i, env))
				return (1);
			if (g_rerror[1])
			{
				free_paths(e->paths);
				free_paths(e->envp);
			}
		}
		s->in = start_in;
		s = s->next;
	}
	return (0);
}

void	child(t_stack *s, t_exe *e, t_env *env, int i)
{
	e->env = env;
	e->in_fd = -1;
	e->out_fd = -1;
	redir(s, e, i);
	dup_in(s, e, i);
	dup_out(s, e, i);
	final_execution(s, e, env, i);
	execve(e->paths[i], s->cmd_final, e->envp);
	child_exit(NULL, NULL, strerror(errno), 126);
}

int	pipe_and_process(t_stack *s, t_exe *e, t_env *env, int i)
{
	if (!s->cmd_final[0] && !s->in && !s->out)
	{
		parent(e, i);
		return (0);
	}
	if (!s->next)
		e->pipe_fd[i][1] = 0;
	else if (pipe(e->pipe_fd[i]) == -1)
		return (return_error("pipe", NULL, strerror(errno), 1));
	e->fork_id[i] = fork();
	if (e->fork_id[i] == -1)
		return (return_error("fork", NULL, strerror(errno), 1));
	if (e->fork_id[i] == 0)
		child(s, e, env, i);
	parent(e, i);
	return (0);
}

int	execution(t_stack *s, t_env *lst_env)
{
	t_exe	e;
	int		i;
	int		y;

	if (!s->cmd_final[0] && !s->in && !s->out)
		return (0);
	e.envp = get_tab_env(lst_env);
	e.paths = all_paths(s, &e);
	if (!e.paths || init_heredoc(s, &e, lst_env) || g_rerror[1])
		return (1);
	i = -1;
	while (s && ++i >= 0)
	{
		if (pipe_and_process(s, &e, lst_env, i))
			return (1);
		s = s->next;
	}
	if (i > 0 && e.pipe_fd[i - 1][0] > 2)
		close(e.pipe_fd[i - 1][0]);
	y = -1;
	while (++y <= i)
		waitpid(e.fork_id[y], &g_rerror[0], 0);
	free_paths(e.paths);
	free_paths(e.envp);
	return (0);
}
