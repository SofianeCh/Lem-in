/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 15:19:49 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 22:42:14 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	b;
	char	*str;

	i = 0;
	str = (char*)haystack;
	if (len == 0)
		return (NULL);
	if (ft_strlen(needle) == 0 || needle == NULL)
		return (str);
	while (haystack[i] && i < len)
	{
		b = 0;
		while (((char*)haystack)[i + b] == ((char*)needle)[b] && (i + b) < len)
		{
			if (needle[b + 1] == '\0')
				return (str + i);
			b++;
		}
		i++;
	}
	return (NULL);
}
