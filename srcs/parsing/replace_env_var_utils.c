/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:27:19 by amery             #+#    #+#             */
/*   Updated: 2023/04/21 18:42:10 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

char	*handle_dollar_variable(char *str, int *i, t_quote_flags *q, char *new)
{
	char	*trim;
	char	*sub;
	char	*value;

	sub = ft_substr(str, *i + 1, get_next_space_var(str + *i + 1,
				&q->simple_quote, &q->double_quote));
	trim = ft_strtrim(sub, " ");
	sub = free_ptr(sub);
	value = verif_sub_in_list(trim, q->ourenv);
	trim = free_ptr(trim);
	if (value == NULL)
	{
		*i += get_next_space_var(str + *i + 1,
				&q->simple_quote, &q->double_quote);
		new = ft_strjoin(new, "");
	}
	else
	{
		*i += get_next_space_var(str + *i + 1,
				&q->simple_quote, &q->double_quote);
		new = ft_strjoin(new, value);
	}
	value = free_ptr(value);
	return (new);
}

char	*handle_tild(char *str, int *i, t_quote_flags *q, char *new)
{
	char	*value;

	if (str[*i - 1] && str[*i - 1] != ' ')
		return (new);
	value = verif_sub_in_list("HOME", q->ourenv);
	if (value == NULL)
	{
		*i += get_next_space_var(str + *i + 1,
				&q->simple_quote, &q->double_quote);
		new = ft_strjoin(new, "");
	}
	else
	{
		*i += get_next_space_var(str + *i + 1,
				&q->simple_quote, &q->double_quote);
		new = ft_strjoin(new, value);
	}
	value = free_ptr(value);
	return (new);
}
