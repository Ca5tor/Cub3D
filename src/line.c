/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 03:04:30 by ltacos            #+#    #+#             */
/*   Updated: 2022/08/26 19:47:49 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	_put_pixel(t_obj *a, int color, t_mlx *mlx)
{
	char	*dst;

	if ((a->x < WIDTH && a->y < HEIGHT) && (a->x > 0 && a->y > 0))
	{
		dst = mlx->p_addr + (((int)a->y * mlx->len)
				+ ((int)a->x * (mlx->bpp / 8)));
		*(unsigned int *)dst = color;
	}
	return (1);
}

double	find_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	mod(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	_dda_line(t_obj a, t_obj b, t_data *data)
{
	t_obj	delta;
	t_obj	cur;
	double	step;
	a.x *= data->map_obj->size_obj + 4.4;
	a.y *= data->map_obj->size_obj + 4.4;

	delta.x = (b.x - a.x);
	delta.y = (b.y - a.y);
	step = find_max(mod(delta.x), mod(delta.y));
	delta.x /= step;
	delta.y /= step;
	cur = a;
	while ((int)step-- && _put_pixel(&cur, PLAYER_B, data->mlx))
	{
		cur.x += delta.x;
		cur.y += delta.y;
	}
}
