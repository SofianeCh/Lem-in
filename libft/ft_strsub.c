/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:01:37 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 22:22:49 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if ((str = (char*)malloc(sizeof(*str) * (len + 1))) == 0)
		return (NULL);
	while (i < len)
	{
		str[i] = ((char*)s)[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
