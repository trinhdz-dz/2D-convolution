#ifndef CONV2D_H
#define CONV2D_H

#define IMG_HEIGHT 256
#define IMG_WIDTH  256
#define KERNEL_HEIGHT 3
#define KERNEL_WIDTH 3

void conv2D(
    int input[IMG_HEIGHT][IMG_WIDTH],
    int kernel[KERNEL_HEIGHT][KERNEL_WIDTH],
    int output[IMG_HEIGHT][IMG_WIDTH]
);

#endif
