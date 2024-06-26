/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkext.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:24:14 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 18:34:52 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Check if file name `str` has the given extension `ext`. */
int	ft_check_ext(char *str, char *ext)
{
	int	str_len;

	str_len = ft_strlen(str);
	return (ft_strncmp(str + str_len - ft_strlen(ext), ext, str_len));
}
