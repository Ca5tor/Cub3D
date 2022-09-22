/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:54:36 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 09:41:43 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


/////////////////////////////////////////////
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

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct s_params
{
	t_texture		so;
	t_texture		no;
	t_texture		we;
	t_texture		ea;
	int				*fl_rgb;
	int				*ce_rgb;
}					t_params;

typedef struct s_map
{
	int	rows;
	int	cols;
	int	pl_x;
	int	pl_y;
	int	**matrix;
}	t_map;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_params		params;
	t_map			map;
}					t_cub;

/// @brief ///////////////////
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

typedef struct s_cs
{
	double	cos;
	double	sin;
}	t_cs;

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
	int		img_width;
	int		img_height;
}				t_img;

//Полученная с файла карта
// typedef struct s_map
// {
// 	int	rows;
// 	int	cols;
// 	int	pl_x;
// 	int	pl_y;
// 	int	**matrix;
// }	t_map;

// typedef struct s_texture
// {
// 	void	*img;
// 	int		width;
// 	int		height;
// }	t_texture;

// typedef struct s_params
// {
// 	t_texture	so;
// 	t_texture	no;
// 	t_texture	we;
// 	t_texture	ea;
// 	int			*fl_rgb;
// 	int			*ce_rgb;
// }	t_params;

typedef struct s_data
{
	t_plr		*plr;
	t_mlx		*mlx;
	t_pos		*map_pos;
	t_map		*map;
	t_params	*params;
	int			num_wall;
}	t_data;

typedef struct s_int_pos
{
	int	x;
	int	y;
}	t_int_pos;

typedef struct s_param_rcst
{
	t_int_pos	o_xy;
	t_int_pos	m_xy;
	t_pos		xy;
	t_pos		depth_hv;
	t_cs		cs;
	t_img		timg;
	int			ray;
	int			proj_height;
	int			offset;
	double		cur_ang;
	double		depth;
}	t_param_rcst;



#endif