/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:13:48 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:16:03 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	map_count_all_zeros(t_map *map)
{
	int	i;
	int	j;
	int	**mtx;
	int	zeros;

	mtx = map_copy_matrix(map->matrix, map->rows, map->cols);
	map_exclude_border(mtx, map);
	i = -1;
	zeros = 0;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (mtx[i][j] == 0 || map_is_num_direction(mtx[i][j]))
				zeros++;
			if (mtx[i][j] == SPACE)
				map->matrix[i][j] = 0;
		}
	}
	map_free_matrix(mtx, map->rows);
	return (zeros);
}

bool	parse_map(char **str_arr, t_map *map)
{
	int		i;
	int		j;
	int		fl;
	int		al;

	i = -1;
	fl = 0;
	map->matrix = map_get_empty_matrix(map->rows, map->cols);
	while (str_arr[++i])
	{
		j = -1;
		while (str_arr[i][++j])
		{
			map->matrix[i][j] = str_arr[i][j] - '0';
			fl += (map_is_direction(str_arr[i][j]) || str_arr[i][j] == '0');
		}
	}
	al = map_count_all_zeros(map);
	if (fl != al)
	{
		map_free_matrix(map->matrix, map->rows);
		map->matrix = NULL;
	}
	return (al == fl);
}

bool	map_pre_parse(char **str_arr, t_map *map)
{
	int		j;
	bool	is_pl_set;

	map->rows = -1;
	map->cols = 0;
	is_pl_set = false;
	while (str_arr[++map->rows])
	{
		j = -1;
		while (str_arr[map->rows][++j])
		{
			if ((map_is_direction(str_arr[map->rows][j]) && is_pl_set == true)
				|| !map_is_allowed_char(str_arr[map->rows][j]))
				return (false);
			if (map_is_direction(str_arr[map->rows][j]) && is_pl_set == false)
			{
				is_pl_set = true;
				map->pl_x = j;
				map->pl_y = map->rows;
			}
		}
		if (j > map->cols)
			map->cols = j;
	}
	return (is_pl_set && parse_map(str_arr, map));
}

/* ------------------ CFG PARSER ------------------*/

void	pars_exit_with_error(int code)
{
	if (code == BAD_FILE)
		printf("Bad file.\n");
	else if (code == BAD_CONFIG)
		printf("Bad config.\n");
	else if (code == BAD_MAP)
		printf("Bad map.\n");
	else if (code == BAD_KEY)
		printf("Bad key.\n");
	else if (code == BAD_TEXTURE)
		printf("Bad texture.\n");
	else if (code == BAD_RGB)
		printf("Bad RGB.\n");
	else if (code == BAD_EXTENSION)
		printf("Bad extension.\n");
	else if (code == BAD_ARGUMENT)
		printf("Bad argument.\n");
	exit(1);
}

void	pars_free_all(t_cub *cub)
{
	if (cub->params.so.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.so.img);
	if (cub->params.no.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.no.img);
	if (cub->params.we.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.we.img);
	if (cub->params.ea.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.ea.img);
	if (cub->params.ce_rgb != NULL)
		free(cub->params.ce_rgb);
	if (cub->params.fl_rgb != NULL)
		free(cub->params.fl_rgb);
	if (cub->map.matrix != NULL)
		map_free_matrix(cub->map.matrix, cub->map.rows);
	free(cub->mlx);
}
