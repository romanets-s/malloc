/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dverbyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 21:13:02 by dverbyts          #+#    #+#             */
/*   Updated: 2018/11/24 21:13:05 by dverbyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

void	ft_putstr(char const *s)
{
	int z;

	if (s)
	{
		z = 0;
		while (s[z])
		{
			write(1, &s[z], 1);
			z++;
		}
	}
}

void	ft_putnbr(long n)
{
	long		p;
	char		x;

	p = n;
	if (p < 0)
	{
		write(1, "-", 1);
		p = p * -1;
	}
	if (p > 9)
	{
		ft_putnbr(p / 10);
	}
	x = p % 10 + 48;
	write(1, &x, 1);
}

void	print_adr(long n, int base)
{
	char tmp;

	if (n < 0)
	{
		ft_putstr("-");
		n = -n;
	}
	if (n > base - 1)
	{
		print_adr(n / base, base);
		print_adr(n % base, base);
	}
	else
	{
		if (n < 10)
		{
			tmp = n + '0';
			write(1, &tmp, 1);
		}
		else
			tmp = n + 'a' - 10;
			write(1, &tmp, 1);
	}
}

void	print_blocks(t_block *tmp, char *type)
{
	size_t adr;

	ft_putstr(type);
	if (tmp == NULL)
		return (ft_putstr(" : \n"));
	ft_putstr(" : ");
	adr = (long)&tmp;
	ft_putnbr((long)&tmp);
	ft_putnbr(adr);
	print_adr((long)tmp, 16);
	while (tmp != NULL)
	{
		if (tmp->status == USED)
		{
			print_adr((long)tmp->memory, 16);
			ft_putstr(" - ");
			print_adr((long)(tmp->memory + tmp->used_memory_size), 16);
			ft_putstr(" : ");
			ft_putnbr(tmp->used_memory_size);
			ft_putstr(tmp->used_memory_size == 1 ? " byte\n" : " bytes\n");
		}
		tmp = tmp->next;
	}
}

void	show_alloc_mem(void)
{
	print_blocks(g_global->tiny, "TINY");
	print_blocks(g_global->small, "SMALL");
	print_blocks(g_global->large, "LARGE");
	ft_putstr("Total : ");
	ft_putnbr(g_global->summary_size);
	ft_putstr(g_global->summary_size == 1 ? " byte\n" : " bytes\n");
}
