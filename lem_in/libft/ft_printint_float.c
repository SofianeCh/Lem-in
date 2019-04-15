/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint_fsc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 21:18:32 by sofchami          #+#    #+#             */
/*   Updated: 2019/01/10 21:18:35 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_floatround(t_float *fl, t_print *sc)
{
	fl->flottant[sc->p > 49 ? 49 : sc->p] = '\0';
	fl->rev = sc->p;
	if ((int)(fl->tmp * 10) > 4)
	{
		fl->round = 1;
		while (fl->round && fl->rev > 0)
		{
			if (fl->flottant[fl->rev - 1] == '9')
			{
				fl->flottant[fl->rev - 1] = '0';
				fl->rev--;
			}
			else
			{
				fl->flottant[fl->rev - 1]++;
				fl->round = 0;
			}
		}
	}
	sc->p2 && (int)(fl->tmp * 10) > 4 ? fl->part1++ : 0;
}

void	ft_floprint2(t_print *sc, t_float *fl)
{
	if (sc->col)
		sc->col -= !sc->p2 ?
	ft_intlen(fl->part1) + sc->p + 1 : ft_intlen(fl->part1) + sc->p;
	sc->p2 && sc->c.dz ? sc->col-- : 0;
	fl->float1 = ft_itoa_base(fl->part1, DEC);
	sc->c.esp && !sc->c.plus && fl->float1[0] != '-' ?
	write(1, " ", 1) && sc->ret++ : 0;
	sc->c.plus && fl->float1[0] != '-' && sc->c.zo ?
	write(1, "+", 1) && sc->ret++ : 0;
	if (sc->col > 0 && !sc->c.moins)
	{
		sc->c.esp && !sc->c.plus && fl->float1[0] != '-' ? sc->col-- : 0;
		sc->c.plus && fl->float1[0] != '-' ? sc->col-- : 0;
		while (sc->col-- > 0 && ++sc->ret)
			write(1, sc->c.zo ? "0" : " ", 1);
	}
	sc->c.plus && fl->float1[0] != '-' && !sc->c.zo ?
	write(1, "+", 1) && sc->ret++ : 0;
	write(1, fl->float1, ft_strlen(fl->float1));
	sc->p2 && sc->c.dz ? write(1, ".", 1) && sc->ret++ : 0;
	sc->ret += (ft_strlen(fl->float1) + (sc->p2 ? 0 : sc->p));
}

void	ft_floprint3(t_print *sc, t_float *fl)
{
	if (!sc->p2)
	{
		write(1, ".", 1);
		sc->ret++;
		if (sc->p > 49)
		{
			write(1, fl->flottant, 49);
			sc->p -= 49;
			while (sc->p-- > 0)
				write(1, "0", 1);
		}
		else
			write(1, fl->flottant, sc->p);
	}
	if (sc->col && sc->c.moins)
	{
		sc->c.plus && fl->float1[0] != '-' ? sc->col-- : 0;
		sc->c.esp && !sc->c.plus && fl->float1[0] != '-' ? sc->col-- : 0;
		while (sc->col-- > 0 && ++sc->ret)
			write(1, " ", 1);
	}
}

void	ft_floprint(va_list ap, t_print *sc)
{
	t_float fl;

	fl.nbr = sc->mod == 3 ?
	(long double)va_arg(ap, long double) : (double)va_arg(ap, double);
	fl.part1 = (long)fl.nbr;
	fl.rest = fl.nbr > 0 ? fl.nbr - fl.part1 : -fl.nbr + fl.part1;
	fl.tmp = fl.rest;
	if (!sc->p2)
		sc->p = sc->p ? sc->p : 6;
	fl.i = 0;
	while (fl.i < sc->p && fl.i < 50)
	{
		fl.tmp *= 10;
		fl.flottant[fl.i] = (int)fl.tmp + '0';
		fl.tmp -= (int)fl.tmp;
		fl.i++;
	}
	ft_floatround(&fl, sc);
	ft_floprint2(sc, &fl);
	ft_floprint3(sc, &fl);
	free(fl.float1);
}
