/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_firstword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:08:19 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/30 18:33:13 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Gets the first word from passed string. */
char	*ft_firstword(char *str)
{
	char	*first_word;
	int		start;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (ft_iswhitespace(str[i]) && str[i])
		i++;
	start = i;
	while (!ft_iswhitespace(str[i]) && str[i])
		i++;
	first_word = ft_substr(str, start, (i - start));
	return (first_word);
}
