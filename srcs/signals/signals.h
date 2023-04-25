/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:46:18 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 15:44:40 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../../Includes/lib.h"
# include "../../Includes/struct.h"

void	sign_kill(int n);
void	sign_shield(int n);
void	sign_newline(int n);
void	sign_segfault(int n);
void	sign_ignore(int n);
int		receive_signal(void);
int		receive_signal_2(void);
int		receive_signal_3(void);
int		receive_signal_4(void);
void	choice_signal(t_stack *s);
int		*init_tab(void);
void	sign_error(void);

#endif