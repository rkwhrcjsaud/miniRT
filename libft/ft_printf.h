/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gibkim <gibkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:20:21 by gibkim            #+#    #+#             */
/*   Updated: 2023/04/12 18:57:38 by gibkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define SPECIFIERS "cspdiuxX%"

typedef struct s_printf_flag
{
	int				width;
	int				precision;
	unsigned char	hyphen;
	unsigned char	zero;
	unsigned char	hash;
	unsigned char	space;
	unsigned char	plus;
}	t_printf_flag;

char			*ft_nullguard(char *buf, char *str);
char			*ft_bufadd_back(char *buf, char *str);
char			*ft_addlen_str(char c, int len, char *buf);
size_t			ft_format_case(const char *format);
int				ft_print_bx_bonus(const char *fmt, unsigned int num);
int				ft_print_c_bonus(const char *fmt, unsigned int num);
int				ft_print_d_bonus(const char *fmt, int num);
int				ft_print_p_bonus(const char *fmt, size_t num);
int				ft_print_percent_bonus(const char *fmt);
int				ft_print_s_bonus(const char *fmt, char *ap);
int				ft_print_sx_bonus(const char *fmt, unsigned int ap);
int				ft_print_u_bonus(const char *fmt, unsigned int num);
int				ft_printf(const char *format, ...);
t_printf_flag	ft_setflag(const char *fmt, t_printf_flag flag);
char			*ft_sizetohex(size_t n, unsigned char isbig);
char			*ft_uitoa(unsigned int n);

#endif