/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 03:36:07 by amery             #+#    #+#             */
/*   Updated: 2023/04/19 17:32:42 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include "../srcs/execution/execution.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/builtins/builtins.h"
# include "../srcs/signals/signals.h"

# include "lib.h"
# include "struct.h"
# include "macro.h"

extern int	g_rerror[3];

void	minishell(t_stack *lst, t_env **our_env, char *line);
int		return_error(char *cmd, char *f_name, char *msg, int r);

#endif
