/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:50:51 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 17:52:23 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	set_file_error(t_ft_nm *nm)
{
	nm->bad_file_passed = true;
}

void	nm_cycle_exec(t_ft_nm *nm, const char *file_path)
{

	int				target_fd;
	t_stat			file_stat;
	void			*target_mapping;
	int				file_format;

	file_stat = nm_getfilestat(file_path, &target_fd);
	if (target_fd == -1)
		return (set_file_error(nm));
	target_mapping = mmap(NULL, file_stat.st_size,
			PROT_READ, MAP_PRIVATE,
			target_fd, 0);
	if (target_mapping == MAP_FAILED)
		return (perror("Error mapping file"), exit(EXIT_FAILURE));
	if (target_mapping == NULL)
		return (write(STDERR_FILENO, "File mapping returned NULL\n", 27),
			set_file_error(nm));
	write(1, file_path, ft_strlen(file_path));
	write(1, ":\n", 2);
	file_format = nm_identify_elf_format(target_mapping);
	if (file_format != ELFCLASSNONE)
	{
		fprintf(stderr, "ELF FORMAT: %s\n", file_format == ELFCLASS32 ? "32-bit"
		: file_format == ELFCLASS64 ? "64-bit" : "unknown");
	}
	munmap(target_mapping, file_stat.st_size);
	close(target_fd);
	if (file_format == ELFCLASSNONE)
		return (set_file_error(nm));
}

void	nm_cycle(t_ft_nm *nm)
{
	int	i;

	i = -1;
	while (nm->argv[++i])
		nm_cycle_exec(nm, nm->argv[i]);
	if (nm->bad_file_passed)
		exit(EXIT_FAILURE);
}
