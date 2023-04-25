/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_second_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:49:58 by amery             #+#    #+#             */
/*   Updated: 2023/04/17 04:49:59 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

char	*ft_strjoin_char(char *s1, char s2)
{
	int		i;
	int		j;
	char	*all;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	all = malloc(ft_strlen(s1) + 2);
	if (!all)
		return (NULL);
	while (s1[i])
		all[j++] = s1[i++];
	i = 0;
	all[j] = s2;
	j++;
	all[j] = '\0';
	s1 = free_ptr(s1);
	return (all);
}

char	*handle_char(char *result, char c, int *single_quote, int *double_quote)
{
	if (c == '"' && *single_quote != 1)
	{
		if (*double_quote == 1)
			*double_quote = 0;
		else
			*double_quote = 1;
	}
	else if (c == '\'' && *double_quote != 1)
	{
		if (*single_quote == 1)
			*single_quote = 0;
		else
			*single_quote = 1;
	}
	else
		result = ft_strjoin_char(result, c);
	return (result);
}

char	*parse_quotes(char *input)
{
	char	*result;
	int		single_quote;
	int		double_quote;
	int		i;

	i = 0;
	result = ft_strdup("");
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		result = handle_char(result, input[i], &single_quote, &double_quote);
		i++;
	}
	input = free_ptr(input);
	return (result);
}
