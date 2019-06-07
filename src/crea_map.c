/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:36:04 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/07 20:26:26 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				ft_crea_salles(t_lem *lem)
{
	size_t			i;
	int				jump;

	i = -1;
	jump = 0;
	lem->salles = (t_salle **)ft_memalloc(sizeof(t_salle *) * lem->nbr_salles);
	while (++i < lem->nbr_salles)
	{
		lem->salles[i] = (t_salle *)ft_memalloc(sizeof(t_salle));
		ft_bzero(lem->salles[i], sizeof(lem->salles[i]));
		lem->salles[i]->index_s = i;
		while (lem->line[lem->index[jump]] == '#' && ++jump)
		{
			if (lem->index[jump] == lem->pos_start)
			{
				lem->salles[i]->start = 1;
				lem->salles[i]->fourmis = lem->fourmis;
			}
			if (lem->index[jump] == lem->pos_end)
				lem->salles[i]->end = 1;
		}
		lem->salles[i]->name = ft_name(lem->line + lem->index[jump]);
		lem->hash[i] = hash((unsigned char*)(lem->line + lem->index[jump]));
		jump++;
	}
}

t_couloir			*ft_list(t_lem *lem, int prem, int deux)
{
	t_couloir		*new;
	t_ptr_couloir	*s1;
	t_ptr_couloir	*s2;

	if (!(new = (t_couloir*)malloc(sizeof(*new))) ||
		!(s1 = (t_ptr_couloir*)malloc(sizeof(t_ptr_couloir))) ||
		!(s2 = (t_ptr_couloir*)malloc(sizeof(t_ptr_couloir))))
		exit(0);
	lem->salles[prem]->nbr_voisin++;
	lem->salles[deux]->nbr_voisin++;
	s1->element = new;
	s2->element = new;
	s1->next = lem->salles[prem]->couloirs;
	s2->next = lem->salles[deux]->couloirs;
	lem->salles[prem]->couloirs = s1;
	lem->salles[deux]->couloirs = s2;
	ft_bzero(new, sizeof(*new));
	new->salle_1 = prem;
	new->salle_2 = deux;
	// new->next = NULL;
	return (new);
}

void			link_list(t_lem *lem, int ind_c, int len1)
{
	int			prem;
	int			deux;

	if (lem->line[ind_c] != '#')
	{
		prem = ft_index(lem, hash((unsigned char*)(lem->line + ind_c)));
		deux = ft_index(lem, hash((unsigned char*)(lem->line + ind_c + len1)));
		if (!ft_verif(lem->salles[prem]->couloirs, prem, deux, lem))
			ft_list(lem, prem, deux);
	}
}

void			ft_link_couloir(t_lem *lem)
{
	int			ind_c;
	int			index_s;
	int			len;
	int			len1;
	int			check;

	ind_c = lem->index[lem->lignes - 1];
	while (lem->line[ind_c])
	{
		len = 0;
		len1 = 0;
		check = 0;
		index_s = 0;
		while (lem->line[ind_c + len] && lem->line[ind_c + len] != '\n')
		{
			!check ? len1++ : 0;
			if (lem->line[ind_c + len] == '-')
				check = 1;
			len++;
		}
		link_list(lem, ind_c, len1);
		ind_c += len + 1;
	}
}
