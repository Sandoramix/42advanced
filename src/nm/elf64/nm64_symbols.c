/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm64_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:33:51 by odudniak          #+#    #+#             */
/*   Updated: 2026/03/25 09:18:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	nm64_is_readonly(Elf64_Word sh_flags, Elf64_Word sh_type)
{
	return ((sh_flags & SHF_ALLOC)
		&& !(sh_flags & SHF_WRITE)
		&& !(sh_flags & SHF_EXECINSTR)
		&& (sh_type == SHT_PROGBITS || sh_type == SHT_RELA
			|| sh_type == SHT_REL || sh_type == SHT_HASH
			|| sh_type == SHT_GNU_versym || sh_type == SHT_GNU_verdef
			|| sh_type == SHT_STRTAB || sh_type == SHT_DYNSYM
			|| sh_type == SHT_NOTE || sh_type == SHT_GNU_HASH
			|| sh_type == SHT_GNU_verneed));
}

static void	nm64_check_section(t_nm_symbol *symbol,
	Elf64_Shdr *s)
{
	const Elf64_Word	sh_type = s->sh_type;
	const Elf64_Word	sh_flags = s->sh_flags;

	if (!(sh_flags & SHF_ALLOC))
	{
		symbol->type = SYMBOL_TYPE_DEBUG;
		symbol->is_dwarf_debug = !ft_strncmp(symbol->name, ".debug", 6);
	}
	else if (sh_type == SHT_NOBITS
		&& (sh_flags & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE))
		symbol->type = SYMBOL_TYPE_BSS;
	else if (nm64_is_readonly(sh_flags, sh_type))
		symbol->type = SYMBOL_TYPE_READONLY;
	else if (sh_type == SHT_PROGBITS
		&& (sh_flags & (SHF_ALLOC | SHF_WRITE)) == (SHF_ALLOC | SHF_WRITE)
		&& !(sh_flags & SHF_EXECINSTR))
		symbol->type = SYMBOL_TYPE_DATA;
	else if (sh_type == SHT_INIT_ARRAY || sh_type == SHT_FINI_ARRAY
		|| sh_type == SHT_PREINIT_ARRAY)
		symbol->type = SYMBOL_TYPE_DATA;
	else if (sh_type == SHT_DYNAMIC)
		symbol->type = SYMBOL_TYPE_DATA;
	else
		symbol->type = SYMBOL_TYPE_TEXT;
}

static void	nm64_identify_symbol(Elf64_Sym *sym, Elf64_Shdr *shdr,
	t_nm_symbol *symbol)
{
	symbol->st_type = ELF64_ST_TYPE(sym->st_info);
	if (ELF64_ST_TYPE(sym->st_info) == STT_FILE
		|| ELF64_ST_TYPE(sym->st_info) == STT_SECTION)
		symbol->is_debug = true;
	if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
		symbol->is_local = true;
	else if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
		symbol->is_weak = true;
	else if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
		symbol->is_unique = true;
	symbol->type = SYMBOL_TYPE_READONLY;
	if (sym->st_shndx == SHN_UNDEF)
		symbol->type = SYMBOL_TYPE_UNDEFINED;
	else if (sym->st_shndx == SHN_COMMON)
		symbol->type = SYMBOL_TYPE_COMMON;
	else if (sym->st_shndx == SHN_ABS)
		symbol->type = SYMBOL_TYPE_ABSOLUTE;
	else
		nm64_check_section(symbol, &shdr[sym->st_shndx]);
}

bool	nm64_get_symbols(t_nm64_meta *meta, Elf64_Shdr *sym_hdr, Elf64_Sym *sym)
{
	size_t			i;
	t_nm_symbol		symbol;
	Elf64_Shdr		*section;

	meta->strtab = (char *)meta->target->mapping
		+ (meta->shdr[sym_hdr->sh_link]).sh_offset;
	i = 0;
	while (++i < sym_hdr->sh_size / sym_hdr->sh_entsize)
	{
		symbol = (t_nm_symbol){0};
		symbol.name = (char *)meta->strtab + sym[i].st_name;
		symbol.offset = sym[i].st_value;
		if (ELF64_ST_TYPE(sym[i].st_info) == STT_SECTION)
		{
			section = &meta->shdr[sym[i].st_shndx];
			symbol.name = meta->shstrtab + section->sh_name;
		}
		nm64_identify_symbol(&sym[i], meta->shdr, &symbol);
		if (!elf_add_symbol(&meta->symbols, &meta->sym_count, symbol))
			return (false);
	}
	return (true);
}
