/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:15:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/08 16:08:20 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				ft_solve_path(t_lem *lem)
{
	t_solve		s;
	int			i;
	int			merge;
	int			stop;
	int			max_way;

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
		merge = ft_modify_directions(lem, i);
		// ft_printf("merge needed = %d\n", merge);
		if (merge)
		{
			// printf("nbr de merge %d\n", ft_nbr_merge(lem) / 2);
			ft_merge(lem, i, ft_nbr_merge(lem) / 2);
		}
		s.count++;
	}
	return (s.count);
}

void				go_fourmis(t_lem *lem, int chemin)
{
	int 			len_chemin;

	len_chemin = lem->paths[chemin]->size;
	while (--len_chemin)
	{
		if (len_chemin > 1 && lem->salles[lem->paths[chemin]->path[len_chemin - 1]]->fourmis)
		{
			lem->salles[lem->paths[chemin]->path[len_chemin]]->fourmis = lem->salles[lem->paths[chemin]->path[len_chemin - 1]]->fourmis;
			lem->salles[lem->paths[chemin]->path[len_chemin - 1]]->fourmis = 0;
		}
		if (len_chemin == lem->paths[chemin]->size - 1 && lem->salles[lem->paths[chemin]->path[len_chemin]]->fourmis == lem->salles[lem->paths[chemin]->path[0]]->fourmis && lem->salles[lem->paths[chemin]->path[len_chemin]]->end)
		{
			lem->last_ant = 1;
		}
	}
	if (lem->fourmis)
	{
		lem->salles[lem->paths[chemin]->path[len_chemin + 1]]->fourmis = lem->ant;
		lem->ant++;
		lem->fourmis--;
	}
	int i = 1;
	while (i < lem->paths[chemin]->size)
	{
		// printf("%d\n", lem->salles[lem->paths[chemin]->path[i]]->fourmis);
		if (lem->salles[lem->paths[chemin]->path[i]]->fourmis)
		{
			// printf("L%d-%s chemin=%d, salles=%d    ",lem->salles[lem->paths[chemin]->path[i]]->fourmis, lem->salles[lem->paths[chemin]->path[i]]->name, chemin, i);
			printf("L%d-%s ",lem->salles[lem->paths[chemin]->path[i]]->fourmis, lem->salles[lem->paths[chemin]->path[i]]->name);
		}
		i++;
	}
}

int					ft_nbr_merge(t_lem *lem)
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
