/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_shortest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpousseu <rpousseu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:35:20 by rpousseu          #+#    #+#             */
/*   Updated: 2019/04/18 22:38:08 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#define NB 9
void	append_to_array(int **array, int toadd)
{
	int i;

	i = -1;
	while ((*array)[++i])
		;
	(*array)[i] = toadd;
}

char    in_array(int e, int *array)
{
	int		i;

	i = -1;
	while (array && array[++i] != -1)
		if (e == array[i])
			return (1);
	return (0);
}

void	init_array(int **array, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		(*array)[i] = -1;
}

int		*find_all(int tunnels[NB][2], int tofind, int *prev, int *current)
{
	int		*ret;
	int		i;
	int		ret_i;

	i = -1;
	ret_i = -1;
	if (!(ret = (int*)malloc(sizeof(int) * 100)))
		return (NULL);
	init_array(&ret, 100);
	while (++i < NB)
	{
		if (tunnels[i][0] == tofind && !in_array(tunnels[i][1], prev)
		&& !in_array(tunnels[i][1], current))
			ret[++ret_i] = tunnels[i][1];
		if (tunnels[i][1] == tofind && !in_array(tunnels[i][0], prev)
		&& !in_array(tunnels[i][0], current))
			ret[++ret_i] = tunnels[i][0];
	}
	ret[++ret_i] = -1;
	return (ret);
}

char    is_end_of_path(int tunnels[NB][2], int elem, int end)
{
	if (tunnels[elem][0] == end || tunnels[elem][1] == end)
		return (1);
	return (0);
}

int		make_layer_of_layer(int tunnels[NB][2], int *layer, int *prev, int end, int **path)
{
	int		*new_layer;
	int		*chunk;
	int		l_i;
	int		c_i;
	int		nl_i;
	int		stat;

	l_i = -1;
	nl_i = -1;
	if (!(new_layer = (int*)malloc(sizeof(int) * 100)))
		return (-1);
	init_array(&new_layer, 100);
	while (layer[++l_i] != -1)
	{
		c_i = -1;
		chunk = find_all(tunnels, layer[l_i], prev, new_layer);
		while (chunk[++c_i] != -1)
		{
			if (chunk[c_i] != end)
				new_layer[++nl_i] = chunk[c_i];
			else
			{
				printf("-->%d\n-->%d\n", chunk[c_i], layer[l_i]);
				append_to_array(path, chunk[c_i]);
				return (layer[l_i]);
			}
		}
	}
	new_layer[++nl_i] = -1;
	if ((stat = make_layer_of_layer(tunnels, new_layer, layer, end, path)) > -1)
	{
		append_to_array(path, stat);
		l_i = -1;
		while (layer[++l_i] != -1)
		{
			// NOTE : make this efficient
			c_i = -1;
			chunk = find_all(tunnels, layer[l_i], prev, NULL);
			while (chunk[++c_i] != -1)
			{
				if (stat == chunk[c_i])
				{
					printf("-->%d\n", layer[l_i]);
					return (layer[l_i]);
				}
			}
		}
	}
	return (-1);
}

/* NOTE :

LAYER COMPOSITION :

[new_room1]
[new_room2]
[   etc   ]


*/


int		make_paths(int tunnels[NB][2], int ends[2])
{
	/* NOTE : creates first layer with the starting room and calls the recursive func */
	int *first_layer;
	int *path;
	int i;

	i = -1;
	if (!(first_layer = (int*)malloc(2 * sizeof(int))))
		return (-1);
	if (!(path = (int*)malloc(100 * sizeof(int))))
		return (-1);
	while (++i < 30)
		path[i] = 0;
	first_layer[0] = ends[0];
	first_layer[1] = -1;
	append_to_array(&path, make_layer_of_layer(tunnels, first_layer, NULL, ends[1], &path));
	i = -1;
	/*while (path[++i])
		printf("%d-", path[i]);*/
	return (1);
}

int		main(void)
{
	//int ends[2] = {10, 11};

	//  EXEMPLES
	/*int tunnels[11][2] = {
		{0, 4},
		{0, 6},
		{1, 3},
		{4, 3},
		{5, 2},
		{4, 2},
		{2, 1},
		{7, 6},
		{7, 2},
		{7, 4},
		{6, 5}
	};
	int tunnels[NB][2] = {
		{0, 1},
		{0, 2},
		{2, 3},
		{3, 4},
		{4, 1}
	};*/
	int ends[2] = {10, 11};
	int tunnels[NB][2] = {
		{10, 1},
		{3, 4},
		{2, 4},
		{1, 5},
		{6, 5},
		{11, 6},
		{1, 2},
		{2, 11},
		{3, 10}
	};
	make_paths(tunnels, ends);
	/*int *ret = find_all(tunnels, 0);
	int i = -1;
	while (ret[++i] != -1)
		printf("%d  %d\n", tunnels[ret[i]][0], tunnels[ret[i]][1]);*/
	return (0);
}
