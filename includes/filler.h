/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juspende <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 08:23:42 by juspende          #+#    #+#             */
/*   Updated: 2019/05/07 01:16:22 by juspende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdint.h>
# include "../libft/includes/libft.h"
# include "../free_all/include/ft_freeall.h"

struct			s_map {
	int32_t		height;
	int32_t		width;
	char		**data;
	char		*stored;
};

struct			s_move {
	uint32_t	x;
	uint32_t	y;
	uint32_t	score;
};

void			play(struct s_map *map, struct s_map *piece, char player_char);

#endif
