/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:52:18 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 18:59:05 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	get_num_wall(const t_map map)
{
	int		iters[2];
	int		count;

	iters[0] = -1;
	count = 0;
	while (++(iters[0]) < map.rows)
	{
		iters[1] = -1;
		while (++(iters[1]) < map.cols)
		{
			if (map.matrix[iters[0]][iters[1]] == WALL)
				count++;
		}
	}
	return (count);
}

t_pos_int	*sort_pos(t_pos_int *a, const int num_wall)
{
	t_pos_int	tmp;
	int			i;
	int			j;

	i = num_wall;
	while (--i > 0)
	{
		j = -1;
		while (++j < i)
		{
			if (a[j].pos[X] > a[j + 1].pos[X])
			{
				tmp.pos[X] = a[j].pos[X];
				tmp.pos[Y] = a[j].pos[Y];
				a[j].pos[X] = a[j + 1].pos[X];
				a[j].pos[Y] = a[j + 1].pos[Y];
				a[j + 1].pos[X] = tmp.pos[X];
				a[j + 1].pos[Y] = tmp.pos[Y];
			}
		}
	}
	return (a);
}
