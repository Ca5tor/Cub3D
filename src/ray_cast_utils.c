/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 08:06:39 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 08:14:55 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	*get_img(double depth, t_pos depth_hv, t_cs cs, t_data *data)
{
	if (depth == depth_hv.x && cs.sin >= 0)
		return (data->params->no.img);
	else if (depth == depth_hv.x && cs.sin < 0)
		return (data->params->so.img);
	else if (depth == depth_hv.y && cs.cos >= 0)
		return (data->params->ea.img);
	return (data->params->we.img);
}

int	get_offset(t_param_rcst rcst)
{
	int	offset;

	if (rcst.depth == rcst.depth_hv.x)
		offset = rcst.xy.x;
	else
		offset = rcst.xy.y;
	offset = mod((int)offset % BLOCK_SIZE);
	return (offset);
}

int	get_proj_height(double depth, double cur_ang, t_data *data)
{
	int	proj_height;

	depth *= cos(data->plr->angl - cur_ang);
	depth = find_max(depth, 0.00001);
	proj_height = mod(find_min((int)(PROJ_COEFF / depth), 2 * HEIGHT));
	return (proj_height);
}

void	get_cur_cs(double cur_ang, t_cs *cs)
{
	cs->cos = cos(cur_ang);
	cs->sin = sin(cur_ang);
}

void	get_o_pos(t_data *data, t_param_rcst *rcst)
{
	rcst->o_xy.x = data->plr->pos.x;
	rcst->o_xy.y = data->plr->pos.y;
	rcst->m_xy.x = rcst->o_xy.x / BLOCK_SIZE * BLOCK_SIZE;
	rcst->m_xy.y = rcst->o_xy.y / BLOCK_SIZE * BLOCK_SIZE;
}
