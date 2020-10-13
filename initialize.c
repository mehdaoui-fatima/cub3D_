
#include "cub3d.h"


t_cub3d    *initialize(t_cub3d  *cub3d)
{
	cub3d->posx = 22;
	cub3d->posy = 12;
	cub3d->dirx = -1;
	cub3d->diry = 0;
	cub3d->planx = 0;
	cub3d->plany = 0.66;
	cub3d->cx = 0;
	cub3d->x = 0;
	cub3d->hit = 0;
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy= (int)cub3d->posy;
	cub3d->movespeed = 7;
	cub3d->rotspeed = 0.2;
	//double olddirx ;
	//double oldplanx;
	cub3d->change = 0;
	cub3d->plus = 0;
	cub3d->jump = 0;
	cub3d->jumpback = 0;
	return (cub3d);
}

