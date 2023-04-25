/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:08:42 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 14:01:26 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_atoi_parsing(char *str)
{
	unsigned long long	result;
	int					i;
	int					n;

	i = 0;
	result = 0;
	n = 1;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
		n = -1;
	else if (str[i] != '+' && !ft_isdigit (str[i--]))
		return (return_error("exit", str, N_ARG_EQ, 255));
	while (str[++i] && ft_isdigit (str[i]) == 1 && result < 9223372036854775807)
		result = result * 10 + str[i] - '0';
	i--;
	while (str[++i])
	{
		if (str[i] != 32 && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\r' && str[i] != '\v' && str[i] != '\f')
			return (return_error("exit", str, N_ARG_EQ, 255));
	}
	return (n);
}

unsigned long long	ft_atoi_exit(const char *str)
{
	unsigned long long	result;
	int					i;

	i = 0;
	result = 0;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
		;
	else if (str[i] != '+' && !ft_isdigit (str[i--]))
		;
	while (str[++i] && ft_isdigit (str[i]) == 1 && result < 9223372036854775807)
		result = result * 10 + str[i] - '0';
	return (result);
}

void	freexit(t_stack *s, t_env *env, char *line)
{
	ft_pwd(NULL, 2);
	get_last_path(NULL, 2);
	return_to_the_old(NULL, 1);
	if (s && s->in)
		freelist_redi(s->in);
	if (s && s->out)
		freelist_redi(s->out);
	if (s && s->cmd_final)
		free_char_array(s->cmd_final);
	if (s)
		freelist(s);
	if (env)
		freelist_env(env);
	if (line)
		free(line);
	std_save(2);
}

int	ft_exit(char **cmds, t_stack *s, t_env *env, char *line)
{
	unsigned long long	exi;
	int					pars;

	pars = 1;
	exi = 1;
	if (cmds && cmds[0] && cmds[1])
		pars = ft_atoi_parsing(cmds[1]);
	if (pars != 255 && (!cmds || !*cmds || (cmds[1] && cmds[2])))
		return (return_error("exit", NULL, "too many arguments", 1));
	if (pars != 255 && cmds[0] && cmds[1])
		exi = ft_atoi_exit(cmds[1]);
	if (!cmds[1])
		exi = g_rerror[0] / 256;
	if (line)
		printf("exit\n");
	if ((pars == -1 && exi + pars > 9223372036854775807)
		|| (pars == 1 && exi > 9223372036854775807))
		exi = return_error("exit", cmds[1], N_ARG_EQ, 255 * pars);
	freexit(s, env, line);
	exit(exi * pars);
	return (0);
}
