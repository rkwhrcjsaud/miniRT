/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:43:05 by gibkim            #+#    #+#             */
/*   Updated: 2023/11/29 14:23:01 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/ft_get_next_line.h"
# include "mlx/mlx.h"

# define INIT_WINX 1920
# define INIT_WINY 1080

# define WORD_AMBIENT "A"
# define WORD_CAMERA "C"
# define WORD_LIGHT "L"
# define WORD_SPHERE "sp"
# define WORD_PLANE "pl"
# define WORD_CYLINDER "cy"
# define WORD_CONE "cn"

# define ERRNO 1
# define E_TYPE 2
# define E_ARGUMENT 3
# define E_MLX 4
# define E_RANGE 5
# define E_VECOTR 6
# define E_COLOR 7

# define FLAG_AMBIENT 1
# define FLAG_CAMERA 2
# define FLAG_LIGHT 3
# define FLAG_SPHERE 4
# define FLAG_PLANE 5
# define FLAG_CYLINDER 6
# define FLAG_CONE 7

# define COLOR_MAX 255
# define COLOR_MIN 0

# define INF 1000000000
# define EPSILON 1e-10

# define SPECULAR 30
# define REFLECT 0.1
# define REFLECT_MAX 3
# define ATTENUATION 0.0002

# define CHEKCKER_R 10
# define CHEKCKER_PL 50
# define CHEKCKER_CY 0.5
# define CHEKCKER_CN 0.5

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
	int		code;
}	t_color;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_point	point;
	t_point	vector;
	t_point	vector_x;
	t_point	vector_y;
	int		fov;
}	t_camera;

typedef struct s_light
{
	double	ratio;
	t_point	point;
	t_color	color;
}	t_light;

typedef struct s_plane
{
	t_point	point;
	t_point	vector;
	t_color	color;
	int		disruption;
}	t_plane;

typedef struct s_sphere
{
	t_point	point;
	double	radius;
	t_color	color;
	int		disruption;
	int		bump_mapping;
}	t_sphere;

typedef struct s_cyl
{
	t_point	point;
	t_point	vector;
	double	radius;
	double	height;
	t_color	color;
	int		disruption;
}	t_cyl;

typedef struct s_cone
{
	t_point	point;
	t_point	vector;
	double	radius;
	double	height;
	t_color	color;
	int		disruption;
}	t_cone;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	t_img	img_bump;
	t_img	img_earth;
}	t_mlx;

typedef struct s_hit
{
	double	t;
	t_point	nv;
	t_color	c;
	int		disruption;
	int		obj_num;
	void	*object;
}	t_hit;

typedef struct s_ray
{
	t_point	origin;
	t_point	dir;
	t_point	inter;
	t_hit	hit;
}	t_ray;

typedef struct s_data
{
	int			fd;
	t_mlx		mlx;
	t_point		win;
	t_ambient	amb;
	t_camera	cam;
	t_list		*light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
	t_list		*cone;
}	t_data;

/*	minirt_utils.c	*/
int		iscolor(t_color a);
int		isvector(t_point a);
int		isratio(double a);
int		isfov(int a);
void	free_double_arr(char **arr);

/*	data_init.c	*/
void	data_init(t_data *data);
void	let_mlx(t_data *data);

/*	data_passing.c	*/
void	data_passing(t_data *data, char *file);

/*	insert_data.c	*/
int		insert_data(t_data *data, char **word);

/*	insert_data_lower.c	*/
void	insert_cylinder(t_data *data, char **word);
void	insert_plane(t_data *data, char **word);
void	insert_sphere(t_data *data, char **word);
void	insert_cone(t_data *data, char **word);

/*	insert_data_upper.c	*/
void	insert_ambient(t_data *data, char **word, int *flag);
void	insert_camera(t_data *data, char **word, int *flag);
void	insert_light(t_data *data, char **word);

/*	insert_data_utils.c	*/
void	insert_color(t_data *data, t_color *color, char *line);
void	insert_coordinate(t_data *data, t_point *point, char *line);
void	insert_vector(t_data *data, t_point *point, char *line);

/*	draw_pixel.c	*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*	ray_tracing.c	*/
void	ray_tracing(t_data *data);
t_color	objects_tracing(t_data *data, t_ray *ray, int depth);
void	light_tracing(t_data *data, t_ray *ray);
t_hit	tie_hit(double t, t_point p);
t_hit	init_t_hit(void);

/*	vector_utils.c	*/
t_point	tie_vector(double a, double b, double c);
t_point	vcross(t_point a, t_point b);
t_point	vsum(t_point a, t_point b);
t_point	vminus(t_point a, t_point b);
t_point	vmul(t_point a, double s);
t_point	vdiv(t_point a, double s);
t_point	vunit(t_point a);
double	vdot(t_point a, t_point b);
void	calc_camera_vector(t_camera *cam);
t_point	calc_ray_direction(t_data *data, int x, int y);
double	vlength(t_point	v);
t_point	dir_vector(t_point n1, t_point n2);
t_point	v_unit_point(t_point p, t_point dest);

/*	hit_plane.c	*/
void	tracing_plane(t_data *data, t_ray *ray);
t_hit	hit_plane(t_plane *p, t_ray ray);

/*	hit_sphere.c	*/
void	tracing_sphere(t_data *data, t_ray *ray);
t_hit	hit_sphere_nv(t_sphere *s, t_ray ray, double t);
t_hit	hit_sphere(t_sphere *s, t_ray ray);

/*	hit_cylinder.c	*/
void	tracing_cylinder(t_data *data, t_ray *ray);
double	hit_cylinder_inf(t_cyl *cy, t_ray ray);
double	hit_cylinder_lid(t_cyl *cy, t_ray ray, double lc);
t_hit	hit_cylinder_side_nv(t_cyl *cy, t_ray ray, double t);
t_hit	hit_cylinder(t_cyl *cy, t_ray ray);

/* hit_cone.c */
void	tracing_cone(t_data *data, t_ray *ray);
t_hit	hit_cone_nv(t_cone *el, t_ray ray, double t);
t_hit	hit_cone_check(t_cone *cn, t_ray ray, double t1, double t2);
t_hit	hit_cone(t_cone *el, t_ray ray);

/*	light_effect	*/
t_color	color_mul(t_color a, double b);
t_color	tie_color(int a, int b, int c);
t_color	light_effect(t_data *data, t_light *light, t_ray ray);
void	set_color_code(t_color *a);
t_color	color_sum(t_color c1, t_color c2);
t_color	lambert(t_light *light, t_ray ray);
t_color	blinn_phong(t_light *light, t_ray ray);
t_color	ambient(t_data *data);
t_color	surface_reflect(t_color light, t_hit temp_hit);
int		shading(t_data *data, t_point ray, t_point inter, t_light *light);

/*	disruption	*/
void	object_disruption(t_ray *ray);
int		uv_plane_mapping(t_plane *pl, t_ray *ray);
int		uv_sphere_mapping(t_sphere *sp, t_ray *ray);
int		uv_cylinder_mapping(t_cyl *cy, t_ray *ray);
int		uv_cone_mapping(t_cone *cn, t_ray *ray);

/*	error	*/
void	ft_error(t_data *data, int e_flag);
void	out_of_range_error(void);
void	errno_error(void);
void	insert_data_error(void);
void	argument_error(void);
void	vector_error(void);
void	mlx_error(void);
void	color_error(void);
void	ft_close(int fd);

/*	bump	*/
void	bump_init(t_data *data);
void	earth_init(t_data *data);
t_color	bump_color(t_data *data, int x, int y);
t_color	earth_color(t_data *data, int x, int y);
void	bump_mapping(t_data *data, t_sphere *sp, t_ray *ray);
void	earth_bump_nv(t_data *data, t_color color, t_ray *ray);

#endif
