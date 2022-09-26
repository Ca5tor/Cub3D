/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:20:44 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 17:31:43 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	my_mlx_pixel_get(t_texture *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
