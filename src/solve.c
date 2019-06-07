/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:15:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/07 16:48:14 by sofchami         ###   ########.fr       */
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
	lem->paths = (t_path**)ft_memalloc(sizeof(t_path*) * (max_way));
	while (++i < max_way && i < lem->fourmis)
	{
		ft_bfs(lem, &s, i);
		// ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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
	// for (int it = 0; it < lem->nbr_salles; it++)
	// {
	// 	printf("valeur dans le room = %d  ", s.rooms[it]);
	// 	s.rooms[it] != -1 ? printf("et chambre %s\n", lem->salles[s.rooms[it]]->name) : printf(" -1\n");
	// }
	// int path = 7;
	// while (!lem->salles[path]->start)
	// {
	// 	printf("papa et room = %s\n", lem->salles[lem->salles[path]->papa]->name);
	// 	path = lem->salles[path]->papa;
	// }
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
			// printf("je rentre last ant\n");
			// printf("%d\n", lem->salles[lem->paths[chemin]->path[len_chemin]]->fourmis);
		}

	}
	if (lem->fourmis)
	{
		lem->salles[lem->paths[chemin]->path[len_chemin + 1]]->fourmis = lem->ant;
		// printf("\nset = %d   %d\n", lem->ant, len_chemin);
		lem->ant++;
		lem->fourmis--;
		// printf("juste pour etre sur = %d\n", lem->salles[lem->paths[chemin]->path[len_chemin]]->fourmis);
	}
	int i = 1;
	while (i < lem->paths[chemin]->size)
	{
		// printf("%d\n", lem->salles[lem->paths[chemin]->path[i]]->fourmis);
		if (lem->salles[lem->paths[chemin]->path[i]]->fourmis)
		{
			// printf("L%d-%s chemin=%d, salles=%d    ",lem->salles[lem->paths[chemin]->path[i]]->fourmis, lem->salles[lem->paths[chemin]->path[i]]->name, chemin, i);
			printf("L%d-%s ",lem->salles[lem->paths[chemin]->path[i]]->fourmis, lem->salles[lem->paths[chemin]->path[i]]->name);
			// printf("je ne rentre pas\n");
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
