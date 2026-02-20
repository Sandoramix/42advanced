/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:50:51 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/20 15:25:31 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	nm_run(t_nm *nm, const char *file_path)
{
	t_nm_target		target;
	void			*mapping;

	mapping = NULL;
	target = (t_nm_target){0};
	target.stat = nm_get_file_stat(file_path, &target.fd);
	if (target.fd == -1)
		return (nm_set_file_error(nm));
	if (!nm_retrieve_file_mapping(nm, &target.stat, target.fd, &mapping))
		return ;
	target.mapping = mapping;
	write(1, file_path, ft_strlen(file_path));
	write(1, ":\n", 2);
	target.format = elf_get_format(file_path, target.mapping);
	if (target.format == ELFCLASS32)
		nm_run_32(nm, &target, mapping);
	else if (target.format == ELFCLASS64)
		nm_run_64(nm, &target, mapping);

	nm_cleanup_file_mapping(&target.stat, target.fd, &mapping);
	if (target.format == ELFCLASSNONE)
		return (nm_set_file_error(nm));
}

void	nm_cycle(t_nm *nm)
{
	int	i;

	i = -1;
	while (nm->argv[++i])
		nm_run(nm, nm->argv[i]);
	if (i == 0)
		nm_run(nm, "./a.out");
	if (nm->bad_file_passed)
		exit(EXIT_FAILURE);
}
