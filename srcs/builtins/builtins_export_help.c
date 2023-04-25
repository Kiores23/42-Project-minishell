/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_help.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:29:44 by amery             #+#    #+#             */
/*   Updated: 2023/04/20 18:12:35 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h" 

int	is_letter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	check_variable_name(char *str)
{
	int	i;

	i = 0;
	if (str[0] && ((is_letter (str[0]) == 1) || (str[0] == '_')))
		i++;
	else
		return (0);
	while (str[i])
	{
		if ((is_letter(str[i]) == 1) || (str[i] == '_')
			|| (is_digit(str[i]) == 1))
			i++;
		else
			return (0);
	}
	return (1);
}

char	**parse_string(char *str, char **tab)
{
	int	i;
	int	y;

	i = 0;
	tab[0] = NULL;
	tab[1] = NULL;
	while (str[i])
	{
		tab[0] = free_ptr(tab[0]);
		tab[0] = ft_strncpy_until_char(str, '=');
		y = 0;
		while (str[y])
		{
			if (str[y] == '=')
			{
				tab[1] = free_ptr(tab[1]);
				tab[1] = ft_strdup(str + y + 1);
				break ;
			}
			y++;
		}
		i++;
	}
	return (tab);
}

void	init_var_export(t_export *export_va, t_env **our_env)
{
	export_va->boolean = 0;
	export_va->i = 1;
	export_va->lst = *our_env;
}
