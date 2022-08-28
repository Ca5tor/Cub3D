/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 01:32:27 by ltacos            #+#    #+#             */
/*   Updated: 2022/08/26 19:46:27 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	_set_background(t_mlx *mlx)
{
	int	*img;
	int	i;

	i = 0;
	img = (int *)(mlx->p_addr);
	while (i < HEIGHT * WIDTH)
		img[i++] = BACKGROUND >> 2;
}

void	put_cub_plyr(int x, int y, t_mlx *mlx)
{
	char	*dst;
	int		color;

	color = PLAYER_B;
	dst = mlx->p_addr + ((y * mlx->len) + (x * (mlx->bpp / 8)));
		*(unsigned int *)dst = color;
}

void	put_cub(int type, int x, int y, t_mlx *mlx)
{
	char	*dst;
	int		color;

	if (type == WL)
		color = WALL_B;
	else if (type == FR)
		color = FLOOR_B;
	else if (type == PR_N || type == PR_S || type == PR_E || type == PR_W)
		color = FLOOR_B;
	else
		return ;
	dst = mlx->p_addr + ((y * mlx->len) + (x * (mlx->bpp / 8)));
		*(unsigned int *)dst = color;
}

void	print_cub_plyr(t_obj obj, int len, t_mlx *mlx)
{
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++)
			put_cub_plyr(i + (obj.x * len), j + (obj.y * len), mlx);
	
}

void	print_cub(t_obj obj, int len, t_mlx *mlx)
{
	for (int i = 0; i < len; i++)
		for (int j = 0; j < len; j++)
			put_cub(obj.type, i + (obj.x * len), j + (obj.y * len), mlx);
}

void	draw(t_data *data)
{
	int	i;

	_set_background(data->mlx);
	i = -1;
	while (++i < 64)
		print_cub(data->map_obj->obj[i], data->map_obj->size_obj, data->mlx);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win,
		data->mlx->p_img, 0, 0);
}

double	find_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

void	rey_cast(t_mlx *mlx, t_data *data)
{
	//print_cub_plyr(data->plyr->obj, data->map_obj->size_obj, data->mlx);
	double left = data->plyr->obj.x - data->plyr->obj.x / data->map_obj->size_obj * data->map_obj->size_obj;
	double top = data->plyr->obj.y - data->plyr->obj.y / data->map_obj->size_obj * data->map_obj->size_obj;
	double right = data->map_obj->size_obj - (left);
	double botton = data->map_obj->size_obj - (top);
	t_obj line_see;



	for (int i = 0; i < NUM_RAYS; i++)
	{
		double cur_ang = data->plyr->angle - HALF_FOV + 0.1 * i;
		double cos_a = cos(cur_ang);
		double sin_a = sin(cur_ang);
		double vd = 0, hd = 0;

		
	
//50 - block size
			//verticale
		for (size_t i = 0; i < MAX_DEPTH; i++)
		{
			if (cos_a > 0)
				vd = right / cos_a + 50 / cos_a * i + 1;
			else if (cos_a < 0)
				vd = left / (-cos_a) + 50 / (-cos_a) * i + 1;
			double x = vd * cos_a + data->plyr->obj.x;
			double y = vd * sin_a + data->plyr->obj.y;
			double fix_x = x / 50 * 50;
			double fix_y = y / 50 * 50;
			int f = 0;
			for (size_t j = 0; j < 34; j++)
			{
				if (fix_x < data->map_obj->obj[j].x && fix_y < data->map_obj->obj[j].y)
				{
					f = 1;
					break;
				}
					
			}
			if (f)
				break;
		}
		
		//gorizontal
		for (size_t i = 0; i < MAX_DEPTH; i++)
		{
			if (sin_a > 0)
				hd = botton / sin_a + 50 / sin_a * i + 1;
			else if (sin_a < 0)
				hd = top / (-sin_a) + 50 / (-sin_a) * i + 1;
			double x = hd * cos_a + data->plyr->obj.x;
			double y = hd * sin_a + data->plyr->obj.y;
			double fix_x = x / 50 * 50;
			double fix_y = y / 50 * 50;
			int f = 0;
			for (size_t j = 0; j < 34; j++)
			{
				printf("Fx=%f Ox=%f\n", fix_x, data->map_obj->obj[j].x);
				printf("Fy=%f Oy=%f\n", fix_y, data->map_obj->obj[j].y);
				if (fix_x < data->map_obj->obj[j].x && fix_y < data->map_obj->obj[j].y)
				{
					f = 1;
					break;
				}
					
			}
			if (f)
				break;
			// if (fix_x == data->map_obj->obj[i].x && fix_y == data->map_obj->obj[i].y)
			// 	break;
		}
		printf("hd=%f vd=%f\n", hd, vd);
		int ray_size = find_min(hd, vd);
		line_see.x = ray_size * cos(cur_ang) + data->plyr->obj.x * data->map_obj->size_obj;
		line_see.y = ray_size * sin(cur_ang) + data->plyr->obj.y * data->map_obj->size_obj;
		//print_cub_plyr(data->plyr->obj, data->map_obj->size_obj, data->mlx);
		_dda_line(data->plyr->obj, line_see, data);
	}

	
	
}

void	draw_player(t_data *data)
{
	draw(data);
	
	rey_cast(data->mlx, data);
	// t_obj line_see;
	// int ray_size = WIDTH;

	// line_see.x = ray_size * cos(data->plyr->angle) + data->plyr->obj.x * data->map_obj->size_obj;
	// line_see.y = ray_size * sin(data->plyr->angle) + data->plyr->obj.y * data->map_obj->size_obj;
	// print_cub_plyr(data->plyr->obj, data->map_obj->size_obj, data->mlx);
	// _dda_line(data->plyr->obj, line_see, data);
	//print_cub_plyr(data->plyr->obj, data->map_obj->size_obj, data->mlx);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win,
		data->mlx->p_img, 0, 0);
}
