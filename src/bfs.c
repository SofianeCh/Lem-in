/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:50:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/11 17:59:29 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				ft_bfs(t_lem *lem, t_solve *s, int way)
{
	int				elem;
	t_ptr_couloir	*tmp;

	while (++s->p < lem->nbr_salles)
	{
		if (s->rooms[s->p] != -1)
		{
			tmp = lem->salles[s->rooms[s->p]]->couloirs;
			elem = 0;
			while (lem->salles[s->rooms[s->p]]->couloirs && tmp)
			{
				elem = visit_rooms(lem, s, tmp, elem);
				if (lem->salles[s->rooms[s->p]]->end)
				{
					crea_path(lem, s->rooms[s->p], way);
					return ;
				}
				tmp = tmp->next;
			}
			s->size_q += elem;
			lem->salles[s->rooms[s->p]]->visited++;
		}
	}
	lem->stop = 1;
}

int					visit_rooms(t_lem *lem, t_solve *s,
	t_ptr_couloir *tmp, int elem)
{
	int				c;

	c = elem + s->size_q;
	if (!lem->salles[tmp->element->salle_2]->visited && tmp->element->salle_1
			== s->rooms[s->p] && !tmp->element->dir_salle2 &&
			croissement(lem, s, tmp, 0))
	{
		elem++;
		s->rooms[0 + elem + s->size_q] = tmp->element->salle_2;
		lem->salles[tmp->element->salle_2]->papa = s->rooms[s->p];
		lem->salles[tmp->element->salle_2]->visited++;
		tmp->element->visited++;
	}
	else if (tmp->element->salle_2 == s->rooms[s->p] &&
			!lem->salles[tmp->element->salle_1]->visited &&
			!tmp->element->dir_salle1 && croissement(lem, s, tmp, 1))
	{
		elem++;
		s->rooms[0 + elem + s->size_q] = tmp->element->salle_1;
		lem->salles[tmp->element->salle_1]->visited++;
		lem->salles[tmp->element->salle_1]->papa = s->rooms[s->p];
		tmp->element->visited++;
	}
	return (elem);
}

int					valid_croisement(t_lem *lem, t_solve *s, t_ptr_couloir *tmp)
{
	int				check;
	int				dir1;
	int				dir2;
	int				i;
	int				p;

	check = 0;
	dir1 = 0;
	dir2 = 0;
	i = 0;
	while (++i <= s->count && (p = 0))
		while (++p < lem->paths[i - 1]->size - 1)
		{
			if (s->rooms[s->p] == tmp->element->salle_2 &&
					lem->paths[i - 1]->path[p] == tmp->element->salle_1)
				dir1 = 1;
			if (s->rooms[s->p] == tmp->element->salle_1 &&
					lem->paths[i - 1]->path[p] == tmp->element->salle_2)
				dir2 = 1;
			if (dir1 || dir2)
				return (1);
		}
	return (0);
}

int					croissement(t_lem *lem, t_solve *s,
	t_ptr_couloir *tmp, int num)
{
	int				i;
	int				ret;
	int				p;

	i = 0;
	ret = 0;
	while (++i <= s->count)
	{
		p = 0;
		while (++p < lem->paths[i - 1]->size - 1)
			if (s->p > 0 && lem->salles[s->rooms[s->p]]->papa ==
					lem->paths[i - 1]->path[p])
				ret = 1;
		p = 0;
		while (++p < lem->paths[i - 1]->size - 1)
			if (!ret && s->p > 0 && s->rooms[s->p] ==
					lem->paths[i - 1]->path[p])
				if (!tmp->element->dir_salle1 && !tmp->element->dir_salle2)
					return (0);
	}
	return (1);
}

void				ft_reset_rooms(t_lem *lem, t_solve *s)
{
	int				i;
	t_ptr_couloir	*tmp;

	i = -1;
	while (++i < lem->nbr_salles)
	{
		tmp = lem->salles[i]->couloirs;
		lem->salles[i]->visited = 0;
		lem->salles[i]->papa = 0;
		i ? s->rooms[i] = -1 : 0;
	}
	s->size_q = 0;
	s->p = -1;
}
