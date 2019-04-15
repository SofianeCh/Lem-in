/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 19:12:49 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/04 13:07:09 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*fill;

	i = 0;
	fill = (unsigned char*)b;
	while (i < len)
	{
		fill[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
