/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing_du.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 21:10:52 by sofchami          #+#    #+#             */
/*   Updated: 2019/01/09 21:10:56 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printdeg(t_print *sc)
{
	sc->c.plus && sc->str[0] != '-' && sc->i_f != 11 ? sc->col-- : 0;
	if (!sc->c.moins)
	{
		sc->c.plus && sc->str[0] != '-' && (!sc->bp && !sc->p2) &&
		sc->c.zo && sc->i_f != 11 ? (write(1, "+", 1) && sc->ret++) : 0;
		sc->c.esp && !sc->c.plus && sc->str[0] != '-' && sc->i_f != 11 ?
		(write(1, " ", 1) && (sc->col-- & sc->ret++)) : 0;
		ft_printcol(sc, sc->str);
		sc->c.plus && sc->str[0] != '-' && (sc->bp || sc->p2 || !sc->c.zo) &&
		sc->i_f != 11 ? (write(1, "+", 1) && sc->ret++) : 0;
		ft_printp(sc, sc->str);
		(sc->str[0] == '-') ? ft_putstr(sc->str + 1) : ft_putstr(sc->str);
	}
	else
	{
		sc->c.esp && !sc->c.plus && sc->str[0] != '-' && sc->i_f != 11 ?
		(write(1, " ", 1) && (sc->col-- & sc->ret++)) : 0;
		sc->c.plus && sc->str[0] != '-' && sc->i_f != 11 ?
		(write(1, "+", 1) && sc->ret++) : 0;
		sc->i_f == 6 && sc->str[0] == '-' && sc->c.zo &&
		(!sc->bp && !sc->p2) ? write(1, "-", 1) : 0;
		ft_printp(sc, sc->str);
		(sc->str[0] == '-') ? ft_putstr(sc->str + 1) : ft_putstr(sc->str);
		ft_printcol(sc, sc->str);
	}
}

void	ft_printitoa(t_print *sc, va_list ap)
{
	sc->str = (sc->i_f < 7 ? ft_fillstrmod(ap, sc) : ft_fillstrmod2(ap, sc));
	sc->bp = sc->p;
	if (sc->i_f == 5)
		return (ft_printoctal(sc));
	if (sc->i_f == 7 || sc->i_f == 8)
		return (ft_printhex(sc));
	if (sc->p2 && sc->str[0] == '0')
	{
		!sc->c.plus && sc->c.esp && !sc->col ?
		write(1, " ", 1) && sc->ret++ : 0;
		return (ft_printcol(sc, sc->str));
	}
	sc->col -= ft_strlen(sc->str);
	if (sc->p)
	{
		sc->p -= ft_strlen(sc->str) > (size_t)sc->p ?
		sc->p : ft_strlen(sc->str);
		sc->col -= sc->str[0] != '-' ? sc->p : (sc->p + 1);
	}
	ft_printdeg(sc);
	sc->ret += ft_strlen(sc->str);
	free(sc->str);
}

void	ft_printstring(t_print *sc, va_list ap)
{
	sc->str = va_arg(ap, char*);
	sc->str == NULL ? (sc->str = ft_strdup("(null)")) : 0;
	if (sc->p2)
		return (ft_printcol(sc, sc->str));
	if (sc->c.moins && ft_strlen(sc->str) > 0)
		write(1, sc->str, sc->p && (size_t)sc->p < ft_strlen(sc->str) ?
			sc->p : ft_strlen(sc->str));
	if (sc->col)
		sc->col -= sc->p && (size_t)sc->p < ft_strlen(sc->str) ?
	sc->p : ft_strlen(sc->str);
	while (sc->col-- > 0 && ++sc->ret)
		write(1, (sc->c.zo) ? "0" : " ", 1);
	if (!sc->c.moins && ft_strlen(sc->str) > 0)
		write(1, sc->str, sc->p && (size_t)sc->p < ft_strlen(sc->str) ?
			sc->p : ft_strlen(sc->str));
	sc->ret += sc->p && (size_t)sc->p < ft_strlen(sc->str) ?
	sc->p : ft_strlen(sc->str);
}

void	ft_printsc(t_print *sc, va_list ap)
{
	if (sc->i_f == 13)
		ft_printstring(sc, ap);
	else
	{
		if (sc->c.moins)
			sc->i_f == 10 ? write(1, "%", 1) : ft_putchar(va_arg(ap, int));
		sc->col ? sc->col-- : 0;
		while (sc->col-- > 0 && ++sc->ret)
			write(1, (sc->c.zo) ? "0" : " ", 1);
		if (!sc->c.moins)
			sc->i_f == 10 ? write(1, "%", 1) : ft_putchar(va_arg(ap, int));
		sc->ret++;
	}
}

char	*ft_convbase(va_list ap, t_print *sc)
{
	unsigned long adress;

	adress = 0;
	if (sc->i_f < 9 && sc->i_f > 4)
		ft_printitoa(sc, ap);
	if (sc->i_f == 9)
	{
		adress = (unsigned long)va_arg(ap, void*);
		sc->len = ft_intlen(adress);
		sc->str = ft_itoa_base(adress, H);
		sc->col -= 2;
		sc->p ? sc->p -= ft_strlen(sc->str) : 0;
		sc->p > 0 ? sc->col -= sc->p : 0;
		sc->p2 && sc->str[0] == '0' ? 0 : (sc->col -= ft_strlen(sc->str));
		ft_printadress(sc);
	}
	if (sc->i_f == 10)
		ft_percent(sc);
	else if (sc->i_f == 11)
		ft_printitoa(sc, ap);
	else if (sc->i_f == 12 || sc->i_f == 10 || sc->i_f == 13)
		ft_printsc(sc, ap);
	else if (sc->i_f == 14)
		ft_floprint(ap, sc);
	return (NULL);
}
