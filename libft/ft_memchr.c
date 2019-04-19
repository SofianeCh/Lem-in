/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:16:54 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/07 17:15:10 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*redst;

	i = 0;
	redst = (unsigned char*)s;
	while (i < n)
	{
		if (redst[i] == (unsigned char)c)
			return (redst + i);
		i++;
	}
	return (0);
}
