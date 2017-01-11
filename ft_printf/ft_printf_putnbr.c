#include "ft_printf.h"

uintmax_t	ft_printf_getarg_nbr_unsigned(va_list args, t_args a)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (a.lenght == SIZE_HH)
		nbr = (unsigned char)nbr;
	else if (a.lenght == SIZE_H)
		nbr = (unsigned short int)nbr;
	else if (a.lenght == SIZE_L)
		nbr = (unsigned long int)nbr;
	else if (a.lenght == SIZE_LL)
		nbr = (unsigned long long int)nbr;
	else if (a.lenght == SIZE_J)
		nbr = (uintmax_t)nbr;
	else if (a.lenght == SIZE_Z)
		nbr = (size_t)nbr;
	else if (a.type == 'p')
		nbr = (unsigned long)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

void	ft_printf_nbrlen_unsigned_recursive(uintmax_t nbr, t_args *a, char base)
{
	a->tmp++;
	if (nbr == 0 && a->tmp != 0)
		return;
	ft_printf_nbrlen_unsigned_recursive(nbr / base, a, base);
}

void	ft_printf_putnbr_unsigned_recursive(uintmax_t nbr, t_args *a, char base)
{
	uintmax_t	n;

	a->tmp++;
	if (nbr == 0 && a->tmp != 0)
		return;
	ft_printf_putnbr_unsigned_recursive(nbr / base, a, base);
	n = nbr % base;
	if (n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 36)
	{
		if (a->type == 'X')
			ft_putchar('A' + (n - 10));
		else
			ft_putchar('a' + (n - 10));
	}
}

void	ft_printf_putnbr_unsigned(uintmax_t nbr, t_args *a, char base)
{
	int 		spaces;
	int			save;
	uintmax_t	n;

	ft_printf_nbrlen_unsigned_recursive(nbr, a, base);
	if (a->plus != -1)
	{
		ft_putchar('+');
		a->tmp++;
	}
	/*else if (a->space != -1)
	{
		ft_putchar(' ');
		a->tmp++;
	}*/
	if(a->hash != -1 && nbr != 0)
	{
		ft_putchar('0');
		a->tmp++;
		if (base == 16)
		{
			ft_putchar('x');
			a->tmp++;
		}
	}
	if (a->width != -1 && a->minus == -1)
	{
		spaces = a->width - a->tmp;
		while (spaces-- > 0)
		{
			ft_putchar((a->zero != -1) ? '0' : ' ');
			a->tmp++;
		}
	}
	if (a->precision != -1)
	{
		n = a->precision - a->tmp;
		while(n-- > 0)
		{
			write(1, "0", 1);
			a->tmp++;
		}
	}
	save = a->tmp;
	a->tmp = -1;
	ft_printf_putnbr_unsigned_recursive(nbr, a, base);
	a->tmp = save;
	if (a->width != -1 && a->minus != -1)
	{
		spaces = a->width - a->tmp;
		while (spaces-- > 0)
		{
			ft_putchar((a->zero != -1) ? '0' : ' ');
			a->tmp++;
		}
	}
}

intmax_t	ft_printf_getarg_nbr_signed(va_list args, t_args a)
{
	intmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (a.lenght == SIZE_HH)
		nbr = (signed char)nbr;
	else if (a.lenght == SIZE_H)
		nbr = (short int)nbr;
	else if (a.lenght == SIZE_L)
		nbr = (long int)nbr;
	else if (a.lenght == SIZE_LL)
		nbr = (long long int)nbr;
	else if (a.lenght == SIZE_J)
		nbr = (intmax_t)nbr;
	else if (a.lenght == SIZE_Z)
		nbr = (ssize_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

void	ft_printf_putnbr_signed_recursive(intmax_t nbr, t_args *a, char base, int neg)
{
	intmax_t	n;
	int 		spaces;

	a->tmp++;
	if (nbr == 0 && a->tmp != 0)
	{

		if (a->plus != -1 && !neg)
		{
			ft_putchar('+');
			a->tmp++;
		}
		else if (a->space != -1 && !neg)
		{
			ft_putchar(' ');
			a->tmp++;
		}
		else if (neg)
		{
			ft_putchar('-');
			a->tmp++;
		}
		if (a->width != -1 && a->minus == -1)
		{
			spaces = a->width - a->tmp;
			while (spaces-- > 0)
			{
				ft_putchar((a->zero != -1) ? '0' : ' ');
				a->tmp++;
			}
		}
		if (a->precision != -1)
		{
			n = a->precision - a->tmp;
			while(n-- > 0)
			{
				write(1, "0", 1);
				a->tmp++;
			}
		}
		return;
	}
	ft_printf_putnbr_signed_recursive(nbr / base, a, base, neg);
	n = nbr % base;
	if (neg)
		n = 0 - n;
	if (n <= 9)
		ft_putchar('0' + n);
	if (n >= 10 && n <= 36)
	{
		if (a->type == 'X')
			ft_putchar('A' + (n - 10));
		else
			ft_putchar('a' + (n - 10));
	}
}

void	ft_printf_putnbr_signed(intmax_t nbr, t_args *a, char base, int neg)
{
	int spaces;

	ft_printf_putnbr_signed_recursive(nbr, a, base, neg);
	if (a->width != -1 && a->minus != -1)
	{
		spaces = a->width - a->tmp;
		while (spaces-- > 0)
		{
			ft_putchar((a->zero != -1) ? '0' : ' ');
			a->tmp++;
		}
	}
}