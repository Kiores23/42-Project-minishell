/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:49:03 by amery             #+#    #+#             */
/*   Updated: 2023/04/25 12:45:37 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	freelist(t_stack *stack)
{
	t_stack	*tmp;

	tmp = NULL;
	while (stack)
	{
		tmp = stack->next;
		stack = free_ptr(stack);
		stack = tmp;
	}
}

void	freelist_env(t_env *stack)
{
	t_env	*tmp;

	while (stack)
	{
		tmp = stack->next;
		stack->name = free_ptr(stack->name);
		stack->value = free_ptr(stack->value);
		stack = free_ptr(stack);
		stack = tmp;
	}
}

void	freelist_redi(t_file *stack)
{
	t_file	*tmp;

	tmp = NULL;
	while (stack)
	{
		tmp = stack->next;
		stack->simple = free_ptr(stack->simple);
		stack->doubles = free_ptr(stack->doubles);
		stack = free_ptr(stack);
		stack = tmp;
	}
}

// void	print_list(t_stack **lst_ptr)
// {
// 	int i;
// 	int ite_tab;
// 	t_file *temp_in;
// 	t_file *temp_out;
// 	t_stack *current;

// 	current = NULL;
// 	current = *lst_ptr;
// 	i = 0;
// 	ite_tab = 0;
// 	while (current)
// 	{
// 		printf("\e[1;32m==================================================\n");
// 		printf("================ CELL NUMBER [%d] =================\n", i);
// 		printf("==================================================\n");
// 		printf("|| Cell content is -> %s\n", current->cmd_sep);
// 		printf("|| Cell final parsing is belong\n");
// 		while (current->cmd_final && current->cmd_final[ite_tab] != 0)
// 		{
// 			printf("||  Tab[%d] -> %s\n", ite_tab, current->cmd_final[ite_tab]);
// 			ite_tab++;
// 		}
// 		ite_tab = 0;
// 		printf("||\n");
// 		printf("|| Voici les redirections;\n\n");
// 		temp_in = current->in;
// 		printf("-------------------------------------------\n");
// 		printf("redirection infiles ;\n");
// 		while (temp_in)
// 		{
// 			printf("les redirections simple ; %s\n", temp_in->simple);
// 			printf("les redirections doubles ; %s\n", temp_in->doubles);
// 			printf("order ; %d\n", temp_in->order);

// 			temp_in = temp_in->next;
// 		}
// 		printf("-------------------------------------------\n");
// 		temp_out = current->out;
// 		printf("\n");
// 		printf("-------------------------------------------\n");
// 		printf("redirection outfile ;\n");
// 		while (temp_out)
// 		{
// 			printf("les redirections simple ; %s\n", temp_out->simple);
// 			printf("les redirections doubles ; %s\n", temp_out->doubles);
// 			temp_out = temp_out->next;
// 		}
// 		printf("-------------------------------------------\n");
// 		printf("==================================================\n");
// 		printf("==================================================\n");
// 		printf("==================================================\e[0m\n\n\n");
// 		current = current->next;
// 		i++;
// 	}
// }
