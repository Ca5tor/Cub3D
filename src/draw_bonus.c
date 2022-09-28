/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:11:31 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/27 13:26:35 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	_put_pixel(t_pos_double *a, int color, t_mlx *mlx)
{
	char	*dst;

	if ((a->pos[X] < WIDTH && a->pos[Y] < HEIGHT) && \
		(a->pos[X] >= 0 && a->pos[Y] >= 0))
	{
		dst = mlx->p_addr + (((int)a->pos[Y] * mlx->len)
				+ ((int)a->pos[X] * (mlx->bpp / 8)));
		*(unsigned int *)dst = color;
	}
	return (1);
}

void	_dda_line(t_pos_double a, t_pos_double b, int color, t_mlx *mlx)
{
	t_pos_double	delta;
	t_pos_double	cur;
	double			step;

	delta.pos[X] = (b.pos[X] - a.pos[X]);
	delta.pos[Y] = (b.pos[Y] - a.pos[Y]);
	step = find_max(mod(delta.pos[X]), mod(delta.pos[Y]));
	delta.pos[X] /= step;
	delta.pos[Y] /= step;
	cur = a;
	while ((int)step-- && _put_pixel(&cur, color, mlx))
	{
		cur.pos[X] += delta.pos[X];
		cur.pos[Y] += delta.pos[Y];
	}
}

void	draw_rect(t_pos_double start, t_pos_double end, t_mlx *mlx, int color)
{
	t_pos_double	tmp;
	int				i;

	tmp.pos[X] = end.pos[X];
	tmp.pos[Y] = start.pos[Y];
	i = -1;
	while (++i < end.pos[Y])
	{
		_dda_line(start, tmp, color, mlx);
		(start.pos[Y])++;
		(tmp.pos[Y])++;
	}
}

static void	print_map2d(t_data *data)
{
	int				i;
	t_pos_double	start;
	t_pos_double	end;
	t_pos_double	plr_0;
	static int		cof = 8;

	i = -1;
	while (++i < data->num_wall)
	{
		start.pos[X] = (int)(data->map_pos[i].pos[X] / cof);
		start.pos[Y] = (int)(data->map_pos[i].pos[Y] / cof);
		end.pos[X] = (int)((data->map_pos[i].pos[X] / cof) + (TILE / cof - 1));
		end.pos[Y] = (int)(TILE / cof - 1);
		draw_rect(start, end, data->mlx, 0x00FFFF);
	}
	plr_0.pos[X] = ((data->plr->pos.pos[X] - (TILE / 2)) / cof);
	plr_0.pos[Y] = ((data->plr->pos.pos[Y] - (TILE / 2)) / cof);
	end.pos[X] = ((plr_0.pos[X]) + (TILE / cof - 1));
	end.pos[Y] = (TILE / cof - 1);
	draw_rect(plr_0, end, data->mlx, 0xADFF2F);
}

void	draw_all(t_data *data)
{
	t_pos_double	pos_floor;
	t_pos_double	pos_sky;
	t_pos_double	pos_end;

	pos_sky.pos[X] = 0;
	pos_sky.pos[Y] = 0;
	pos_floor.pos[X] = 0;
	pos_floor.pos[Y] = HEIGHT / 2;
	pos_end.pos[X] = WIDTH;
	pos_end.pos[Y] = HEIGHT / 2;
	draw_rect(pos_sky, pos_end, data->mlx, data->clr_fons[CLR_SKY]);
	draw_rect(pos_floor, pos_end, data->mlx, data->clr_fons[CLR_FLOOR]);
	ray_cast2(data);
	print_map2d(data);
	mlx_put_image_to_window(data->mlx->p_mlx, data->mlx->p_win, \
		data->mlx->p_img, 0, 0);
}
