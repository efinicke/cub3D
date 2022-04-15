/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spayeur <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 05:15:54 by spayeur           #+#    #+#             */
/*   Updated: 2022/04/14 16:28:06 by spayeur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*								   Libraries								  */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../miniLibX/mlx.h"

/* ************************************************************************** */
/*									 Macros									  */
/* ************************************************************************** */

/* ********************************* Window ********************************* */

# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720

/* ***************************** Field of view ****************************** */

/* The FOV_ANGLE is equal to:			                                      */
/* - ANGLE * PI / 180										                  */
/* With an ANGLE of 60 degrees, the FOV_ANGLE is about 1.04719755119659774615 */

# define FOV_ANGLE 1.04719755119659774615

/* ******************************** Minimap ********************************* */

/* The width and height of the minimap are respectively equal to:			  */
/* - MINIMAP_RATIO_X * MINITILE_SIZE										  */
/* - MINIMAP_RATIO_Y * MINITILE_SIZE										  */

# define MINIMAP_X 10
# define MINIMAP_Y 10
# define MINIMAP_RATIO_X 11
# define MINIMAP_RATIO_Y 11
# define MINIMAP_BACKGROUND_COLOR 0x00ffffff
# define MINITILE_SIZE 24
# define MINITILE_VOID_COLOR 0xff000000
# define MINITILE_SPACE_COLOR 0x00000000
# define MINITILE_WALL_COLOR 0x00000000
# define MINIPLAYER_SIZE 6
# define MINIPLAYER_COLOR 0x00ff0000
# define MINIPLAYER_RAY_SIZE 24
# define MINIPLAYER_RAY_COLOR 0x000000ff

/* ********************************** Rays ********************************** */

# define NUM_RAYS WINDOW_WIDTH
# define RENDER_RAYS FALSE
# define RAYS_COLOR 0x0000ff00

/* ********************************* Player ********************************* */

# define PLAYER_WALKSPEED 0.04
# define PLAYER_TURNSPEED 1.2

/* *********************************** Pi *********************************** */

# define ZERO_PI 0
# define HALF_PI 1.570796326794896619231
# define PI 3.14159265358979323846
# define THREE_PI_TWO 4.71238898038468985769
# define TWO_PI 6.28318530717958647692

/* ******************************* X11 events ******************************* */

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_DESTROY 17

/* ******************************** Keycodes ******************************** */

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ARROWUP 65362
# define KEY_ARROWDOWN 65364
# define KEY_ARROWLEFT 65361
# define KEY_ARROWRIGHT 65363
# define KEY_ESC 65307

/* ******************************** Boolean ********************************* */

# define FALSE 0
# define TRUE 1

/* **************************** Standard Streams **************************** */

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* ************************************************************************** */
/*								   Structures								  */
/* ************************************************************************** */

typedef struct s_ipoint
{
	int	x;
	int	y;
}		t_ipoint;

typedef struct s_fpoint
{
	float	x;
	float	y;
}			t_fpoint;

typedef struct s_img
{
	void	*ptr;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		pixel_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_minimap
{
	int		width;
	int		height;
	t_img	frame;
	t_img	background;
	t_img	tile_void;
	t_img	tile_wall;
	t_img	tile_space;
	t_img	player;
}			t_minimap;

typedef struct s_player
{
	float	x;
	float	y;
	int		turn_direction;
	int		walk_direction_h;
	int		walk_direction_v;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}			t_player;

typedef struct s_ray
{
	float	angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	int		was_hit_vertical;
	int		is_facing_up;
	int		is_facing_down;
	int		is_facing_left;
	int		is_facing_right;
	char	wall_hit_content;
}			t_ray;

typedef struct s_3d
{
	float	distance_projection;
	float	projected_wall_height;
	float	perp_distance;
	int		wall_strip_height;
	int		top_wall_pixel;
	int		bot_wall_pixel;
}				t_3d;

typedef struct s_texture
{
	t_img	east;
	t_img	west;
	t_img	north;
	t_img	south;
}				t_texture;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f;
	int			c;
	char		**map;
	int			map_width;
	int			map_height;
	t_img		frame;
	t_ray		rays[NUM_RAYS];
	t_minimap	minimap;
	t_player	player;
	t_3d		plane;
	t_texture	texture;
}				t_cub;

/* ************************************************************************** */
/*							 Function declarations							  */
/* ************************************************************************** */

int				game_loop(t_cub *cub);
int				map_has_wall_at(t_cub *cub, char **map, float x, float y);
int				failure(const char *s);

/* ****************************** Structures  ******************************* */

int				init_cub(t_cub *cub, const char *filename);
int				init_cub_graphics(t_cub *cub);
void			delete_cub(t_cub *cub);

int				init_minimap(t_cub *cub);
void			destroy_minimap(t_cub *cub);

void			init_player(t_player *player);

int				init_textures(t_cub *cub);
void			destroy_textures(t_cub *cub);

int				init_img(t_cub *cub, t_img *img, int width, int height);

void			init_point(t_ipoint *point, int x, int y);
float			distance_between_points(float x1, float y1, float x2, float y2);

/* ******************************** Parsing ********************************* */

int				parse_cub_file(t_cub *cub, int fd);
int				parse_line(t_cub *cub, const char *line);
int				parse_texture(char **texture, const char *line, unsigned int i);
int				parse_color(int *color, const char *line, unsigned int i);
int				parse_map(char ***map, const char *line);
int				parse_player(t_cub *cub, char **map, const char *line);
int				normalize_map(t_cub *cub, char **map);
int				check_missing_element(const t_cub *cub);
int				check_map(char **map);

unsigned int	skip_spaces(const char *s, unsigned int *i);

/* ******************************** Drawing ********************************* */

int				draw_rect(t_cub *cub, t_img *img, const int wh[2], int color);
int				draw_rect_unfilled(t_cub *cub, t_img *img, const int wh[2], \
				int color);
int				draw_circ(t_cub *cub, t_img *img, int radius, int color);
int				draw_line(t_cub *cub, t_img *img, t_ipoint *pts[3], int color);

void			img_set_pixel(t_img *data, int x, int y, int color);
int				img_get_pixel(t_img *data, int x, int y);
void			img_fill(t_img *img, int color);

void			put_img_to_background(t_cub *cub, t_img *img, int x, int y);
void			put_img_to_minimap(t_cub *cub, t_img *img, int x, int y);

/* ******************************* Raycasting ******************************* */

void			cast_all_rays(t_cub *cub);
void			search_horizontal_wall_hit(t_cub *cub, int id);
void			search_vertical_wall_hit(t_cub *cub, int id);

/* ******************************* Rendering ******************************** */

int				render(t_cub *cub);
void			generate_3d_projection(t_cub *cub, t_img *background, \
				t_img *texture);
void			set_wall_stripe(int x, t_cub *cub, t_img *background, \
				t_img *texture);
void			minimap_render(t_cub *cub);
void			rays_render(t_cub *cub);

/* ********************************* Events ********************************* */

int				on_keydown(int keycode, t_cub *cub);
int				on_keyup(int keycode, t_cub *cub);
int				on_destroy(t_cub *cub);

#endif
