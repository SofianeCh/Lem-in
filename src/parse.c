/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:00:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/06 14:33:16 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ft_check_names(char *line, char *name)
{
	int i;

	i = 0;
	if (!line || !name)
		return (0);
	while (line[i] && line[i] != '-' && line[i] != '\n')
	{
		if (line[i] != name[i])
			return (0);
		i++;
	}
	if (name[i])
		return (0);
	return (1);
}

char			*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	len_dst;
	size_t	len_src;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_dst = ft_strlen(s1);
	len_src = ft_strlen(s2);
	if ((str = (char*)malloc(sizeof(*str) * (len_src + len_dst + 1))) == 0)
		return (NULL);
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

char			*ft_strdup2(const char *s, t_lem *lem)
{
	int		i;
	int min;
	char	*str;

	i = -1;
	while (!ft_isdigit((int)s[++i]))
	{
		while (s[i] != '\n')
			i++;
	}
	min = i;
	lem->fourmis = ft_atoi(s + i);
	i = ft_strlen(s);
	if ((str = (char*)malloc(sizeof(*str) * i + 1)) == 0)
		return (!(lem->probleme = 1) ? NULL : 0);
	i = min;
	while (s[++i])
	{
		str[i] = s[i];
		s[i] == '-' ? lem->couloirs++ : 0;
		if (s[i] == '#')
		{
			if (s[i + 1] && s[i + 1] == '#' && s[i + 2])
			{
				if (ft_check_names((char*)(s + i + 2), "start"))
					!lem->pos_start ? lem->pos_start++ : lem->probleme++;
				if (ft_check_names((char*)(s + i + 2), "end"))
					!lem->pos_end ? lem->pos_end++ : lem->probleme++;
				lem->dieze++;
			}
			else if (!lem->dieze)
				lem->dieze = 2;
		}
		if (i > min && s[i] == '\n' && !lem->couloirs)
		{
			lem->index[lem->lignes] = i + 1;
			(lem->dieze && lem->pos_start == 1) ? (lem->pos_start = i + 1) : 0;
			(lem->dieze && lem->pos_end == 1) ? (lem->pos_end = i + 1) : 0;
			lem->dieze == 2 ? lem->comm++ : 0;
			lem->lignes++;
			lem->dieze = 0;
		}
	}
	lem->nbr_salles = lem->lignes - 3 - lem->comm;
	str[i] = '\0';
	return (str);
}

void			ft_read_map(t_lem *lem)
{
	lem->b_size = 5000000;
	lem->buff = ft_strnew(lem->b_size - 1);
	while ((lem->ret = read(0, lem->buff, lem->b_size)) > 0)
	{
		ft_putendl(lem->buff);
		lem->len += lem->ret;
		lem->b_size *= 2;
		lem->tmp = lem->line;
		lem->line = !lem->line ? ft_strdup(lem->buff) :
		ft_strjoin2(lem->line, lem->buff);
		ft_cln(&lem->tmp, &lem->buff, NULL);
		lem->buff = ft_strnew(lem->b_size - 1);
	}
	lem->tmp = lem->line;
	lem->line = ft_strdup2(lem->line, lem);
	ft_cln(&lem->tmp, &lem->buff, NULL);
}
