/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:39:39 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:11:39 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h" 

int	verif_n(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (1);
	else
		return (0);
}

int	manage_arg(char *str, int *n_flag)
{
	*n_flag = 1;
	if (verif_n(str) == 1)
	{
		*n_flag = 0;
		return (0);
	}
	else
	{
		*n_flag = 1;
		return (1);
	}
}

void	ft_print_echo(char *str, int (*in_quote), int (*in_apostrophe))
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && !(*in_apostrophe))
			(*in_quote) = !(*in_quote);
		else if (str[i] == '\'' && !(*in_quote))
			(*in_apostrophe) = !(*in_apostrophe);
		if (!(*in_quote) && !(*in_apostrophe))
			printf("%c", str[i]);
		else if ((*in_quote))
		{
			if (str[i] != '\'')
				printf("%c", str[i]);
		}
		else if ((*in_apostrophe))
		{
			if (str[i] != '"')
				printf("%c", str[i]);
		}
		i++;
	}
}

void	init_var_echo(t_echo *ech)
{
	ech->i = 1;
	ech->n_flag = 0;
	ech->in_quote = 0;
	ech->in_apostrophe = 0;
}

int	ft_echo(char **line)
{
	t_echo		ech;

	init_var_echo(&ech);
	if (!line[ech.i] && ech.n_flag == 0)
	{
		printf("%c", '\n');
		return (0);
	}
	if ((ft_strncmp(line[ech.i], "-n", 2) == 0)
		&& manage_arg(line[ech.i], &ech.n_flag) == 1)
	{
		ech.i++;
		while (line[ech.i] && (ft_strncmp(line[ech.i], "-n", 2) == 0)
			&& line[ech.i] && verif_n(line[ech.i]) == 0)
			ech.i++;
	}
	while (line[ech.i])
	{
		ft_print_echo(line[ech.i++], &ech.in_quote, &ech.in_apostrophe);
		if (line[ech.i])
			printf(" ");
	}
	if (ech.n_flag == 0)
		printf("%c", '\n');
	return (0);
}
