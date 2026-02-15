/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 14:39:19 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 17:35:57 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * List of all the options that can be passed to the program.
 * @return the list of all the options (`t_option_info` structure)
 */
const t_option_info	*get_help_options(void)
{
	static const t_option_info	options[] = {
	{"a", "debug-syms", "Display debugger-only symbols",
		NMFLAG_DEBUG_SYMS},
	{"g", "extern-only", "Display only external symbols",
		NMFLAG_EXTERN_ONLY},
	{"u", "undefined-only", "Display only undefined symbols",
		NMFLAG_UNDEFINED_ONLY},
	{"r", "reverse-sort", "Reverse the sense of the sort",
		NMFLAG_REVERSE_SORT},
	{"p", "no-sort", "Do not sort the symbols",
		NMFLAG_NO_SORT},
	{"h", "help", "Display this information",
		NMFLAG_HELP},
	{NULL, NULL, NULL, 0}
	};

	return (options);
}
