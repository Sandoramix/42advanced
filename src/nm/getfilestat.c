/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getfilestat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 08:11:22 by odudniak          #+#    #+#             */
/*   Updated: 2026/02/12 08:11:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/**
 * Opens the file from the given path and returns the metadata about it.
 * @param filename the path of the file to open
 * @param fd pointer to the file descriptor which will be set to the opened file
 * @returns the metadata about the file
 */
t_stat	nm_getfilestat(const char *filename, int *fd)
{
	int		target_fd;
	t_stat	file_stat;

	file_stat = (t_stat){0};
	target_fd = open(filename, O_RDONLY);
	if (target_fd == -1)
	{
		*fd = -1;
		return (perror("Error opening file"), file_stat);
	}
	if (fstat(target_fd, &file_stat) == -1)
	{
		close(target_fd);
		*fd = -1;
		file_stat = (t_stat){0};
		return (perror("Error getting file metadata"), file_stat);
	}
	*fd = target_fd;
	return (file_stat);
}
