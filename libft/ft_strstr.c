/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 13:18:52 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 21:11:39 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		b;
	char	*str;

	i = 0;
	b = 0;
	str = (char*)haystack;
	if (ft_strlen(needle) == 0)
		return (str);
	while (str[i])
	{
		while (str[i + b] == needle[b])
		{
			if (needle[b + 1] == '\0')
				return (str + i);
			b++;
		}
		b = 0;
		i++;
	}
	return (0);
}
