/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:33:55 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 11:44:09 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	pipe_heredoc(char *fullstr, int fd[2])
{
	close(fd[0]);
	ft_putstr_fd(fullstr, fd[1]);
	fullstr = free_ptr(fullstr);
	close(fd[1]);
}

char	*create_heredoc(char *stop, t_env *env)
{
	t_termios	o_term;
	char		*fullstr;
	char		*str;

	fullstr = ft_strdup("");
	str = NULL;
	tcgetattr(STDIN_FILENO, &o_term);
	while (1)
	{
		str = free_ptr(str);
		receive_signal_4();
		str = readline("> ");
		tcsetattr(STDIN_FILENO, TCSANOW, &o_term);
		if (!str || str[0] == 127 || !ft_strcmp(str, stop))
			break ;
		str = ft_strjoin(str, "\n");
		fullstr = ft_strjoin(fullstr, str);
	}
	receive_signal_2();
	str = free_ptr(str);
	fullstr = replace_env_variables_heardoc(fullstr, &env);
	if (!fullstr)
		fullstr = ft_strdup("");
	return (fullstr);
}

void	infile(t_stack *s, t_exe *e, int i_heredoc, int *place)
{
	while (s->in && *place == s->in->order && (*place)++)
	{
		if (s->in->doubles)
		{
			e->in_fd = e->heredoc_fd[i_heredoc][0];
			if (e->in_fd == -1)
				child_exit("open", s->in->doubles, strerror(errno), 1);
		}
		else if (s->in->simple)
		{
			s->in->simple = replace_env_variables(s->in->simple, &e->env);
			e->in_fd = open(s->in->simple, O_RDONLY, 0644);
			if (e->in_fd == -1)
				child_exit("open", s->in->simple, strerror(errno), 1);
			if (s->in->next)
				close(e->in_fd);
		}
		s->in = s->in->next;
	}
}

void	outfile(t_stack *s, t_exe *e)
{
	if (s->out->simple)
	{
		s->out->simple = replace_env_variables(s->out->simple, &e->env);
		e->out_fd = open(s->out->simple, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (e->out_fd == -1)
			child_exit("open", s->out->simple, strerror(errno), 1);
	}
	else if (s->out->doubles)
	{
		s->out->doubles = replace_env_variables(s->out->doubles, &e->env);
		e->out_fd = open(s->out->doubles, O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (e->out_fd == -1)
			child_exit("open", s->out->doubles, strerror(errno), 1);
	}
	if (s->out->next)
		close(e->out_fd);
	s->out = s->out->next;
}

void	redir(t_stack *s, t_exe *e, int i_heredoc)
{
	int	place;

	place = 1;
	while (s->in || s->out)
	{
		if (s->in)
			infile(s, e, i_heredoc, &place);
		if (s->out)
			outfile(s, e);
		place++;
	}
}
