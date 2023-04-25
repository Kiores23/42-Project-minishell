/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:50:41 by amery             #+#    #+#             */
/*   Updated: 2023/04/20 15:04:09 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	int_check_in_quotes(char c, int *in_simple, int *double_quote)
{
	if (c == '"' && !(*in_simple))
		*double_quote = !(*double_quote);
	else if (c == '\'' && !(*double_quote))
		*in_simple = !(*in_simple);
}

void	*ft_freearray(char **s, int i)
{
	while (i-- > 0)
	{
		s[i] = free_ptr(s[i]);
	}
	s = free_ptr(s);
	return (NULL);
}

size_t	ft_len_split(const char *s)
{
	unsigned int	i;
	size_t			lenght;
	int				simple_quote;
	int				double_quote;

	i = 0;
	lenght = 0;
	simple_quote = 0;
	double_quote = 0;
	while (s[i] == ' ' || s[i] == '\t')
	{
		i++;
		int_check_in_quotes(s[i], &simple_quote, &double_quote);
	}
	while (s[i] && (s[i] != ' ' || simple_quote || double_quote))
	{
		int_check_in_quotes(s[i], &simple_quote, &double_quote);
		lenght++;
		i++;
	}
	return (lenght);
}

size_t	ft_count_words(const char *str)
{
	size_t			i;
	size_t			t;
	int				simple_quote;
	int				double_quote;

	i = 0;
	t = 0;
	simple_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && !simple_quote && !double_quote)
			t++;
		while ((str[i] != ' ' && str[i] != '\t' && (str[i + 1]))
			|| ((str[i] == ' ' || str[i] == '\t')
				&& (simple_quote == 1 || double_quote == 1)))
		{
			int_check_in_quotes(str[i], &simple_quote, &double_quote);
			i++;
		}
		i++;
	}
	return (t);
}

int	ft_count(char const *s, int t)
{
	int				simple_quote;
	int				double_quote;

	simple_quote = 0;
	double_quote = 0;
	while (s[t] == ' ' || s[t] == '\t' || simple_quote || double_quote)
	{
		int_check_in_quotes(s[t], &simple_quote, &double_quote);
		t++;
	}
	return (t);
}
