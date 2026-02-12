/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_elf_format.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 08:49:50 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/12 08:52:38 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * Identifies the format of the given ELF file.
 * @param e_indent the buffer received from mmap of the file
 * @returns 
 * 		- `ELFCLASSNONE` if the file is not a valid ELF file
 * 
 * 		- `ELFCLASS32` if the file is 32-bit
 * 
 * 		- `ELFCLASS64` if the file is 64-bit
 */
int	nm_identify_elf_format(unsigned char *e_indent)
{
	int	class;

	if (!e_indent)
		return (ELFCLASSNONE);
	if (e_indent[EI_MAG0] != ELFMAG0
		|| e_indent[EI_MAG1] != ELFMAG1
		|| e_indent[EI_MAG2] != ELFMAG2
		|| e_indent[EI_MAG3] != ELFMAG3)
	{
		write(STDERR_FILENO, "Error: Provided file is not valid\n", 34);
		return (ELFCLASSNONE);
	}
	class = e_indent[EI_CLASS];
	if (class != ELFCLASS32 && class != ELFCLASS64)
		return (ELFCLASSNONE);
	return (class);
}
