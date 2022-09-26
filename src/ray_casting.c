/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:25:04 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:35:01 by ltacos           ###   ########.fr       */
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
	xh = rcst.m_xy.pos[X];
	if (rcst.cs.pos[COS] >= 0)
	{
		xh += TILE;
		dx = 1;
	}
	i = -1;
	while (++i < (WIDTH / TILE))
	{
		depth_v = (xh - rcst.o_xy.pos[X]) / rcst.cs.pos[COS];
		*y = rcst.o_xy.pos[Y] + depth_v * rcst.cs.pos[SIN];
		if (bin_search_pos(data, xh + dx, *y))
			break ;
		xh += dx * TILE;
	}
	return (depth_v);
}

static double	get_depth_h(t_data *data, t_param_rcst rcst, double *x)
{
	int		i;
	int		yv;
	int		dy;
	double	depth_h;

	yv = rcst.m_xy.pos[Y];
	dy = -1;
	if (rcst.cs.pos[SIN] >= 0)
	{
		yv += TILE;
		dy = 1;
	}
	i = -1;
	while (++i < HEIGHT / TILE)
	{
		depth_h = (yv - rcst.o_xy.pos[Y]) / rcst.cs.pos[SIN];
		*x = rcst.o_xy.pos[X] + depth_h * rcst.cs.pos[COS];
		if (bin_search_pos(data, *x, yv + dy))
			break ;
		yv += (dy * TILE);
	}
	return (depth_h);
}

static void	draw_rect11(t_param_rcst rcst, t_data *data)
{
	t_pos_double	tmp;
	t_pos_double	start;
	int				clr;
	int				i;

	start.pos[X] = rcst.ray * rcst.vars.scale;
	start.pos[Y] = ((HEIGHT / 2) - rcst.proj_height / 2);
	tmp.pos[X] = rcst.ray * rcst.vars.scale + rcst.vars.scale;
	tmp.pos[Y] = ((HEIGHT / 2) - rcst.proj_height / 2);
	i = -1;
	while (++i < rcst.proj_height)
	{	
		clr = my_mlx_pixel_get(&rcst.timg, rcst.offset, \
			(int)(i * TILE / rcst.proj_height));
		_dda_line(start, tmp, clr, data->mlx);
		(start.pos[Y])++;
		(tmp.pos[Y])++;
	}
}

static void	init_const_rcst(t_param_rcst *rcst)
{
	rcst->vars.fov = PI / 3;
	rcst->vars.half_fov = (rcst->vars.fov / 2);
	rcst->vars.max_depth = (WIDTH / TILE * TILE);
	rcst->vars.delta_ray = (rcst->vars.fov / (NUM_RAYS - 1));
	rcst->vars.dist = (NUM_RAYS / tan(rcst->vars.half_fov));
	rcst->vars.scale = (WIDTH / (NUM_RAYS - 1));
	rcst->vars.proj_coeff = rcst->vars.scale / 2 * rcst->vars.dist * TILE;
}

void	ray_cast2(t_data *data)
{
	t_param_rcst	rcst;

	init_const_rcst(&rcst);
	get_o_pos(data, &rcst);
	rcst.cur_ang = data->plr->angl - rcst.vars.half_fov;
	rcst.ray = -1;
	while (++(rcst.ray) < NUM_RAYS)
	{
		get_cur_cs(rcst.cur_ang, &rcst.cs);
		rcst.depth_hv.pos[DEPTH_H] = get_depth_h(data, rcst, &rcst.xy.pos[X]);
		rcst.depth_hv.pos[DEPTH_V] = get_depth_v(data, rcst, &rcst.xy.pos[Y]);
		rcst.depth = find_min(rcst.depth_hv.pos[DEPTH_H], \
			rcst.depth_hv.pos[DEPTH_V]);
		rcst.timg.img = get_img(rcst.depth, rcst.depth_hv, rcst.cs, data);
		rcst.timg.addr = mlx_get_data_addr(rcst.timg.img, &rcst.timg.bpp, \
			&rcst.timg.llen, &rcst.timg.endian);
		rcst.proj_height = get_proj_height(rcst.depth, rcst.cur_ang, \
			rcst.vars.proj_coeff, data);
		rcst.offset = get_offset(rcst);
		draw_rect11(rcst, data);
		rcst.cur_ang += rcst.vars.delta_ray;
	}
}
