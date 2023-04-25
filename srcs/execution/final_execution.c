/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:00:04 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 14:24:39 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*to_down(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	final_execution(t_stack *s, t_exe *e, t_env *envp, int i)
{
	if ((e->in_fd != -1 || e->out_fd != -1) && !s->cmd_final[0])
		exit(0);
	if (!ft_strcmp(to_down(s->cmd_final[0]), "echo"))
		exit(ft_echo(s->cmd_final));
	else if (!ft_strcmp(s->cmd_final[0], "env")
		|| !ft_strcmp(s->cmd_final[0], "printenv"))
		exit(env(e->envp, s->cmd_final));
	else if (!ft_strcmp(s->cmd_final[0], "cd"))
		exit(changedirectory(s->cmd_final, envp));
	else if (!ft_strcmp(s->cmd_final[0], "unset"))
		exit(unset_env_var(&envp, s->cmd_final));
	else if (!ft_strcmp(s->cmd_final[0], "export"))
	{
		if (s->cmd_final[1])
			exit(export_env(&envp, s->cmd_final));
		else
			exit(print_export(&envp));
	}
	else if (!ft_strcmp(s->cmd_final[0], "exit"))
		exit(ft_exit(s->cmd_final, s, envp, NULL));
	else if (!ft_strcmp(s->cmd_final[0], "pwd"))
		exit(ft_pwd(s->cmd_final, 0));
	else if (!e->paths[i][0] || !s->cmd_final[0] || !s->cmd_final[0][0])
		child_exit(s->cmd_final[0], NULL, "command not found", 127);
}
