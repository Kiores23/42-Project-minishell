/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_print_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:27:13 by amery             #+#    #+#             */
/*   Updated: 2023/04/19 14:46:22 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

t_env	*ft_lst_cpy(t_env *lst)
{
	t_env	*curr;
	t_env	*new;
	char	*value;

	new = NULL;
	curr = lst;
	while (curr)
	{
		value = NULL;
		if (curr->value)
		{
			value = ft_strdup(curr->value);
			if (!value)
			{
				freelist_env(new);
				return (NULL);
			}
		}
		add_cell_env(&new, ft_strdup(curr->name), value);
		curr = curr->next;
	}
	return (new);
}

t_env	*sorted_list(t_env **our_env)
{
	t_env		*tmp;
	t_env		*head;
	char		*name_tmp;
	char		*value_tmp;

	tmp = ft_lst_cpy(*our_env);
	head = tmp;
	while (tmp && tmp->next)
	{
		if (strcmp(tmp->name, tmp->next->name) > 0)
		{
			name_tmp = tmp->name;
			value_tmp = tmp->value;
			tmp->name = tmp->next->name;
			tmp->value = tmp->next->value;
			tmp->next->name = name_tmp;
			tmp->next->value = value_tmp;
			tmp = head;
		}
		else
			tmp = tmp->next;
	}
	tmp = head;
	return (tmp);
}

int	print_export(t_env **our_env)
{
	t_env	*cpy;
	t_env	*head;

	cpy = sorted_list(our_env);
	head = cpy;
	while (cpy)
	{
		if (cpy->value != NULL)
			printf("declare -x %s=\"%s\"\n", cpy->name, cpy->value);
		else
			printf("declare -x %s\n", cpy->name);
		cpy = cpy->next;
	}
	freelist_env(head);
	return (0);
}
