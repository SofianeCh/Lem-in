/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:00:32 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 02:31:51 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*str;
	size_t	i;
	size_t	taille;

	taille = size;
	i = 1;
	str = NULL;
	while (taille > '9')
	{
		taille = taille / 10;
		i++;
		if (i == 19)
			return (NULL);
	}
	if ((str = (char*)malloc(sizeof(*str) * size + 1)) == 0)
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
