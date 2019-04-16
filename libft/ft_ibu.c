/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sofchami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 22:24:15 by sofchami          #+#    #+#             */
/*   Updated: 2018/12/12 22:24:23 by sofchami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_isvalid(char *base)
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

char					*ft_ibu(unsigned long long nb, char *base)
{
	long long			n;
	char				*res;
	unsigned long long	tmp;

	tmp = nb;
	n = 1;
	if (ft_isvalid(base) == 0)
		return (NULL);
	if (nb == 0)
		return (ft_strdup("0"));
	while (tmp >= ft_strlen(base))
	{
		tmp = tmp / ft_strlen(base);
		n++;
	}
	if (!(res = (char*)malloc(sizeof(*res) * (n + 1))))
		return (NULL);
	res[n] = '\0';
	while (n > 0)
	{
		res[--n] = (base[nb % ft_strlen(base)]);
		nb /= ft_strlen(base);
	}
	return (res);
}
