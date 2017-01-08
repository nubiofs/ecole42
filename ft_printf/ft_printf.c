/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 09:48:59 by mprevot           #+#    #+#             */
/*   Updated: 2017/01/04 11:37:02 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_synonyms(t_args *a)
{
	if (a->type == 'D')
	{
		a->type = 'd';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'O')
	{
		a->type = 'o';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'U')
	{
		a->type = 'u';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'C')
	{
		a->type = 'c';
		a->lenght = SIZE_L;
	}
	else if (a->type == 'S')
	{
		a->type = 's';
		a->lenght = SIZE_L;
	}
}

wchar_t		*ft_wstrdup(const char *str, size_t len)
{
	wchar_t	*r;

	if (!(r = malloc((len + 1) * sizeof(wchar_t))))
		return (NULL);
	r[len] = '\0';
	while(len--)
		r[len] = str[len];
	return r;
}

int	ft_recursive_printf(const char *str, va_list ap)
{
	int		i;
	char	*tmp;
	intmax_t 	n;
	wchar_t	*s;
	char	c;
	t_args	a;
	int 	printed;

	i = 0;
	tmp = ft_strchr(str, '%');
	if (tmp == NULL)
	{
		ft_putstr(str);
		return (ft_strlen(str));
	}
	i = tmp - str;
	write(1, str, i);
	a = ft_printf_readarg(str + i);
	ft_printf_synonyms(&a);
	if (a.type == 's')
	{
		if (a.lenght == SIZE_L)
		{
			
			ft_printf_wputstr(va_arg(ap, t_unicode *), &a);
		}
		else
		{
			tmp = va_arg(ap, char *);
			s = ft_wstrdup(tmp, ft_strlen(tmp));
			if (!s)
				return (0);
			ft_printf_wputstr(s, &a);
			free(s);
		}
	}
	else if (a.type == 'p')
	{
		a.hash = 1;
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 16);
	}
	else if (a.type == 'b')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 2);
	else if (a.type == 'r')
	{
		if (a.lenght == SIZE_L)
		{
			ft_printf_rwputstr(va_arg(ap, wchar_t *), &a);
		}
		else
		{
			tmp = va_arg(ap, char *);
			s = ft_wstrdup(tmp, ft_strlen(tmp));
			if (!s)
				return (0);
			ft_printf_rwputstr(s, &a);
			free(s);
		}
	}
	else if (a.type == 'd' || a.type == 'i')
	{
		n = ft_printf_getarg_nbr_signed(ap, a);
	 	ft_printf_putnbr_signed(n, &a, 10, n < 0);
	}
	else if (a.type == 'o')
	 	ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 8);
	else if (a.type == 'u')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 10);
	else if (a.type == 'x')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 16);
	else if (a.type == 'X')
		ft_printf_putnbr_unsigned(ft_printf_getarg_nbr_unsigned(ap, a), &a, 16);
	else if (a.type == 'c')
	{
		c = va_arg(ap, int);
		s = ft_wstrdup(&c, 1);
		if (!s)
			return (0);
		ft_printf_wputstr(s, &a);
		free(s);
	}
	else if (a.type == '%')
	{
		c = '%';
		s = ft_wstrdup(&c, 1);
		if (!s)
			return (0);
		ft_printf_wputstr(s, &a);
		free(s);
	}
	printed = i + a.tmp;
	i += a.nbr;
	return ft_recursive_printf(str + i, ap) + printed;
}

int	ft_printf(const char *format, ...)
{
	va_list ap;
	int 	r;

	va_start(ap, format);
	r = ft_recursive_printf(format, ap);

	va_end(ap);
	return (r);
}

int ft_vprintf(const char * restrict format, va_list ap)
{
	return ft_recursive_printf(format, ap);
}