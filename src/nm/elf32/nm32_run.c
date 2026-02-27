/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm32_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:58:07 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/27 09:40:49 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	nm32_sort_symbols(t_nm32_meta *meta, bool reverse)
{
	t_nm_symbol		tmp;
	size_t			i;
	size_t			j;
	int				cmp;

	i = 0;
	while (i < meta->sym_count)
	{
		j = i + 1;
		while (j < meta->sym_count)
		{
			cmp = ft_strcoll(meta->symbols[i].name, meta->symbols[j].name);
			if (cmp == 0)
				cmp = (meta->symbols[i].offset > meta->symbols[j].offset)
					- (meta->symbols[i].offset < meta->symbols[j].offset);
			if ((!reverse && cmp > 0) || (reverse && cmp < 0))
			{
				tmp = meta->symbols[i];
				meta->symbols[i] = meta->symbols[j];
				meta->symbols[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

bool	nm32_retrieve_symbols(t_nm_target *t, t_nm32_meta *meta)
{
	size_t		i;

	i = 0;
	while (i < meta->ehdr->e_shnum)
	{
		if (meta->shdr[i].sh_type == SHT_SYMTAB)
		{
			return (nm32_get_symbols(meta, &meta->shdr[i],
					(Elf32_Sym *)(t->mapping + meta->shdr[i].sh_offset)));
		}
		i++;
	}
	return (false);
}

/**
 * Run the 32-bit ELF parser.
 * @param nm Pointer to the main structure
 * @param t Pointer to the target structure
 * @param ehdr Pointer to the ELF header
 * @return true if the file was parsed successfully and symbols were added
 * @return false otherwise
 */
bool	nm32_run(t_nm *nm, t_nm_target *t, Elf32_Ehdr *ehdr)
{
	t_nm32_meta	meta;

	meta = (t_nm32_meta){
		.target = t,
		.ehdr = ehdr,
		.shdr = (Elf32_Shdr *)(t->mapping + ehdr->e_shoff),
		.sym_count = 0, .symbols = NULL, .strtab = NULL, .shstrtab = NULL
	};
	meta.shstrtab = (char *)meta.target->mapping
		+ meta.shdr[meta.ehdr->e_shstrndx].sh_offset;
	if (!nm32_retrieve_symbols(t, &meta))
		return (false);
	if (!(nm->options.value & NMFLAG_NO_SORT))
		nm32_sort_symbols(&meta, nm->options.value & NMFLAG_REVERSE_SORT);
	nm32_hide_symbols(nm->options.value, &meta);
	nm32_print_symbols(&meta);
	free(meta.symbols);
	return (true);
}
