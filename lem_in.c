/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/05/21 19:48:44 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Proteger les mallocs.
** erreurs quand map ne termine pas part \n, (ft-link_couloirs)
** gestoin d'erreur map valid dans le parsins (14/15)
** gestoin d'erreur map unvalid dans le parsins (0/38)
** normer
** fuites memoires
** hash plus opti avec modulo
*/

#include "lem_in.h"
#include <stdio.h>

void			ft_cln(char **line, char **line2, char **line3)
{
	line ? ft_strdel(line) : 0;
	line2 ? ft_strdel(line2) : 0;
	line3 ? ft_strdel(line3) : 0;
}

int				ft_check_names(char *line, char *name)
{
	int i;

	i = 0;
	if (!line || !name)
		return (0);
	while (line[i] && line[i] != '-' && line[i] != '\n')
	{
		if (line[i] != name[i])
			return (0);
		i++;
	}
	if (name[i])
		return (0);
	return (1);
}

char			*ft_strjoin2(char const *s1, char const *s2)
{
	size_t	i;
	size_t	k;
	size_t	len_dst;
	size_t	len_src;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_dst = ft_strlen(s1);
	len_src = ft_strlen(s2);
	if ((str = (char*)malloc(sizeof(*str) * (len_src + len_dst + 1))) == 0)
		return (NULL);
	i = 0;
	k = 0;
	while (i < (len_src + len_dst))
	{
		if (i < (len_dst))
			str[i] = ((char*)s1)[i];
		else
			str[i] = ((char*)s2)[k++];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char			*ft_strdup2(const char *s, t_lem *lem)
{
	int		i;
	int min;
	char	*str;

	i = -1;
	while (!ft_isdigit((int)s[++i]))
	{
		while (s[i] != '\n')
			i++;
	}
	min = i;
	lem->fourmis = ft_atoi(s + i);
	// ft_printf("%d\n", lem->fourmis);
	// while (s[i])
	// 	i++;
	i = ft_strlen(s);
	if ((str = (char*)malloc(sizeof(*str) * i + 1)) == 0)
		return (!(lem->probleme = 1) ? NULL : 0);
	i = min;
	while (s[++i])
	{
		str[i] = s[i];
		s[i] == '-' ? lem->couloirs++ : 0;
		if (s[i] == '#')
		{
			if (s[i + 1] && s[i + 1] == '#' && s[i + 2])
			{
				if (ft_check_names((char*)(s + i + 2), "start"))
					!lem->pos_start ? lem->pos_start++ : lem->probleme++;
				if (ft_check_names((char*)(s + i + 2), "end"))
					!lem->pos_end ? lem->pos_end++ : lem->probleme++;
				lem->dieze++;
			}
			else if (!lem->dieze)
				lem->dieze = 2;
		}
		if (i > min && s[i] == '\n' && !lem->couloirs)
		{
			lem->index[lem->lignes] = i + 1;
			(lem->dieze && lem->pos_start == 1) ? (lem->pos_start = i + 1) : 0;
			(lem->dieze && lem->pos_end == 1) ? (lem->pos_end = i + 1) : 0;
			lem->dieze == 2 ? lem->comm++ : 0;
			lem->lignes++;
			lem->dieze = 0;
		}
	}
	lem->nbr_salles = lem->lignes - 3 - lem->comm;
	// printf("%d  %d\n", lem->lignes, lem->comm);
	// lem->nbr_salles = 9;
	str[i] = '\0';
	return (str);
}

void			ft_read_map(t_lem *lem)
{
	lem->b_size = 5000000;
	lem->buff = ft_strnew(lem->b_size - 1);
	while ((lem->ret = read(0, lem->buff, lem->b_size)) > 0)
	{
		ft_putendl(lem->buff);
		lem->len += lem->ret;
		lem->b_size *= 2;
		lem->tmp = lem->line;
		lem->line = !lem->line ? ft_strdup(lem->buff) :
		ft_strjoin2(lem->line, lem->buff);
		ft_cln(&lem->tmp, &lem->buff, NULL);
		lem->buff = ft_strnew(lem->b_size - 1);
	}
	lem->tmp = lem->line;
	lem->line = ft_strdup2(lem->line, lem);
	// ft_printf("%s\n", lem->line + 1);
	ft_cln(&lem->tmp, &lem->buff, NULL);
}

char			*ft_name(char *str)
{
	int		i;
	char	*s;

	i = -1;
	while (str[++i] && str[i] != ' ')
		;
	if ((s = (char*)malloc(sizeof(*s) * i + 1)) == 0)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != ' ')
		s[i] = str[i];
	s[i] = '\0';
	return (s);
}

unsigned long		hash(unsigned char *str)
{
	unsigned long	hash;
	int				c;
	int				i;

	hash = 012405;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '-' && str[i] != '\n')
	{
		c = str[i];
		hash = ((hash << 5) + hash) + c;
		i++;
	}
	return (hash);
}

void			ft_crea_salles(t_lem *lem)
{
	size_t i;
	int jump;

	i = -1;
	jump = 0;
	lem->salles = (t_salle **)ft_memalloc(sizeof(t_salle *) * lem->nbr_salles);
	while (++i < lem->nbr_salles)
	{
		lem->salles[i] = (t_salle *)ft_memalloc(sizeof(t_salle));
		ft_bzero(lem->salles[i], sizeof(lem->salles[i]));
		lem->salles[i]->index_s = i;
		while (lem->line[lem->index[jump]] == '#')
		{
			jump++;
			if (lem->index[jump] == lem->pos_start)
			{
				lem->salles[i]->start = 1;
				lem->salles[i]->fourmis = lem->fourmis;
			}
			if (lem->index[jump] == lem->pos_end)
				lem->salles[i]->end = 1;
		}
		lem->salles[i]->name = ft_name(lem->line + lem->index[jump]);
		// printf("bef hash %c\n", lem->line[lem->index[jump]]);
		lem->hash[i] = hash((unsigned char*)(lem->line + lem->index[jump]));
		jump++;
	}
	// printf("nbr de salles = %d\n", lem->nbr_salles);
	// for (int p = 0;p < lem->nbr_salles;p++)
	// {
	// 	printf("%lD\n", lem->hash[p]);
	// }
}

int		ft_index(t_lem *lem, unsigned long hash)
{
	size_t	i;

	i = 0;
	while (i < lem->nbr_salles)
	{
		if (hash == lem->hash[i])
			return (i);
		i++;
	}
	return (-1);
}

t_couloir	*ft_list(t_lem *lem, int prem, int deux)
{
	t_couloir		*new;
	t_ptr_couloir	*s1;
	t_ptr_couloir	*s2;

	if (!(new = (t_couloir*)malloc(sizeof(*new))) ||
		!(s1 = (t_ptr_couloir*)malloc(sizeof(t_ptr_couloir))) ||
		!(s2 = (t_ptr_couloir*)malloc(sizeof(t_ptr_couloir))))
		return (NULL);
	s1->element = new;
	s2->element = new;
	s1->next = lem->salles[prem]->couloirs;
	s2->next = lem->salles[deux]->couloirs;
	lem->salles[prem]->couloirs = s1;
	lem->salles[deux]->couloirs = s2;
	ft_bzero(new, sizeof(*new));
	new->salle_1 = prem;
	new->salle_2 = deux;
	new->next = NULL;
	return (new);
}

int			ft_verif(t_ptr_couloir *list, int prem, int deux, t_lem *lem)
{
	t_ptr_couloir *tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->element->salle_1 == deux || tmp->element->salle_2 == deux)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		ft_link_couloir(t_lem *lem)
{
	int		index_c;
	int		index_s;
	int		len;
	int		len1;
	int		prem;
	int		deux;
	int		check;

	index_c = lem->index[lem->lignes - 1];
	while (lem->line[index_c])
	{
		len = 0;
		len1 = 0;
		check = 0;
		index_s = 0;
		t_couloir clr;
		while (lem->line[index_c + len] && lem->line[index_c + len] != '\n')
		{
			!check ? len1++ : 0;
			if (lem->line[index_c + len] == '-')
				check = 1;
			len++;
		}
		if (lem->line[index_c] != '#')
		{
			prem = ft_index(lem, hash((unsigned char*)(lem->line + index_c)));
			deux = ft_index(lem, hash((unsigned char*)(lem->line + index_c + len1)));
			if (!ft_verif(lem->salles[prem]->couloirs, prem, deux, lem))
			{
				ft_list(lem, prem, deux);
				lem->salles[prem]->nbr_voisin++;
				lem->salles[deux]->nbr_voisin++;
			}
		}
		index_c += len + 1;
	}
	// t_ptr_couloir *tmp;
	// for (int k = 0; k <lem->nbr_salles; k++)
	// {
	// 	tmp = lem->salles[k]->couloirs;
	// 	printf("%s\n\n", lem->salles[k]->name);
	// 	while (tmp)
	// 	{
	// 		printf("%s, %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
	// 		tmp = tmp->next;
	// 	}
	// }
	// printf("----------------------Parse-------------------\n");
}

void	crea_path(t_lem *lem, int p, int way)
{
	int len;
	int tmp;

	len = 1;
	tmp = p;
	while (!lem->salles[p]->start && ++len)
		p = lem->salles[p]->papa;
	lem->paths[way] = (t_path *)ft_memalloc(sizeof(t_path));
	lem->paths[way]->size = len;
	lem->paths[way]->path = malloc(sizeof(int) * len);
	while (--len)
	{
		lem->paths[way]->path[len] = lem->salles[tmp]->index_s;
		tmp = lem->salles[tmp]->papa;
	}
	lem->paths[way]->path[len] = lem->salles[tmp]->index_s;
	while (len < lem->paths[way]->size)
	{
		len++;
	}
	if (way < 3)
	{
		for (int i = 1; i < lem->paths[way]->size; i++)
		{
			if (way == 0 && i == 1)
			printf("- - %d - - \n", lem->paths[way]->path[i]);
			printf("%s ", lem->salles[lem->paths[way]->path[i]]->name);
		}
		printf("\n");
	}
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

int 	croissement(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int num)
{
	int i;

	i = 0;
	// printf("le count = %d\n", s->count);
	// printf("~~~~  %d et %s\n", s->rooms[s->p], lem->salles[s->rooms[s->p]]->name);
	if (lem->salles[tmp->element->salle_2]->papa && !num)
		return (0);
	if (lem->salles[tmp->element->salle_1]->papa && num)
		return (0);
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

		for (int p = 1; p < lem->paths[i - 1]->size; p++)
		{
			// printf("la room donne = %d\n", s->rooms[s->p]);
		 	if (s->p > 0 && s->rooms[s->p - 1] == lem->paths[i - 1]->path[p])
			{
				// printf("je bloque ici %s\n", lem->salles[lem->paths[i - 1]->path[p]]->name);
				// printf("%d\n", tmp->element->visited);
				// printf("%s    %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
				// return (0);
			}
			// printf("%s ", lem->salles[lem->paths[i - 1]->path[p]]->name);
		}
		// printf("\n");
	}
	return (1);
}

int		check_cross(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int room)
{
	int i = 0;

	while (++i <= s->count)
	{
		for (int p = 1; p < lem->paths[i - 1]->size; p++)
		{
			// printf("la room donne = %d\n", s->rooms[s->p]);
			if (s->p > 0 && s->rooms[s->p - 1] == lem->paths[i - 1]->path[p])
			{
				// printf("room = %s  %s %s       %d %d\n", lem->salles[s->rooms[s->p]]->name, lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name, tmp->element->dir_salle1, tmp->element->dir_salle2);
				// printf("el = %d    room = %d \n", tmp->element->salle_2, room);
				// printf("je bloque ici %s\n", lem->salles[lem->paths[i - 1]->path[p]]->name);
				// printf("%s    |     %s\n", lem->salles[s->rooms[s->p - 1]]->name, lem->salles[lem->salles[room]->papa]->name);
				if (s->rooms[s->p - 1] == lem->salles[room]->papa)
				{
					lem->salles[room]->papa = 0;
					lem->salles[room]->visited = 0;
				}
				// printf("%d\n", tmp->element->visited);
				// printf("%s    %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
				// return (0);
			}
			// printf("%s ", lem->salles[lem->paths[i - 1]->path[p]]->name);
		}
	}
	return (1);

}

int		visit_rooms(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int elem)
{

	// printf("%s\n", tmp->element->);
	// printf("av room = %s  %s %s       %d %d\n", lem->salles[s->rooms[s->p]]->name, lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name, tmp->element->dir_salle1, tmp->element->dir_salle2);
	// s->count > 0 ? printf("avant %s    %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name):0;
	if (lem->salles[tmp->element->salle_2]->visited || lem->salles[tmp->element->salle_1]->visited)
	{
		for (int m = 0; m <= elem; m++)
		{
			if (s->rooms[(s->p - m)] == 3428 && s->count == 2)
			{
				printf("le bug = %s   ", lem->salles[s->rooms[(s->p - m)]]->name);
				printf("chemin = %d = %d\n", s->count, s->p - m);
				printf("%s   %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
			}

		}
		s->rooms[s->p] == tmp->element->salle_2 ? check_cross(lem, s, tmp, tmp->element->salle_1) : check_cross(lem, s, tmp, tmp->element->salle_2);
	}
	if (!lem->salles[tmp->element->salle_2]->visited && tmp->element->salle_2 != s->rooms[s->p] && !tmp->element->dir_salle2 && croissement(lem, s, tmp, 0))
	{
		elem++;
		// printf("room = %s  %s %s       %d %d\n", lem->salles[s->rooms[s->p]]->name, lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name, tmp->element->dir_salle1, tmp->element->dir_salle2);
		// printf("size q = %d\n", s->size_q);
		// printf("1ste while - - - - %s\n", lem->salles[tmp->element->salle_2]->name);
		s->rooms[0 + elem + s->size_q] = tmp->element->salle_2;
		lem->salles[tmp->element->salle_2]->papa = s->rooms[s->p];
		lem->salles[tmp->element->salle_2]->visited++;
		tmp->element->visited++;
		// printf("%s    %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
		// printf("queue = %d %s\n", 0 + elem + s->size_q, lem->salles[s->rooms[0 + elem + s->size_q]]->name);
	}
	else if (tmp->element->salle_2 == s->rooms[s->p] && !lem->salles[tmp->element->salle_1]->visited && !tmp->element->dir_salle1 && croissement(lem, s, tmp, 1))
	{
		elem++;
		// printf("room = %s  %s %s       %d %d\n", lem->salles[s->rooms[s->p]]->name, lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name, tmp->element->dir_salle1, tmp->element->dir_salle2);
		// printf("2de while - - - - %s\n", lem->salles[tmp->element->salle_1]->name);
		s->rooms[0 + elem + s->size_q] = tmp->element->salle_1;
		lem->salles[tmp->element->salle_1]->visited++;
		lem->salles[tmp->element->salle_1]->papa = s->rooms[s->p];
		tmp->element->visited++;
		// printf("%s    %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
	}
	return (elem);
}

void 	ft_bfs(t_lem *lem, t_solve *s, int way)
{
	int elem;
	t_ptr_couloir *tmp;

	// for (int l = 0; l<lem->nbr_salles;l++)
	// {
	// 	// printf("yop \n");
	// 	printf("%s ", s->rooms[l] != -1 ? lem->salles[s->rooms[l]]->name : "-1");
	// }
	// printf("\n");

	while (++s->p < lem->nbr_salles)
	{
		// printf("queue = %d %s\n", s->p, lem->salles[s->rooms[s->p]]->name);
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
					// for (int l = 0; l < lem->paths[way]->size;l++)
					// {
					// 	printf("%s ", lem->salles[lem->paths[way]->path[l]]->name);
					// }
					// printf(" == j'ai mon chemin\n");
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

void 	finilize_merge(t_lem *lem, int way1, int way2)
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
	while(++i < lem->paths[way1]->size)
	{
		lem->paths[way1]->path[i] = lem->paths[way1]->f_path[i];
		lem->paths[way1]->f_path[i] = '\0';
	}
	i = -1;
	while(++i < lem->paths[way2]->size)
	{
		lem->paths[way2]->path[i] = lem->paths[way2]->f_path[i];
		lem->paths[way2]->f_path[i] = '\0';
	}
	// lem->merge->dir_salle1 = 0;
	// lem->merge->dir_salle2 = 0;
}

int		ft_calcul_etapes(t_lem *lem, int chemins)
{
	// int		i;
	// int		len_path;
	// double	calcul;
	//
	// i = -1;
	// len_path = 0;
	// calcul = 0.0;
	// while (++i < chemins)
	// {
	// 	len_path += (lem->paths[i]->size - 1);
	// }
	// calcul = (double)((lem->fourmis + len_path) / chemins) - 1;
	// calcul > (int)calcul ? calcul++ : 0;
	// // printf("apres = %d\n", (int)calcul);
	// if (!lem->nbr_etapes)
	// 	lem->nbr_etapes = calcul;
	// else if (lem->nbr_etapes > calcul)
	// 	lem->nbr_etapes = calcul;
	// if (lem->nbr_etapes < calcul)
	// 	return (1);
	// return (0);

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
    nb_turn =  sum / i + nb_ants / i + !!(nb_ants % i);
	if (!lem->nbr_etapes)
		lem->nbr_etapes = nb_turn;
	else if (lem->nbr_etapes > nb_turn)
		lem->nbr_etapes = nb_turn;
	if (lem->nbr_etapes < nb_turn)
		return (1);
	return (0);
}

int		ft_modify_directions(t_lem *lem, int way)
{
	int i;
	int merge;
	int room1;
	int room2;
	t_ptr_couloir *tmp;

	i = -1;
	merge = 0;
	// printf("- - - je rentre dans modify direction - - -\n");
	while (++i < lem->paths[way]->size - 1)
	{
		room1 = lem->paths[way]->path[i];
		room2 = lem->paths[way]->path[i + 1];
		// printf("le room 2 = %s\n", lem->salles[room2]->name);
		tmp = lem->salles[lem->paths[way]->path[i]]->couloirs;
		while (tmp && ((tmp->element->salle_1 != room2 && tmp->element->salle_2 == room1) || (tmp->element->salle_2 != room2 && tmp->element->salle_1 == room1)))
		{
			// printf(" mod - = %s   = %s\n", lem->salles[tmp->element->salle_1]->name, lem->salles[tmp->element->salle_2]->name);
			tmp = tmp->next;
		}
		if (tmp && tmp->element->salle_1 == room2)
		{
			tmp->element->dir_salle1 = 1;
			// if (!merge && tmp->element->dir_salle1 && tmp->element->dir_salle2)
			// {
			// 	merge++;
			// 	lem->merge = tmp->element;
			// }
		}
		if (tmp && tmp->element->salle_2 == room2)
		{
			tmp->element->dir_salle2 = 1;
		}
		if (!merge && tmp->element->dir_salle1 && tmp->element->dir_salle2)
		{
			merge++;
			lem->merge = tmp->element;
		}
	}
	// for (int k = 0; k < lem->nbr_salles; k++)
	// {
	// 	tmp = lem->salles[k]->couloirs;
	// 	printf("%s\n", lem->salles[k]->name);
	// 	while (tmp)
	// 	{
	// 		printf("dir 1 = %d dir 2 = %d\n", tmp->element->dir_salle1, tmp->element->dir_salle2);
	// 		tmp = tmp->next;
	// 	}
	// }
	return (merge);

}

void		ft_reset_rooms(t_lem *lem, t_solve *s)
{
	int i;
	t_ptr_couloir *tmp;

	i = -1;
	// printf("reset rooms\n");
	while (++i < lem->nbr_salles)
	{
		tmp = lem->salles[i]->couloirs;
		lem->salles[i]->visited = 0;
		lem->salles[i]->papa = 0;
		i ? s->rooms[i] = -1 : 0;
		// while (tmp)
		// {
		// 	lem->salles[i]->couloirs->element->visited = 0;
		// 	tmp = tmp->next;
		// }
	}
	s->size_q = 0;
	s->p = -1;
}

void 	ft_merge_way(t_lem *lem, int way, int alt, int i)
{
	int b;
	int ok;

	b = -1;
	ok = 0;
	// printf("le i = %d\n", i);
	// printf("check %s \n", lem->salles[lem->paths[way]->f_path[3]]->name);
	while (++b < lem->paths[alt]->size)
	{
		if (ok || lem->paths[way]->f_path[i] == lem->paths[alt]->path[b])
		{
			lem->paths[way]->f_path[i++] = lem->paths[alt]->path[b];
			ok++;
		}
	}
	lem->paths[way]->f_size = i;
	// printf("---- count af merge = %d %d\n", lem->paths[way]->f_size, i);
	// printf("result merge\n");
	// for (int i = 0;i < lem->paths[way]->f_size; i++)
	// {
	// 	printf("%s ", lem->salles[lem->paths[way]->f_path[i]]->name);
	// }
	// printf("\n- - - - - - - - - - - - - - - - - - - - -\n");
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
		{
			len_path += lem->paths[i]->f_size - 1;
			// printf("f_size = %d\n", lem->paths[i]->f_size);
		}
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
	nb_turn =  len_path / i + nb_ants / i + !!(nb_ants % i);

	// printf("len path = %d\n", len_path);
	// calcul = (double)((lem->fourmis + len_path) / chemins) - 1;
	// calcul > (int)calcul ? calcul++ : 0;
	// printf("nombre d'etapes apres merge %f\n", calcul);
	if (lem->nbr_etapes >= nb_turn)
	{
		finilize_merge(lem, chemins - 1, alt);
		lem->nbr_etapes = nb_turn;
	}


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
			if ((lem->paths[i]->path[k] == room1 && lem->paths[i]->path[k-1] == room2) || (k <= lem->paths[i]->size && lem->paths[i]->path[k] == room1 && lem->paths[i]->path[k+1] == room2))
				return (i);
		}
	}
	return (0);
}

int 	doublecon(t_lem *lem, int way, int alt)
{
	int k;
	int i;
	int count;

	i = 0;
	count = 0;

	// printf("way %s\n", lem->salles[lem->paths[way]->path[i]]->name);
	// printf("alt %s\n", lem->salles[lem->paths[way]->path[1]]->name);
	// printf("alt %s\n", lem->salles[lem->paths[way]->path[2]]->name);
	// printf("alt %s\n", lem->salles[lem->paths[way]->path[3]]->name);
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
				// printf("way = %d    node = %s   %s\n", way, lem->salles[lem->paths[way]->path[k]]->name, lem->salles[lem->paths[alt]->path[z]]->name);
				if (lem->paths[way]->path[k] == lem->paths[alt]->path[z])
					return (lem->paths[way]->path[k]);
			}
	}
	return (0);

}

void 	ft_merge(t_lem *lem, int way, int tomerge)
{
	int		way2;
	int		i;
	int		ok;
	int		r1;
	int		r2;

	ok = 0;
	i = -1;
	// printf("to merge = %d\n",tomerge );
	while (tomerge--)
	{
		way2 = way_for_merge(lem, way);
		// printf("node a merger  = %s   %s\n", lem->salles[node_to_megre(lem, way, way2)]->name, lem->salles[node_to_megre(lem, way2, way)]->name);
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
	// printf("etapes av = %d\n", lem->nbr_etapes);
	ft_calcul_merge(lem, way + 1, way2);
	// printf("~~~~~~~~~~~~~~~~~~~~~~~~ \n way1 %d\n", way);
	// for (int i = 0;i < lem->paths[way]->f_size; i++)
	// {
	// 	printf("%s ", lem->salles[lem->paths[way]->f_path[i]]->name);
	// }
	// printf("\n way 2\n");
	// for (int i = 0;i < lem->paths[way2]->f_size; i++)
	// {
	// 	printf("%s ", lem->salles[lem->paths[way2]->f_path[i]]->name);
	// }
	// printf("\n");
}

int 	ft_nbr_merge(t_lem *lem)
{
	int i;
	int count;
	t_ptr_couloir *tmp;

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

int		ft_solve_path(t_lem *lem)
{
	t_solve		s;
	int 		i;
	int 		merge;
	int			stop;
	int 		max_way;

	ft_bzero(&s, sizeof(s));
	s.p = -1;
	i = -1;
	ft_init_queue(lem, &s);
	max_way = (s.start > s.end) ? s.start : s.end;
	lem->paths = (t_path**)ft_memalloc(sizeof(t_path*) * (max_way));
	while (++i < max_way && i < lem->fourmis)
	{
		ft_bfs(lem, &s, i);
		// printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		if (lem->stop)
			break ;
		stop = ft_calcul_etapes(lem, i + 1);
		if (stop)
			break ;
		ft_reset_rooms(lem, &s);
		merge = ft_modify_directions(lem, i);
		if (i == 2)
		{
			printf("merge needed %d\n", merge);
			merge ? printf("%s %s %d %d \n", lem->salles[lem->merge->salle_1]->name, lem->salles[lem->merge->salle_2]->name, lem->merge->dir_salle1, lem->merge->dir_salle2) :0;
		}
		if (merge)
		{
			printf("nbr de merge %d\n", ft_nbr_merge(lem)/2);
			ft_merge(lem, i, ft_nbr_merge(lem)/2);
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

void 		go_fourmis(t_lem *lem, int chemin)
{
	int len_chemin;

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
			printf("L%d-%s chemin=%d, salles=%d    ",lem->salles[lem->paths[chemin]->path[i]]->fourmis, lem->salles[lem->paths[chemin]->path[i]]->name, chemin, i);
			// printf("je ne rentre pas\n");
		}
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_lem	lem;
	t_ptr_couloir *tmp;
	int 	chemin;
	int i;

	chemin = 0;
	// if (argc == 2)
	// {
		ft_bzero(&lem, sizeof(lem));
		lem.ant = 1;
		// lem.fd = open(argv[1], O_RDONLY);
		ft_read_map(&lem);
		ft_crea_salles(&lem);
		ft_link_couloir(&lem);
		int nbr_coul = 0;
		tmp = lem.salles[3428]->couloirs;
		while (tmp)
		{
			nbr_coul++;
			printf("%s  - - - ", tmp->element->salle_1 != 3428 ? lem.salles[tmp->element->salle_1]->name : lem.salles[tmp->element->salle_2]->name);
			tmp = tmp->next;

		}
		printf("nbr de couloir = %d\n", nbr_coul);
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
		// unsigned long check;
		// int check = 0;
		chemin = ft_solve_path(&lem);
		int check = 0;
		int b = 1;
		int p = -1;
		// printf("= %d - - - - - - - - - - - - len_chemin = %d\n", lem.salles[lem.paths[chemin]->path[8]]->fourmis, 8);
		while (/*!lem.last_ant */b--)
		{
			i = -1;
			while (++i < chemin)
			{
				!lem.last_ant ? go_fourmis(&lem, i): 0;
			}
			printf("\n");
			check++;
		}
		//
		// printf("\n\n- - - - - - - - - - - - - - - - \n\n");
		// // printf("le fameux check = %d\n", check);
		// // printf("chemin = %d\n", chemin);
		// for(int k = 0; k < chemin; k++)
		// {
		// 	for (int l = 1; l < lem.paths[k]->size-1; l++)
		// 	{
		// 		ft_putstr(lem.salles[lem.paths[k]->path[l]]->name);
		// 		write (1, " ", 1);
		// 		for (int h = k; h < chemin ; h++)
		// 		{
		// 			for (int z = 1; z < lem.paths[k]->size - 1; z++)
		// 			{
		// 				if ((l != z && k != h) && lem.paths[k]->path[l] == lem.paths[h]->path[z])
		// 					printf("--- CROISEMENT --- %s ways = %d<-->%d pl %d<-->%d",lem.salles[lem.paths[k]->path[l]]->name, k , h, l, z);
		// 					// printf("CROISEMENT");
		// 			}
		//
		// 		}
		//
		// 	}
		// 	// printf(" -- %d", lem.paths[k]->size);
		// 	printf("\n");
		// }
		printf("nb_turn %d\n", lem.nbr_etapes);
	return (0);
}
//
