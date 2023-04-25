/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amery <amery@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:33:55 by amery             #+#    #+#             */
/*   Updated: 2023/04/20 14:47:01 by amery            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*replace_env_variables_heardoc(char *str, t_env **ourenv)
{
	int				i;
	char			*new_str;
	t_quote_flags	quotes;

	init_variables(&quotes, ourenv);
	new_str = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			new_str = handle_dollar_question_mark(new_str, &i);
		else if (str[i] == '$' && str[i + 1] && (str[i + 1] != ' '
				|| str[i + 1] != '\t'))
			new_str = handle_dollar_variable(str, &i, &quotes, new_str);
		else
			new_str = ft_strjoin_char(new_str, str[i]);
		i++;
	}
	str = free_ptr(str);
	return (new_str);
}
