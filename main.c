# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "filter.h"
# include "op.h"

int main(int argc, char const *argv[]) {
    for (int i = 0; i < argc; i++)
        printf("%s   ", argv[i]);
    printf("\n");

    char path[] = "img.jpg";
    SDL_Surface *image = load_image(path);
    char fichierGradient[] = "none";
    int saveGradient = 0, tolerance = 0, flou = 0, tailleMini = 0;

    display_image(image);
    SDL_FreeSurface(image);

    return 0;
}
