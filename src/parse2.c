/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:47:10 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/11 17:35:49 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char				*ft_name(char *str)
{
	int				i;
	char			*s;

	i = -1;
	while (str[++i] && str[i] != ' ')
		;
	if ((s = (char*)malloc(sizeof(*s) * i + 1)) == 0)
		exit(0);
	i = -1;
	while (str[++i] && str[i] != ' ')
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}

unsigned long		hash(unsigned char *str)
{
	unsigned long	hash;
	int				c;
	int				i;

	hash = 012405;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '-' && str[i] != '\n')
	{
		c = str[i];
		hash = ((hash << 5) + hash) + c;
		i++;
	}
	return (hash);
}

int					ft_index(t_lem *lem, unsigned long hash)
{
	size_t			i;

	i = 0;
	while (i < lem->nbr_salles)
	{
		if (hash == lem->hash[i])
			return (i);
		i++;
	}
	return (-1);
}

int					ft_verif(t_ptr_couloir *list, int prem,
	int deux, t_lem *lem)
{
	t_ptr_couloir	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->element->salle_1 == deux || tmp->element->salle_2 == deux)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char				*ft_strjoin2(char const *s1, char const *s2)
{
	size_t			i;
	size_t			k;
	size_t			len_dst;
	size_t			len_src;
	char			*str;

	if (!s1 || !s2)
		return (NULL);
	len_dst = ft_strlen(s1);
	len_src = ft_strlen(s2);
	if ((str = (char*)malloc(sizeof(*str) * (len_src + len_dst + 1))) == 0)
		exit(0);
	i = 0;
	k = 0;
	while (i < (len_src + len_dst))
	{
		if (i < (len_dst))
			str[i] = ((char*)s1)[i];
		else
			str[i] = ((char*)s2)[k++];
		i++;
	}
	str[i] = '\0';
	return (str);
}
