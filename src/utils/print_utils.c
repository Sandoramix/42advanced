/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:36:02 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/25 16:57:24 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_hexa(uint64_t n, int zeropad)
{
	static const char	hex[] = "0123456789abcdef";
	int					i;
	char				c;

	i = 0;

	c = hex[(n % 16)];
	if (n > 15 || zeropad > 0)
		print_hexa(n / 16, zeropad - 1);
	write(1, &c, 1);
}

void	print_chr_repeat(char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

void	nm_print_symbol_line(t_nm_symbol *symbol, int zeropad)
{
	char	c;

	if (symbol->type == SYMBOL_TYPE_UNDEFINED)
		print_chr_repeat(' ', zeropad);
	else
		print_hexa(symbol->offset, zeropad - 1);
	write(1, " ", 1);
	c = nm_symbol_chr(symbol->type, symbol->is_local, symbol->is_weak);
	write(1, &c, 1);
	write(1, " ", 1);
	write(1, symbol->name, ft_strlen(symbol->name));
	write(1, "\n", 1);
}
