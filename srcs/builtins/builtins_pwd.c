/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:15:47 by amery             #+#    #+#             */
/*   Updated: 2023/04/19 15:44:18 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

int	ft_pwd(char **argv, int infun)
{
	static char	*thx_pwd;
	char		*pwd;

	if (infun == 1)
	{
		pwd = NULL;
		pwd = getcwd(pwd, sizeof(pwd));
		if (pwd && !free_ptr(thx_pwd))
			thx_pwd = pwd;
		return (0);
	}
	if (infun == 2)
	{
		thx_pwd = free_ptr(thx_pwd);
		return (0);
	}
	if (argv && argv[0] && argv[1])
		return (return_error("pwd", argv[1], "arguments", 1));
	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	if (!pwd)
		return (printf("%s\n", thx_pwd) * 0);
	printf("%s\n", pwd);
	pwd = free_ptr(pwd);
	return (0);
}
