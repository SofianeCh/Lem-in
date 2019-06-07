/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:04:56 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/06 16:59:34 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void 	ft_merge(t_lem *lem, int way, int tomerge)
{
	int		way2;
	int		i;
	int		ok;
	int		r1;
	int		r2;

	ok = 0;
	i = -1;
	while (tomerge--)
	{
		way2 = way_for_merge(lem, way);
		r1 = node_to_megre(lem, way, way2);
		r2 = node_to_megre(lem, way2, way);
		// if (tomerge)
		// {
		// 	tomerge -= doublecon(lem, way, way2);
		// }
		while (++i < lem->paths[way]->size)
		{
			lem->paths[way]->f_path[i] = lem->paths[way]->path[i];
			if (lem->paths[way]->path[i] == r1 || lem->paths[way]->path[i] == r2)
			{
				ft_merge_way(lem, way, way2, i);
				break ;
			}
		}
		i = -1;
		while (++i < lem->paths[way2]->size)
		{
			lem->paths[way2]->f_path[i] = lem->paths[way2]->path[i];
			if (lem->paths[way2]->path[i] == r1 || lem->paths[way2]->path[i] == r2)
			{
				ft_merge_way(lem, way2, way, i);
				break ;
			}
		}
	}
	ft_calcul_merge(lem, way + 1, way2);
}

int 	node_to_megre(t_lem *lem, int way, int alt)
{
	int k;
	int z;

	k = 0;
	while (++k < lem->paths[way]->size - 1)
	{
		z = 0;
		while (++z < lem->paths[alt]->size - 1)
		{
			if (lem->paths[way]->path[k] == lem->paths[alt]->path[z])
				return (lem->paths[way]->path[k]);
		}
	}
	return (0);
}

int		way_for_merge(t_lem *lem, int way)
{
	int i;
	int k;
	int room1;
	int room2;

	i = -1;
	room1 = lem->merge->salle_1;
	room2 = lem->merge->salle_2;
	while (++i < way)
	{
		k = 0;
		while (++k < lem->paths[i]->size)
		{
			if ((lem->paths[i]->path[k] == room1 && lem->paths[i]->path[k - 1] == room2) || (k <= lem->paths[i]->size && lem->paths[i]->path[k] == room1 && lem->paths[i]->path[k+1] == room2))
				return (i);
		}
	}
	return (0);
}

void	finilize_merge(t_lem *lem, int way1, int way2)
{
	int i;

	i = -1;
	lem->paths[way1]->size = lem->paths[way1]->f_size;
	lem->paths[way2]->size = lem->paths[way2]->f_size;
	lem->paths[way1]->f_size = 0;
	lem->paths[way2]->f_size = 0;
	free(lem->paths[way1]->path);
	free(lem->paths[way2]->path);
	lem->paths[way1]->path = malloc(sizeof(int) * lem->paths[way1]->size);
	lem->paths[way2]->path = malloc(sizeof(int) * lem->paths[way2]->size);
	while (++i < lem->paths[way1]->size)
	{
		lem->paths[way1]->path[i] = lem->paths[way1]->f_path[i];
		lem->paths[way1]->f_path[i] = '\0';
	}
	i = -1;
	while (++i < lem->paths[way2]->size)
	{
		lem->paths[way2]->path[i] = lem->paths[way2]->f_path[i];
		lem->paths[way2]->f_path[i] = '\0';
	}
}
