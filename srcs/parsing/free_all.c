/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:37:04 by amery             #+#    #+#             */
/*   Updated: 2023/04/19 15:09:08 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h"

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		array[i] = free_ptr(array[i]);
		i++;
	}
	array = free_ptr(array);
}

void	free_stack(t_stack *lst)
{
	t_stack	*tmp;

	while (lst)
	{
		tmp = lst->next;
		freelist_redi(lst->in);
		freelist_redi(lst->out);
		free_char_array(lst->cmd_final);
		lst->cmd_sep = free_ptr(lst->cmd_sep);
		lst = free_ptr(lst);
		lst = tmp;
	}
}
