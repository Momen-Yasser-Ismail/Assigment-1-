#pragma once

#include "Image_Class.h"

void grayscale(Image &image);

void black_and_white(Image &img);

void Invert(Image &img);

void frame (Image &image, int type_of_frame, int color_of_the_frame);

void flip(Image &image, bool h);

void rotate(Image &img, int rotation);

void lighten_darken(Image &img, int change, int rate_of_change);

void resize(Image &image, int new_width, int new_height);

void merge(Image &image, Image &image2, bool apply_resize);

void sepia(Image &image);

void Detact_Image_Edges(Image &img);

void crop(Image &img, int x, int y, int width, int height);

void televisions(Image &img);

void blur(Image &image, double percentage);

void purple_effect(Image &img, int power_of_effect);

void infrared(Image &image);

void OilPainting(Image& image, int radius = 2, int numLevels = 20);

void skewImage(Image& image, double degree);

void contrast(Image &image, double factor);

void saturation(Image &image, double factor);

void wave(Image &image);

void pixelated(Image &img, int power_of_pixelated);

void vignette(Image &img , double power);
