/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <sofchami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:08:55 by sofchami          #+#    #+#             */
/*   Updated: 2019/06/07 18:34:07 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include <fcntl.h>

typedef struct s_salle		t_salle;

typedef struct				s_couloir
{
	int						visited;
	int						salle_1;
	int						salle_2;
	t_salle					*salle_origine;
	t_salle					*salle_dest;
	int						dir_salle1;
	int						dir_salle2;
	struct s_couloir		*next;
}							t_couloir;

typedef struct				s_ptr_couloir
{
	t_couloir				*element;
	struct s_ptr_couloir	*next;
}							t_ptr_couloir;

typedef struct				s_path
{
	int						size;
	int						f_size;
	int*					path;
	int						f_path[50000];
}							t_path;

typedef struct				s_salle
{
	char					*name;
	int						visited;
	int						papa;
	int						index_s;
	int						start;
	int						fourmis;
	int						end;
	int						nbr_voisin;
	t_ptr_couloir			*couloirs;
}							t_salle;

typedef struct				s_solve
{
	int						*rooms;
	int						it;
	int						p;
	int						size_q;
	int						start;
	int						end;
	int						count;
}							t_solve;

typedef struct				s_lem
{
	int						lignes;
	int						dieze;
	int						ant;
	int						last_ant;;
	int						nbr_etapes;
	int						pos_start;
	int						pos_end;
	int						comm;
	int						len;
	int						probleme;
	int						stop;
	int						fd;
	int						ret;
	int						fourmis;
	int						nbr_salles;
	int						couloirs;
	int						nbr_connection;
	char					*tmp;
	char					*buff;
	char					*line;
	t_salle					**salles;
	t_path					**paths;
	t_couloir				*merge;
	int						index[50000];
	unsigned long			hash[50000];
	int						b_size;
}							t_lem;

t_couloir					*ft_list(t_lem *lem, int prem, int deux);
unsigned long				hash(unsigned char *str);
unsigned long				hash(unsigned char *str);
char						*ft_strjoin2(char const *s1, char const *s2);
char						*ft_strdup2(const char *s, t_lem *lem);
char						*ft_name(char *str);
int							ft_index(t_lem *lem, unsigned long hash);
int							ft_verif(t_ptr_couloir *list, int prem, int deux, t_lem *lem);
int							ft_check_names(char *line, char *name);
int							ft_index(t_lem *lem, unsigned long hash);
int							ft_verif(t_ptr_couloir *list, int prem, int deux, t_lem *lem);
int							ft_index(t_lem *lem, unsigned long hash);
int							visit_rooms(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int elem);
int 						croissement(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int num);
int							check_cross(t_lem *lem, t_solve *s, t_ptr_couloir *tmp, int room, int elem);
int							ft_modify_directions(t_lem *lem, int way);
int							ft_calcul_etapes(t_lem *lem, int chemins);
int 						node_to_megre(t_lem *lem, int way, int alt);
int							ft_solve_path(t_lem *lem);
int 						ft_nbr_merge(t_lem *lem);
int							way_for_merge(t_lem *lem, int way);
void 						ft_bfs(t_lem *lem, t_solve *s, int way);
void						ft_link_couloir(t_lem *lem);
void						crea_path(t_lem *lem, int p, int way);
void						ft_cln(char **line, char **line2, char **line3);
void						ft_crea_salles(t_lem *lem);
void						ft_init_queue(t_lem *lem, t_solve *s);
void						ft_read_map(t_lem *lem);
void						ft_calcul_merge(t_lem *lem, int chemins, int alt);
void 						ft_merge_way(t_lem *lem, int way, int alt, int i);
void 						ft_merge(t_lem *lem, int way, int tomerge);
void 						finilize_merge(t_lem *lem, int way1, int way2);
void 						go_fourmis(t_lem *lem, int chemin);
void						ft_reset_rooms(t_lem *lem, t_solve *s);

#endif
