#include "../../include/utils/ImageProcessor.hpp"
#include <iostream>
#include <algorithm>

std::vector<double> ImageProcessor::process(const std::string& imagePath) {
    int width, height, channels;
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load image: " + imagePath);
    }

    auto normalized = normalizeImage(data, width, height, channels);
    stbi_image_free(data);
    return normalized;
}

std::vector<double> ImageProcessor::processFashionMNIST(const std::string& imagePath) {
    int width, height, channels;
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load image: " + imagePath);
    }

    auto normalized = normalizeImage(data, width, height, channels);
    stbi_image_free(data);

    // Resize to 28x28 for Fashion MNIST
    return resizeImage(normalized, width, height, 28, 28);
}

std::vector<double> ImageProcessor::normalizeImage(unsigned char* data, int width, int height, int channels) {
    std::vector<double> normalized;
    normalized.reserve(width * height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double pixelValue = 0.0;
            for (int c = 0; c < channels; c++) {
                pixelValue += data[(y * width + x) * channels + c];
            }
            normalized.push_back(pixelValue / (channels * 255.0)); // Normalize to [0.0, 1.0]
        }
    }

    return normalized;
}

std::vector<double> ImageProcessor::resizeImage(const std::vector<double>& data, int srcWidth, int srcHeight, int dstWidth, int dstHeight) {
    std::vector<double> resized(dstWidth * dstHeight, 0.0);

    double xRatio = static_cast<double>(srcWidth) / dstWidth;
    double yRatio = static_cast<double>(srcHeight) / dstHeight;

    for (int y = 0; y < dstHeight; y++) {
        for (int x = 0; x < dstWidth; x++) {
            int srcX = static_cast<int>(x * xRatio);
            int srcY = static_cast<int>(y * yRatio);
            resized[y * dstWidth + x] = data[srcY * srcWidth + srcX];
        }
    }

    return resized;
}