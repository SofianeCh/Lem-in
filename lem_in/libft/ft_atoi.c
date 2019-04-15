/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:33:19 by sofchami          #+#    #+#             */
/*   Updated: 2018/10/17 04:21:35 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_error(int i, int neg)
{
	if (i == 19 && neg == 1)
		return (0);
	if (i == 19 && neg == 0)
		return (-1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int i;
	int neg;
	int res;

	i = 0;
	neg = 0;
	res = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\n' ||
	str[i] == '\r' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		if (i == 19)
			return (ft_error(i, neg));
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (neg == 1)
		res = -res;
	return ((int)res);
}
