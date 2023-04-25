/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_first_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:49:52 by amery             #+#    #+#             */
/*   Updated: 2023/04/20 12:46:16 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	change_quotes(char c, int *in_apostrophe, int *in_quote)
{
	if (c == '"' && !(*in_apostrophe))
		(*in_quote) = !(*in_quote);
	else if (c == '\'' && !(*in_quote))
		(*in_apostrophe) = !(*in_apostrophe);
}

int	is_only_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	syntax_error('|');
	return (1);
}

void	handle_pipe(char **line, int *len, int i, t_stack **lst)
{
	char	*substr;

	substr = ft_substr(*line, 0, i);
	if (ft_strchr(*line, '|') && !g_rerror[1])
		is_only_space(substr);
	if (!*substr && !g_rerror[1])
		syntax_error(*line[i]);
	add_cell_tstack(lst, ft_strtrim(substr, " "));
	substr = free_ptr(substr);
	*line += i + 1;
	*len -= i + 1;
}

void	init_var_pipe(t_pipe *vars_pipe, char *line)
{
	vars_pipe->i = 0;
	vars_pipe->len = ft_strlen(line);
	vars_pipe->in_quote = 0;
	vars_pipe->in_apostrophe = 0;
}

t_stack	*filter_pipe(t_stack *lst, char *line)
{
	t_pipe	vars_pipe;
	char	*substr;

	init_var_pipe(&vars_pipe, line);
	while (vars_pipe.i < vars_pipe.len)
	{
		change_quotes(line[vars_pipe.i], &vars_pipe.in_apostrophe,
			&vars_pipe.in_quote);
		if (!vars_pipe.in_quote && !vars_pipe.in_apostrophe
			&& line[vars_pipe.i] == '|')
		{
			handle_pipe(&line, &vars_pipe.len, vars_pipe.i, &lst);
			vars_pipe.i = 0;
			continue ;
		}
		vars_pipe.i++;
	}
	substr = ft_substr(line, 0, vars_pipe.len);
	if ((!*substr || is_only_space(substr) == 1) && !g_rerror[1])
		syntax_error(line[vars_pipe.len - 1]);
	add_cell_tstack(&lst, ft_strtrim(substr, " "));
	substr = free_ptr(substr);
	return (lst);
}
