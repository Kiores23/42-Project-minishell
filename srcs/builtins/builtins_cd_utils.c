/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:22:25 by amery             #+#    #+#             */
/*   Updated: 2023/04/24 18:53:03 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*return_to_the_old(char *pwd, int free)
{
	static char	*pwd2 = NULL;
	char		*tmp;

	if (free == 1)
		return (free_ptr(pwd2));
	if (pwd)
	{
		pwd2 = free_ptr(pwd2);
		pwd2 = ft_strdup(pwd);
		return (pwd);
	}
	if (!access(pwd2, R_OK | X_OK))
		return (ft_strdup(pwd2));
	pwd = ft_strdup(pwd2);
	tmp = pwd;
	while (ft_strchr(tmp, '/'))
		tmp = ft_strchr(tmp, '/') + 1;
	pwd2 = free_ptr(pwd2);
	pwd2 = ft_substr(pwd, 0, (size_t)tmp - (size_t)pwd - 1);
	pwd = free_ptr(pwd);
	if (!pwd2)
		return (ft_strdup(""));
	return (return_to_the_old(NULL, 0));
}

char	*get_last_path(char *pwd, int act)
{
	static char	*last_path = NULL;

	if (act == 0)
	{
		last_path = free_ptr(last_path);
		last_path = ft_strdup(pwd);
		return (NULL);
	}
	else if (act == 1)
	{
		if (*last_path)
			printf("%s\n", last_path);
		return (ft_strdup(last_path));
	}
	else if (act == 2)
		return (free_ptr(last_path));
	return (NULL);
}
