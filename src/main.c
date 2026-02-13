/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:28:59 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 16:45:23 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * This is the entry point of the program.
 * `ft_nm` is the main function of the program.
 * Based of the compilation type (mandatory or bonus)
 * it calls the appropriate function (same name)
 * from the `mandatory` or `bonus` folder respectively.
 */
int	main(int argc, char **argv)
{
	t_ft_nm	nm;

	nm = (t_ft_nm){
		.progname = argv[0],
		.argc = argc - 1,
		.argv = argv,
		.options = (t_nm_option){0}
	};
	nm.options.value = parse_argv(nm.argv, &nm.options.valid, &nm.options.bad);
	nm.argc = argc - 1 - nm.options.valid;
	ft_nm(&nm);
	return (0);
}
