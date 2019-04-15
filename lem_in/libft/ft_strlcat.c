/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:47:30 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 02:45:50 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	dst_sz;
	size_t	src_sz;

	i = 0;
	len = ft_strlen(dst);
	src_sz = ft_strlen(src);
	if (size < len)
		return (src_sz + size);
	dst_sz = len;
	while (src[i] && (size - 1) > len)
		dst[len++] = src[i++];
	dst[len] = '\0';
	len = dst_sz + src_sz;
	return (len);
}
