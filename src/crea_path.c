/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:55:54 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/07 18:17:04 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				crea_path(t_lem *lem, int p, int way)
{
	int				len;
	int				tmp;

	len = 1;
	tmp = p;
	while (!lem->salles[p]->start && ++len)
		p = lem->salles[p]->papa;
	if (!(lem->paths[way] = (t_path *)ft_memalloc(sizeof(t_path))))
		exit(0);
	lem->paths[way]->size = len;
	lem->paths[way]->path = malloc(sizeof(int) * len);
	while (--len)
	{
		lem->paths[way]->path[len] = lem->salles[tmp]->index_s;
		tmp = lem->salles[tmp]->papa;
	}
	lem->paths[way]->path[len] = lem->salles[tmp]->index_s;
	while (len < lem->paths[way]->size)
		len++;
	// for (int i = 0; i < lem->paths[way]->size; i++)
	// {
	// 	lem->paths[way]->path[i] > -1 ? ft_printf("%s ", lem->salles[lem->paths[way]->path[i]]->name) : ft_printf("%d ", lem->paths[way]->path[i]);
	// }
	// ft_printf("\n");
}

int				directions(t_lem *lem, t_ptr_couloir **tmp,
	int merge, int room2)
{
	if (*tmp && (*tmp)->element->salle_1 == room2)
	{
		(*tmp)->element->dir_salle1 = 1;
		if (!merge && (*tmp)->element->dir_salle2)
		{
			merge = 1;
			lem->merge = (*tmp)->element;
		}
	}
	if (*tmp && (*tmp)->element->salle_2 == room2)
	{
		(*tmp)->element->dir_salle2 = 1;
		if (!merge && (*tmp)->element->dir_salle1)
		{
			merge = 1;
			lem->merge = (*tmp)->element;
		}
	}
	return (merge);
}

int					ft_modify_directions(t_lem *lem, int way)
{
	int				i;
	int				merge;
	int				room1;
	int				room2;
	t_ptr_couloir	*tmp;

	i = -1;
	merge = 0;
	while (++i < lem->paths[way]->size - 1)
	{
		room1 = lem->paths[way]->path[i];
		room2 = lem->paths[way]->path[i + 1];
		tmp = lem->salles[lem->paths[way]->path[i]]->couloirs;
		while (tmp && ((tmp->element->salle_1 != room2 && tmp->element->salle_2
			== room1) || (tmp->element->salle_2 != room2 &&
				tmp->element->salle_1 == room1)))
			tmp = tmp->next;
		merge = directions(lem, &tmp, merge, room2);
	}
	return (merge);
}

int		ft_calcul_etapes(t_lem *lem, int chemins)
{
	int i;
	int sum;
	int nb_ants;
	int nb_turn;

	sum = 0;
	i = -1;
	while (++i < chemins)
		sum += lem->paths[i]->size - 1;
	nb_ants = lem->fourmis - i;
	while (sum % i)
	{
		sum++;
		if (--nb_ants == 0)
			break ;
	}
	nb_turn = sum / i + nb_ants / i + !!(nb_ants % i);
	if (!lem->nbr_etapes)
		lem->nbr_etapes = nb_turn;
	else if (lem->nbr_etapes > nb_turn)
		lem->nbr_etapes = nb_turn;
	if (lem->nbr_etapes < nb_turn)
		return (1);
	return (0);
}

void	ft_merge_way(t_lem *lem, int way, int alt, int i)
{
	int b;
	int ok;

	b = -1;
	ok = 0;
	while (++b < lem->paths[alt]->size)
	{
		if (ok || lem->paths[way]->f_path[i] == lem->paths[alt]->path[b])
		{
			lem->paths[way]->f_path[i++] = lem->paths[alt]->path[b];
			ok++;
		}
	}
	lem->paths[way]->f_size = i;
}
