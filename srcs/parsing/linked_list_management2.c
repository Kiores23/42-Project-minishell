/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_management2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:49:14 by amery             #+#    #+#             */
/*   Updated: 2023/04/19 17:35:12 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	init_tstack(t_stack *new_cell)
{
	new_cell->next = NULL;
	new_cell->prec = NULL;
	new_cell->cmd_final = NULL;
	new_cell->in = NULL;
	new_cell->out = NULL;
}

void	add_cell_tstack(t_stack **list, char *cmd_sep)
{
	t_stack	*new_cell;
	t_stack	*current;
	t_stack	*prev;

	new_cell = malloc (sizeof (t_stack));
	if (!new_cell)
		return ;
	init_tstack(new_cell);
	new_cell->cmd_sep = cmd_sep;
	if (!(*list))
		*list = new_cell;
	else
	{
		current = *list;
		prev = NULL;
		while (current)
		{
			prev = current;
			current = current->next;
		}
		prev->next = new_cell;
		new_cell->prec = prev;
	}
}

void	init_redi(t_file *new_cell, int i, char *str, int order)
{
	if (i == 0)
	{
		new_cell->simple = str;
		new_cell->doubles = NULL;
		new_cell->order = order;
	}
	else
	{
		new_cell->simple = NULL;
		new_cell->doubles = str;
		new_cell->order = order;
	}
	new_cell->next = NULL;
	new_cell->prev = NULL;
}

void	add_cell_redirections(t_file **list, char *str, int i, int order)
{
	t_file	*new_cell;
	t_file	*current;
	t_file	*prev;

	if (!*str)
		return ((void)free_ptr(str));
	new_cell = malloc(sizeof(t_file));
	if (!new_cell)
		return ;
	init_redi(new_cell, i, str, order);
	if (!(*list))
		*list = new_cell;
	else
	{
		current = *list;
		prev = NULL;
		while (current)
		{
			prev = current;
			current = current->next;
		}
		prev->next = new_cell;
		new_cell->prev = prev;
	}
}

void	add_cell_env(t_env **list_env, char *name, char *value)
{
	t_env	*new_cell;
	t_env	*current;
	t_env	*prev;

	if (!*name)
		return ((void)free_ptr(name));
	new_cell = malloc(sizeof(t_env));
	if (!new_cell)
		return ;
	new_cell->name = name;
	new_cell->value = value;
	new_cell->next = NULL;
	if (!(*list_env))
		*list_env = new_cell;
	else
	{
		current = *list_env;
		prev = NULL;
		while (current)
		{
			prev = current;
			current = current->next;
		}
		prev->next = new_cell;
	}
}
