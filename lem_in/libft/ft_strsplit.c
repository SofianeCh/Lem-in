/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:13:27 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 21:33:57 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_filltab(char **tab, char c, size_t k, char const *s)
{
	size_t	b;
	size_t	i;

	i = 0;
	while (s[i])
	{
		b = 0;
		if (s[i] == c)
			i++;
		else
		{
			if ((tab[k] = (char*)malloc(sizeof(char) *
				(ft_lengtword((char*)s, i, c) + 1))) == 0)
			{
				ft_strdel(tab);
				return (NULL);
			}
			while (s[i] && s[i] != c)
				tab[k][b++] = s[i++];
			tab[k++][b] = '\0';
		}
	}
	tab[k] = 0;
	return (tab);
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	k;
	char	**tab;

	i = 0;
	k = 0;
	if (!s)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(char*) * (ft_word((char*)s, c) + 1))) == 0)
		return (NULL);
	tab = ft_filltab(tab, c, k, s);
	return (tab);
}
