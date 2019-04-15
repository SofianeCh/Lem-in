/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 19:32:59 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/18 20:38:04 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs1(int n, char *itoa)
{
	n = ft_abs(n);
	itoa[0] = '-';
	return (n);
}

static char	*ft_zero(char *itoa)
{
	itoa[0] = '0';
	return (itoa);
}

char		*ft_itoa(int n)
{
	size_t		i;
	char		*itoa;

	i = ft_intlen(n);
	if ((itoa = (char*)malloc(sizeof(*itoa) * (i + 1))) == 0)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	itoa[i] = '\0';
	if (n < 0)
		n = ft_abs1(n, itoa);
	if (n == 0)
		return (ft_zero(itoa));
	while (i > 1)
	{
		itoa[--i] = (n % 10) + '0';
		n /= 10;
	}
	if (n > 0)
		itoa[0] = n + '0';
	return (itoa);
}
