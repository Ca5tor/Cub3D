/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 01:27:08 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 08:14:33 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static double	get_depth_v(t_data *data, t_param_rcst rcst, double *y)
{
	int		i;
	int		xh;
	int		dx;
	double	depth_v;

	dx = -1;
	xh = rcst.m_xy.x;
	if (rcst.cs.cos >= 0)
	{
		xh += BLOCK_SIZE;
		dx = 1;
	}
	i = -1;
	while (++i < (WIDTH / BLOCK_SIZE))
	{
		depth_v = (xh - rcst.o_xy.x) / rcst.cs.cos;
		*y = rcst.o_xy.y + depth_v * rcst.cs.sin;
		if (bin_search_pos(data, xh + dx, *y))
			break ;
		xh += dx * BLOCK_SIZE;
	}
	return (depth_v);
}

static double	get_depth_h(t_data *data, t_param_rcst rcst, double *x)
{
	int		i;
	int		yv;
	int		dy;
	double	depth_h;

	yv = rcst.m_xy.y;
	dy = -1;
	if (rcst.cs.sin >= 0)
	{
		yv += BLOCK_SIZE;
		dy = 1;
	}
	i = -1;
	while (++i < HEIGHT / BLOCK_SIZE)
	{
		depth_h = (yv - rcst.o_xy.y) / rcst.cs.sin;
		*x = rcst.o_xy.x + depth_h * rcst.cs.cos;
		if (bin_search_pos(data, *x, yv + dy))
			break ;
		yv += dy * BLOCK_SIZE;
	}
	return (depth_h);
}

static void	draw_rect11(t_param_rcst rcst, t_data *data)
{
	t_pos	tmp;
	t_pos	start;
	int		clr;
	int		i;

	start.x = rcst.ray * SCALE;
	start.y = (HALF_HEIGHT - rcst.proj_height / 2);
	tmp.x = rcst.ray * SCALE + SCALE;
	tmp.y = (HALF_HEIGHT - rcst.proj_height / 2);
	i = -1;
	while (++i < rcst.proj_height)
	{	
		clr = my_mlx_pixel_get(&rcst.timg, rcst.offset, \
			(int)(i * BLOCK_SIZE / rcst.proj_height));
		_dda_line(start, tmp, clr, data->mlx);
		start.y++;
		tmp.y++;
	}
}

/*
depth_hv.x = depth_h;
depth_hv.y = depth_v;
*/
void	ray_cast2(t_data *data)
{
	t_param_rcst	rcst;

	get_o_pos(data, &rcst);
	rcst.cur_ang = data->plr->angl - HALF_FOV;
	rcst.ray = -1;
	while (++(rcst.ray) < NUM_RAYS)
	{
		get_cur_cs(rcst.cur_ang, &rcst.cs);
		rcst.depth_hv.y = get_depth_v(data, rcst, &rcst.xy.y);
		rcst.depth_hv.x = get_depth_h(data, rcst, &rcst.xy.x);
		rcst.depth = find_min(rcst.depth_hv.x, rcst.depth_hv.y);
		rcst.timg.img = get_img(rcst.depth, rcst.depth_hv, rcst.cs, data);
		rcst.timg.addr = mlx_get_data_addr(rcst.timg.img, \
			&rcst.timg.bpp, &rcst.timg.llen, &rcst.timg.endian);
		rcst.proj_height = get_proj_height(rcst.depth, rcst.cur_ang, data);
		rcst.offset = get_offset(rcst);
		draw_rect11(rcst, data);
		rcst.cur_ang += DELTA_RAY;
	}
}
