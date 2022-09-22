/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:27:05 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/20 11:52:23 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	_put_pixel(t_pos *a, int color, t_mlx *mlx)
{
	char	*dst;

	if ((a->x < WIDTH && a->y < HEIGHT) && (a->x >= 0 && a->y >= 0))
	{
		dst = mlx->p_addr + (((int)a->y * mlx->len)
				+ ((int)a->x * (mlx->bpp / 8)));
		*(unsigned int *)dst = color;
	}
	return (1);
}

int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}

void	_dda_line(t_pos a, t_pos b, int color, t_mlx *mlx)
{
	t_pos	delta;
	t_pos	cur;
	double	step;

	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);
	step = find_max(mod(delta.x), mod(delta.y));
	delta.x /= step;
	delta.y /= step;
	cur = a;
	while ((int)step-- && _put_pixel(&cur, color, mlx))
	{
		cur.x += delta.x;
		cur.y += delta.y;
	}
}

void	draw_rect(t_pos start, t_pos end, t_mlx *mlx, int color)
{
	t_pos	tmp;
	int		i;

	tmp.x = end.x;
	tmp.y = start.y;
	i = -1;
	while (++i < end.y)
	{
		_dda_line(start, tmp, color, mlx);
		start.y++;
		tmp.y++;
	}
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_all(t_data *data)
{
	t_pos	pos_floor;
	t_pos	pos_sky;
	t_pos	pos_end;
	int		clr_sly;
	int		clr_floor;

	pos_sky.x = 0;
	pos_sky.y = 0;
	pos_floor.x = 0;
	pos_floor.y = HALF_HEIGHT;
	pos_end.x = WIDTH;
	pos_end.y = HEIGHT / 2;

	clr_sly = create_rgb(data->params->ce_rgb[0], \
		data->params->ce_rgb[1], data->params->ce_rgb[2]);
	clr_floor = create_rgb(data->params->fl_rgb[0], \
		data->params->fl_rgb[1], data->params->fl_rgb[2]);

	draw_rect(pos_sky, pos_end, data->mlx, clr_sly);
	draw_rect(pos_floor, pos_end, data->mlx, clr_floor);
	ray_cast2(data);

	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win, \
		data->mlx->p_img, 0, 0);
}
