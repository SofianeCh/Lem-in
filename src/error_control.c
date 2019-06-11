/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:48:13 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/11 18:01:47 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	checker(t_lem *lem, const char *s, int i, int min)
{
	if (s[i] == '#')
	{
		if (s[i + 1] && s[i + 1] == '#' && s[i + 2])
		{
			if (ft_check_names((char*)(s + i + 2), "start"))
				!lem->pos_start ? lem->pos_start++ : probleme(0);
			if (ft_check_names((char*)(s + i + 2), "end"))
				!lem->pos_end ? lem->pos_end++ : probleme(0);
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

void	check_salle_crd(t_lem *lem, int i)
{
	int	crd_x;
	int	crd_y;
	int	p;

	p = 0;
	crd_x = 0;
	crd_y = 0;
	while (lem->line[lem->index[i] + p] != ' ')
		p++;
	while (ft_isdigit((int)lem->line[lem->index[i] + p + 1]))
	{
		if (ft_atoi(lem->line + (lem->index[i] + p + 1)) == -1)
			probleme(0);
		p++;
		crd_x = 1;
	}
	while (ft_isdigit((int)lem->line[lem->index[i] + p + 2]))
	{
		if (ft_atoi(lem->line + (lem->index[i] + p + 2)) == -1)
			probleme(0);
		p++;
		crd_y = 1;
	}
	if (!(lem->line[lem->index[i] + p + 2] == '\n') || !crd_x || !crd_y)
		probleme(0);
}

void	check_coord(t_lem *lem)
{
	int	i;
	int	salles;

	i = 0;
	salles = lem->nbr_salles;
	while (i < salles)
	{
		if (lem->line[lem->index[i]] != '#')
			check_salle_crd(lem, i);
		else
			salles++;
		i++;
	}
}

void	map_checker(t_lem *lem, const char *s)
{
	int	i;
	int	ok;
	int	ants;

	i = -1;
	ok = 0;
	ants = 0;
	check_coord(lem);
	if (!lem->pos_start || !lem->pos_end || !lem->ant ||
		s[lem->pos_start] == '#' || s[lem->pos_end] == '#')
		probleme(0);
	while (s[++i])
	{
		if ((s[i - 1] && s[i - 1] == '\n') || (i == 0 && ft_isdigit((int)s[i])))
			if (ft_isdigit((int)s[i]) && s[i + ft_intlen(ft_atoi(s + i))]
			== '\n')
				ants++;
		if ((s[i] == '\n' && s[i + 1] == '\n') ||
		(s[i] == '\n' && s[i + 1] == 'L'))
			probleme(0);
		if (s[i] == '-')
			ok++;
	}
	if (!ok || ants != 1)
		probleme(0);
}

void	map_checker2(t_lem *lem)
{
	int i;

	i = 0;
	while (i < lem->nbr_salles)
	{
		if (lem->salles[i]->end)
		{
			if (!lem->salles[i]->nbr_voisin)
				probleme(0);
		}
		i++;
	}
}
