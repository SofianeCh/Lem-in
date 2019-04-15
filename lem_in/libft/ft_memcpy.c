/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:28:03 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/04 16:47:45 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*redst;
	const char	*resrc;

	redst = (char *)dst;
	resrc = (const char*)src;
	i = 0;
	while (i < n)
	{
		redst[i] = resrc[i];
		i++;
	}
	return (redst);
}
