/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_symbol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:31:29 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/27 12:22:32 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

char	nm_symbol_chr(const t_nm_symbol *symbol)
{
	char					val;

	val = symbol->type;
	if (symbol->is_weak)
	{
		if (symbol->st_type == STT_OBJECT)
		{
			val = 'V';
			if (symbol->type == SYMBOL_TYPE_UNDEFINED)
				val = 'v';
		}
		else
		{
			val = 'W';
			if (symbol->type == SYMBOL_TYPE_UNDEFINED)
				val = 'w';
		}
	}
	if (symbol->is_local)
		return (ft_tolower(val));
	return (val);
}
