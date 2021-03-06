/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 12:32:04 by mprevot           #+#    #+#             */
/*   Updated: 2016/11/11 13:41:57 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../libft.h"
#include <stdlib.h>

int		main(void)
{
	char	a[] = "cou\0cou";
	char	b[7];

	ft_memcpy(a, b, 7);
	return (memcmp(a, b, 7));
}
