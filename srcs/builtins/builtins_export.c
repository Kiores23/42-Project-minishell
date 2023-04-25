/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:32:11 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 14:47:13 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h" 

int	handle_error(char *strings, t_export *export_va)
{
	if (ft_strlen(strings) == 0)
	{
		export_va->i = export_va->i + 1;
		ft_putstr_fd("\e[1;31m", 2);
		ft_putstr_fd("minishell: export: '': not a valid identifier\e[0m\n",
			2);
		g_rerror[1] = 1;
		return (0);
	}	
	else
		return (1);
}

int	handle_underscore(char *strings, t_export *export_va)
{
	if ((ft_strcmp(strings, "_") == 0))
	{
		export_va->i = export_va->i + 1;
		return (0);
	}	
	else
		return (1);
}

void	update_export_variables(t_export *export_va, char *tab[], t_env **env)
{
	while (export_va->lst)
	{
		if (ft_strcmp(export_va->lst->name, tab[0]) == 0)
		{
			if (tab[1])
			{
				export_va->lst->value = free_ptr(export_va->lst->value);
				export_va->lst->value = ft_strdup(tab[1]);
				tab[0] = free_ptr(tab[0]);
				tab[1] = free_ptr(tab[1]);
			}
			export_va->boolean++;
			break ;
		}
		export_va->lst = export_va->lst->next;
	}
	if (export_va->boolean == 0)
	{
		add_cell_env(env, ft_strdup(tab[0]), tab[1]);
		tab[0] = free_ptr(tab[0]);
	}
}

void	process(t_export *e, char **strings, t_env **our_env, char **tab)
{
	while (strings[e->i])
	{
		parse_string(strings[e->i], tab);
		if (handle_error(strings[e->i], e) == 0)
		{
			free_tab_ptrs(tab);
			continue ;
		}
		else if (handle_underscore(tab[0], e) == 0)
		{
			free_tab_ptrs(tab);
			continue ;
		}
		else if (check_variable_name(tab[0]) == 0)
			handle_the_case(tab);
		else
		{
			update_export_variables(e, tab, our_env);
			tab[0] = free_ptr(tab[0]);
		}
		e->i++;
		e->boolean = 0;
		e->lst = *our_env;
	}
}

int	export_env(t_env **our_env, char **strings)
{
	t_export	export_va;
	char		*tab[2];

	tab[0] = NULL;
	tab[1] = NULL;
	if (!our_env || !*our_env || !strings)
	{
		g_rerror[1] = 1;
		return (0);
	}
	init_var_export(&export_va, our_env);
	process(&export_va, strings, our_env, tab);
	export_va.lst = *our_env;
	return (0);
}
