/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:04:14 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 13:15:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static bool	traslate(char **argv, int from, int to)
{
	argv[to] = argv[from];
	return (true);
}

/**
 * Parse the options passed to the program.
 * @param argvp Pointer to the array of arguments passed to the program
 * (will be updated by removing the options from the array)
 * @param valid_opts Number of valid options parsed (will be zeroed and updated)
 * @param bad_opts Number of invalid options parsed (will be zeroed and updated)
 * @return Options parsed
 */
t_option_enum	parse_argv(char **argv, int *valid_opts, int *bad_opts)
{
	t_option_enum	result;
	t_option_enum	opt;
	int				i;
	int				new_idx;

	*valid_opts = 0;
	*bad_opts = 0;
	i = -1;
	new_idx = 0;
	result = 0;
	while (argv[++i])
	{
		if (argv[i][0] != '-' && traslate(argv, i, new_idx++))
			continue ;
		opt = nm_identify_option(argv[i]);
		if (opt == NMFLAG_NONE && traslate(argv, i, new_idx++))
		{
			(*bad_opts)++;
			continue ;
		}
		result |= opt;
		(*valid_opts)++;
	}
	traslate(argv, i, new_idx++);
	return (result);
}
