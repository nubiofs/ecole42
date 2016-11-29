/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:26:56 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/28 14:30:25 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = ft_strdup(s);
	while (dup[i])
	{
		dup[i] = f(i, dup[i]);
		i++;
	}
	return (dup);
}