/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:15:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/11 17:42:16 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int					ft_solve_path(t_lem *lem)
{
	t_solve			s;
	int				i;
	int				stop;
	int				max_way;

	ft_bzero(&s, sizeof(s));
	s.p = -1;
	i = -1;
	ft_init_queue(lem, &s);
	max_way = (s.start > s.end) ? s.start : s.end;
	if (!(lem->paths = (t_path**)ft_memalloc(sizeof(t_path*) * (max_way))))
		exit(0);
	while (++i < max_way && i < lem->fourmis)
	{
		ft_bfs(lem, &s, i);
		if (lem->stop)
			break ;
		stop = ft_calcul_etapes(lem, i + 1);
		if (stop)
			break ;
		ft_reset_rooms(lem, &s);
		ft_modify_directions(lem, i) ? ft_merge(lem, i, nbr_merge(lem) / 2) : 0;
		s.count++;
	}
	return (s.count);
}

void				move_fourmis(t_lem *lem, int chemin)
{
	int				len_chemin;

	len_chemin = lem->paths[chemin]->size;
	while (--len_chemin)
	{
		if (len_chemin > 1 &&
			lem->salles[lem->paths[chemin]->path[len_chemin - 1]]->fourmis)
		{
			lem->salles[lem->paths[chemin]->path[len_chemin]]->fourmis =
			lem->salles[lem->paths[chemin]->path[len_chemin - 1]]->fourmis;
			lem->salles[lem->paths[chemin]->path[len_chemin - 1]]->fourmis = 0;
		}
		if (len_chemin == lem->paths[chemin]->size - 1 &&
			lem->salles[lem->paths[chemin]->path[len_chemin]]->fourmis ==
			lem->salles[lem->paths[chemin]->path[0]]->fourmis &&
			lem->salles[lem->paths[chemin]->path[len_chemin]]->end)
		{
			lem->last_ant = 1;
		}
	}
}

void				go_fourmis(t_lem *lem, int chemin)
{
	int				len_chemin;
	int				i;

	len_chemin = 0;
	move_fourmis(lem, chemin);
	if (lem->fourmis)
	{
		lem->salles[lem->paths[chemin]->path[len_chemin + 1]]->fourmis =
		lem->ant;
		lem->ant++;
		lem->fourmis--;
	}
	i = 1;
	while (i < lem->paths[chemin]->size)
	{
		if (lem->salles[lem->paths[chemin]->path[i]]->fourmis)
		{
			write(1, "L", 1);
			ft_putnbr(lem->salles[lem->paths[chemin]->path[i]]->fourmis);
			write(1, "-", 1);
			ft_putstr(lem->salles[lem->paths[chemin]->path[i]]->name);
			write(1, " ", 1);
		}
		i++;
	}
}

int					nbr_merge(t_lem *lem)
{
	int				i;
	int				count;
	t_ptr_couloir	*tmp;

	i = 0;
	count = 0;
	while (i < lem->nbr_salles)
	{
		tmp = lem->salles[i]->couloirs;
		while (tmp)
		{
			if (tmp->element->dir_salle1 && tmp->element->dir_salle2)
				count++;
			tmp = tmp->next;
		}
		i++;
	}
	return (count);
}
