/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:52:42 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/15 18:08:31 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * Add a symbol to the array of symbols.
 * @param sym_head Pointer to the head of the array of symbols
 * @param sym_size Pointer to the size of the array of symbols
 * @param sym Symbol to be added
 * @return true if the symbol was added, false otherwise (malloc failed)
 * @note `malloc` and `free` are used
 * to allocate enough memory for the new symbol
 */
bool	elf_add_symbol(t_nm_symbol **sym_head, size_t *sym_size,
	t_nm_symbol sym)
{
	size_t		i;
	size_t		sym_len;
	t_nm_symbol	*new_head;

	if (!sym_head)
		return (false);
	sym_len = *sym_size;
	*sym_size += 1;
	new_head = malloc((sym_len + 1) * sizeof(t_nm_symbol));
	if (!new_head)
		return (false);
	new_head[sym_len].name = sym.name;
	new_head[sym_len].offset = sym.offset;
	new_head[sym_len].type = sym.type;
	i = 0;
	while (*sym_head && i < sym_len)
	{
		new_head[i] = (*sym_head)[i];
		i++;
	}
	free(*sym_head);
	*sym_head = new_head;
	return (true);
}

/**
 * Identifies the format of the given ELF file.
 * @param e_ident the buffer received from mmap of the file
 * @returns 
 * 		- `ELFCLASSNONE` if the file is not a valid ELF file
 * 
 * 		- `ELFCLASS32` if the file is 32-bit
 * 
 * 		- `ELFCLASS64` if the file is 64-bit
 */
int	elf_get_format(const char *file_path, unsigned char *e_ident)
{
	int	class;

	if (!e_ident)
		return (ELFCLASSNONE);
	if (e_ident[EI_MAG0] != ELFMAG0
		|| e_ident[EI_MAG1] != ELFMAG1
		|| e_ident[EI_MAG2] != ELFMAG2
		|| e_ident[EI_MAG3] != ELFMAG3)
	{
		write(STDERR_FILENO, "Error: ", 7);
		write(STDERR_FILENO, file_path, ft_strlen(file_path));
		write(STDERR_FILENO, " is not a valid ELF file\n", 25);
		return (ELFCLASSNONE);
	}
	class = e_ident[EI_CLASS];
	if (class != ELFCLASS32 && class != ELFCLASS64)
		return (ELFCLASSNONE);
	return (class);
}
