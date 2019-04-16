/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:17:57 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/08 15:21:01 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	*str;
	char	*str1;

	str = (char*)s1;
	str1 = (char*)s2;
	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)str[i] - (unsigned char)str1[i]);
		i++;
	}
	if (s2[i] && i < n)
		return ((unsigned char)str[i] - (unsigned char)str1[i]);
	return (0);
}
