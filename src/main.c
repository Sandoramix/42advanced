/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:28:59 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 14:43:57 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	remove_progname_from_argv(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		argv[i] = argv[i + 1];
	argv[i] = NULL;
}

/**
 * This is the entry point of the program.
 * `ft_nm` is the main function of the program.
 * Based of the compilation type (mandatory or bonus)
 * it calls the appropriate function `ft_nm` (same name)
 * from the `mandatory` or `bonus` folder respectively.
 */
int	main(int argc, char **argv)
{
	t_nm	nm;

	nm = (t_nm){
		.progname = argv[0],
		.argc = argc - 1,
		.argv = argv,
		.options = (t_nm_option){0}
	};
	remove_progname_from_argv(nm.argv);
	ft_nm(&nm);
	return (0);
}
