/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_mangement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:50:16 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 11:14:01 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	handledouble_inputredi(t_redi *redi, char *s, t_file **in)
{
	int		index;
	char	*sub;

	(redi->i)++;
	while (s[redi->i] == ' ' || s[redi->i] == '\t')
		(redi->i)++;
	index = get_next_space(s + redi->i);
	sub = ft_substr(s, redi->i, index);
	if (!*sub && !g_rerror[1])
	{
		if (s[redi->i])
			syntax_error(s[redi->i]);
		else
			syntax_error('\n');
	}
	sub = parse_quotes(sub);
	(redi->order)++;
	add_cell_redirections(in, sub, 1, redi->order);
	redi->i += index;
}

void	handlesingle_inputredi(t_redi *redi, char *s, t_file **in, t_env **env)
{
	int		index;
	char	*sub;
	char	*tmp;

	while (s[redi->i] == ' ' || s[redi->i] == '\t')
		(redi->i)++;
	index = get_next_space(s + redi->i);
	sub = ft_substr(s, redi->i, index);
	sub = parse_quotes(sub);
	if (!*sub && !g_rerror[1])
	{
		if (s[redi->i])
			syntax_error(s[redi->i]);
		else
			syntax_error('\n');
	}
	tmp = ft_strdup(sub);
	sub = replace_env_variables(sub, env);
	(redi->order)++;
	if (!*sub && !free_ptr(sub))
		sub = ft_strdup(tmp);
	tmp = free_ptr(tmp);
	add_cell_redirections(in, sub, 0, redi->order);
	redi->i += index;
}

int	actualise_order(t_redi *redi, char *str)
{
	if (str[redi->i + 1] && str[redi->i + 1] == '>')
	{
		(redi->i)++;
		(redi->order)++;
		return (1);
	}
	(redi->order)++;
	return (0);
}

void	handle_remaining_characters(t_redi *redi, char *str, char *new_str)
{
	if (str[redi->i] == '>' && !redi->in_double && !redi->in_simple)
	{
		if (actualise_order(redi, str) == 1)
		{
			new_str[redi->j++] = '>';
		}
	}
	new_str[redi->j++] = str[redi->i++];
}

char	*ft_for_input_redirection(char *str, t_file **in, t_env **ourenv)
{
	t_redi	redi;
	char	*new_str;

	init_var_redi(&redi);
	new_str = (char *) malloc (strlen (str) + 1);
	while (str[redi.i])
	{
		handle_quotes_redi(str[redi.i], &redi);
		if (str[redi.i] == '<' && !redi.in_double && !redi.in_simple)
		{
			redi.i++;
			if (str[redi.i] == '<')
				handledouble_inputredi(&redi, str, in);
			else
				handlesingle_inputredi(&redi, str, in, ourenv);
			redi.i += get_next_space(str + redi.i);
		}
		else
			handle_remaining_characters(&redi, str, new_str);
	}
	new_str[redi.j] = '\0';
	str = free_ptr(str);
	return (new_str);
}
