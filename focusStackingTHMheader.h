#ifndef THMfocus
#define THMfocus

#include<iostream>
#include<array>
#include<vector>
#include<filesystem>
#include<opencv2/opencv.hpp>



namespace FSTHM {

	/*

		DAUBECHIS COEFFICIENTS

	*/
	//D4
	extern const std::vector<float> D4_low_pass;
	extern const std::vector<float> D4_high_pass;

	//D6
	extern const std::vector<float> D6_low_pass;
	extern const std::vector<float> D6_high_pass;

	//D8
	extern const std::vector<float> D8_low_pass;
	extern const std::vector<float> D8_high_pass;

	//D10
	extern const std::vector<float> D10_low_pass;
	extern const std::vector<float> D10_high_pass;

	//D12
	extern const std::vector<float> D12_low_pass;
	extern const std::vector<float> D12_high_pass;

	//D14
	extern const std::vector<float> D14_low_pass;
	extern const std::vector<float> D14_high_pass;

	//D16
	extern const std::vector<float> D16_low_pass ;
	extern const std::vector<float> D16_high_pass;



	/*

		SYMLET COEFFICIENTS

	*/
	//S4
	extern const std::vector<float> sym4_low_pass;

	extern const std::vector<float> sym4_high_pass;

	//S6
	extern const std::vector<float> sym6_low_pass;

	extern const std::vector<float> sym6_high_pass;

	//S8
	extern const std::vector<float> sym8_low_pass;

	extern const std::vector<float> sym8_high_pass;



	/*

		COIFLET COEFFICIENT

	*/
	//C4
	extern const std::vector<float> coif4_low_pass;

	extern const std::vector<float> coif4_high_pass;

	//C6
	extern const std::vector<float> coif6_low_pass;

	extern const std::vector<float> coif6_high_pass;

	//C8
	extern const std::vector<float> coif8_low_pass;

	extern const std::vector<float> coif8_high_pass;



	/*

		BIOR COEFFICIENT

	*/
	//BIOR2.2
	extern const std::vector<float> bior2_2_low_decomp;

	extern const std::vector<float> bior2_2_high_decomp;

	extern const std::vector<float> bior2_2_low_recon;

	extern const std::vector<float> bior2_2_high_recon;

	//BIOR3.3
	extern const std::vector<float> bior3_3_low_decomp;

	extern const std::vector<float> bior3_3_high_decomp;

	extern const std::vector<float> bior3_3_low_recon;

	extern const std::vector<float> bior3_3_high_recon;

	//BIOR4.4
	extern const std::vector<float> bior4_4_high_decomp;

	extern const std::vector<float> bior4_4_low_decomp;

	extern const std::vector<float> bior4_4_low_recon;

	extern const std::vector<float> bior4_4_high_recon;



	/*

		CENTER FREQUENCY AND BANDWIDTH

	*/
	extern const float morlet_center_frequency;
	extern const float morlet_sigma;
	extern const float mexican_hat_sigma;



	/*

	DATA RETRIEVING

	*/
	std::vector<cv::Mat> getPhotoFromFileSystem(std::string folder_path);

	/*

		DATA PROCESSING

	*/
	cv::Mat createSinglePixelFocusStackedImage(const std::vector<cv::Mat>& images, std::vector<cv::Mat> focus_maps, bool use_alignment);
	cv::Mat createPatchesFocusStackedImage(const std::vector<cv::Mat>& images, std::vector<cv::Mat> focus_maps, int patch_size, bool use_alignment);
	cv::Mat alignImages(const cv::Mat& image1, const cv::Mat& image2, const std::string& featureType);
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
