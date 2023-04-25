/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 03:36:10 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 11:32:55 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "macro.h"

typedef struct s_stack
{
	char			*cmd_sep;
	char			**cmd_final;
	struct s_file	*in;
	struct s_file	*out;
	struct s_stack	*next;
	struct s_stack	*prec;
}	t_stack;

typedef struct s_file
{
	char			*simple;
	char			*doubles;
	int				order;
	struct s_file	*next;
	struct s_file	*prev;
}	t_file;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exe
{
	t_env	*env;
	char	**paths;
	char	**envp;
	int		fork_id[BUFFER_SIZE];
	int		pipe_fd[BUFFER_SIZE][2];
	int		heredoc_fd[BUFFER_SIZE][2];
	int		in_fd;
	int		out_fd;
	int		std_in;
	int		std_out;
}	t_exe;

#endif