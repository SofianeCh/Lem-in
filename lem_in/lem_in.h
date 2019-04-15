/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:55 by sofchami          #+#    #+#             */
/*   Updated: 2019/04/15 17:16:44 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <fcntl.h>

typedef struct s_salle t_salle;

typedef struct		s_couloir
{
	int				salle_1;
	int				salle_2;
	t_salle			*salle_origine;
	t_salle			*salle_dest;
	int				dir_orig;
	int				dir_dest;

}					t_couloir;

typedef struct		s_salle
{
	char			*name;
	int				index_s;
	int				start;
	int				fourmis;
	int				end;
	int				nbr_voisin;
	t_list			*couloir2;
	t_couloir		**couloirs;
}					t_salle;

typedef struct		s_lem
{
	int				lignes;
	int				dieze;
	int				pos_start;
	int				pos_end;
	int				probleme;
	int				comm;
	int				len;
	int				fd;
	int				ret;
	int				fourmis;
	int				nbr_salles;
	int				couloirs;
	int				nbr_connection;
	char			*tmp;
	char			*buff;
	char			*line;
	t_salle			**salles;
	int				index[10000];
	int				hash[10000];
	int				b_size;
}					t_lem;
#endif
