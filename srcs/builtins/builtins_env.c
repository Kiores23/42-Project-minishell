/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:28:26 by amery             #+#    #+#             */
/*   Updated: 2023/04/22 21:51:40 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

int	ft_lstlen(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		if (lst->next == NULL)
			return (i);
		lst = lst->next;
	}
	return (i);
}

void	free_double(t_env **lst)
{
	if ((*lst)->name)
		free ((*lst)->name);
	(*lst)->name = NULL;
	if ((*lst)->value)
		free ((*lst)->value);
	(*lst)->value = NULL;
}

void	*free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	free_at(t_env **lst, int pos)
{
	t_env	*prec;
	t_env	*cur;
	int		i;

	prec = *lst;
	cur = *lst;
	i = 0;
	if (ft_lstlen(*lst) == 0)
		return ;
	if (pos == 0)
	{
		*lst = (*lst)->next;
		cur = free_cur(cur);
		return ;
	}
	while (i++ < pos && cur->next)
	{
		prec = cur;
		cur = cur->next;
	}
	prec->next = cur->next;
	cur = free_cur(cur);
	return ;
}

int	unset_env_var(t_env **lst_ptr, char **names)
{
	t_unset	unset_vars;

	init_var_unset(&unset_vars, lst_ptr);
	if (!lst_ptr || !*lst_ptr || !names)
		return (1);
	while (names[++unset_vars.i])
	{
		unset_vars.pos = -1;
		if (ft_strcmp(names[unset_vars.i], "_") == 0)
			;
		else if (print_unset_message(names[unset_vars.i]))
			unset_vars.r = 1;
		else
		{
			while (unset_vars.lst && ++unset_vars.pos >= 0)
			{
				if (ft_strcmp(unset_vars.lst->name, names[unset_vars.i]) == 0)
					free_at(lst_ptr, unset_vars.pos);
				unset_vars.lst = unset_vars.lst->next;
			}
		}
		unset_vars.lst = *lst_ptr;
	}
	return (unset_vars.r);
}
