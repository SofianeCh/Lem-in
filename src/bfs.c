/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:50:41 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/07 16:53:18 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	ft_bfs(t_lem *lem, t_solve *s, int way)
{
	int elem;
	t_ptr_couloir *tmp;
	// printf("\n------------------je rentre dans le bfs-----------------\n");
	while (++s->p < lem->nbr_salles)
	{
		if (s->rooms[s->p] != -1)
		{
			tmp = lem->salles[s->rooms[s->p]]->couloirs;
			elem = 0;
			while (lem->salles[s->rooms[s->p]]->couloirs && tmp)
			{
				// if (way == 5)
					// ft_printf(" salles  %s   |%s  -  %s| \n", lem->salles[s->rooms[s->p]]->name,lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
				elem = visit_rooms(lem, s, tmp, elem);
				if (lem->salles[s->rooms[s->p]]->end)
				{
					// printf("\n-----------------je cree un path------------------------\n");
					// printf("path = ");
					crea_path(lem, s->rooms[s->p], way);
					// printf("len = %d\n",  lem->paths[way]->size);
					// for (int p = 0; p < lem->paths[way]->size; p++)
					// {
					// 	printf("%s ", lem->salles[s->rooms[p]]->name);
					// }
					// printf(" =>  queu\n");
					return ;
				}
				tmp = tmp->next;
			}
			s->size_q += elem;
			lem->salles[s->rooms[s->p]]->visited++;
		}
		// if (s->rooms[s->p] == -1)
			// printf("le voila \n");
	}
	lem->stop = 1;
	// printf("- - - - - - - y a un pblem - - - - - - ");
	// ft_printf(" = =  %d  -   %d\n", lem->nbr_salles, s->p);
	// for (int a = 0; a < lem->nbr_salles - 1; a++)
	// {
	// 	s->rooms[a] > -1 ? ft_printf("%s ", lem->salles[s->rooms[a]]->name) : ft_printf("%d ", s->rooms[a]);
	// }
}

int		visit_rooms(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int elem)
{
	// if (lem->salles[tmp->element->salle_2]->visited || lem->salles[tmp->element->salle_1]->visited)
	// {
	// 	if (s->rooms[s->p] == tmp->element->salle_2)
	// 	{
	// 		if (!check_cross(lem, s, tmp, tmp->element->salle_1, elem))
	// 			return (0);
	// 	}
	// 	else
	// 	{
	// 		if (!check_cross(lem, s, tmp, tmp->element->salle_2, elem))
	// 			return (0);
	// 	}
	// }
	int c = elem + s->size_q;
	if (!lem->salles[tmp->element->salle_2]->visited && tmp->element->salle_1 == s->rooms[s->p] && !tmp->element->dir_salle2 && croissement(lem, s, tmp, 0))
	{
		elem++;
		s->rooms[0 + elem + s->size_q] = tmp->element->salle_2;
		if (s->count == 5)
		{
			// ft_printf("1) salles  %s   |%s  -  %s| \n", lem->salles[s->rooms[s->p]]->name,lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
			// ft_printf("1) - - - %s - - - 	el = %d, size = %d  Dir = %d-%d \n", lem->salles[s->rooms[elem + s->size_q]]->name, elem, s->size_q, tmp->element->dir_salle1, tmp->element->dir_salle2);
		}
		lem->salles[tmp->element->salle_2]->papa = s->rooms[s->p];
		lem->salles[tmp->element->salle_2]->visited++;
		tmp->element->visited++;
	}
	else if (tmp->element->salle_2 == s->rooms[s->p] && !lem->salles[tmp->element->salle_1]->visited && !tmp->element->dir_salle1 && croissement(lem, s, tmp, 1))
	{
		elem++;
		s->rooms[0 + elem + s->size_q] = tmp->element->salle_1;
		if (s->count == 5)
		{
			// ft_printf("2) salles  %s   |%s  -  %s| \n", lem->salles[s->rooms[s->p]]->name,lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
			// ft_printf("2)  - - - %s - - -	el = %d, size = %d    Dir = %d-%d \n", lem->salles[s->rooms[elem + s->size_q]]->name, elem, s->size_q, tmp->element->dir_salle1, tmp->element->dir_salle2);
		}
		lem->salles[tmp->element->salle_1]->visited++;
		lem->salles[tmp->element->salle_1]->papa = s->rooms[s->p];
		tmp->element->visited++;
	}
	return (elem);
}

int		check_cross(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int room, int elem)
{
	int i = -1;
	int b = 0;
	t_ptr_couloir *tmp1;

	while (++i < s->count)
	{
		for (int p = 1; p < lem->paths[i]->size; p++)
		{
			if (s->p > 0 && lem->salles[s->rooms[s->p]]->papa == lem->paths[i]->path[p])
			{
				// printf("CROSS ~ ~ ~ ~ ~ ~ ~  %s\n", lem->salles[lem->paths[i]->path[p]]->name);
				tmp1 = lem->salles[lem->salles[s->rooms[s->p]]->papa]->couloirs;
				while (tmp1)
				{
					if ((tmp1->element->salle_1 == lem->salles[s->rooms[s->p]]->papa && tmp1->element->salle_2 == s->rooms[s->p]) || (tmp1->element->salle_2 == lem->salles[s->rooms[s->p]]->papa && tmp1->element->salle_1 == s->rooms[s->p]))
					{
						printf("%s    - - -     %s   - - - -   %s | %d - %d |\n", lem->salles[tmp1->element->salle_1]->name, lem->salles[tmp1->element->salle_2]->name, lem->salles[s->rooms[s->p]]->name, tmp1->element->dir_salle1, tmp1->element->dir_salle2);
						// if ((s->rooms[s->p] == tmp1->element->salle_1 && tmp1->element->dir_salle1) || (s->rooms[s->p] == tmp1->element->salle_2 && tmp1->element->dir_salle2))
						if (!tmp1->element->dir_salle1 && !tmp1->element->dir_salle2)
						{
							printf("check %s\n", lem->salles[s->rooms[s->p]]->name);
							lem->salles[s->rooms[s->p]]->papa = 0;
							lem->salles[s->rooms[s->p]]->visited = 0;
							return (0);
						}
					}
					tmp1 = tmp1->next;
				}
				// if (s->count == 2)
				// {
					// printf("room = %s  %s %s       %d %d\n", lem->salles[s->rooms[s->p]]->name, lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name, tmp->element->dir_salle1, tmp->element->dir_salle2);
					// printf("el = %d    room = %d \n", tmp->element->salle_2, room);
					// printf("je bloque ici %s\n", lem->salles[lem->paths[i - 1]->path[p]]->name);
					// printf("%s    |     %s\n", lem->salles[s->rooms[s->p - 1]]->name, lem->salles[lem->salles[room]->papa]->name);
				// }
				// if (s->rooms[s->p - 1] == lem->salles[room]->papa)
				// {
				// 	for (int f = 0; f < s->p; f++)
				// 		printf(" - - %d \n", s->rooms[f]);
				// 	lem->salles[room]->papa = 0;
				// 	lem->salles[room]->visited = 0;
				// 	// room == tmp->element->salle_1 ? tmp->element->dir_salle2 = 1 : 0;
				// 	// room == tmp->element->salle_2 ? tmp->element->dir_salle1 = 1 : 0;
				// }
				// printf("%d\n", tmp->element->visited);
				// printf("%s    %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
				// return (0);
			}
			// printf("%s ", lem->salles[lem->paths[i - 1]->path[p]]->name);
		}
	}
	return (1);
}
