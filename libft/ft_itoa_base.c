/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 20:52:21 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/19 20:52:23 by sofchami         ###   ########.fr       */
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
		k = i;
		if (base[i] < 32 && base[i] > 126)
			return (0);
		while (base[k])
			if (base[++k] == check)
				return (0);
		i++;
	}
	return (1);
}

char			*ft_itoa_base(long long nb, char *base)
{
	int			sign;
	char		*res;
	long long	n;
	long long	tmp;

	tmp = ft_abs(nb);
	if ((n = 1) && ft_isvalid(base) == 0)
		return (NULL);
	if ((nb < 0 && -(nb + 1) == 9223372036854775807) || (nb == 0))
		return (nb == 0 ? ft_strdup("0") : ft_strdup("-9223372036854775808"));
	while (tmp >= (long long)ft_strlen(base) && ++n)
		tmp = tmp / ft_strlen(base);
	n = (nb < 0) ? n + 1 : n;
	sign = (nb < 0) ? 1 : 0;
	if (!(res = (char*)malloc(sizeof(*res) * (n + 1))))
		return (NULL);
	nb = (sign > 0) ? ft_abs(nb) : nb;
	res[n] = '\0';
	while (n > 0)
	{
		res[--n] = (base[nb % ft_strlen(base)]);
		nb /= ft_strlen(base);
		sign == 1 ? res[0] = '-' : 0;
	}
	return (res);
}
