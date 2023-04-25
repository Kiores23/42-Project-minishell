/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_help2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:29:44 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 14:47:05 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h" 

void	handle_export_conditions(char *string, t_export *e, char **tab, int *r)
{
	if (handle_error(string, e) == 0)
	{
		tab[0] = free_ptr(tab[0]);
		tab[1] = free_ptr(tab[1]);
	}
	else if (handle_underscore(string, e) == 0)
	{
		tab[0] = free_ptr(tab[0]);
		tab[1] = free_ptr(tab[1]);
	}
	else if (check_variable_name(tab[0]) == 0)
	{
		ft_putstr_fd("\e[1;31mminishell: export: '", 2);
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd("': not a valid identifier\e[0m\n", 2);
		g_rerror[1] = 1;
		tab[0] = free_ptr(tab[0]);
		tab[1] = free_ptr(tab[1]);
		*r = 1;
	}
}

void	free_tab_ptrs(char **tab)
{
	tab[0] = free_ptr(tab[0]);
	tab[1] = free_ptr(tab[1]);
}

void	handle_the_case(char **tab)
{
	g_rerror[1] = return_error("export", tab[0],
			"not a valid identifier", 1);
	free_tab_ptrs(tab);
}
