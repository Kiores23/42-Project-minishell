/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_mangemment_out.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:50:23 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:43:14 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	init_var_r_out(t_r_out *r_out)
{
	r_out->i = 0;
	r_out->j = 0;
	r_out->in_simple = 0;
	r_out->in_double = 0;
}

void	handle_quotes_r_out(char current_char, t_r_out *r_out)
{
	if (current_char == '"' && !r_out->in_simple)
		r_out->in_double = !r_out->in_double;
	else if (current_char == '\'' && !r_out->in_double)
		r_out->in_simple = !r_out->in_simple;
}

void	handledouble_outputredi(t_r_out *r_out, char *s, t_file **o, t_env **e)
{
	char	*sub;
	char	*tmp;

	r_out->i++;
	while (s[r_out->i] == ' ' || s[r_out->i] == '\t')
		r_out->i++;
	sub = ft_substr(s, r_out->i, get_next_space(s + r_out->i));
	if (!*sub && !g_rerror[1])
	{
		if (s[r_out->i])
			syntax_error(s[r_out->i]);
		else
			syntax_error('\n');
	}
	sub = parse_quotes(sub);
	tmp = ft_strdup(sub);
	sub = replace_env_variables(sub, e);
	if (!*sub && !free_ptr(sub))
		sub = ft_strdup(tmp);
	tmp = free_ptr(tmp);
	add_cell_redirections(o, sub, 1, -1);
}

void	handlesingle_outputredi(t_r_out *r_out, char *s, t_file **o, t_env **e)
{
	char	*sub;
	char	*tmp;

	while (s[r_out->i] == ' ' || s[r_out->i] == '\t')
		r_out->i++;
	sub = ft_substr(s, r_out->i, get_next_space(s + r_out->i));
	if (!*sub && !g_rerror[1])
	{
		if (s[r_out->i])
			syntax_error(s[r_out->i]);
		else
			syntax_error('\n');
	}
	sub = parse_quotes(sub);
	tmp = ft_strdup(sub);
	sub = replace_env_variables(sub, e);
	if (!*sub && !free_ptr(sub))
		sub = ft_strdup(tmp);
	tmp = free_ptr(tmp);
	add_cell_redirections(o, sub, 0, -1);
}

char	*ft_for_output_redirection(char *s, t_file **out, t_env **env)
{
	t_r_out		r_out;
	char		*new_str;

	init_var_r_out(&r_out);
	new_str = (char *) malloc (strlen (s) + 1);
	while (s[r_out.i])
	{
		handle_quotes_r_out(s[r_out.i], &r_out);
		if (s[r_out.i] == '>' && !r_out.in_double && !r_out.in_simple)
		{
			r_out.i++;
			if (s[r_out.i] == '>')
				handledouble_outputredi(&r_out, s, out, env);
			else
				handlesingle_outputredi(&r_out, s, out, env);
			r_out.i += get_next_space(s + r_out.i);
		}
		else
			new_str[r_out.j++] = s[r_out.i++];
	}
	new_str[r_out.j] = '\0';
	s = free_ptr(s);
	return (new_str);
}
