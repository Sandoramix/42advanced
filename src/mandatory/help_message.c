/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 07:43:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 16:30:49 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm_help_message(t_ft_nm *nm)
{
	write(STDERR_FILENO, "Usage: ", 7);
	write(STDERR_FILENO, nm->progname, ft_strlen(nm->progname));
	write(STDERR_FILENO, " [file(s)]\n", 11);
	write(STDERR_FILENO, " List symbols in [file(s)] "
		"(a.out by default).\n", 47);
}
