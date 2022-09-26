/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:12:29 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 18:58:34 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

double	find_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	find_min(double x, double y)
{
	if (x < y)
		return (x);
	return (y);
}

double	mod(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	bin_search_pos(t_data *data, double ax, double ay)
{
	int				levl[3];
	t_pos_double	guess;

	if (ax < 0 || ay < 0)
		return (0);
	levl[VAR_LOW] = 0;
	levl[VAR_HEIGHT] = data->num_wall - 1;
	while (levl[VAR_LOW] <= levl[VAR_HEIGHT])
	{
		levl[VAR_MID] = (levl[VAR_LOW] + levl[VAR_HEIGHT]) / 2;
		guess.pos[X] = data->map_pos[levl[VAR_MID]].pos[X];
		guess.pos[Y] = data->map_pos[levl[VAR_MID]].pos[Y];
		if (ax > guess.pos[X] && ay > guess.pos[Y] && \
			ax < (guess.pos[X] + TILE) && ay < (guess.pos[Y] + TILE))
			return (1);
		if (((ax < guess.pos[X] || ay < guess.pos[Y]) && \
			(ax < (guess.pos[X] + TILE) && ay < (guess.pos[Y] + TILE))) || \
				(ax < guess.pos[X] && ay > guess.pos[Y]))
			levl[VAR_HEIGHT] = levl[VAR_MID] - 1;
		else
			levl[VAR_LOW] = levl[VAR_MID] + 1;
	}
	return (0);
}
