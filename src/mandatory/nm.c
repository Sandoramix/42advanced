/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:42:27 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/13 17:43:28 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void	set_file_error(t_ft_nm *nm)
{
	nm->bad_file_passed = true;
}

void	cycle(t_ft_nm *nm, const char *file_path)
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

void	ft_nm(t_ft_nm *nm)
{
	int	i;

	fprintf(stderr, "MANDATORY NM CALLED\n");
	if (nm->options.valid > 0 || nm->options.bad > 0)
		return (nm_help_message(nm), exit(EXIT_FAILURE));
	i = -1;
	while (nm->argv[++i])
		cycle(nm, nm->argv[i]);
	if (nm->bad_file_passed)
		exit(EXIT_FAILURE);
}
