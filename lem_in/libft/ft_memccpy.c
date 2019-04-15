/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:53:23 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/07 23:29:12 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*redst;
	char	*resrc;

	i = 0;
	redst = (char*)dst;
	resrc = (char*)src;
	while (i < n)
	{
		redst[i] = resrc[i];
		if ((unsigned char)resrc[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
