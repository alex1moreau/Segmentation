# ifndef FILTER_H
# define FILTER_H

SDL_Surface* filter(SDL_Surface* image, int mask[3][3], char name[], int save);
SDL_Surface* Sobel_filter(char path[]);

# endif
