/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/14 15:03:01 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				ft_init_queue(t_lem *lem, t_solve *s)
{
	s->it = -1;
	if (!(s->rooms = malloc(sizeof(s->rooms) * lem->nbr_salles)))
		probleme(0);
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

void				probleme(int p)
{
	if (!p)
		ft_putstr("Error\n");
	exit(1);
}

void					print_result(t_lem *lem, int chemin)
{
	int p;
	int i;

	p = lem->nbr_etapes + 1;
	while (p--)
	{
		i = -1;
		while (++i < chemin)
			!lem->last_ant ? go_fourmis(lem, i) : 0;
		write(1, "\n", 1);
	}
}

int					main(int argc, char **argv)
{
	t_lem			lem;
	int				chemin;
	int				i;
	int				p;

	chemin = 0;
	ft_bzero(&lem, sizeof(lem));
	ft_read_map(&lem);
	ft_crea_salles(&lem);
	ft_link_couloir(&lem);
	map_checker2(&lem);
	chemin = ft_solve_path(&lem);
	ft_printf("%d\n", lem.fourmis);
	ft_putendl(lem.line + lem.print);
	print_result(&lem, chemin);
	if (argc > 1 && argv[1] && argv[1][0] == '-' && argv[1][1] == 'p')
		ft_printf("nb_turn %d\n", lem.nbr_etapes);
	big_clean(&lem, chemin);
	exit(0);
}
