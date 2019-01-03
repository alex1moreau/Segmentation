# ifndef OP_H
# define OP_H

SDL_Surface* load_image(char path[]);
void display_image(SDL_Surface *image);
Uint32 GetPixel(SDL_Surface *surface, int x, int y);
void SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

# endif
