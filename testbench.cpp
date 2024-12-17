#include <iostream>
#include <opencv2/opencv.hpp>
#include "conv2D.h"
#include "hls_stream.h"

using namespace std;
using namespace cv;

void loadImage(const string &image_path, int input[IMG_HEIGHT][IMG_WIDTH]) {
    Mat img = imread(image_path, IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Error loading image!" << endl;
        exit(-1);
    }

    int rows = img.rows;
    int cols = img.cols;

    if (rows > IMG_HEIGHT || cols > IMG_WIDTH) {
        cerr << "Image size exceeds the maximum size!" << endl;
        exit(-1);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            input[i][j] = img.at<uchar>(i, j);
        }
    }
}

void saveConvolutionResult(const string &output_path, int result[IMG_HEIGHT][IMG_WIDTH]) {
    Mat conv_img(IMG_HEIGHT, IMG_WIDTH, CV_8UC1);
    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            conv_img.at<uchar>(i, j) = static_cast<uchar>(result[i][j]);
        }
    }
    imwrite(output_path, conv_img);
}

int main() {
    string image_path = "C:\\FinalPj\\daulau.jpg";
    int input[IMG_HEIGHT][IMG_WIDTH];

    loadImage(image_path, input);

    int kernel[KERNEL_HEIGHT][KERNEL_WIDTH] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };

    int hw_result[IMG_HEIGHT][IMG_WIDTH] = {0};
    int sw_result[IMG_HEIGHT][IMG_WIDTH] = {0};

    cout << "Processing..." << endl;

    for (int i = 0; i < IMG_HEIGHT - KERNEL_HEIGHT + 1; i++) {
        for (int j = 0; j < IMG_WIDTH - KERNEL_WIDTH + 1; j++) {
            sw_result[i][j] = 0;
            for (int ki = 0; ki < KERNEL_HEIGHT; ki++) {
                for (int kj = 0; kj < KERNEL_WIDTH; kj++) {
                    sw_result[i][j] += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
        }
    }

#ifdef HW_COSIM
    hls::stream<int> in_stream;
    hls::stream<int> out_stream;

    for (int i = 0; i < IMG_HEIGHT; i++) {
        for (int j = 0; j < IMG_WIDTH; j++) {
            in_stream.write(input[i][j]);
        }
    }

    conv2D(input, kernel, hw_result);

    int k = 0;
    for (int i = 0; i < IMG_HEIGHT - KERNEL_HEIGHT + 1; i++) {
        for (int j = 0; j < IMG_WIDTH - KERNEL_WIDTH + 1; j++) {
            hw_result[i][j] = out_stream.read();
            k++;
        }
    }
#endif

    int err_cnt = 0;

#ifdef HW_COSIM
    for (int i = 0; i < IMG_HEIGHT - KERNEL_HEIGHT + 1; i++) {
        for (int j = 0; j < IMG_WIDTH - KERNEL_WIDTH + 1; j++) {
            if (hw_result[i][j] != sw_result[i][j]) {
                err_cnt++;
            }
        }
    }
#endif

    if (err_cnt == 0) {
        cout << "Test passed." << endl;
    } else {
        cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
    }

    cout << "Image saving..." << endl;
    saveConvolutionResult("C:\\FinalPj\\convolution_result.jpg", sw_result);
    cout << "Image saved" << endl;

    return err_cnt;
}
