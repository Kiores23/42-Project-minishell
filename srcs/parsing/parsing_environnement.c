/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_environnement.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:49:41 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 10:26:44 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h" 

void	env_i(t_env **our_env)
{
	char	*pwd_buff;
	char	*pwd;

	pwd_buff = NULL;
	pwd_buff = getcwd(pwd_buff, sizeof(pwd_buff));
	pwd = ft_strdup(pwd_buff);
	if (pwd_buff)
		free(pwd_buff);
	add_cell_env(our_env, ft_strdup("SHLVL"), ft_strdup("0"));
	add_cell_env(our_env, ft_strdup("PWD"), pwd);
	add_cell_env(our_env, ft_strdup("OLDPWD"), NULL);
	add_cell_env(our_env, ft_strdup("_"), ft_strdup("/usr/bin/env"));
}

char	*return_value(char *name, char *value, int y, char *envp_i)
{
	if (ft_strcmp(name, "OLDPWD") == 0)
		value = NULL;
	else if (ft_strcmp(name, "_") == 0)
		value = ft_strdup("/usr/bin/env");
	else if (name)
		value = ft_strdup(envp_i + y + 1);
	return (value);
}

void	handle_env_variable(char *envp_i, t_env **our_env)
{
	int		y;
	char	*name;
	char	*value;

	value = NULL;
	name = NULL;
	if (*envp_i)
		name = ft_strncpy_until_char(envp_i, '=');
	y = 0;
	while (name && envp_i[y])
	{
		if (envp_i[y] == '=')
		{
			value = return_value(name, value, y, envp_i);
			break ;
		}
		y++;
	}
	add_cell_env(our_env, name, value);
}

t_env	*parse_environnement(char **envp, t_env *our_env)
{
	int	i;

	i = 0;
	if (!*envp)
		env_i(&our_env);
	else
	{
		while (envp[i])
		{
			handle_env_variable(envp[i], &our_env);
			i++;
		}
	}
	return (our_env);
}

t_env	*increment_shlvl(t_env *our_env)
{
	t_env	*current;
	int		shlvl;
	char	*shlvl_str;

	current = our_env;
	while (current)
	{
		if (ft_strcmp(current->name, "SHLVL") == 0)
		{
			shlvl = ft_atoi(current->value);
			shlvl++;
			shlvl_str = ft_itoa(shlvl);
			current->value = free_ptr(current->value);
			current->value = shlvl_str;
			break ;
		}
		current = current->next;
	}
	return (our_env);
}
