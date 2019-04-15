/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:37:00 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/19 15:37:03 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isvalid(char *base)
{
	int		i;
	int		k;
	char	check;

	i = 0;
	k = 0;
	if (!base)
		return (0);
	if (ft_strlen(base) < 2)
		return (0);
	while (base[i])
	{
		check = base[i];
		if (base[i] == '-' || base[i] == '+')
			return (0);
		if (base[i] < 32 && base[i] > 126)
			return (0);
		k = i;
		while (base[k])
			if (base[++k] == check)
				return (0);
		i++;
	}
	return (1);
}

static	void	ft_print_base(char *base, char *res, int n)
{
	while (res[n])
		if (n == 0 && res[n] == '-')
			ft_putchar(res[n++]);
		else
			ft_putchar(base[res[n++] - '0']);
}

void			ft_putnbr_base(int nb, char *base)
{
	int		sign;
	int		n;
	int		k;
	char	*res;

	k = 0;
	n = 0;
	if (ft_isvalid(base) == 0)
		return ;
	while (ft_power(ft_strlen(base), n) < ft_abs(nb))
		n++;
	n = (nb < 0) ? n += 1 : n;
	sign = (nb < 0) ? 1 : 0;
	if (!(res = (char*)malloc(sizeof(*res) * (n + 1))))
		return ;
	nb = (sign > 0) ? ft_abs(nb) : nb;
	while (n > 0)
	{
		res[--n] = (nb % ft_strlen(base)) + '0';
		nb /= ft_strlen(base);
		if (sign == 1)
			res[0] = '-';
	}
	ft_print_base(base, res, n);
}
