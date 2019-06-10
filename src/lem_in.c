/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/10 17:26:52 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** gestoin d'erreur map unvalid dans le parsins (25/38)
 ** normer
 ** fuites memoires
 */

#include "lem_in.h"

void			ft_cln(char **line, char **line2, char **line3)
{
	line ? ft_strdel(line) : 0;
	line2 ? ft_strdel(line2) : 0;
	line3 ? ft_strdel(line3) : 0;
}

void	ft_init_queue(t_lem *lem, t_solve *s)
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

int 	valid_croisement(t_lem *lem, t_solve *s, t_ptr_couloir *tmp)
{
	int check;
	int dir1;
	int dir2;
	int i;
	int p;

	check = 0;
	dir1 = 0;
	dir2 = 0;
	i = 0;
	if (s->count == 5)
		ft_printf("			Valid cross check  | %s | ret = ", lem->salles[s->rooms[s->p]]->name);
	while (++i <= s->count)
	{
		p = 0;
		while (++p < lem->paths[i - 1]->size - 1)
		{
			if (s->rooms[s->p] == tmp->element->salle_2 && lem->paths[i - 1]->path[p] == tmp->element->salle_1)
			{
				dir1 = 1;
				// if (s->count == 5)
				// ft_printf("way = %d, index = %d, name = %s\n", i-1, p, lem->salles[tmp->element->salle_1]->name);
			}
			if (s->rooms[s->p] == tmp->element->salle_1 && lem->paths[i - 1]->path[p] == tmp->element->salle_2)
			{
				dir2 = 1;
				if (s->count == 5)
				ft_printf("way = %d, index = %d, name = %s\n", i-1, p, lem->salles[lem->paths[i - 1]->path[p]]->name);
							}
			if (dir1 || dir2)
			{
				if (s->count == 5)
				ft_printf("%d-> dir1 %d - %d %s---%s\n", 1, dir1, dir2, lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
				return (1);
			}
		}
	}
	if (s->count == 5)
		ft_printf("%d\n", 0);
	return (0);
}

int 	croissement(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int num)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	// if (lem->salles[tmp->element->salle_2]->papa && !num)
	// 	return (0);
	// if (lem->salles[tmp->element->salle_1]->papa && num)
	// 	return (0);
	while (++i <= s->count)
	{
		//
		// printf("Room = %d\n", s->rooms[s->p]);
		// s->p > 0 ? printf("la room precedente = %d\n", s->rooms[s->p - 1]) : 0;
		// s->p > 0 ? printf("name room precedente = %s\n", lem->salles[s->rooms[s->p - 1]]->name) : 0;
		// for (int r = 0; r < s->p; r++)
		// {
		// 	printf("%s ", lem->salles[s->rooms[r]]->name);
		// }

		for (int p = 1; p < lem->paths[i - 1]->size - 1; p++)
		{
			if (s->p > 0 && lem->salles[s->rooms[s->p]]->papa == lem->paths[i - 1]->path[p])
			{
				ret = 1;
			}
			// if (s->p > 0 && s->rooms[s->p] == lem->paths[i - 1]->path[p])
			// {
			// 	printf("j'ai un croissement ici %s\n", lem->salles[lem->paths[i - 1]->path[p]]->name);
			// 	if (!tmp->element->dir_salle1 && !tmp->element->dir_salle2)
			// 	{
			// 		printf("%d - %d\n", tmp->element->dir_salle1,tmp->element->dir_salle2);
			// 		return (0);
			// 	}
			// }
		}
		// valid_croisement(lem, s, tmp);
		for (int p = 1; p < lem->paths[i - 1]->size - 1; p++)
		{
			if (!ret && s->p > 0 && s->rooms[s->p] == lem->paths[i - 1]->path[p])
			{
				// if (s->count == 5)
				// 	ft_printf("je retourne %s\n", lem->salles[lem->paths[i - 1]->path[p]]->name);
				if (!tmp->element->dir_salle1 && !tmp->element->dir_salle2)
				// if (!valid_croisement(lem, s, tmp))
				{
					if (s->count == 5)
					{
						// ft_printf(" salles  %s   |%s  -  %s| \n", lem->salles[s->rooms[s->p]]->name,lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
						// ft_printf("%d - %d\n", tmp->element->dir_salle1,tmp->element->dir_salle2);
					}
					// printf("%d - %d\n", tmp->element->dir_salle1,tmp->element->dir_salle2);
					return (0);
				}
			}
		}
		// printf("\n");
	}
	return (1);
}

void		ft_reset_rooms(t_lem *lem, t_solve *s)
{
	int i;
	t_ptr_couloir *tmp;

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

void		ft_calcul_merge(t_lem *lem, int chemins, int alt)
{
	int		i;
	int		len_path;
	double	calcul;
	int nb_turn;
	int nb_ants;

	i = -1;
	len_path = 0;
	calcul = 0.0;
	while (++i < chemins)
	{
		if (i == alt || i == (chemins - 1))
			len_path += lem->paths[i]->f_size - 1;
		else
			len_path += lem->paths[i]->size - 1;
	}
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

int		doublecon(t_lem *lem, int way, int alt)
{
	int k;
	int i;
	int count;

	i = 0;
	count = 0;
	while (++i < lem->paths[way]->size - 1)
	{
		k = 0;
		while (++k < lem->paths[alt]->size - 1)
			if (lem->paths[way]->path[i] == lem->paths[alt]->path[k])
			{
				while (lem->paths[way]->path[++i] == lem->paths[alt]->path[--k])
					count++;
				return (count > 1 ? count - 1 : 0);
			}
	}
	return (0);
}

void		big_clean(t_lem *lem, int chemin)
{
	int i;
	t_ptr_couloir *tmp;
	t_ptr_couloir *next;
	t_couloir *next_s;
	t_couloir *tmp_s;

	i = -1;
	while (++i <= chemin)
		free(lem->paths[i]->path);
	free(lem->paths);
	free(lem->line);
	free(lem->buff);
	free(lem->tmp);
	i = -1;
	while (++i < lem->nbr_salles)
	{
		tmp = lem->salles[i]->couloirs;
		while (tmp)
		{
			next = tmp->next;
			tmp_s = tmp->element;
			// while (tmp_s)
			// {
			// 	// next_s = tmp_s->next;
			// 	// free(tmp_s);
			// 	tmp_s = next_s;
			// }
			// if (tmp_s)
			// 	free(tmp_s);
			// free(tmp);
			tmp = next;
		}
		if (lem->salles[i]->couloirs)
			free(lem->salles[i]->couloirs);
		ft_printf("pas direct %d  %d\n", i, lem->nbr_salles);
	}
}

void probleme(int p)
{
	if (!p)
		ft_putstr("Error\n");
	exit(1);
}

void	map_checker2(t_lem *lem)
{
	int i;

	i = 0;
	while (i < lem->nbr_salles)
	{
		if (lem->salles[i]->end)
		{
			if (!lem->salles[i]->nbr_voisin)
				probleme(0);
		}
		i++;
	}

}

int			main(int argc, char **argv)
{
	t_lem			lem;
	t_ptr_couloir	*tmp;
	int				chemin;
	int				i;

	chemin = 0;
	ft_bzero(&lem, sizeof(lem));
	lem.ant = 1;
	ft_read_map(&lem);
	ft_crea_salles(&lem);
	ft_link_couloir(&lem);
	map_checker2(&lem);
	for (int k = 0; k < lem.nbr_salles ; k ++)
	{
		// printf("nom de la salles %s et le nombre de connection = %d\n", lem.salles[k]->name, lem.salles[k]->nbr_voisin);
		tmp = lem.salles[k]->couloirs;
		while (tmp)
		{
			// printf("couloir = %s -> = %s\n", lem.salles[tmp->element->salle_1]->name, lem.salles[tmp->element->salle_2]->name);
			tmp = tmp->next;
		}
	}
	chemin = ft_solve_path(&lem);
	int check = 0;
	int b = 1;
	int p = -1;
	// printf("= %d - - - - - - - - - - - - len_chemin = %d\n", lem.salles[lem.paths[chemin]->path[8]]->fourmis, 8);
	ft_printf("%d\n", lem.fourmis);
	ft_putendl(lem.line + lem.print);
	while (!lem.last_ant)
	{
		i = -1;
		while (++i < chemin)
		{
			!lem.last_ant ? go_fourmis(&lem, i) : 0;
		}
		printf("\n");
		check++;
	}
	// ft_printf("\n\n- - - - - - - - - - - - - - - - \n\n");
	// for (int k = 0; k < chemin; k++)
	// {
	// 	for (int l = 1; l < lem.paths[k]->size-1; l++)
	// 	{
	// 		ft_putstr(lem.salles[lem.paths[k]->path[l]]->name);
	// 		write(1, " ", 1);
	// 		for (int h = 0; h < chemin ; h++)
	// 		{
	// 			for (int z = 1; z < lem.paths[h]->size - 1; z++)
	// 			{
	// 				if ((l != z && k != h) && lem.paths[k]->path[l] == lem.paths[h]->path[z])
	// 					ft_printf("|| --- CROISEMENT --- ==> %s ways = %d<-->%d pl %d<-->%d ||",lem.salles[lem.paths[k]->path[l]]->name, k , h, l, z);
	// 			}
	// 		}
	// 	}
	// 	ft_printf(" way = %d   SIZE == %d", k, lem.paths[k]->size);
	// 	ft_printf("\n");
	// }
	// printf("nb_turn %d\n", lem.nbr_etapes);
	// big_clean(&lem, chemin);
	exit (0);
}
