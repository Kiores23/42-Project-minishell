/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_third_part.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:50:06 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 11:08:47 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

int	syntax_error(char c)
{
	ft_putstr_fd("\e[1;31m"MN_SHELL": "SYNTAX_ERROR"`", 2);
	if (c != '\n' && c != '\0')
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\e[0m\n", 2);
	g_rerror[1] = 258 * 256;
	return (1);
}

void	make_f(t_stack *l, t_file *in, t_file *out, t_env *o)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	str = l->cmd_sep;
	str = ft_strdup(l->cmd_sep);
	str = ft_for_input_redirection(str, &in, &o);
	str = ft_for_output_redirection(str, &out, &o);
	str = replace_env_variables(str, &o);
	l->cmd_final = ft_split_for_quotes(str);
	while (l->cmd_final[i])
	{
		l->cmd_final[i] = parse_quotes(l->cmd_final[i]);
		i++;
	}
	l->in = in;
	l->out = out;
	l->cmd_sep = free_ptr(l->cmd_sep);
	str = free_ptr(str);
}

void	parse_commande(t_stack *lst, t_env *our_env)
{
	t_file	*in;
	t_file	*out;

	while (lst)
	{
		in = NULL;
		out = NULL;
		make_f(lst, in, out, our_env);
		lst = lst->next;
	}
}
