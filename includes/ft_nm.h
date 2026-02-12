/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:31:32 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/12 08:53:06 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <elf.h>

# define NM_HELP_MESSAGE "Usage: nm <filename>\n"

typedef struct stat	t_stat;

void	ft_nm(int argc, char **argv);

t_stat	nm_getfilestat(const char *filename, int *fd);
void	nm_help_message(void);
int		nm_identify_elf_format(unsigned char *e_indent);

#endif