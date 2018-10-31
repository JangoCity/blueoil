/* Copyright 2018 Leapmind Inc. */

#include "blueoil.hpp"
#include "blueoil_image.hpp"
#include "blueoil_opencv.hpp"

namespace blueoil {
namespace opencv {

/*
 * accept BGR OpenCV Mat images (not RGB)
 */
Tensor Tensor_fromCVMat(cv::Mat img) {
    int width = img.cols;
    int height = img.rows;
    int channels = img.elemSize();
    if ((channels != 1) && (channels != 3)) {
	throw std::invalid_argument("wrong channles != 1,3");
    }
    blueoil::Tensor tensor = blueoil::Tensor::zeros({height, width, channels});
    for (int y = 0 ; y < height ; y++) {
	for (int x = 0 ; x < width ; x++) {
	    float *tensorPixel = blueoil::image::Tensor_at(tensor, x, y);
	    uchar *imgPixel = &(img.data[ y * img.step + x * img.elemSize()]);
	    if (channels == 1) {
		tensorPixel[0] = imgPixel[0]; // I (grayscale)
	    } else {  // (channels == 3)
		tensorPixel[0] = imgPixel[2]; // R
		tensorPixel[1] = imgPixel[1]; // G
		tensorPixel[2] = imgPixel[0]; // B
	    }
	}
    }
    //
    return tensor;
}

/*
 * generate BGR OpenCV Mat images (not RGB)
 */
cv::Mat Tensor_toCVMat(Tensor &tensor) {
    int height = tensor.shape[0];
    int width  = tensor.shape[1];
    int channels = tensor.shape[2];
    cv::Mat img;
    if (channels == 1) {
	img = cv::Mat::zeros(height, width, CV_8U);   // uchar[1] grayscale
    } else if (channels == 3) {
	img = cv::Mat::zeros(height, width, CV_8UC3); // uchar[3] rgb color
    } else {
	throw std::invalid_argument("wrong channles != 1,3");
    }
    for (int y = 0 ; y < height ; y++) {
	for (int x = 0 ; x < width ; x++) {
	    float *tensorPixel = blueoil::image::Tensor_at(tensor, x, y);
	    uchar *imgPixel = &(img.data[ y * img.step + x * img.elemSize()]);
	    if (channels == 1) {
		imgPixel[0] = tensorPixel[0]; // I (grayscale)
	    } else {  // (channels == 3)
		imgPixel[2] = tensorPixel[0]; // R
		imgPixel[1] = tensorPixel[1]; // G
		imgPixel[0] = tensorPixel[2]; // B
	    }
	}
    }
    return img;
}

}  // namespace opencv
}  // namespace blueoil


