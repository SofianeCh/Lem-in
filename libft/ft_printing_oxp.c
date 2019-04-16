/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:47:49 by sofchami          #+#    #+#             */
/*   Updated: 2019/01/09 16:47:51 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printoctal(t_print *sc)
{
	if (sc->p2 && sc->str[0] == '0')
		if (!sc->c.dz)
			return (ft_printcol(sc, sc->str));
	sc->col -= ft_strlen(sc->str);
	sc->p ? sc->p -= ft_strlen(sc->str) : 0;
	sc->p > 0 ? sc->col -= sc->p : 0;
	if (!sc->c.moins)
	{
		ft_printcol(sc, sc->str);
		ft_printp(sc, sc->str);
		sc->str[0] != '0' && sc->c.dz ? (write(1, "0", 1) && sc->ret++) : 0;
		ft_putstr(sc->str);
	}
	else
	{
		ft_printp(sc, sc->str);
		sc->str[0] != '0' && sc->c.dz ? (write(1, "0", 1) && sc->ret++) : 0;
		ft_putstr(sc->str);
		ft_printcol(sc, sc->str);
	}
	sc->ret += ft_strlen(sc->str);
	free(sc->str);
}

void	ft_printhex2(t_print *sc)
{
	if (!sc->c.moins)
	{
		if (sc->c.zo && sc->c.dz && sc->str[0] != '0' && !sc->bp && !sc->p2)
			sc->i_f != 8 ? write(1, "0x", 2) && (sc->ret += 2) :
		write(1, "0X", 2) && (sc->ret += 2);
		ft_printcol(sc, sc->str);
		if ((!sc->c.zo && sc->c.dz && sc->str[0] != '0') ||
			(sc->c.zo && sc->str[0] != '0' && sc->c.dz && (sc->bp || sc->p2)))
			sc->i_f != 8 ? write(1, "0x", 2) && (sc->ret += 2) :
		write(1, "0X", 2) && (sc->ret += 2);
		ft_printp(sc, sc->str);
		ft_putstr(sc->str);
	}
	else
	{
		if (sc->str[0] != '0' && sc->c.dz)
			sc->i_f != 8 ? (write(1, "0x", 2) && (sc->ret += 2)) :
		write(1, "0X", 2) && (sc->ret += 2);
		ft_printp(sc, sc->str);
		ft_putstr(sc->str);
		ft_printcol(sc, sc->str);
	}
}

void	ft_printhex(t_print *sc)
{
	if (sc->p2 && sc->str[0] == '0')
		return (ft_printcol(sc, sc->str));
	sc->col -= ft_strlen(sc->str);
	sc->p ? sc->p -= ft_strlen(sc->str) : 0;
	sc->p > 0 ? sc->col -= sc->p : 0;
	sc->c.dz && sc->str[0] != '0' ? sc->col -= 2 : 0;
	ft_printhex2(sc);
	sc->ret += ft_strlen(sc->str);
	free(sc->str);
}

void	ft_printadress2(t_print *sc)
{
	if (sc->c.moins)
	{
		sc->len > 1 ? (write(1, "0x", 2) && (sc->ret += 2)) :
		(write(1, "0x", 2) && (sc->ret += 2));
		ft_printp(sc, sc->str);
		ft_putstr(sc->str);
		ft_printcol(sc, sc->str);
	}
	else
	{
		ft_printcol(sc, sc->str);
		sc->len > 1 ? (write(1, "0x", 2) && (sc->ret += 2)) :
		(write(1, "0x", 2) && (sc->ret += 2));
		ft_printp(sc, sc->str);
		ft_putstr(sc->str);
	}
}

void	ft_printadress(t_print *sc)
{
	if (sc->p2 && sc->str[0] == '0')
	{
		if (sc->c.moins)
			write(1, "0x", 2) && (sc->ret += 2);
		ft_printcol(sc, sc->str);
		if (!sc->c.moins)
			write(1, "0x", 2) && (sc->ret += 2);
		return ;
	}
	sc->ret += ft_strlen(sc->str);
	ft_printadress2(sc);
	free(sc->str);
}
