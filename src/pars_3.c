/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:13:45 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:16:05 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	map_free_matrix(int	**matrix, int rows)
{
	int	i;

	i = -1;
	while (++i < rows)
		free(matrix[i]);
	free(matrix);
}

bool	map_is_floor(int c)
{
	return (c == NORTH || c == SOUTH
		|| c == EAST || c == WEST || c == SPACE || c == 0);
}

bool	map_is_safe(int x, int y, int **mtx, t_map *map)
{
	if (x >= 0 && x < map->rows
		&& y >= 0 && y < map->cols && (map_is_floor(mtx[x][y])))
		return (true);
	return (false);
}

void	map_dfs(int x, int y, int **mtx, t_map *map)
{
	int	k;
	int	r[4];
	int	c[4];

	r[0] = 0;
	r[1] = 0;
	r[2] = 1;
	r[3] = -1;
	c[0] = 1;
	c[1] = -1;
	c[2] = 0;
	c[3] = 0;
	mtx[x][y] = 1;
	k = -1;
	while (++k < 4)
		if (map_is_safe(x + r[k], y + c[k], mtx, map))
			map_dfs(x + r[k], y + c[k], mtx, map);
}

void	map_exclude_border(int **mtx, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->cols)
		if (map_is_floor(mtx[0][i]))
			map_dfs(0, i, mtx, map);
	i = -1;
	while (++i < map->cols)
		if (map_is_floor(mtx[map->rows - 1][i]))
			map_dfs(map->rows - 1, i, mtx, map);
	i = -1;
	while (++i < map->rows)
		if (map_is_floor(mtx[i][0]))
			map_dfs(i, 0, mtx, map);
	i = -1;
	while (++i < map->rows)
		if (map_is_floor(mtx[i][map->cols - 1]))
			map_dfs(i, map->cols - 1, mtx, map);
}
