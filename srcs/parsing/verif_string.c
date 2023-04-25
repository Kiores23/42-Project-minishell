/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:50:51 by amery             #+#    #+#             */
/*   Updated: 2023/04/22 14:56:07 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	verif_quotes(char c, int *in_double, int *double_quotes, int *in_single)
{
	if (c == '\"' && !(*in_single))
	{
		(*in_double) = !(*in_double);
		(*double_quotes) = *double_quotes + 1;
	}
}

int	count_unquoted_quotes(char *str)
{
	int	in_single;
	int	double_quote;
	int	single_quotes;
	int	double_quotes;

	in_single = 0;
	double_quote = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (*str)
	{
		if (*str == '\'' && !double_quote)
		{
			in_single = !in_single;
			(single_quotes)++;
		}
		verif_quotes(*str, &double_quote, &double_quotes, &in_single);
		str++;
	}
	if (single_quotes % 2 != 0 && !g_rerror[1])
		return (syntax_error('\''));
	else if (double_quotes % 2 != 0 && !g_rerror[1])
		return (syntax_error('\"'));
	return (0);
}

int	verif_semicolon(char *str)
{
	int	in_single_quotes;
	int	double_quote;
	int	i;

	in_single_quotes = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && in_single_quotes == 0)
			double_quote = !double_quote;
		else if (str[i] == '\'' && !double_quote)
			in_single_quotes = !in_single_quotes;
		if (str[i] == ';' && in_single_quotes == 0 && double_quote == 0
			&& !g_rerror[1])
			return (syntax_error(str[i]));
		i++;
	}
	return (0);
}

int	verif_double_redirections(char *str)
{
	int	in_single_quotes;
	int	double_quote;
	int	i;

	in_single_quotes = 0;
	double_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && in_single_quotes == 0)
			double_quote = !double_quote;
		else if (str[i] == '\'' && !double_quote)
			in_single_quotes = !in_single_quotes;
		if (str[i] == '>' && in_single_quotes == 0 && double_quote == 0
			&& str[i + 1] && str[i + 1] == '<' && !g_rerror[1])
			return (syntax_error(str[i + 1]));
		if (str[i] == '<' && in_single_quotes == 0 && double_quote == 0
			&& str[i + 1] && str[i + 1] == '>' && !g_rerror[1])
			return (syntax_error(str[i + 1]));
		i++;
	}
	return (0);
}

int	verif_string(char *str)
{
	int	semiclon;
	int	quotes;
	int	redir;

	semiclon = 0;
	quotes = 0;
	redir = 0;
	semiclon = verif_semicolon(str);
	quotes = count_unquoted_quotes(str);
	redir = verif_double_redirections(str);
	if (semiclon == 1 || quotes == 1 || redir == 1)
		return (1);
	return (0);
}
