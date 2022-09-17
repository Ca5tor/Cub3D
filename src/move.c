/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 02:00:32 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/17 03:53:12 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	gaze_direction(int key, t_data *data)
{
	double	num;

	num = 0.5 * DELTA * SPEED_SIGHT;
	if (key == TURN_L)
	{
		data->plr->angl -= num;
		return (draw_all(data));
	}
	data->plr->angl += num;
	draw_all(data);
}

static void	direction_move(int key, t_data *data)
{
	double	num_x;
	double	num_y;

	num_x = cos(data->plr->angl) * DELTA * SPEED_MOVE;
	num_y = sin(data->plr->angl) * DELTA * SPEED_MOVE;
	if (key == M_DIRECTLY)
	{
		data->plr->pos.x += num_x;
		data->plr->pos.y += num_y;
		return (draw_all(data));
	}
	data->plr->pos.x -= num_x;
	data->plr->pos.y -= num_y;
	draw_all(data);
}

static void	sideways_move(int key, t_data *data)
{
	double	num_x;
	double	num_y;

	num_x = sin(data->plr->angl) * DELTA * SPEED_MOVE;
	num_y = cos(data->plr->angl) * DELTA * SPEED_MOVE;
	if (key == M_RIGHT)
	{
		data->plr->pos.x -= num_x;
		data->plr->pos.y += num_y;
		return (draw_all(data));
	}
	data->plr->pos.x += num_x;
	data->plr->pos.y -= num_y;
	draw_all(data);
}

int	close_win(t_data *data)
{
	free(data->mlx);
	free(data->plr);
	free(data->map_pos);
	free(data);
	exit(0);
	return (0);
}

void	move(int key, t_data *data)
{
	if (!chek_key(key))
		return ;
	if (key == TURN_L || key == TURN_R)
		return (gaze_direction(key, data));
	if (key == M_DIRECTLY || key == M_BACK)
		return (direction_move(key, data));
	if (key == M_RIGHT || key == M_LEFT)
		return (sideways_move(key, data));
	if (key == EXIT_WINDW)
		close_win(data);
}
