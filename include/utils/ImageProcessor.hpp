#ifndef IMAGEPROCESSOR_HPP
#define IMAGEPROCESSOR_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <filesystem>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace fs = std::filesystem;

class ImageProcessor {
public:
    /**
     * @brief Processes an image file into a vector of normalized pixel values.
     * 
     * @param imagePath Path to the image file.
     * @return std::vector<double> A vector of normalized pixel values (0.0 to 1.0).
     * @throws std::runtime_error If the image cannot be loaded or processed.
     */
    static std::vector<double> process(const std::string& imagePath);

    /**
     * @brief Resizes and normalizes an image to 28x28 grayscale.
     * 
     * @param imagePath Path to the image file.
     * @return std::vector<double> A flattened vector of 784 normalized pixel values.
     * @throws std::runtime_error If the image cannot be loaded or processed.
     */
    static std::vector<double> processFashionMNIST(const std::string& imagePath);

private:
    /**
     * @brief Converts an image to grayscale and normalizes pixel values.
     * 
     * @param data Pointer to the image data.
     * @param width Width of the image.
     * @param height Height of the image.
     * @param channels Number of channels in the image.
     * @return std::vector<double> A vector of normalized grayscale pixel values.
     */
    static std::vector<double> normalizeImage(unsigned char* data, int width, int height, int channels);

    /**
     * @brief Resizes an image to the specified dimensions.
     * 
     * @param data Pointer to the image data.
     * @param srcWidth Width of the source image.
     * @param srcHeight Height of the source image.
     * @param dstWidth Width of the destination image.
     * @param dstHeight Height of the destination image.
     * @return std::vector<double> A vector of resized pixel values.
     */
    static std::vector<double> resizeImage(const std::vector<double>& data, int srcWidth, int srcHeight, int dstWidth, int dstHeight);
};

#endif // IMAGEPROCESSOR_HPP