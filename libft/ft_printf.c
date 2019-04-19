/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:43:01 by sofchami          #+#    #+#             */
/*   Updated: 2018/11/30 07:47:36 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flag(char c, t_print *sc, int pos)
{
	static char flags[14] = {'#', '~', '.', 'M', 'o', 'd',
	'x', 'X', 'p', '%', 'u', 'c', 's', 'f'};

	if (c == 'O' || c == 'U' || c == 'D')
	{
		sc->mod = 1;
		if (c == 'D')
			return (6);
		return (c != 'U' ? 5 : 11);
	}
	while (++pos < 14)
	{
		if (c == '0' || c == '#' || c == '+' || c == '-' || c == ' ')
			return (1);
		if (ft_isdigit(c) || c == 'i')
			return (c == 'i' ? 6 : 2);
		if (c == 'l' || c == 'h' || c == 'L')
			return (4);
		if (flags[pos] == c || (flags[pos] - 32 == c && c != 'X'))
			return (pos + 1);
	}
	return (0);
}

void	ft_options(t_print *sc, char *str)
{
	while (sc->i_f == 1)
	{
		if (str[sc->i] == ' ')
			sc->c.esp = 1;
		if (str[sc->i] == '+')
			sc->c.plus = 1;
		if (str[sc->i] == '-')
			sc->c.moins = 1;
		if (str[sc->i] == '0')
			sc->c.zo = 1;
		if (str[sc->i] == '#')
			sc->c.dz = 1;
		sc->i++;
		sc->i_f = ft_flag(*(str + sc->i), sc, -1);
	}
	sc->options++;
}

void	ft_modarg(t_print *sc, char *str)
{
	sc->i_f < 4 ? sc->i_f = ft_flag(*(str + sc->i), sc, -1) : 0;
	if (*(str + sc->i) == 'l')
		sc->mod = *(str + sc->i + 1) == 'l' ? 4 : 1;
	else if (*(str + sc->i) == 'L')
		sc->mod = 3;
	else if (*(str + sc->i) == 'h')
		sc->mod = *(str + sc->i + 1) == 'h' ? 5 : 2;
	if (sc->i_f == 4)
		sc->mod < 4 ? (sc->i++) : (sc->i += 2);
}

void	ft_fillstruc(t_print *sc, char *str)
{
	sc->i_f == 1 ? ft_options(sc, str) : sc->i++;
	if (sc->i_f == 2)
	{
		sc->col = ft_atoi(str + sc->i);
		sc->i += ft_intlen(sc->col);
	}
	if (sc->i_f < 4)
	{
		sc->i_f < 3 ? sc->i_f = ft_flag(*(str + sc->i), sc, -1) : 0;
		sc->p2 += sc->i_f == 3 && !ft_isdigit(str[sc->i + 1]) ? 1 : 0;
		str[sc->i + 1] == '0' ? sc->p2 += 2 : 0;
		sc->i_f == 3 ? sc->p = ft_atoi(str + sc->i + 1) : 0;
		if (sc->i_f == 3)
			sc->p2 == 1 ? (sc->i += ft_intlen(sc->p)) :
		(sc->i += ft_intlen(sc->p) + 1);
	}
	if (sc->i_f < 5)
		ft_modarg(sc, str);
	sc->i_f < 5 ? sc->i_f = ft_flag(*(str + sc->i), sc, -1) : 0;
}

int		ft_printf(const char *format, ...)
{
	t_print	sc;
	va_list	ap;
	t_tmp	tmp;

	va_start(ap, format);
	ft_bzero(&sc, sizeof(sc));
	while ((size_t)sc.i < ft_strlen(format))
	{
		if (format[sc.i] != '%' && ++sc.ret)
			write(1, &format[sc.i], 1);
		if (format[sc.i] == '%' && (sc.i_f = ft_flag(format[sc.i + 1],
			&sc, -1)))
		{
			ft_fillstruc(&sc, (char*)format);
			ft_convbase(ap, &sc);
			tmp.tmpopt = sc.ret;
			tmp.tmp = !sc.i_f ? sc.i - 1 : sc.i;
			ft_bzero(&sc, sizeof(sc));
			sc.i = tmp.tmp;
			sc.ret = tmp.tmpopt;
		}
		sc.i++;
	}
	va_end(ap);
	return (sc.ret);
}
