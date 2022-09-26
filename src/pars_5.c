/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:13:52 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 20:16:01 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	pars_textures3(char *key, char *value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key, "EA") && !(*flags & FLAGS_EA))
	{
		*flags |= FLAGS_EA;
		cub->params.we.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.we.width), &(cub->params.we.height));
		cub->params.we.addr = mlx_get_data_addr(cub->params.we.img,
				&cub->params.we.bpp, &cub->params.we.llen,
				&cub->params.we.endian);
		return (0);
	}
	if (!ft_strcmp(key, "WE") && !(*flags & FLAGS_WE))
	{
		*flags |= FLAGS_WE;
		cub->params.ea.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.ea.width), &(cub->params.ea.height));
		cub->params.ea.addr = mlx_get_data_addr(cub->params.ea.img,
				&cub->params.ea.bpp, &cub->params.ea.llen,
				&cub->params.ea.endian);
		return (0);
	}
	return (BAD_KEY);
}

int	pars_textures2(char *key, char *value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key, "SO") && !(*flags & FLAGS_SO))
	{
		*flags |= FLAGS_SO;
		cub->params.so.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.so.width), &(cub->params.so.height));
		cub->params.so.addr = mlx_get_data_addr(cub->params.so.img,
				&cub->params.so.bpp, &cub->params.so.llen,
				&cub->params.so.endian);
		return (0);
	}
	if (!ft_strcmp(key, "NO") && !(*flags & FLAGS_NO))
	{
		*flags |= FLAGS_NO;
		cub->params.no.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.no.width), &(cub->params.no.height));
		cub->params.no.addr = mlx_get_data_addr(cub->params.no.img,
				&cub->params.no.bpp, &cub->params.no.llen,
				&cub->params.no.endian);
		return (0);
	}
	return (pars_textures3(key, value, flags, cub));
}

int	pars_textures(char *key, char *value, int *flags, t_cub *cub)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd == -1)
		return (BAD_TEXTURE);
	close(fd);
	if (!pars_ends_with(value, ".xpm"))
		return (BAD_TEXTURE);
	return (pars_textures2(key, value, flags, cub));
}

int	pars_rgb_value(char *key, char *value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key, "F") && !(*flags & FLAGS_F))
	{
		*flags |= FLAGS_F;
		cub->params.fl_rgb = pars_get_rgb(value);
		if (cub->params.fl_rgb == NULL)
			return (BAD_RGB);
		return (0);
	}
	if (!ft_strcmp(key, "C") && !(*flags & FLAGS_C))
	{
		*flags |= FLAGS_C;
		cub->params.ce_rgb = pars_get_rgb(value);
		if (cub->params.ce_rgb == NULL)
			return (BAD_RGB);
		return (0);
	}
	return (BAD_KEY);
}

int	pars_handle_str(char **key_value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key_value[0], "SO") || !ft_strcmp(key_value[0], "WE")
		|| !ft_strcmp(key_value[0], "EA") || !ft_strcmp(key_value[0], "NO"))
		return (pars_textures(key_value[0], key_value[1], flags, cub));
	else if (!ft_strcmp(key_value[0], "F") || !ft_strcmp(key_value[0], "C"))
		return (pars_rgb_value(key_value[0], key_value[1], flags, cub));
	else
		return (BAD_KEY);
}
