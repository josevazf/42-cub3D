/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:15:54 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 18:30:59 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  */
void	*ft_safe_malloc(size_t bytes)
{
	void	*output;

	output = malloc(bytes);
	if (output == NULL)
		ft_error("malloc error\n", EXIT_FAILURE);
	return (output);
}
