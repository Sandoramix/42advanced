/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_symbol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:31:29 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/25 12:31:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	nm_symbol_chr(t_nm_symbol_type type, bool local, bool weak)
{
	char	val;

	val = type;
	if (weak)
	{
		val = 'W';
		if (type == SYMBOL_TYPE_UNDEFINED)
			val = 'w';
	}
	if (local)
		return (ft_tolower(val));
	return (val);
}
