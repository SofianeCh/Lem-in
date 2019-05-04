/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:55 by sofchami          #+#    #+#             */
/*   Updated: 2019/05/04 22:56:36 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "libft/ft_printf.h"
# include <fcntl.h>

typedef struct s_salle t_salle;

typedef struct			s_couloir
{
	int					salle_1;
	int					salle_2;
	t_salle				*salle_origine;
	t_salle				*salle_dest;
	int					dir_salle1;
	int					dir_salle2;
	struct s_couloir	*next;
}						t_couloir;

typedef struct			s_ptr_couloir
{
	t_couloir				*element;
	struct s_ptr_couloir	*next;
}						t_ptr_couloir;

typedef struct 		s_path
{
	int				size;
	int				f_size;
	int*			path;
	int				f_path[50000];
}					t_path;

typedef struct		s_salle
{
	char			*name;
	int				visited;
	int				papa;
	int				index_s;
	int				start;
	int				fourmis;
	int				end;
	int				nbr_voisin;
	t_ptr_couloir	*couloirs;
}					t_salle;

typedef struct 		s_solve
{
	int				*rooms;
	int				it;
	int				p;
	int				size_q;
	int				start;
	int				end;
	int				count;
}					t_solve;

typedef struct		s_lem
{
	int				lignes;
	int				dieze;
	int 			ant;
	int 			last_ant;;
	int 			nbr_etapes;
	int				pos_start;
	int				pos_end;
	int				comm;
	int				len;
	int				probleme;
	int				stop;
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
	t_path			**paths;
	t_couloir		*merge;
	int				index[50000];
	unsigned long	hash[50000];
	int				b_size;
}					t_lem;
#endif
