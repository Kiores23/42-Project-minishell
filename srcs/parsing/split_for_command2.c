/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_command2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:50:44 by amery             #+#    #+#             */
/*   Updated: 2023/04/20 13:01:06 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	init_split(t_split *vars)
{
	vars->i = -1;
	vars->t = 0;
	vars->double_quote = 0;
	vars->simple_quote = 0;
	vars->tab = NULL;
}

void	fill_tab(char const *s, t_split *vars, char **tab)
{
	while (s[vars->t] && ((s[vars->t] != ' ' && s[vars->t] != '\t')
			|| vars->simple_quote || vars->double_quote))
	{
		int_check_in_quotes(s[vars->t], &vars->simple_quote,
			&vars->double_quote);
		tab[vars->i][vars->j++] = s[vars->t++];
	}
	tab[vars->i][vars->j] = '\0';
	while (s[vars->t] == ' ' || s[vars->t] == '\t')
		vars->t++;
}

char	**ft_split_for_quotes(char const *s)
{
	t_split	vars;
	char	**tab;

	init_split(&vars);
	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_count_words(s) + 1));
	if (!tab)
		return (NULL);
	while (++vars.i < ft_count_words(s))
	{
		tab[vars.i] = (char *) malloc(sizeof(char)
				* (ft_len_split(s + vars.t) + 1));
		if (!tab[vars.i])
			return (ft_freearray(tab, vars.i));
		vars.j = 0;
		vars.t = ft_count(s, vars.t);
		fill_tab(s, &vars, tab);
	}
	tab[vars.i] = NULL;
	return (tab);
}
