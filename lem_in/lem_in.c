/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/04/15 22:23:41 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Proteger les malloc.
** Liez les couloirs au chambres
** gestions des couloirs
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
	char	*str;

	i = 0;
	lem->fourmis = ft_atoi(s);
	while (s[i])
		i++;
	if ((str = (char*)malloc(sizeof(*str) * i + 1)) == 0)
		return (!(lem->probleme = 1) ? NULL : 0);
	i = -1;
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
		if (s[i] == '\n' && !lem->couloirs)
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
	str[i] = 0;
	return (str);
}

void			ft_read_map(t_lem *lem)
{
	lem->b_size = 2000;
	lem->buff = ft_strnew(lem->b_size - 1);
	while ((lem->ret = read(lem->fd, lem->buff, lem->b_size)) > 0)
	{
		lem->len += lem->ret;
		lem->b_size *= 1.6;
		lem->tmp = lem->line;
		lem->line = !lem->line ? ft_strdup(lem->buff) :
		ft_strjoin2(lem->line, lem->buff);
		ft_cln(&lem->tmp, &lem->buff, NULL);
		lem->buff = ft_strnew(lem->b_size - 1);
	}
	lem->tmp = lem->line;
	lem->line = ft_strdup2(lem->line, lem);
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

	hash = 5381;
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '-' && str[i] != '\n')
	{
		c = str[i];
		hash = ((hash << 7) + hash) + c;
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
		lem->hash[i] = hash((unsigned char*)(lem->line + lem->index[jump]));
		lem->salles[i]->couloirs = NULL;
		// ft_printf("nom des salles = %s\n", lem->salles[i]->name);
		// ft_printf("start = %d et end = %d\n", lem->salles[i]->start, lem->salles[i]->end);
		ft_printf("nom salle = %s et hash par salles = %lu\n", lem->salles[i]->name, lem->hash[i]);
		jump++;
	}
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

t_couloir	*ft_list(t_couloir *couloir, int prem, int deux)
{
	t_couloir	*new;

	if ((new = (t_couloir*)malloc(sizeof(*new))) == NULL)
		return (NULL);
	if (!couloir)
	{
		new->salle_1 = prem;
		new->salle_2 = deux;
		new->next = NULL;
	}
	else
	{
		if ((new->content = (void*)malloc(content_size)) == NULL)
			return (NULL);
		ft_memcpy(new->couloir, couloir, sizeof(couloir));
		new->next = NULL;
	}
	return (new);
}

void ft_verif(t_lem *lem, int prem, int deux)
{
	lem->salles[prem]->couloir2

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
			if (lem->salles[prem]->couloirs)
			{
				ft_verif(lem, prem, deux);
			}
			else
				lem->salles[prem]->couloirs = ft_list((void*)&clr, sizeof(clr));
		}
		// ft_lstadd(salle->couloirs, node);
		// t_couloir *couloir;
		// while (list)
		// {
		// 	couloir = (t_couloir *)list->content;
		// 	couloir->a
		// 	list = list->next;
		// }
		index_c += len + 1;
	}
}

int			main(int argc, char **argv)
{
	t_lem	lem;

	if (argc == 2)
	{
		ft_bzero(&lem, sizeof(lem));
		lem.fd = open(argv[1], O_RDONLY);
		ft_read_map(&lem);
		ft_crea_salles(&lem);
		ft_link_couloir(&lem);
		// ft_printf("couloirs = %d\n", lem.couloirs);
		// printf("test: %d\n", lem.salles[0]->start);
		// printf("%s\n", lem.line);
		// ft_printf("\n\n\n");
		close(lem.fd);
	}
	// printf("%s\n", lem.line);
	return (0);
}
