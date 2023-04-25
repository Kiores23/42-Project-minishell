/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplace_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:27:13 by amery             #+#    #+#             */
/*   Updated: 2023/04/22 17:46:04 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

char	*verif_sub_in_list(char *str, t_env **ourenv)
{
	t_env	*cpy;
	t_env	*cp_start;
	char	*result;

	cpy = ft_lst_cpy(*ourenv);
	if (!cpy)
		return (NULL);
	cp_start = cpy;
	while (cpy)
	{
		if (ft_strcmp(str, cpy->name) == 0)
		{
			result = NULL;
			if (cpy->value)
				result = ft_strdup(cpy->value);
			freelist_env(cp_start);
			return (result);
		}
		cpy = cpy->next;
	}
	freelist_env(cp_start);
	return (NULL);
}

int	is_legit(char c)
{
	if ((is_letter(c) == 1) || (c == '_') || (is_digit(c) == 1))
		return (1);
	else
		return (0);
}

int	get_next_space_var(char *str, int *in_simple, int *double_quote)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] != ' ' && str[i] != '\t' && is_legit(str[i])))
	{
		if (str[i] == '"' && !(*in_simple))
			*double_quote = !(*double_quote);
		else if (str[i] == '\'' && !(*double_quote))
			*in_simple = !(*in_simple);
		i++;
	}
	return (i);
}

char	*handle_dollar_question_mark(char *new_str, int *i)
{
	char	*nombre;

	nombre = ft_itoa(g_rerror[0] / 256);
	new_str = ft_strjoin(new_str, nombre);
	nombre = free_ptr(nombre);
	*i = *i + 1;
	return (new_str);
}

void	init_variables(t_quote_flags *quotes, t_env **ourenv)
{
	quotes->simple_quote = 0;
	quotes->double_quote = 0;
	quotes->ourenv = ourenv;
}
