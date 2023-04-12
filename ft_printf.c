/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo <hubrygo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:45:23 by hubrygo           #+#    #+#             */
/*   Updated: 2023/04/12 15:57:46 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <../19_libft/libft.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	if (!c)
		return ;
	write(1, &c, 1);
}

void	ft_put_unsigned_nbr(unsigned int nb)
{
	unsigned int	num;

	if (nb >= 10)
	{
		ft_put_unsigned_nbr(nb / 10);
		ft_put_unsigned_nbr(nb % 10);
	}
	if (nb < 10)
	{
		num = nb + 48;
		write (1, &num, 1);
	}
}

void	ft_putnbr(int nb)
{
	int	num;

	if (nb != -2147483648)
	{
		if (nb < 0)
		{
			write (1, "-", 1);
			nb = -nb;
		}
		if (nb >= 10)
		{
			ft_putnbr(nb / 10);
			nb = nb % 10;
		}
		if (nb < 10)
		{
			num = nb + 48;
			write (1, &num, 1);
		}
	}
	else
	{
		write (1, "-2147483648", 11);
	}
}

void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		write (1, &str[i], 1);
		i++;
	}
}

void	ft_putnbr_base(unsigned long int nb, int i)
{
	if (nb >= 16)
	{
		ft_putnbr_base(nb / 16, i);
		ft_putnbr_base(nb % 16, i);
	}
	if (nb < 16 && i == 1)
		ft_putchar("0123456789abcdef"[nb]);
	if (nb < 16 && i == 2)
		ft_putchar("0123456789ABCDEF"[nb]);
}

int	ft_hub(char c, va_list lst)
{
	if (c == 'c')
		ft_putchar(va_arg(lst, int));
	if (c == 's')
		ft_putstr(va_arg(lst, char *));
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(lst, int));
	if (c == 'u')
		ft_put_unsigned_nbr(va_arg(lst, unsigned int));
	if (c == 'p')
	{
		ft_putstr("0x");
		ft_putnbr_base(va_arg(lst, unsigned long), 1);
	}
	if (c == 'x')
		ft_putnbr_base(va_arg(lst, unsigned long), 1);
	if (c == 'X')
		ft_putnbr_base(va_arg(lst, unsigned long), 2);
	if (c == '%')
		ft_putchar('%');
	return (1);
}

char	ft_is_in(char c)
{
	if (c == 'c')
		return (1);
	if (c == 's')
		return (1);
	if (c == 'd' || c == 'i')
		return (1);
	if (c == 'u')
		return (1);
	if (c == 'p')
		return (1);
	if (c == 'x')
		return (1);
	if (c == 'X')
		return (1);
	if (c == '%')
		return (1);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	lst;
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%' && ft_is_in(str[i + 1]) == 1)
		{
			ft_hub(str[i + 1], lst);
			i += 2;
		}
		else
		{
			ft_putchar(str[i]);
			i++;
		}
	}
	va_end(lst);
	return (1);
}

int main()
{	
	printf("Printf: %u\n", 4);
	ft_printf("My printf: %u\n", 4);
}
