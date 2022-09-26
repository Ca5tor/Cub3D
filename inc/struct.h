/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 01:16:06 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/26 17:47:26 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

enum e_map_elem
{
	SPACE = -16,
	FLOOR = 0,
	WALL = 1,
	EAST = 21,
	NORTH = 30,
	SOUTH = 35,
	WEST = 39
};

enum e_error
{
	BAD_FILE = 1,
	BAD_CONFIG = 2,
	BAD_MAP = 3,
	BAD_KEY = 4,
	BAD_TEXTURE = 5,
	BAD_RGB = 6,
	BAD_EXTENSION = 7,
	BAD_ARGUMENT = 8
};

typedef struct s_pos_double
{
	double	pos[2];
}	t_pos_double;

typedef struct s_pos_int
{
	int		pos[2];
}	t_pos_int;

typedef struct s_plr
{
	t_pos_double	pos;
	double			angl;
}	t_plr;

typedef struct s_map
{
	int	rows;
	int	cols;
	int	pl_x;
	int	pl_y;
	int	**matrix;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_params
{
	t_texture		so;
	t_texture		no;
	t_texture		we;
	t_texture		ea;
	int				*fl_rgb;
	int				*ce_rgb;
}	t_params;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_params		params;
	t_map			map;
}	t_cub;

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

typedef struct s_data
{
	int			clr_fons[2];
	int			num_wall;
	t_texture	texture[4];
	t_pos_int	*map_pos;
	t_plr		*plr;
	t_mlx		*mlx;
}	t_data;

typedef struct s_constant_rcst
{
	double	fov;
	double	half_fov;
	double	max_depth;
	double	delta_ray;
	double	dist;
	double	proj_coeff;
	double	scale;
}	t_constant_rcst;

typedef struct s_param_rcst
{
	t_pos_int		o_xy;
	t_pos_int		m_xy;
	t_pos_double	xy;
	t_pos_double	depth_hv;
	t_pos_double	cs;
	t_texture		timg;
	t_constant_rcst	vars;
	int				ray;
	int				proj_height;
	int				offset;
	double			cur_ang;
	double			depth;
}	t_param_rcst;

#endif