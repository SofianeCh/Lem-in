/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 20:34:04 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/08 20:09:46 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (len == 0)
		return (dst);
	if ((unsigned char)dst <= (unsigned char)src)
		ft_memcpy(dst, src, len);
	else
		while (len > 0)
		{
			len--;
			((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
		}
	return (dst);
}
