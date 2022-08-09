/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:20:55 by ltacos            #+#    #+#             */
/*   Updated: 2022/07/21 00:31:35 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define ERR_MEM "Cub3d: failed to allocate memory\n"

t_data	*init_data(void)
{
	t_data	*new_data;

	new_data = malloc(sizeof(t_data *));
	if (!new_data && write(2, ERR_MEM, 34))
		return (NULL);
	new_data->cub = NULL;
	new_data->file_lines = NULL;
	return (new_data);
}

t_cub	*init_cub()
{
	t_cub	*new_cub;

	new_cub = malloc(sizeof(t_cub *));
	if (!new_cub && write(2, ERR_MEM, 34))
		return (NULL);
	*(new_cub)->idntfrs = NULL;
	*(new_cub)->map = NULL;
	return (new_cub);
}

t_mlx	*t_mlx_init(void)
{
	t_mlx	*new_mlx;

	new_mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!new_mlx && write(1, ERR_MEM, 34))
	{
		//free_struct(data);
		exit(1);
	}
	new_mlx->p_mlx = mlx_init();
	new_mlx->p_win = mlx_new_window(new_mlx->p_mlx, WIDTH, HEIGHT, "Cub3D");
	new_mlx->p_img = mlx_new_image(new_mlx->p_mlx, WIDTH, HEIGHT);
	new_mlx->p_addr = mlx_get_data_addr(new_mlx->p_img, &(new_mlx->bpp),
			&(new_mlx->len), &(new_mlx->endian));
	ft_bzero(new_mlx->p_addr, WIDTH * HEIGHT * (new_mlx->bpp / 8));
	return (new_mlx);
}
