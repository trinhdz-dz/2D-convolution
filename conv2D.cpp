#include "conv2D.h"

void conv2D(
    int input[IMG_HEIGHT][IMG_WIDTH],
    int kernel[KERNEL_HEIGHT][KERNEL_WIDTH],
    int output[IMG_HEIGHT][IMG_WIDTH]
) {
    int line_buffer[KERNEL_HEIGHT - 1][IMG_WIDTH];
    int window[KERNEL_HEIGHT][KERNEL_WIDTH];
    int right[KERNEL_HEIGHT];

    // #pragma HLS ARRAY_PARTITION variable=line_buffer complete dim=1
    // #pragma HLS ARRAY_PARTITION variable=window complete dim=0
    // #pragma HLS ARRAY_PARTITION variable=right complete

    for (int x = 0; x < IMG_WIDTH; x++) {
        // #pragma HLS PIPELINE
        line_buffer[KERNEL_HEIGHT - 2][x] = input[0][x];
    }

    for (int y = 0; y < KERNEL_HEIGHT; y++) {
        for (int x = 0; x < KERNEL_WIDTH; x++) {
            // #pragma HLS PIPELINE
            window[y][x] = 0;
        }
    }

    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            // #pragma HLS PIPELINE

            if (i > 0) {
                right[0] = line_buffer[0][j];
                for (int y = 1; y < KERNEL_HEIGHT - 1; y++) {
                    right[y] = line_buffer[y][j];
                    line_buffer[y - 1][j] = line_buffer[y][j];
                }
            }
            if (i < IMG_HEIGHT - 1) {
                line_buffer[KERNEL_HEIGHT - 2][j] = input[i][j];
            }
            for (int y = 0; y < KERNEL_HEIGHT; y++) {
            	for (int x = 0; x < KERNEL_WIDTH - 1; x++) {
                    window[y][x] = window[y][x + 1];
                }
            }

            for (int y = 0; y < KERNEL_HEIGHT; y++) {
                window[y][KERNEL_WIDTH - 1] = right[y];
            }
            if (i >= KERNEL_HEIGHT - 1 && j >= KERNEL_WIDTH - 1) {
                output[i - KERNEL_HEIGHT + 1][j - KERNEL_WIDTH + 1] = 0;
                for (int ki = 0; ki < KERNEL_HEIGHT; ki++) {
                    for (int kj = 0; kj < KERNEL_WIDTH; kj++) {
                        if ((i - ki) >= 0 && (j - kj) >= 0) {
                            output[i - KERNEL_HEIGHT + 1][j - KERNEL_WIDTH + 1] +=
                                window[ki][kj] * kernel[ki][kj];
                        }
                    }
                }
            }
        }
    }
}
