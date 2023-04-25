/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:28:02 by amery             #+#    #+#             */
/*   Updated: 2023/04/22 17:46:19 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../Includes/macro.h"
# include "../../Includes/lib.h"
# include "../../Includes/struct.h"

// CORE EXE

int		execution(t_stack *s, t_env *lst_env);

// END EXE

int		env_execution(t_stack *s, t_env **env, char *line);
void	final_execution(t_stack *s, t_exe *e, t_env *envp, int i);

// FD AND REDIRECTION

void	redir(t_stack *s, t_exe *e, int i);
void	dup_in(t_stack *s, t_exe *e, int i);
void	dup_out(t_stack *s, t_exe *e, int i);
int		env_redir(t_stack *s, t_env *lst_env, t_exe *e);

// HEREDOC

void	pipe_heredoc(char *fullstr, int fd[2]);
char	*create_heredoc(char *stop, t_env *env);
int		create_pipe_for_heredoc(t_stack *s, t_exe *e);
int		process_heredoc(t_stack *s, t_exe *e, int i, t_env *env);
char	*replace_env_variables_heardoc(char *str, t_env **ourenv);
int		init_heredoc(t_stack *s, t_exe *e, t_env *env);

// EXIT

void	child_exit(char *cmd, char *f_name, char *msg, int r);
void	std_save(int i);

// PATH AND ENV

void	free_paths(char **paths);
char	**all_paths(t_stack *s, t_exe *e);
char	**get_tab_env(t_env *lst_env);

#endif