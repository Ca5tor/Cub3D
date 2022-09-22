/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltacos <ltacos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 00:27:45 by ltacos            #+#    #+#             */
/*   Updated: 2022/09/22 04:32:52 by ltacos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURE_H
# define CONFIGURE_H

/* NUM FROM CHAR MAP*/
# define VD 32
# define WL 49
# define FR 48
# define PR_N 78
# define PR_S 83
# define PR_E 69
# define PR_W 87

/*	COLOR BLOCK FOR 2D MAP*/
// # define WALL_B 0x808080
// # define FLOOR_B 0xFFFFFF
// # define PLAYER_B 0x008080

// # define BACKGROUND 0x404040

/*	SIZE WINDOW	*/

# define WIDTH 800
# define HEIGHT 600

/*	*/
# define HALF_WIDTH (WIDTH / 2)
# define HALF_HEIGHT (HEIGHT / 2)

/*	MOVE CONTROL WSAD	*/

# define M_DIRECTLY	119
# define M_BACK		115
# define M_LEFT		97
# define M_RIGHT	100

/*	TURN TO THE SIDES <- ->	*/

# define TURN_L		65361
# define TURN_R		65363

/*	EXIT PROGRAMM ESC	*/

# define EXIT_WINDW	65307

#endif