/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:34:00 by odudniak          #+#    #+#             */
/*   Updated: 2026/03/25 07:55:13 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_print_possible_warnings(t_nm *nm, t_nm_target *t)
{
	if (t->symbol_count == 0)
	{
		write(2, nm->progname, ft_strlen(nm->progname));
		write(2, ": ", 2);
		write(2, t->path, ft_strlen(t->path));
		write(2, ": no symbols\n", 13);
		return ;
	}
}

void	nm_set_file_error(t_nm *nm)
{
	nm->bad_file_passed = true;
}
