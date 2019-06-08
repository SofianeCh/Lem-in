/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:50:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/08 15:36:50 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	ft_bfs(t_lem *lem, t_solve *s, int way)
{
	int elem;
	t_ptr_couloir *tmp;
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

int		visit_rooms(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int elem)
{
	int c;
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

// int		check_cross(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int room, int elem)
// {
// 	int i = -1;
// 	int b = 0;
// 	t_ptr_couloir *tmp1;
//
// 	while (++i < s->count)
// 	{
// 		for (int p = 1; p < lem->paths[i]->size; p++)
// 		{
// 			if (s->p > 0 && lem->salles[s->rooms[s->p]]->papa == lem->paths[i]->path[p])
// 			{
// 				tmp1 = lem->salles[lem->salles[s->rooms[s->p]]->papa]->couloirs;
// 				while (tmp1)
// 				{
// 					if ((tmp1->element->salle_1 == lem->salles[s->rooms[s->p]]->papa && tmp1->element->salle_2 == s->rooms[s->p]) || (tmp1->element->salle_2 == lem->salles[s->rooms[s->p]]->papa && tmp1->element->salle_1 == s->rooms[s->p]))
// 					{
// 						if (!tmp1->element->dir_salle1 && !tmp1->element->dir_salle2)
// 						{
// 							printf("check %s\n", lem->salles[s->rooms[s->p]]->name);
// 							lem->salles[s->rooms[s->p]]->papa = 0;
// 							lem->salles[s->rooms[s->p]]->visited = 0;
// 							return (0);
// 						}
// 					}
// 					tmp1 = tmp1->next;
// 				}
// 			}
// 		}
// 	}
// 	return (1);
// }
