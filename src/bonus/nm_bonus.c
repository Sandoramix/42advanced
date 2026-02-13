/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:31:16 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 17:19:33 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_nm(t_ft_nm *nm)
{
	nm->options.value = parse_argv(nm->argv,
			&nm->options.valid, &nm->options.bad);
	nm->argc = nm->argc - nm->options.valid;
	if (nm->options.value & NMFLAG_HELP)
		return (nm_help_message(nm), exit(EXIT_SUCCESS));
	if (nm->options.bad > 0)
		return (nm_help_message(nm), exit(EXIT_FAILURE));
}
