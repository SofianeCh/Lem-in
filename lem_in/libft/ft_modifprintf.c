/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modifprintf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 08:10:23 by sofchami          #+#    #+#             */
/*   Updated: 2019/01/09 16:58:11 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_fillstrmod(va_list ap, t_print *sc)
{
	if (sc->i_f == 6)
	{
		if (!sc->mod)
			return (ft_itoa_base(va_arg(ap, int), DEC));
		if (sc->mod == 1)
			return (ft_itoa_base(va_arg(ap, long), DEC));
		if (sc->mod == 4)
			return (ft_itoa_base(va_arg(ap, long long), DEC));
		if (sc->mod == 2)
			return (ft_itoa_base((short)va_arg(ap, int), DEC));
		return (ft_itoa_base((signed char)va_arg(ap, int), DEC));
	}
	if (!sc->mod)
		return (ft_ibu(va_arg(ap, unsigned int), OCTAL));
	if (sc->mod == 1)
		return (ft_ibu(va_arg(ap, unsigned long), OCTAL));
	if (sc->mod == 4)
		return (ft_ibu(va_arg(ap, unsigned long long), OCTAL));
	if (sc->mod == 2)
		return (ft_ibu((unsigned short)va_arg(ap, int), OCTAL));
	return (ft_ibu((unsigned char)va_arg(ap, int), OCTAL));
}

char	*ft_fillstrmod2(va_list ap, t_print *sc)
{
	if (sc->mod == 2 && sc->i_f < 10)
		return (ft_ibu((unsigned short)va_arg(ap, int), sc->i_f != 8 ? H : HM));
	if (sc->i_f < 10)
	{
		if (!sc->mod)
			return (ft_ibu(va_arg(ap, unsigned int), sc->i_f != 8 ? H : HM));
		if (sc->mod == 1 || sc->mod == 4)
			return (ft_ibu(va_arg(ap, unsigned long), sc->i_f != 8 ? H : HM));
		return (ft_ibu((unsigned char)va_arg(ap, int), sc->i_f != 8 ? H : HM));
	}
	if (!sc->mod)
		return (ft_ibu(va_arg(ap, unsigned int), DEC));
	if (sc->mod == 1)
		return (ft_ibu(va_arg(ap, unsigned long), DEC));
	if (sc->mod == 4)
		return (ft_ibu(va_arg(ap, unsigned long long), DEC));
	if (sc->mod == 2)
		return (ft_ibu((unsigned short)va_arg(ap, int), DEC));
	return (ft_ibu((unsigned char)va_arg(ap, int), DEC));
}

void	ft_printcol(t_print *sc, char *s)
{
	sc->i_f == 6 && sc->bp && (size_t)sc->bp < ft_strlen(s) &&
	(size_t)sc->col >= ft_strlen(sc->str) && s[0] == '-' ? sc->col++ : 0;
	if (!sc->c.moins)
		s[0] != '0' && sc->c.dz && sc->i_f == 5 && !sc->p ? sc->col-- : 0;
	else
		s[0] != '0' && sc->c.dz && sc->i_f == 5 && sc->p != -1 ? sc->col-- : 0;
	if (sc->i_f == 6 && sc->c.plus && sc->p2 && sc->str[0] == '0')
	{
		sc->col--;
		sc->ret++;
	}
	sc->i_f == 6 && sc->c.plus && sc->c.moins && sc->p2 &&
	sc->str[0] == '0' ? write(1, "+", 1) : 0;
	sc->i_f == 6 && sc->str[0] == '-' && sc->c.zo && (!sc->bp && !sc->p2)
	&& !sc->c.moins ? write(1, "-", 1) : 0;
	while (sc->col-- > 0)
	{
		if ((sc->c.zo && sc->c.moins) || sc->p)
			write(1, " ", 1);
		else
			write(1, (sc->p == sc->bp && sc->c.zo && !sc->p2) ? "0" : " ", 1);
		sc->ret++;
	}
	sc->i_f == 6 && sc->c.plus && !sc->c.moins && sc->p2 && sc->str[0]
	== '0' ? write(1, "+", 1) : 0;
}

void	ft_printp(t_print *sc, char *str)
{
	if (sc->i_f == 5)
		sc->str[0] != '0' && sc->c.dz ? sc->p-- : 0;
	if (str[0] == '-')
	{
		sc->i_f == 6 && sc->str[0] == '-' && sc->c.zo &&
			sc->col && (!sc->bp && !sc->p2) ? 0 : write(1, "-", 1);
		if (!sc->p && sc->bp)
			(size_t)sc->bp >= ft_strlen(sc->str) ? sc->p++ : 0;
		else if (sc->p)
			sc->p++;
	}
	while (sc->p-- > 0)
	{
		write(1, "0", 1);
		sc->ret++;
	}
}

void	ft_percent(t_print *sc)
{
	int tmp;

	tmp = sc->col - 1;
	while (!sc->c.moins && tmp-- > 0)
	{
		write(1, sc->c.zo ? "0" : " ", 1);
		sc->ret++;
	}
	if (sc->c.moins)
	{
		write(1, "%", 1);
		while (tmp-- > 0)
		{
			write(1, " ", 1);
			sc->ret++;
		}
	}
	else
		write(1, "%", 1);
	sc->ret += 1;
}
