/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 00:36:43 by sofchami          #+#    #+#             */
/*   Updated: 2019/01/09 22:38:17 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <wctype.h>
# include <wchar.h>
# include "libft.h"
# include <locale.h>
# define H "0123456789abcdef"
# define HM "0123456789ABCDEF"
# define OCTAL "01234567"
# define DEC "0123456789"

typedef struct		s_c
{
	int				plus;
	int				moins;
	int				dz;
	int				esp;
	int				zo;
}					t_c;

typedef struct		s_tmp
{
	int				tmp;
	int				tmpopt;
}					t_tmp;

typedef struct		s_float
{
	long double		nbr;
	long double		rest;
	long double		tmp;
	long			part1;
	int				i;
	int				round;
	int				rev;
	char			*float1;
	char			flottant[50];
}					t_float;

typedef struct		s_printf
{
	int				i;
	int				p;
	int				options;
	int				i_f;
	int				intlen;
	int				col;
	int				mod;
	int				len;
	int				ret;
	int				p2;
	int				bp;
	char			*str;
	struct s_c		c;
}					t_print;

void				ft_printhex(t_print *sc);
void				ft_printoctal(t_print *sc);
int					ft_flag(char c, t_print *sc, int pos);
void				ft_percent(t_print *sc);
void				ft_printcol(t_print *sc, char *str);
void				ft_printp(t_print *sc, char *str);
char				*ft_fillstrmod(va_list ap, t_print *sc);
char				*ft_fillstrmod2(va_list ap, t_print *sc);
void				ft_printitoa(t_print *sc, va_list ap);
void				ft_printadress(t_print *sc);
void				ft_printsc(t_print *sc, va_list ap);
char				*ft_convbase(va_list ap, t_print *sc);
void				ft_options(t_print *sc, char *str);
int					ft_printf(const char *format, ...);
void				ft_floprint(va_list ap, t_print *sc);

#endif
