/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tab_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 10:48:38 by amery             #+#    #+#             */
/*   Updated: 2023/04/19 16:01:42 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	env(char **our_env, char **cmds)
{
	int	i;

	i = -1;
	if (cmds[1])
		return (return_error("env", cmds[1], "arguments", 127));
	if (!our_env)
		return (return_error("env", NULL, "env not found", 127));
	while (our_env[++i])
		printf("%s\n", our_env[i]);
	return (0);
}

char	**get_tab_env(t_env *lst_env)
{
	char	**env;
	char	*str_tmp;
	int		i;

	str_tmp = ft_strdup("");
	i = -1;
	while (lst_env && lst_env->name)
	{
		if (lst_env && lst_env->name && lst_env->value)
		{
			str_tmp = ft_strjoin(str_tmp, lst_env->name);
			str_tmp = ft_strjoin(str_tmp, "=");
		}
		if (lst_env && lst_env->name && lst_env->value)
		{
			str_tmp = ft_strjoin(str_tmp, lst_env->value);
			str_tmp = ft_strjoin(str_tmp, "\n");
		}
		if (!str_tmp)
			return (NULL);
		lst_env = lst_env->next;
	}
	env = ft_split(str_tmp, '\n');
	str_tmp = free_ptr(str_tmp);
	return (env);
}
