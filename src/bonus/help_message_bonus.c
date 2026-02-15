/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_message_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 07:43:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 16:28:25 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	show_known_options(void)
{
	const t_option_info	*options = get_help_options();
	int					pad;
	int					i;
	int					short_len;
	int					long_len;

	write(STDERR_FILENO, " The options are:\n", 18);
	i = -1;
	while (options[++i].value)
	{
		short_len = ft_strlen(options[i].short_name);
		long_len = ft_strlen(options[i].long_name);
		write(STDERR_FILENO, "   -", 4);
		write(STDERR_FILENO, options[i].short_name, short_len);
		write(STDERR_FILENO, ", --", 4);
		write(STDERR_FILENO, options[i].long_name, long_len);
		pad = 25 - 8 - short_len - long_len;
		while (--pad >= 0)
			write(STDERR_FILENO, " ", 1);
		write(STDERR_FILENO, options[i].description,
			ft_strlen(options[i].description));
		write(STDERR_FILENO, "\n", 1);
	}
}

void	nm_help_message(t_nm *nm)
{
	write(STDERR_FILENO, "Usage: ", 7);
	write(STDERR_FILENO, nm->progname, ft_strlen(nm->progname));
	write(STDERR_FILENO, " [option(s)] [file(s)]\n", 23);
	write(STDERR_FILENO, " List symbols in [file(s)] "
		"(a.out by default).\n", 47);
	show_known_options();
}
