# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "op.h"

SDL_Surface* load_image(char path[]) {
    SDL_Surface* image = IMG_Load(path);

	if(!image)
	{
		printf("Cannot load the image : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

    return image;
}

void wait_for_keypressed(void) {
	SDL_Event event;
	for (;;) {
		SDL_PollEvent( &event );
		switch (event.type) {
			case SDL_KEYDOWN: return;
			default: break;
		}
	}
}

void display_image(SDL_Surface* image) {
    SDL_Surface *screen;
	screen = SDL_SetVideoMode(image->w, image->h, 0, SDL_SWSURFACE|
		SDL_ANYFORMAT);
	if (!screen)
	{
        // error management
		printf("Couldn't set %dx%d video mode: %s\n",
			image->w, image->h, SDL_GetError());
	}
	if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
		printf("BlitSurface error: %s\n", SDL_GetError());

	SDL_UpdateRect(screen, 0, 0, image->w, image->h);

	wait_for_keypressed();

	SDL_FreeSurface(screen);
}

Uint32 GetPixel(SDL_Surface *surface, int x, int y) {
	int nbOctets = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctets;

    // different cases according to nb bytes per pixel
	switch(nbOctets)
	{
		case 1:
		return *p;

		case 2:
		return *(Uint16 *)p;

		case 3:
            //x32 or x64
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
		return *(Uint32 *)p;

        //never called
		default:
		return 0;
	}
}

void SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	int nbOctets = surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctets;

	// different cases according to nb bytes per pixel
	switch(nbOctets)
	{
		case 1:
		*p = pixel;
		break;

		case 2:
		*(Uint16 *)p = pixel;
		break;

		case 3:
		//x32 or x64
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

		case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}
