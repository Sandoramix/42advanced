/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm64_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:58:34 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/20 15:45:05 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"



char	nm64_get_symbol_type(Elf64_Sym *sym, Elf64_Shdr *shdr)
{
	Elf64_Shdr	*section;
	char		type;

	type = 'R';
	if (sym->st_shndx == SHN_UNDEF)
		type = 'U';
	else if (sym->st_shndx == SHN_ABS)
		type = 'A';
	else
	{
		section = &shdr[sym->st_shndx];
		if (section->sh_type == SHT_NOBITS)
			type = 'B';
		if (section->sh_flags & SHF_EXECINSTR)
			type = 'T';
		if (section->sh_flags & SHF_WRITE)
			type = 'D';
	}
	if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		type = ft_tolower(type);
	return (type);
}

bool	nm64_get_symbols(t_nm64_meta *meta, Elf64_Shdr *sym_hdr, Elf64_Sym *sym)
{
	const size_t	sym_len = sym_hdr->sh_size / sym_hdr->sh_entsize;
	size_t			i;
	t_nm_symbol		symbol;
	Elf64_Shdr		*section;

	meta->strtab = (char *)meta->target->mapping
		+ (meta->shdr[sym_hdr->sh_link]).sh_offset;
	i = 0;
	while (++i < sym_len)
	{
		symbol = (t_nm_symbol){
			.name = (char *)meta->strtab + sym[i].st_name,
			.type = nm64_get_symbol_type(&sym[i], meta->shdr),
			.offset = sym[i].st_value,
		};
		if (sym[i].st_info == STT_SECTION)
		{
			section = &meta->shdr[sym[i].st_shndx];
			symbol.name = meta->strtab + section->sh_name;
		}
		if (!elf_add_symbol(&meta->symbols, &meta->sym_count, symbol))
			return (false);
	}
	return (true);
}

bool	nm64_retrieve_symbols(t_nm_target *t, t_nm64_meta *meta)
{
	size_t		i;

	i = 0;
	while (i < meta->ehdr->e_shnum)
	{
		if (meta->shdr[i].sh_type == SHT_SYMTAB)
		{
			return (nm64_get_symbols(meta, &meta->shdr[i],
					(Elf64_Sym *)(t->mapping + meta->shdr[i].sh_offset)));
		}
		i++;
	}
	return (false);
}

void	print_symbols(t_nm64_meta *meta)
{
	size_t		i;
	t_nm_symbol	*symbol;

	i = 0;
	while (i < meta->sym_count)
	{
		symbol = &meta->symbols[i];
		if (symbol->type == 'U')
			fprintf(stderr, "%16c: U %s\n", ' ', symbol->name);
		else
			fprintf(stderr, "%016lx: %c %s\n", symbol->offset, symbol->type,
				symbol->name);
		i++;
	}
}

void	nm64_sort_symbols(t_nm64_meta *meta)
{
	t_nm_symbol		tmp;
	size_t			i;
	size_t			j;

	i = 0;
	while (i < meta->sym_count)
	{
		j = i + 1;
		while (j < meta->sym_count)
		{
			if (ft_strcmp(meta->symbols[i].name, meta->symbols[j].name) > 0)
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

/**
 * Run the 64-bit ELF parser.
 * @param nm Pointer to the main structure
 * @param t Pointer to the target structure
 * @param ehdr Pointer to the ELF header
 * @return true if the file was parsed successfully and symbols were added
 * @return false otherwise
 */
bool	nm_run_64(t_nm *nm, t_nm_target *t, Elf64_Ehdr *ehdr)
{
	t_nm64_meta	meta;

	(void)nm;
	fprintf(stderr, "ELF64 FORMAT\n");
	meta = (t_nm64_meta){
		.target = t,
		.ehdr = ehdr,
		.shdr = (Elf64_Shdr *)(t->mapping + ehdr->e_shoff),
		.sym_count = 0, .symbols = NULL, .strtab = NULL
	};
	if (!nm64_retrieve_symbols(t, &meta))
		return (false);
	nm64_sort_symbols(&meta);
	print_symbols(&meta);
	free(meta.symbols);
	return (true);
}
