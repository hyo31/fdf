#include "fdf.h"

struct s_line	make_struct(int x, int y, float xend, float yend)
{
	struct s_line	line;

	line.x = x;
	line.y = y;
	line.xstart = x;
	line.ystart = y;
	line.xend = xend;
	line.yend = yend;
	line.diff = (yend - line.ystart) / (xend - line.xstart);
	return (line);
}

void	make_rev_line(struct s_line line, t_vars vars, int colour1)
{
	line.diff = (line.xend - line.xstart) / (line.yend - line.ystart);
	while ((line.y != line.yend))
	{
		mlx_pixel_put(vars.mlx, vars.win, line.x, line.y, colour1);
		if (line.y < line.yend)
			line.y++;
		else if (line.y > line.yend)
			line.y--;
		line.x = line.diff * (line.y - line.ystart) + line.xstart;
		if ((line.xstart > line.xend && line.x < line.xend)
			|| (line.xstart < line.xend && line.x > line.xend))
			line.x = line.xend;
	}
}

void	make_line(struct s_line line, t_vars vars, int colour1)
{
	while ((line.x != line.xend) && (line.diff >= -1 && line.diff <= 1))
	{
		mlx_pixel_put(vars.mlx, vars.win, line.x, line.y, colour1);
		if (line.x < line.xend)
			line.x++;
		else if (line.x > line.xend)
			line.x--;
		line.y = line.diff * (line.x - line.xstart) + line.ystart;
		if ((line.ystart > line.yend && line.y < line.yend)
			|| (line.ystart < line.yend && line.y > line.yend))
			line.y = line.yend;
	}
	if (line.diff < -1 || line.diff > 1)
		make_rev_line(line, vars, colour1);
	mlx_pixel_put(vars.mlx, vars.win, line.x, line.y, colour1);
}

void	make_rectangle(struct s_map	*row, int i, t_vars vars, int len[2])
{
	struct s_line	line;
	int				l;
	int				xstart;
	int				ystart;

	l = 0;
	while (l <= len[1])
	{
		xstart = vars.start[0] + (l * (vars.scale[0])) - (i * (vars.scale[0]));
		ystart = vars.start[1] + (l * (vars.scale[1]))
			+ (i * (vars.scale[1])) + (row[l].val * vars.scale[2]);
		line = make_struct(xstart, ystart, xstart + vars.scale[0],
				ystart + vars.scale[1] + (row[l + 1].val * vars.scale[2])
				- (row[l].val * vars.scale[2]));
		if (l < len[1] && xstart <= 2500 && ystart <= 1250)
			make_line(line, vars, row[l].colour);
		line = make_struct(xstart, ystart, xstart + vars.scale[0],
				ystart - vars.scale[1] + (row[l].old_val * vars.scale[2])
				- (row[l].val * vars.scale[2]));
		if (i > 0)
			make_line(line, vars, row[l].colour);
		l++;
	}
}
