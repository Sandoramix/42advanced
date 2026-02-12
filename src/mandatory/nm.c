/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:42:27 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/12 08:56:23 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	ft_nm(int argc, char **argv)
{
	int				target_fd;
	t_stat			file_stat;
	void			*target_mapping;
	int				file_format;

	fprintf(stderr, "MANDATORY NM CALLED\n");
	if (argc != 2)
		return (nm_help_message(), exit(EXIT_FAILURE));
	file_stat = nm_getfilestat(argv[1], &target_fd);
	if (target_fd == -1)
		return (exit(EXIT_FAILURE));
	target_mapping = mmap(NULL, file_stat.st_size,
			PROT_READ, MAP_PRIVATE,
			target_fd, 0);
	if (target_mapping == MAP_FAILED)
		return (perror("Error mapping file"), exit(EXIT_FAILURE));
	if (target_mapping == NULL)
		return (write(STDERR_FILENO, "File mapping returned NULL\n", 27),
			exit(EXIT_FAILURE));
	file_format = nm_identify_elf_format(target_mapping);
	if (file_format != ELFCLASSNONE)
	{
		fprintf(stderr, "ELF FORMAT: %s\n", file_format == ELFCLASS32 ? "32-bit"
		: file_format == ELFCLASS64 ? "64-bit" : "unknown");
	}
	munmap(target_mapping, file_stat.st_size);
	close(target_fd);
	if (file_format == ELFCLASSNONE)
		exit(EXIT_FAILURE);
}
