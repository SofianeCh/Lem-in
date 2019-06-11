/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/11 17:46:24 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				ft_init_queue(t_lem *lem, t_solve *s)
{
	s->it = -1;
	s->rooms = malloc(sizeof(s->rooms) * lem->nbr_salles);
	while (++s->it < lem->nbr_salles)
	{
		s->rooms[s->it] = -1;
		if (lem->salles[s->it]->start)
		{
			s->rooms[0] = s->it;
			s->start = lem->salles[s->it]->nbr_voisin;
		}
		if (lem->salles[s->it]->end)
			s->end = lem->salles[s->it]->nbr_voisin;
	}
}

void				ft_calcul_merge(t_lem *lem, int chemins, int alt)
{
	int				i;
	int				len_path;
	int				nb_turn;
	int				nb_ants;

	i = -1;
	len_path = 0;
	while (++i < chemins)
		if (i == alt || i == (chemins - 1))
			len_path += lem->paths[i]->f_size - 1;
		else
			len_path += lem->paths[i]->size - 1;
	nb_ants = lem->fourmis - i;
	while (len_path % i)
	{
		len_path++;
		if (--nb_ants == 0)
			break ;
	}
	nb_turn = len_path / i + nb_ants / i + !!(nb_ants % i);
	if (lem->nbr_etapes >= nb_turn)
	{
		finilize_merge(lem, chemins - 1, alt);
		lem->nbr_etapes = nb_turn;
	}
}

void				big_clean(t_lem *lem, int chemin)
{
	int				i;
	t_ptr_couloir	*tmp;
	t_ptr_couloir	*next;
	t_couloir		*next_s;
	t_couloir		*tmp_s;

	i = -1;
	while (++i <= chemin)
		free(lem->paths[i]->path);
	free(lem->paths);
	ft_cln(&lem->line, &lem->buff, &lem->tmp);
	i = -1;
	while (++i < lem->nbr_salles)
	{
		tmp = lem->salles[i]->couloirs;
		while (tmp)
		{
			next = tmp->next;
			tmp_s = tmp->element;
			tmp = next;
		}
		if (lem->salles[i]->couloirs)
			free(lem->salles[i]->couloirs);
	}
}

void				probleme(int p)
{
	if (!p)
		ft_putstr("Error\n");
	exit(1);
}

int					main(int argc, char **argv)
{
	t_lem			lem;
	int				chemin;
	int				i;

	chemin = 0;
	ft_bzero(&lem, sizeof(lem));
	ft_read_map(&lem);
	ft_crea_salles(&lem);
	ft_link_couloir(&lem);
	map_checker2(&lem);
	chemin = ft_solve_path(&lem);
	ft_printf("%d\n", lem.fourmis);
	ft_putendl(lem.line + lem.print);
	while (!lem.last_ant)
	{
		i = -1;
		while (++i < chemin)
			!lem.last_ant ? go_fourmis(&lem, i) : 0;
		write(1, "\n", 1);
	}
	ft_printf("nb_turn %d\n", lem.nbr_etapes);
	big_clean(&lem, chemin);
	exit(0);
}
