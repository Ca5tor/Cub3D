/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:54:36 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/17 01:45:57 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_mlx
{
	void	*p_mlx;
	void	*p_win;
	void	*p_img;
	char	*p_addr;
	int		bpp;
	int		len;
	int		endian;
}	t_mlx;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_plr
{
	t_pos	pos;
	double	angl;
}	t_plr;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	char	*relative_path;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_data
{
	t_plr	*plr;
	t_mlx	*mlx;
	t_pos	*map_pos;
}	t_data;



#endif