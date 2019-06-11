/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:00:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/11 17:34:15 by sofchami         ###   ########.fr       */
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

int				beg_comment(const char *s, t_lem *lem)
{
	int			len;
	int			i;

	i = -1;
	len = ft_strlen(s);
	while (!ft_isdigit((int)s[++i]))
	{
		if (s[i] == '#' && s[i + 1] && s[i + 1] == '#' && s[i + 2])
			if (ft_check_names((char*)(s + i + 2), "start"))
				probleme(0);
		while (s[i] != '\n')
		{
			i++;
			if (i > len)
				probleme(0);
		}
	}
	return (i);
}

char			*ft_strdup2(const char *s, t_lem *lem)
{
	int			i;
	int			min;
	char		*str;

	i = beg_comment(s, lem);
	min = i;
	lem->fourmis = ft_atoi(s + i);
	i = ft_strlen(s);
	if ((str = (char*)malloc(sizeof(*str) * i + 1)) == 0)
		exit(0);
	i = min;
	while (s[++i])
	{
		str[i] = s[i];
		s[i] == '-' ? lem->couloirs++ : 0;
		checker(lem, s, i, min);
	}
	lem->nbr_salles = lem->lignes - 3 - lem->comm;
	str[i] = '\0';
	map_checker(lem, s);
	lem->print = min + ft_intlen(lem->fourmis) + 1;
	return (str);
}

void			ft_read_map(t_lem *lem)
{
	lem->ant = 1;
	lem->b_size = 5000000;
	if (!(lem->buff = ft_strnew(lem->b_size - 1)))
		exit(1);
	while ((lem->ret = read(0, lem->buff, lem->b_size)) > 0)
	{
		lem->len += lem->ret;
		lem->b_size *= 2;
		lem->tmp = lem->line;
		lem->line = !lem->line ? ft_strdup(lem->buff) :
		ft_strjoin2(lem->line, lem->buff);
		ft_cln(&lem->tmp, &lem->buff, NULL);
		lem->buff = ft_strnew(lem->b_size - 1);
	}
	!lem->line ? probleme(0) : 0;
	lem->tmp = lem->line;
	lem->line = ft_strdup2(lem->line, lem);
	ft_cln(&lem->tmp, &lem->buff, NULL);
}

void			ft_cln(char **line, char **line2, char **line3)
{
	line ? ft_strdel(line) : 0;
	line2 ? ft_strdel(line2) : 0;
	line3 ? ft_strdel(line3) : 0;
}
