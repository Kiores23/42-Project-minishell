/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:15:58 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 11:40:08 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_paths(char **paths)
{
	int	i;

	i = -1;
	while (paths && paths[++i])
	{
		paths[i] = free_ptr(paths[i]);
	}
	paths = free_ptr(paths);
}

char	*get_path(char **tmp, char *cmd)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (tmp[++i] && cmd)
	{
		tmp[i] = ft_strjoin(tmp[i], "/");
		tmp[i] = ft_strjoin(tmp[i], cmd);
		if (!access(tmp[i], F_OK | X_OK))
			break ;
	}
	if (tmp[i] && cmd)
		path = ft_strdup(tmp[i]);
	return (path);
}

char	*get_pwd_path(char *cmd)
{
	char	*path;

	path = NULL;
	if (cmd[0] != '/')
	{
		path = getcwd(path, sizeof(path));
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, cmd);
	}
	else if (cmd[0] == '/')
		path = ft_strdup(cmd);
	if (path && !access(path, F_OK | X_OK))
		return (path);
	path = free_ptr(path);
	return (ft_strdup(""));
}

char	*get_bin_path(char **enpv, char *cmd)
{
	char	**tmp;
	char	*path;
	int		i;

	tmp = NULL;
	if (cmd && cmd[0] == '/')
		return (get_pwd_path(cmd));
	if (cmd && cmd[0] != '/' && ft_strchr(cmd, '/'))
		return (get_pwd_path(cmd));
	i = -1;
	while (enpv[++i] && ft_strncmp(enpv[i], "PATH=", 5))
		;
	if (!enpv[i])
		return (ft_strdup(""));
	if (ft_strlen(enpv[i]) >= 5)
		tmp = ft_split(enpv[i] + 5, ':');
	path = get_path(tmp, cmd);
	i = -1;
	while (tmp && tmp[++i])
		tmp[i] = free_ptr(tmp[i]);
	tmp = free_ptr(tmp);
	if (path)
		return (path);
	return (ft_strdup(""));
}

char	**all_paths(t_stack *s, t_exe *e)
{
	t_stack	*first_cmd;
	char	**paths;
	int		i;

	first_cmd = s;
	i = 0;
	while (++i && s->next)
		s = s->next;
	paths = malloc(sizeof(char *) * (i + 1));
	if (!paths)
		return (paths + return_error("malloc", NULL, strerror(errno), 0));
	paths[i] = NULL;
	i = -1;
	s = first_cmd;
	while (++i >= 0 && s)
	{
		paths[i] = get_bin_path(e->envp, s->cmd_final[0]);
		s = s->next;
	}
	return (paths);
}
