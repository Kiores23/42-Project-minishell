/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 03:36:02 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:08:19 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

# define V_MINISHELL "minishell.1.0.0~$ "
# define BUFFER_SIZE 1000

// ----- ERROR ----- //

# define MN_SHELL "minishell"
# define ERROR "error"

// PARSINF

# define SYNTAX_ERROR "syntax error near unexpected token "

// CMDS

# define CD "cd"
# define GETCWD "getcwd"
# define ACCESS_PARRENT_DIR "cannot access parent directories"

// EXIT

# define N_ARG_EQ "numeric argument required"

// REGULAR

# define NO_FILE_OR_DIR "No such file or directory"

#endif