/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_envrionnement_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatteau <fcatteau@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 04:49:41 by amery             #+#    #+#             */
/*   Updated: 2023/04/19 14:29:10 by fcatteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../Includes/minishell.h" 

char	*ft_strncpy_until_char(char *src, char delimiter)
{
	size_t	len;
	char	*dst;

	dst = NULL;
	len = 0;
	while (src[len] && src[len] != delimiter)
		len++;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	len = 0;
	while (src[len] && src[len] != delimiter)
	{
		dst[len] = src[len];
		len++;
	}
	dst[len] = '\0';
	return (dst);
}
