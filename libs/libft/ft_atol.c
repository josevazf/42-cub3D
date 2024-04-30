/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:31:45 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 16:37:12 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Converts the string argument `nstr` to a long.
   This function returns the converted integral number as a long value. 
   If no valid conversion could be performed, it returns zero. */
long	ft_atol(const char *nstr)
{
	size_t		i;
	long		sign;
	long		nb;

	nb = 0;
	sign = 1;
	i = 0;
	while ((nstr[i] >= 9 && nstr[i] <= 13) || nstr[i] == 32)
		i++;
	if (nstr[i] == '-' || nstr[i] == '+')
	{
		if (nstr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nstr[i] >= '0' && nstr[i] <= '9')
		nb = nb * 10 + nstr[i++] - '0';
	return (nb * sign);
}
