/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:35:06 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:14:14 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*get_home_path(t_env *env)
{
	char	*home;

	while (env)
	{
		if (!ft_strcmp(env->name, "HOME"))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	home = ft_strdup(env->value);
	return (home);
}

char	*get_new_pwd(char *arg, char *pwd, t_env *env)
{
	char	*path;

	if (!arg || arg[0] != '-' || arg[1])
		get_last_path(pwd, 0);
	if (!arg || !arg[0])
		path = get_home_path(env);
	else if (arg[0] == '-' && !arg[1])
		path = get_last_path(NULL, 1);
	else if (arg[0] != '/')
	{
		path = ft_strjoin(pwd, "/");
		path = ft_strjoin(path, arg);
		return (path);
	}
	else
		path = ft_strdup(arg);
	pwd = free_ptr(pwd);
	return (path);
}

void	change_pwd(t_env *env, char *pwd)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
			break ;
		env = env->next;
	}
	if (!env)
		return ;
	env->value = free_ptr(env->value);
	env->value = ft_strdup(pwd);
}

void	change_old_pwd(t_env *env, char *pwd)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "OLDPWD"))
			break ;
		env = env->next;
	}
	if (!env)
		return ;
	if (env->value)
		free(env->value);
	env->value = ft_strdup(pwd);
}

int	changedirectory(char **argv, t_env *env)
{
	char	*pwd;
	char	*old_pwd;
	int		r;

	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	pwd = return_to_the_old(pwd, 0);
	old_pwd = ft_strdup(pwd);
	pwd = get_new_pwd(argv[1], pwd, env);
	r = chdir(pwd);
	pwd = free_ptr(pwd);
	pwd = getcwd(pwd, sizeof(pwd));
	pwd = return_to_the_old(pwd, 0);
	if (pwd && ft_strcmp(pwd, old_pwd))
	{
		change_old_pwd(env, old_pwd);
		change_pwd(env, pwd);
	}
	pwd = free_ptr(pwd);
	old_pwd = free_ptr(old_pwd);
	ft_pwd(NULL, 1);
	if (r == -1)
		return (return_error("cd", argv[1], strerror(errno), 1));
	return (0);
}
