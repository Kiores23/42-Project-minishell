/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:50:30 by amery             #+#    #+#             */
/*   Updated: 2023/04/20 15:03:34 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

int	get_next_space(char *str)
{
	int		i;
	int		simple_quote;
	int		double_quote;

	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while ((str[i] && str[i] != ' ' && str[i] != '\t'
			&& str[i] != '<' && str[i] != '>')
		|| (simple_quote || double_quote))
	{
		if (str[i] == '"' && !simple_quote)
			double_quote = !double_quote;
		else if (str[i] == '\'' && !double_quote)
			simple_quote = !simple_quote;
		i++;
	}
	return (i);
}

void	init_var_redi(t_redi *redi)
{
	redi->i = 0;
	redi->j = 0;
	redi->in_simple = 0;
	redi->in_double = 0;
	redi->order = 0;
}

void	handle_quotes_redi(char current_char, t_redi *redi)
{
	if (current_char == '"' && !redi->in_simple)
		redi->in_double = !redi->in_double;
	else if (current_char == '\'' && !redi->in_double)
		redi->in_simple = !redi->in_simple;
}

int	is_only_space_start(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
