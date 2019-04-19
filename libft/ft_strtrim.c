/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:47:40 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 02:07:19 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		k;
	int		len;
	char	*str;
	int		taille;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	len--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while ((s[len] == ' ' || s[len] == '\n' || s[len] == '\t') && len > 0)
		len--;
	taille = len - i + 1;
	k = 0;
	if (len == 0)
		taille = 0;
	if ((str = (char*)malloc(sizeof(*str) * (taille + 1))) == 0)
		return (NULL);
	while (taille-- > 0)
		str[k++] = ((char*)s)[i++];
	str[k] = '\0';
	return (str);
}
