/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray_casting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:57:16 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 19:05:26 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	*get_img(double depth, t_pos_double depth_hv, \
	t_pos_double cs, t_data *data)
{	
	if (depth == depth_hv.pos[DEPTH_H] && cs.pos[SIN] >= 0)
		return (data->texture[IMG_NO].img);
	else if (depth == depth_hv.pos[DEPTH_H] && cs.pos[SIN] < 0)
		return (data->texture[IMG_SO].img);
	else if (depth == depth_hv.pos[DEPTH_V] && cs.pos[COS] >= 0)
		return (data->texture[IMG_EA].img);
	return (data->texture[IMG_WE].img);
}

int	get_offset(t_param_rcst rcst)
{
	int	offset;

	if (rcst.depth == rcst.depth_hv.pos[DEPTH_H])
		offset = rcst.xy.pos[X];
	else
		offset = rcst.xy.pos[Y];
	offset = mod((int)offset % TILE);
	return (offset);
}

int	get_proj_height(double depth, double cur_ang, \
	double proj_coeff, t_data *data)
{
	int	proj_height;

	depth *= cos(data->plr->angl - cur_ang);
	depth = find_max(depth, 0.00001);
	proj_height = mod(find_min((int)(proj_coeff / depth), 2 * HEIGHT));
	return (proj_height);
}

void	get_cur_cs(double cur_ang, t_pos_double *cs)
{
	cs->pos[COS] = cos(cur_ang);
	cs->pos[SIN] = sin(cur_ang);
}

void	get_o_pos(t_data *data, t_param_rcst *rcst)
{
	rcst->o_xy.pos[X] = data->plr->pos.pos[X];
	rcst->o_xy.pos[Y] = data->plr->pos.pos[Y];
	rcst->m_xy.pos[X] = rcst->o_xy.pos[X] / TILE * TILE;
	rcst->m_xy.pos[Y] = rcst->o_xy.pos[Y] / TILE * TILE;
}
