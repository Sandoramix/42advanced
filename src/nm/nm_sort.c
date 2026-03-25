/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 07:54:54 by odudniak          #+#    #+#             */
/*   Updated: 2026/03/25 08:15:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	swap_sym(t_nm_symbol *a, t_nm_symbol *b)
{
	t_nm_symbol	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	cmp_sym(t_nm_symbol *a, t_nm_symbol *b, bool rev)
{
	int	cmp;

	cmp = ft_strcoll(a->name, b->name);
	if (rev)
		return (-cmp);
	return (cmp);
}

static void	inplace_merge(t_nm_symbol *arr, size_t mid, size_t n, bool rev)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = mid;
	while (i < j && j < n)
	{
		if (cmp_sym(&arr[i], &arr[j], rev) <= 0)
			i++;
		else
		{
			k = j;
			while (k > i)
			{
				swap_sym(&arr[k], &arr[k - 1]);
				k--;
			}
			i++;
			j++;
		}
	}
}

static void	merge_sort(t_nm_symbol *symbols, size_t sym_count, bool reverse)
{
	size_t	mid;

	if (sym_count < 2)
		return ;
	mid = sym_count / 2;
	merge_sort(symbols, mid, reverse);
	merge_sort(symbols + mid, sym_count - mid, reverse);
	inplace_merge(symbols, mid, sym_count, reverse);
}

void	nm_sort_symbols(t_nm_symbol *symbols, size_t sym_count, bool reverse)
{
	merge_sort(symbols, sym_count, reverse);
}
