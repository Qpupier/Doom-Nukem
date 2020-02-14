/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   delimiter_clamp.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/29 11:10:16 by slopez       #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 18:17:30 by slopez      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h"

static void		reduce_x_max_array(t_polygon *w, t_2d_line line, int width)
{
	unsigned int	i;
	unsigned int	prev_count;
	t_real			next;
	t_real			res;
	t_real			tmp[w->proj.nb_tmp];

	treal_arraycpy(w->proj.pt_tmp, tmp, w->proj.nb_tmp);
	prev_count = w->proj.nb_tmp;
	w->proj.nb_tmp = 0;
	i = -1;
	while (++i < prev_count && w->proj.nb_tmp < (w->nb_points * 3) - 1)
	{
		next = (i < prev_count - 1) ? tmp[i + 1] : tmp[0];
		if (tmp[i].x >= width && next.x < width - 1
				&& inter_2d_line_seg(line, 								\
					(t_2d_seg){(tmp[i]), (next)}, &res))
			w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		else if (tmp[i].x < width)
		{
			w->proj.pt_tmp[w->proj.nb_tmp++] = tmp[i];
			if (next.x >= width && inter_2d_line_seg(line, 				\
					(t_2d_seg){(tmp[i]), (next)}, &res))
				w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		}
	}
}

static void		reduce_y_max_array(t_polygon *w, t_2d_line line, int height)
{
	unsigned int	i;
	unsigned int	prev_count;
	t_real			next;
	t_real			res;
	t_real			tmp[w->proj.nb_tmp];

	treal_arraycpy(w->proj.pt_tmp, tmp, w->proj.nb_tmp);
	prev_count = w->proj.nb_tmp;
	w->proj.nb_tmp = 0;
	i = -1;
	while (++i < prev_count)
	{
		next = (i < prev_count - 1) ? tmp[i + 1] : tmp[0];
		if (tmp[i].y >= height && next.y < height - 1 && inter_2d_line_seg(line,
			(t_2d_seg){(tmp[i]), (next)}, &res))
			w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		else if (tmp[i].y < height)
		{
			w->proj.pt_tmp[w->proj.nb_tmp++] = tmp[i];
			if (next.y >= height
				&& inter_2d_line_seg(line, 	\
					(t_2d_seg){(tmp[i]), (next)}, &res))
				w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		}
	}
}

static void		reduce_y_min_array(t_polygon *w, t_2d_line line)
{
	unsigned int	i;
	unsigned int	prev_count;
	t_real			next;
	t_real			res;
	t_real			tmp[w->proj.nb_tmp];

	treal_arraycpy(w->proj.pt_tmp, tmp, w->proj.nb_tmp);
	prev_count = w->proj.nb_tmp;
	w->proj.nb_tmp = 0;
	i = -1;
	while (++i < prev_count && w->proj.nb_tmp < (w->nb_points * 3) - 1)
	{
		next = (i < prev_count - 1) ? tmp[i + 1] : tmp[0];
		if (tmp[i].y < 0 && next.y > 0 && inter_2d_line_seg(line
						, (t_2d_seg){(tmp[i]), (next)}, &res))
			w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		else if (tmp[i].y >= 0)
		{
			w->proj.pt_tmp[w->proj.nb_tmp++] = tmp[i];
			if (next.y < 0 && inter_2d_line_seg(line, 		\
							(t_2d_seg){(tmp[i]), (next)}, &res))
				w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		}
	}
}

static void		reduce_x_min_array(t_polygon *w, t_2d_line line)
{
	unsigned int	i;
	t_real			next;
	t_real			curr;
	t_real			res;

	i = -1;
	w->proj.nb_tmp = 0;
	while (++i < w->proj.nb)
	{
		if (w->proj.nb_tmp >= (w->nb_points * 3) - 1)
			break ;
		next = i + 1 == w->proj.nb ? 	\
								w->proj.pt_delim[0] : w->proj.pt_delim[i + 1];
		curr = w->proj.pt_delim[i];
		if (curr.x < 0 && next.x > 0 && inter_2d_line_seg(line,\
							(t_2d_seg){(curr), (next)}, &res))
			w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		else if (curr.x >= 0)
		{
			w->proj.pt_tmp[w->proj.nb_tmp++] = curr;
			if (next.x < 0 && inter_2d_line_seg(line, 		\
							(t_2d_seg){(curr), (next)}, &res))
				w->proj.pt_tmp[w->proj.nb_tmp++] = (t_real){res.x, res.y};
		}
	}
}

void			clamp_to_window(t_engine_settings *settings, t_polygon *p)
{
	reduce_x_min_array(p, (t_2d_line){1, 0, 0});
	reduce_x_max_array(p, (t_2d_line){1, 0, 1 - settings->width},
		settings->width);
	reduce_y_min_array(p, (t_2d_line){0, 1, 0});
	reduce_y_max_array(p, (t_2d_line){0, 1, 1 - settings->height},
		settings->height);
}
