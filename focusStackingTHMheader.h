#ifndef THMfocus
#define THMfocus

#include<iostream>
#include<array>
#include<vector>
#include<filesystem>
#include<opencv2/opencv.hpp>



namespace FSTHM {
	/*

	DATA RETRIEVING

	*/
	std::vector<cv::Mat> getPhotoFromFileSystem(std::string folder_path);

	/*

		DATA PROCESSING

	*/
	cv::Mat createFocusStackedImage(const std::vector<cv::Mat>& images, std::vector<cv::Mat> focus_maps);
	std::vector<cv::Mat> convertFocusMapsTo32F(const std::vector<cv::Mat>& focus_maps);
	void saveResult(const cv::Mat& image, const std::string& filename, const std::string& output_path);


	/*

		DEBUG

	*/
	void showImage(cv::Mat image);
	void showFocusMaps(const std::vector<cv::Mat>& images, const std::vector<cv::Mat>& focus_maps);
	void visualizeWaveletFocus(const std::vector<cv::Mat>& focus_maps, const std::string& window_name);
	void visualizeFFTFocus(const std::vector<cv::Mat>& images, const std::string& window_name);



	/*

		UTILITY

	*/
	std::vector<cv::Mat> convertToGrayscale(const std::vector<cv::Mat>& images);
	cv::Mat calculateGaussianOfLaplacian(const cv::Mat& grayscale_image, const double sigma);
	std::vector<cv::Mat> computeWaveletsFocusMap(const std::vector<cv::Mat>& wavelets);
	cv::Mat paddedImageConstructor(const cv::Mat& grayscale_image, int& rows, int& cols);
	void dftShift(const cv::Mat& input, cv::Mat& output);
	cv::Mat createMorletKernel(int rows, int cols, float center_frequency, float sigma);
	cv::Mat generateMexicanHatKernel(int kernel_size, float sigma);
	cv::Mat generateMeyerFilter(cv::Size size);
	cv::Mat generateShannonFilter(cv::Size size);
	void applyFrequencyFilter(const cv::Mat& complex_image, const cv::Mat& filter, cv::Mat& filtered_image);



	/*

		FOCUS DETECTION ALGORITHM

	*/
	std::vector<cv::Mat> calculateLaplacianVariance(const std::vector<cv::Mat>& images, const bool blur, const std::array<int, 2>& gaussian_blur_kernel);
	std::vector<cv::Mat> calculateTenengrad(const std::vector<cv::Mat>& images, const int kernel_size);
	std::vector<cv::Mat> calculateFFTBasedFrequency(const std::vector<cv::Mat>& images, const double cutoff_percentage);
	std::vector<cv::Mat> calculateSML(const std::vector<cv::Mat>& images, const bool blur, const std::array<int, 2>& gaussian_blur_kernel);
	std::vector<cv::Mat> calculateGaussianDifference(const std::vector<cv::Mat>& images, const double sigma1, const double sigma2);
	std::vector<cv::Mat> calculateGHPF(const std::vector<cv::Mat>& images, const double sigma);
	std::vector<cv::Mat> calculateMSG(const std::vector<cv::Mat>& images, const std::vector<int>& scales, const std::vector<double>& sigmas);
	std::vector<cv::Mat> calculateHaarWaveletsFocus(const std::vector<cv::Mat>& images);
	std::vector<cv::Mat> calculateDaubechisWavelets(const std::vector<cv::Mat>& images, const std::vector<float> low_pass, const std::vector<float> high_pass);
	std::vector<cv::Mat> calculateSymletWavelets(const std::vector<cv::Mat>& images, const std::vector<float> sym_low_pass, const std::vector<float> sym_high_pass);
	std::vector<cv::Mat> calculateCoifletWavelets(const std::vector<cv::Mat>& images, const std::vector<float> coif_low_pass, const std::vector<float> coif_high_pass);
	std::vector<cv::Mat> calculateBiorthogonalWavelets(const std::vector<cv::Mat>& images, const std::vector<float>& low_decomp, const std::vector<float>& high_decomp);
	std::vector<cv::Mat> calculateMorletWavelets(const std::vector<cv::Mat>& images, float center_frequency, float sigma);
	std::vector<cv::Mat> calculateMexicanHatWavelets(const std::vector<cv::Mat>& images, float sigma);
	std::vector<cv::Mat> calculateMeyerWavelets(const std::vector<cv::Mat>& images);
	std::vector<cv::Mat> calculateShannonWavelets(const std::vector<cv::Mat>& images);



}


#endif 
