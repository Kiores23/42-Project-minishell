/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:04:36 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:45:49 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include <signal.h>

int	g_rerror[3];

int	return_error(char *cmd, char *f_name, char *msg, int r)
{
	if (r)
		ft_putstr_fd("\e[1;31m"MN_SHELL": ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (f_name)
	{
		ft_putstr_fd(f_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\e[0m\n", 2);
	return (r);
}

void	minishell(t_stack *lst, t_env **our_env, char *line)
{
	if (is_only_space_start(line) == 1)
		return ;
	if (verif_string(line) == 0)
		lst = filter_pipe(lst, line);
	if (!g_rerror[1])
		parse_commande(lst, *our_env);
	if (g_rerror[1])
	{
		g_rerror[0] = g_rerror[1];
		g_rerror[1] = 0;
	}
	else
	{
		choice_signal(lst);
		if (!env_execution(lst, our_env, line))
			execution(lst, *our_env);
	}
	sign_error();
	std_save(1);
	free_stack(lst);
}

void	input_minishell(t_stack *lst, t_env **env, t_termios o_term, char *line)
{
	while (1)
	{
		receive_signal();
		line = readline(V_MINISHELL);
		tcsetattr(STDIN_FILENO, TCSANOW, &o_term);
		if (!line)
			break ;
		if (ft_strlen(line) >= 1)
			add_history(line);
		if (ft_strlen (line) != 0)
			minishell(lst, env, line);
		tcsetattr(STDIN_FILENO, TCSANOW, &o_term);
		if (g_rerror[1] && ((g_rerror[0] == 2 || g_rerror[0] == 3)
				|| g_rerror[2] == 2 || g_rerror[2] == 3))
			g_rerror[0] = g_rerror[1];
		g_rerror[1] = 0;
		g_rerror[2] = 0;
		free(line);
	}
}

int	syntax_error_readline(char *c)
{
	ft_putstr_fd(MN_SHELL": ", 2);
	ft_putstr_fd(c, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	g_rerror[1] = 127 * 256;
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_stack		*lst;
	t_env		*our_env;
	t_termios	o_term;
	char		*line;

	if (argc != 1 || argv[1])
		return (syntax_error_readline(argv[1]));
	init_tab();
	our_env = NULL;
	lst = NULL;
	line = NULL;
	std_save(0);
	our_env = parse_environnement(envp, our_env);
	our_env = increment_shlvl(our_env);
	get_last_path("", 0);
	tcgetattr(STDIN_FILENO, &o_term);
	input_minishell(lst, &our_env, o_term, line);
	if (our_env)
		freelist_env(our_env);
	printf("exit\n");
	ft_pwd(NULL, 2);
	get_last_path(NULL, 2);
	return_to_the_old(NULL, 1);
	std_save(2);
	return (g_rerror[0] / 256);
}
