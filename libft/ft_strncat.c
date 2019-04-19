/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:32:44 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/09 14:15:32 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (dst[i])
		i++;
	while (src[len] && len < n)
	{
		dst[i] = src[len];
		i++;
		len++;
	}
	dst[i] = '\0';
	return (dst);
}
