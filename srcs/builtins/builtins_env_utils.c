/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:15:47 by amery             #+#    #+#             */
/*   Updated: 2023/04/22 21:51:50 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	print_unset_message(char *name)
{
	if (check_variable_name(name) == 0)
	{
		ft_putstr_fd("\e[1;31mMinishell : unset:'", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\e[0m\n", 2);
		return (1);
	}
	return (0);
}

void	init_var_unset(t_unset *unset_vars, t_env **lst_ptr)
{
	unset_vars->i = -1;
	unset_vars->r = 0;
	unset_vars->lst = *lst_ptr;
}

t_env	*free_cur(t_env *ptr)
{
	if (ptr)
	{
		if (ptr->name)
			free(ptr->name);
		if (ptr->value)
			free(ptr->value);
		free(ptr);
	}
	return (NULL);
}
