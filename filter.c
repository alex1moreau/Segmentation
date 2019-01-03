# include <stdio.h>
# include <math.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "op.h"

void deterCoef(int mask[3][3], int *coef, int *decal) {
    int sommeP = 0, sommeN = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (mask[i][j] > 0)
                sommeP += mask[i][j];
            else
                sommeN += mask[i][j];
        }
    *decal = sommeN * 255;
    *coef = sommeN + sommeP;
}

int convolution(SDL_Surface *image, int x, int y, int mask[3][3]) {
    int somme = 0, centre = 4;
    Uint8 r, g, b, a;
    for (int i = -centre; i <= centre; i++)
        for (int j = -centre; j <= centre; j++) {
            if (mask[i+centre][j+centre] != 0) {
                int xl, yl;
                if (0 <= x+i && x+i < image->w && 0 <= y+j && y+j < image->h) {
                    xl = x + i;
                    yl = y + j;
                }
                else {
                    xl = x - i;
                    xl = y - j;
                }
                if ((!(0 <= xl) && !(xl < image->w)) ||
                    (!(0 <= yl) && !(yl < image->h))) {
                    xl = x;
                    yl = y;
                }
                Uint32 pixel = GetPixel(image, x, y);
                SDL_GetRGBA(pixel, image->format, &r, &g, &b, &a);
                somme += r * mask[i+centre][j+centre];
            }
        }
    return somme;
}

SDL_Surface* copy_image(SDL_Surface *src) {
    SDL_Surface* res = SDL_CreateRGBSurface(0, src->w, src->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(src, NULL, res, NULL); //copy everything into res
    return res;
}

SDL_Surface* apply_filter(SDL_Surface *image, int mask[3][3]) {
    SDL_Surface* res = copy_image(image);
    int coef = 0, decal = 0;
    deterCoef(mask, &coef, &decal);
    for (int x = 0; x < image->w; x++) {
        for (int y = 0; y < image->h; y++) {
            int sum = convolution(image, x, y, mask);
            int val = round((sum + decal) / coef);
            SetPixel(res, x, y, val);
        }
    }
    return res;
}

SDL_Surface* filter(SDL_Surface* image, int mask[3][3], char name[], int save) {
    SDL_Surface* res = apply_filter(image, mask);
    if (save)
        SDL_SaveBMP(res, name);
    return res;
}

SDL_Surface* Sobel_filter(char path[]) {
    SDL_Surface *image = load_image(path);
    SDL_Surface *res = copy_image(image);

    int maskx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int masky[3][3] = {{-1, 2, 1}, {0, 0, 0}, {1, 2, 1}};

    for (int x = 0; x < image->w; x++) {
        for (int y = 0; y < image->h; y++) {
            int dx = convolution(image, x, y, maskx);
            int dy = convolution(image, x, y, masky);

            int val = round(sqrt(pow(dx, 2) + pow(dy, 2)*255/sqrt(2)*1020));
            SetPixel(res, x, y, val);
        }
    }
    return res;
}

//==============================================================================
