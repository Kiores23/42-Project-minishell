/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplace_env_var2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 05:27:19 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 14:13:37 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	handle_quotes(char current_char, t_quote_flags *quotes)
{
	if (current_char == '"' && !quotes->simple_quote)
		quotes->double_quote = !quotes->double_quote;
	else if (current_char == '\'' && !quotes->double_quote)
		quotes->simple_quote = !quotes->simple_quote;
}

char	*replace_sp(char *s, int *i, t_quote_flags *quotes, char *new_str)
{
	if (s[*i] == '$')
	{
		if (s[*i] == '$' && (!s[*i + 1] || s[*i + 1] == ' '
				|| s[*i + 1] == '\t'))
			new_str = ft_strjoin_char(new_str, s[*i]);
		if (s[*i] == '$' && s[*i + 1] && s[*i + 1] == '?')
			new_str = handle_dollar_question_mark(new_str, i);
		else if (s[*i] == '$' && s[*i + 1] && s[*i + 1] != ' '
			&& s[*i + 1] != '\t' && (s [*i + 1] != '"'
				|| s[*i + 2] != '\0')
			&& (is_legit(s[*i + 1]) == 1))
			new_str = handle_dollar_variable(s, i, quotes, new_str);
		else if ((is_legit(s[*i + 1]) == 0 && s[*i + 1] != '\''
				&& s[*i + 1] != '"' && s[*i + 1] != ' ' && s[*i + 1] != '\t'
				&& s[*i + 1] != '\0') || ((s[*i - 1] && s[*i - 1] == '"')
				&& s[*i + 1] && s[*i + 1] == '"'))
			new_str = ft_strjoin_char(new_str, '$');
	}
	else if (s[*i] == '~'
		&& ((s[*i + 1] && (s[*i + 1] == ' '
					|| s[*i + 1] == '\t')) || (!(s[*i + 1]))))
		new_str = handle_tild(s, i, quotes, new_str);
	else
		new_str = ft_strjoin_char(new_str, s[*i]);
	return (new_str);
}

char	*replace_env_variables(char *str, t_env **ourenv)
{
	int				i;
	char			*new_str;
	t_quote_flags	quotes;

	new_str = NULL;
	init_variables(&quotes, ourenv);
	new_str = ft_strdup("");
	i = 0;
	while (str[i])
	{
		handle_quotes(str[i], &quotes);
		if (quotes.simple_quote)
			new_str = ft_strjoin_char(new_str, str[i]);
		else
			new_str = replace_sp(str, &i, &quotes, new_str);
		i++;
	}
	str = free_ptr(str);
	return (new_str);
}
