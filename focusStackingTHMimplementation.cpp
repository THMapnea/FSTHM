#include<iostream>
#include<array>
#include<vector>
#include<filesystem>
#include<opencv2/opencv.hpp>
#include "focusStackingTHMheader.h"



/*

	DAUBECHIS COEFFICIENTS

*/
//D4
const std::vector<float> FSTHM::D4_low_pass = { 0.48296f, 0.83652f, 0.22414f, -0.12941f };
const std::vector<float> FSTHM::D4_high_pass = { -0.12941f, -0.22414f, 0.83652f, -0.48296f };

//D6
const std::vector<float> FSTHM::D6_low_pass = {
	0.33267f, 0.80689f, 0.45988f, -0.13501f, -0.08544f, 0.03522f
};
const std::vector<float> FSTHM::D6_high_pass = {
	0.03522f, 0.08544f, -0.13501f, -0.45988f, 0.80689f, -0.33267f
};

//D8
const std::vector<float> FSTHM::D8_low_pass = {
	0.23038f, 0.71485f, 0.63088f, -0.02798f, -0.18703f, 0.03084f, 0.03288f, -0.01060f
};
const std::vector<float> FSTHM::D8_high_pass = {
	-0.01060f, -0.03288f, 0.03084f, 0.18703f, -0.02798f, -0.63088f, 0.71485f, -0.23038f
};

//D10
const std::vector<float> FSTHM::D10_low_pass = {
	0.16010f, 0.60382f, 0.72431f, 0.13843f, -0.24229f, -0.03224f, 0.07757f, -0.00624f,
	-0.01258f, 0.00333f
};
const std::vector<float> FSTHM::D10_high_pass = {
	0.00333f, 0.01258f, -0.00624f, -0.07757f, -0.03224f, 0.24229f, 0.13843f, -0.72431f,
	0.60382f, -0.16010f
};

//D12
const std::vector<float> FSTHM::D12_low_pass = {
	0.11154f, 0.49462f, 0.75113f, 0.31525f, -0.22626f, -0.12927f, 0.09750f, 0.02752f,
	-0.03158f, 0.00055f, 0.00343f, -0.00067f
};
const std::vector<float> FSTHM::D12_high_pass = {
	-0.00067f, -0.00343f, 0.00055f, 0.03158f, 0.02752f, -0.09750f, -0.12927f, 0.22626f,
	0.31525f, -0.75113f, 0.49462f, -0.11154f
};

//D14
const std::vector<float> FSTHM::D14_low_pass = {
	0.07785f, 0.39617f, 0.72913f, 0.46978f, -0.14329f, -0.22483f, 0.07181f, 0.08056f,
	-0.03887f, -0.01699f, 0.01276f, -0.00043f, -0.00177f, 0.00035f
};
const std::vector<float> FSTHM::D14_high_pass = {
	0.00035f, 0.00177f, -0.00043f, -0.01276f, -0.01699f, 0.03887f, 0.08056f, -0.07181f,
	-0.22483f, 0.14329f, 0.46978f, -0.72913f, 0.39617f, -0.07785f
};

//D16
const std::vector<float> FSTHM::D16_low_pass = {
	0.05441f, 0.31287f, 0.67563f, 0.58536f, -0.01583f, -0.28402f, 0.00047f, 0.12875f,
	-0.01737f, -0.04408f, 0.01398f, 0.00874f, -0.00482f, -0.00024f, 0.00107f, -0.00020f
};
const std::vector<float> FSTHM::D16_high_pass = {
	-0.00020f, -0.00107f, -0.00024f, 0.00482f, 0.00874f, -0.01398f, -0.04408f, 0.01737f,
	0.12875f, -0.00047f, -0.28402f, 0.01583f, 0.58536f, -0.67563f, 0.31287f, -0.05441f
};



/*

	SYMLET COEFFICIENTS

*/
//S4
const std::vector<float> FSTHM::sym4_low_pass = {
	-0.07576571478927333f,
	 0.02963552764599851f,
	 0.49761866763201545f,
	 0.8037387518059161f,
	 0.29785779560527736f,
	-0.09921954357684722f,
	-0.012603967262037833f,
	 0.032223100604078156f
};

const std::vector<float> FSTHM::sym4_high_pass = {
	 0.032223100604078156f,
	 0.012603967262037833f,
	-0.09921954357684722f,
	-0.29785779560527736f,
	 0.8037387518059161f,
	-0.49761866763201545f,
	 0.02963552764599851f,
	 0.07576571478927333f
};

//S6
const std::vector<float> FSTHM::sym6_low_pass = {
	 0.015404109327027373f,
	-0.0034907120842174702f,
	-0.11799011114819057f,
	 0.048311742585632998f,
	 0.49105594192674662f,
	 0.787641141030194f,
	 0.3379294217276218f,
	-0.072637522786462516f,
	-0.021060292512300564f,
	 0.044724901770665779f,
	 0.0017677118642428036f,
	-0.007800708325034148f
};

const std::vector<float> FSTHM::sym6_high_pass = {
	-0.007800708325034148f,
	-0.0017677118642428036f,
	 0.044724901770665779f,
	 0.021060292512300564f,
	-0.072637522786462516f,
	-0.3379294217276218f,
	 0.787641141030194f,
	-0.49105594192674662f,
	 0.048311742585632998f,
	 0.11799011114819057f,
	-0.0034907120842174702f,
	-0.015404109327027373f
};

//S8
const std::vector<float> FSTHM::sym8_low_pass = {
	-0.0033824159510061256f,
	-0.00054213233180001076f,
	 0.031695087811492981f,
	 0.0076074873249176054f,
	-0.14329423835080971f,
	-0.061273359067658524f,
	 0.48135965125920119f,
	 0.77718575170052351f,
	 0.3644418948353314f,
	-0.051945838107709037f,
	-0.027219029916813704f,
	 0.04913717967373029f,
	 0.0038087520138906151f,
	-0.014952258337048231f,
	-0.0003029205147213668f,
	 0.0018899503327594609f
};

const std::vector<float> FSTHM::sym8_high_pass = {
	 0.0018899503327594609f,
	 0.0003029205147213668f,
	-0.014952258337048231f,
	-0.0038087520138906151f,
	 0.04913717967373029f,
	 0.027219029916813704f,
	-0.051945838107709037f,
	-0.3644418948353314f,
	 0.77718575170052351f,
	-0.48135965125920119f,
	-0.061273359067658524f,
	 0.14329423835080971f,
	 0.0076074873249176054f,
	-0.031695087811492981f,
	-0.00054213233180001076f,
	 0.0033824159510061256f
};



/*

	COIFLET COEFFICIENT

*/
//C4
const std::vector<float> FSTHM::coif4_low_pass = {
	-0.01565572813546454f,
	-0.0727326195128539f,
	 0.3848648468642029f,
	 0.8525720202122554f,
	 0.3378976624578092f,
	-0.0727326195128539f,
	-0.01565572813546454f,
	 0.0040137940350814977f,
	-0.01418196459152224f,
	 0.0029931690316299962f,
	 0.00012083269606503066f,
	-0.00042699924234236515f
};

const std::vector<float> FSTHM::coif4_high_pass = {
	0.00042699924234236515f,
	0.00012083269606503066f,
	-0.0029931690316299962f,
	-0.01418196459152224f,
	-0.0040137940350814977f,
	 0.01565572813546454f,
	 0.0727326195128539f,
	 0.3378976624578092f,
	-0.8525720202122554f,
	 0.3848648468642029f,
	 0.0727326195128539f,
	-0.01565572813546454f
};

//C6
const std::vector<float> FSTHM::coif6_low_pass = {
	-0.0007205494453645122f,
	-0.0018232088707029932f,
	 0.005611434819393291f,
	 0.023680171946334084f,
	-0.0594344186464569f,
	-0.0764885990783064f,
	 0.41700518442169254f,
	 0.81272363544554227f,
	 0.38611006682116222f,
	-0.0673725547222829f,
	-0.04146493678175915f,
	 0.0163873364635221f,
	 0.0034907120843301426f,
	-0.001139264476616531f,
	-0.0002467807072627997f,
	 0.00007804255378677326f,
	 0.000013680421484497926f,
	-0.00000393972539849266f
};

const std::vector<float> FSTHM::coif6_high_pass = {
	 0.00000393972539849266f,
	 0.000013680421484497926f,
	-0.00007804255378677326f,
	-0.0002467807072627997f,
	 0.001139264476616531f,
	 0.0034907120843301426f,
	-0.0163873364635221f,
	-0.04146493678175915f,
	 0.0673725547222829f,
	 0.38611006682116222f,
	-0.81272363544554227f,
	 0.41700518442169254f,
	 0.0764885990783064f,
	-0.0594344186464569f,
	-0.023680171946334084f,
	 0.005611434819393291f,
	 0.0018232088707029932f,
	-0.0007205494453645122f
};

//C8
const std::vector<float> FSTHM::coif8_low_pass = {
	-0.00021208083980379827f,
	-0.0005789333798969873f,
	 0.0025879090265397886f,
	 0.00986988334335955f,
	-0.02074968632551592f,
	-0.03254163863693243f,
	 0.1088906719788801f,
	 0.2660425723491694f,
	 0.6029490182363579f,
	 0.6619552637803058f,
	 0.27667196456980826f,
	-0.14046359136067608f,
	-0.03268230375820756f,
	 0.023885656720429735f,
	 0.006761520351296729f,
	-0.004236120144170733f,
	-0.0010009058946436357f,
	 0.0008923136685823141f,
	 0.00016886780760007356f,
	-0.00018331889827622913f,
	-0.000019189505569650145f,
	 0.000019329074517485016f,
	 0.00000011558636332385817f,
	-0.000000051131435272605515f
};

const std::vector<float> FSTHM::coif8_high_pass = {
	 0.000000051131435272605515f,
	 0.00000011558636332385817f,
	-0.000019329074517485016f,
	-0.000019189505569650145f,
	 0.00018331889827622913f,
	 0.00016886780760007356f,
	-0.0008923136685823141f,
	-0.0010009058946436357f,
	 0.004236120144170733f,
	 0.006761520351296729f,
	-0.023885656720429735f,
	-0.03268230375820756f,
	 0.14046359136067608f,
	 0.27667196456980826f,
	-0.6619552637803058f,
	 0.6029490182363579f,
	-0.2660425723491694f,
	 0.1088906719788801f,
	-0.03254163863693243f,
	 0.02074968632551592f,
	-0.00986988334335955f,
	 0.0025879090265397886f,
	-0.0005789333798969873f,
	 0.00021208083980379827f
};



/*

	BIOR COEFFICIENT

*/
//BIOR2.2
const std::vector<float> FSTHM::bior2_2_low_decomp = {
	0.0f,
	0.03782845550726404f,
	-0.02384946501938000f,
	-0.11062440441843718f,
	0.37740285561283066f,
	0.85269867900889385f,
	0.37740285561283066f,
	-0.11062440441843718f,
	-0.02384946501938000f,
	0.03782845550726404f
};

const std::vector<float> FSTHM::bior2_2_high_decomp = {
	0.0f,
	-0.06453888262869706f,
	0.04068941760955844f,
	0.41809227322161724f,
	-0.7884856164055829f,
	0.41809227322161724f,
	0.04068941760955844f,
	-0.06453888262869706f,
	0.0f,
	0.0f
};

const std::vector<float> FSTHM::bior2_2_low_recon = {
	0.0,
	-0.06453888262869706f,
	-0.04068941760955844f,
	0.41809227322161724f,
	0.7884856164055829f,
	0.41809227322161724f,
	-0.04068941760955844f,
	-0.06453888262869706f,
	0.0f,
	0.0f
};

const std::vector<float> FSTHM::bior2_2_high_recon = {
	0.0f,
	0.03782845550726404f,
	0.02384946501938000f,
	-0.11062440441843718f,
	-0.37740285561283066f,
	0.85269867900889385f,
	-0.37740285561283066f,
	-0.11062440441843718f,
	0.02384946501938000f,
	0.03782845550726404f
};

//BIOR3.3
const std::vector<float> FSTHM::bior3_3_low_decomp = {
	-0.035226291882100656f,
	-0.08544127388224149f,
	 0.13501102001039084f,
	 0.4598775021193313f,
	 0.8068915093133388f,
	 0.3326705529509569f,
	 0.0f,
	 0.0f,
	 0.0f,
	 0.0f
};

const std::vector<float> FSTHM::bior3_3_high_decomp = {
	-0.3326705529509569f,
	 0.8068915093133388f,
	-0.4598775021193313f,
	 0.13501102001039084f,
	 0.08544127388224149f,
	-0.035226291882100656f,
	 0.0f,
	 0.0f,
	 0.0f,
	 0.0f
};

const std::vector<float> FSTHM::bior3_3_low_recon = {
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	 0.3326705529509569f,
	 0.8068915093133388f,
	 0.4598775021193313f,
	-0.13501102001039084f,
	-0.08544127388224149f,
	 0.035226291882100656f
};

const std::vector<float> FSTHM::bior3_3_high_recon = {
	0.0f,
	0.0f,
	0.0f,
	0.0f,
	-0.035226291882100656f,
	-0.08544127388224149f,
	 0.13501102001039084f,
	-0.4598775021193313f,
	 0.8068915093133388f,
	-0.3326705529509569f
};

//BIOR4.4
const std::vector<float> FSTHM::bior4_4_high_decomp = {
	 0.0f,
	 0.0f,
	-0.04143203796014927f,
	-0.052480581416189075f,
	-0.26792717880896527f,
	 0.07181553246425972f,
	 0.966747552403483f,
	-0.966747552403483f,
	 0.07181553246425972f,
	 0.26792717880896527f,
	-0.052480581416189075f,
	-0.04143203796014927f,
	 0.013810679320049757f,
	 0.0f
};

const std::vector<float> FSTHM::bior4_4_low_decomp = {
	 0.0f,
	 0.037828455506995005f,
	-0.023849465019556843f,
	-0.11062440441843718f,
	 0.37740285561283066f,
	 0.85269867900889385f,
	 0.37740285561283066f,
	-0.11062440441843718f,
	-0.023849465019556843f,
	 0.037828455506995005f,
	 0.0f
};


const std::vector<float> FSTHM::bior4_4_low_recon = {
	 0.0f,
	-0.06453888262893845f,
	-0.04068941760955844f,
	 0.41809227322161724f,
	 0.7884856164055829f,
	 0.41809227322161724f,
	-0.04068941760955844f,
	-0.06453888262893845f,
	 0.0f
};

const std::vector<float> FSTHM::bior4_4_high_recon = {
	 0.0f,
	 0.037828455506995005f,
	 0.023849465019556843f,
	-0.11062440441843718f,
	-0.37740285561283066f,
	 0.85269867900889385f,
	-0.37740285561283066f,
	-0.11062440441843718f,
	 0.023849465019556843f,
	 0.037828455506995005f,
	 0.0f
};


/*

	CENTER FREQUENCY AND BANDWIDTH

*/
const float FSTHM::morlet_center_frequency = 0.2f;
const float FSTHM::morlet_sigma = 0.8f;
const float FSTHM::mexican_hat_sigma = 0.2f;



/*

	TAKES CARE OF CREATING THE ARRAY OF DATA FOR PROJECT PURPOSE
	later it will be eliminated after implementing image request
	from directory trough gui or flutter

*/
std::vector<cv::Mat> FSTHM::getPhotoFromFileSystem(const std::string folder_path) {

	//vector that will contain the images
	std::vector<cv::Mat> data;

	//we will now iterate all over the folder to get all the images
	for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
		//store the single filepath
		std::string file_path = entry.path().string();

		//check if the extension of the file is valid
		if (file_path.ends_with(".jpg") || file_path.ends_with(".JPG")
			|| file_path.ends_with(".png") || file_path.ends_with(".JPG")
			|| file_path.ends_with("jpeg") || file_path.ends_with("JPEG")) {

			//we can now read the image
			cv::Mat image = cv::imread(file_path);

			//check if the image is empty
			if (!image.empty()) {

				//save the image in the data vector
				data.push_back(image);

			}

		}

	}


	//return the images
	return data;
}



/*

	TAKES CARE OF SHOWING THE IMAGES FOR DEBUG PURPOSES

*/
void FSTHM::showImage(cv::Mat image) {

	cv::namedWindow("image", cv::WINDOW_NORMAL);
	cv::imshow("image", image);
	cv::waitKey();
}

/*

	FUNCTION THAT SHOWS THE RESULT OF THE FOCUS MAP

*/
void FSTHM::showFocusMaps(const std::vector<cv::Mat>& images, const std::vector<cv::Mat>& focus_maps) {
	if (images.size() != focus_maps.size()) {
		std::cerr << "Error: The number of images and focus maps must be the same." << std::endl;
		return;
	}

	size_t num_images = images.size();
	int grid_cols = std::ceil(std::sqrt(num_images));  // Number of columns in the grid
	int grid_rows = std::ceil(static_cast<double>(num_images) / grid_cols);  // Number of rows in the grid

	// Determine a uniform display size for all images and focus maps
	int display_width = 200;  // Width for each image in the grid (can be adjusted)
	int display_height = 200; // Height for each image in the grid (can be adjusted)

	// Create empty matrices to hold the image and focus map grids
	cv::Mat image_grid = cv::Mat::zeros(display_height * grid_rows, display_width * grid_cols, CV_8UC3);
	cv::Mat focus_map_grid = cv::Mat::zeros(display_height * grid_rows, display_width * grid_cols, CV_8UC3);

	// Loop to populate both grids
	for (size_t i = 0; i < images.size(); i++) {
		// Resize the current image and focus map to the desired display size
		cv::Mat resized_image, resized_focus_map;
		cv::resize(images[i], resized_image, cv::Size(display_width, display_height));
		cv::resize(focus_maps[i], resized_focus_map, cv::Size(display_width, display_height));

		// Convert grayscale focus map to BGR if necessary for consistent display
		if (resized_focus_map.channels() == 1) {
			cv::cvtColor(resized_focus_map, resized_focus_map, cv::COLOR_GRAY2BGR);
		}

		// Calculate the grid position (row, col) for this image
		int row = i / grid_cols;
		int col = i % grid_cols;

		// Define the ROI (Region of Interest) for placing the resized image in the grid
		cv::Rect image_roi(col * display_width, row * display_height, display_width, display_height);
		resized_image.copyTo(image_grid(image_roi));
		resized_focus_map.copyTo(focus_map_grid(image_roi));
	}

	// Concatenate the image grid and focus map grid side by side
	cv::Mat display;
	cv::hconcat(image_grid, focus_map_grid, display);

	// Show the combined display with both grids
	cv::namedWindow("Image and Focus Map Grids", cv::WINDOW_NORMAL);
	cv::imshow("Image and Focus Map Grids", display);
	cv::waitKey(0);  // Wait for key press to close
}

/*

	FUNCTION THAT HANDLE THE DISPLAY OF THE WAVELET FOCUS

*/
void FSTHM::visualizeWaveletFocus(const std::vector<cv::Mat>& focus_maps, const std::string& window_name = "Wavelet Focus Visualization") {
	if (focus_maps.empty()) {
		std::cerr << "Error: No focus maps to visualize." << std::endl;
		return;
	}

	int num_maps = focus_maps.size();
	int grid_cols = std::ceil(std::sqrt(num_maps));  // Determine grid columns
	int grid_rows = std::ceil(static_cast<double>(num_maps) / grid_cols);  // Determine grid rows

	int display_width = 200;  // Width for each focus map in the grid
	int display_height = 200; // Height for each focus map in the grid

	// Create an empty canvas for the focus map grid
	cv::Mat focus_map_grid = cv::Mat::zeros(display_height * grid_rows, display_width * grid_cols, CV_8UC3);

	for (size_t i = 0; i < focus_maps.size(); ++i) {
		// Normalize the focus map to [0, 255]
		cv::Mat normalized_focus_map;
		cv::normalize(focus_maps[i], normalized_focus_map, 0, 255, cv::NORM_MINMAX);

		// Convert to CV_8U for display
		normalized_focus_map.convertTo(normalized_focus_map, CV_8U);

		// Apply a colormap for better focus visualization
		cv::Mat colored_focus_map;
		cv::applyColorMap(normalized_focus_map, colored_focus_map, cv::COLORMAP_JET);

		// Resize to the display size
		cv::Mat resized_focus_map;
		cv::resize(colored_focus_map, resized_focus_map, cv::Size(display_width, display_height));

		// Determine the grid position
		int row = i / grid_cols;
		int col = i % grid_cols;

		// Place the resized focus map into the grid
		cv::Rect roi(col * display_width, row * display_height, display_width, display_height);
		resized_focus_map.copyTo(focus_map_grid(roi));
	}

	// Display the focus map grid
	cv::namedWindow(window_name, cv::WINDOW_NORMAL);
	cv::imshow(window_name, focus_map_grid);
	cv::waitKey(0);  // Wait for a key press
}



/*

	FUNCTION THAT SHOWS THE FOCUS OF THE FFT

*/
void FSTHM::visualizeFFTFocus(const std::vector<cv::Mat>& images, const std::string& window_name = "FFT Focus Visualization") {
	if (images.empty()) {
		std::cerr << "Error: No images to process." << std::endl;
		return;
	}

	int num_images = images.size();
	int grid_cols = std::ceil(std::sqrt(num_images));  // Determine grid columns
	int grid_rows = std::ceil(static_cast<double>(num_images) / grid_cols);  // Determine grid rows

	int display_width = 200;  // Width for each FFT visualization in the grid
	int display_height = 200; // Height for each FFT visualization in the grid

	// Create an empty canvas for the FFT visualization grid
	cv::Mat fft_grid = cv::Mat::zeros(display_height * grid_rows, display_width * grid_cols, CV_8UC3);

	for (size_t i = 0; i < images.size(); ++i) {
		// Convert the image to grayscale if necessary
		cv::Mat gray_image;
		if (images[i].channels() == 3) {
			cv::cvtColor(images[i], gray_image, cv::COLOR_BGR2GRAY);
		}
		else {
			gray_image = images[i];
		}

		// Convert to float for FFT computation
		cv::Mat float_image;
		gray_image.convertTo(float_image, CV_32F);

		// Pad the image to optimal size for FFT
		int optimal_rows = cv::getOptimalDFTSize(float_image.rows);
		int optimal_cols = cv::getOptimalDFTSize(float_image.cols);
		cv::Mat padded;
		cv::copyMakeBorder(float_image, padded, 0, optimal_rows - float_image.rows, 0, optimal_cols - float_image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

		// Perform the FFT
		cv::Mat complex_image;
		cv::dft(padded, complex_image, cv::DFT_COMPLEX_OUTPUT);

		// Compute magnitude spectrum
		std::vector<cv::Mat> planes(2);
		cv::split(complex_image, planes);
		cv::Mat magnitude_spectrum;
		cv::magnitude(planes[0], planes[1], magnitude_spectrum);

		// Log scale to enhance visibility
		magnitude_spectrum += cv::Scalar::all(1);  // Avoid log(0)
		cv::log(magnitude_spectrum, magnitude_spectrum);

		// Crop the spectrum to remove padding
		magnitude_spectrum = magnitude_spectrum(cv::Rect(0, 0, gray_image.cols, gray_image.rows));

		// Normalize to [0, 255] for display
		cv::normalize(magnitude_spectrum, magnitude_spectrum, 0, 255, cv::NORM_MINMAX);
		magnitude_spectrum.convertTo(magnitude_spectrum, CV_8U);

		// Apply colormap for better visualization
		cv::Mat colored_fft;
		cv::applyColorMap(magnitude_spectrum, colored_fft, cv::COLORMAP_JET);

		// Resize to display dimensions
		cv::Mat resized_fft;
		cv::resize(colored_fft, resized_fft, cv::Size(display_width, display_height));

		// Determine the grid position
		int row = i / grid_cols;
		int col = i % grid_cols;

		// Place the resized FFT visualization into the grid
		cv::Rect roi(col * display_width, row * display_height, display_width, display_height);
		resized_fft.copyTo(fft_grid(roi));
	}

	// Display the FFT visualization grid
	cv::namedWindow(window_name, cv::WINDOW_NORMAL);
	cv::imshow(window_name, fft_grid);
	cv::waitKey(0);  // Wait for a key press
}



/*

	FUNCTION THAT CONVERTS TO GRAYSCALE

*/
std::vector<cv::Mat> FSTHM::convertToGrayscale(const std::vector<cv::Mat>& images) {
	//vector that will hold the grayscale images
	std::vector<cv::Mat> grayscale_images(images.size());

	//convert to grayscale
	for (size_t i = 0; i < images.size(); i++) {
		if (images[i].channels() == 3) {
			//convert to grayscale
			cv::cvtColor(images[i], grayscale_images[i], cv::COLOR_BGR2GRAY);
		}
		else {
			//clone it if already in grayscale
			grayscale_images[i] = images[i];
		}
	}
	return grayscale_images;
}



/*

	LAPLACIAN VARIANCE
	we basically first calculate the laplacian of the grayscale,
	we use the grayscale for simplicity of processing the
	image and then we calculate the variance in it
	"the higher the variance the higher the sharpness", below a
	certain treshold we can consider that part blurry, we then
	create a focus map to visualize wich part of the image are in focus

*/
std::vector<cv::Mat> FSTHM::calculateLaplacianVariance(const std::vector<cv::Mat>& images, const bool blur, const std::array<int, 2>& gaussian_blur_kernel) {
	//create a vector to hold the grayscale images and the resulting focus map
	std::vector<cv::Mat> focus_map(images.size());
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	//create a vector to hold the laplacian variance of the images
	std::vector<double> variances;

	//we need to also apply a gaussian filter since images can be noisy and cause 
	//rapid changes that might affect badly the laplacian
	//and then call the laplacian
	for (size_t i = 0; i < images.size(); i++) {

		//we apply a gaussian blur if necessary with a kernel size suggested of 3, bigger kernel gets us bigger blur
		if (blur) {
			cv::GaussianBlur(grayscale_images[i], grayscale_images[i], cv::Size(gaussian_blur_kernel[0], gaussian_blur_kernel[1]), 0, 0, cv::BORDER_DEFAULT);
		}

		//we can apply the laplacian
		cv::Laplacian(grayscale_images[i], focus_map[i], CV_64F);

		//then to account for pixel distribution or rapid variances we converto absolute values
		cv::convertScaleAbs(focus_map[i], focus_map[i]);

	}

	return focus_map;

}



/*

	TENENEGRAD
	we are calculating the sobel operator that is a first order derivative
	operator that calculates the intensity gradient in the X and Y
	direction and then we convolute them with the sobel kernel, then we get
	the gradient of the image, then we convert to a focus map to visualize
	the focus area with brighter spots are considered in focus

*/
std::vector<cv::Mat> FSTHM::calculateTenengrad(const std::vector<cv::Mat>& images, const int kernel_size) {
	//create the vector that will hold the focus map and create the grayscales
	std::vector<cv::Mat> focus_map(images.size());
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	//we can now loop trough the grayscales and perform the tenengrad algorithm
	for (size_t i = 0; i < images.size(); i++) {
		//create the matrix holding the gradients
		cv::Mat grad_X, grad_Y;

		//we then compute the sobel gradient in the X and Y direction
		cv::Sobel(grayscale_images[i], grad_X, CV_64F, 1, 0, kernel_size);
		cv::Sobel(grayscale_images[i], grad_Y, CV_64F, 1, 0, kernel_size);

		//now we need to compute the gradient magnitude
		cv::Mat gradient_magnitude;
		cv::magnitude(grad_X, grad_Y, gradient_magnitude);

		//then we convert to focus map
		cv::convertScaleAbs(gradient_magnitude, focus_map[i]);
	}

	return focus_map;
}



/*

	FFT BASED
	this approach take advantages of the property of the fast fourier
	transform to get the values of frequency and then create the focus
	map for the detailed explanation is best to look to the documentation
	to avoid writing too much comment

*/
std::vector<cv::Mat> FSTHM::calculateFFTBasedFrequency(const std::vector<cv::Mat>& images, const double cutoff_percentage) {
	//create a vector containing the grayscales and one empty for the focus map
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);
	std::vector<cv::Mat> focus_map(images.size());

	for (size_t i = 0; i < grayscale_images.size(); i++) {
		//for the fast fourier trasform to perform optimally it is useful to make the matrix a multiple of 2,3 or 5
		//so we declare a new matrix(m x n) that will rescale our image 
		cv::Mat padded;
		int m = cv::getOptimalDFTSize(grayscale_images[i].rows);
		int n = cv::getOptimalDFTSize(grayscale_images[i].cols);

		//we also need to set all the borders to zero
		cv::copyMakeBorder(grayscale_images[i], padded, 0, m - grayscale_images[i].rows, 0, n - grayscale_images[i].cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

		//we can now perform the FFT
		//since the FFT will gives us a complex valued image we will need to save both real and imaginary components
		//the first part are the real values from the padded and the second is the complex image set to 0
		cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };

		//we then combine the two planes in a single image
		cv::Mat complex_image;
		cv::merge(planes, 2, complex_image);

		//apply the dft saving the output in the input
		cv::dft(complex_image, complex_image);

		// Shift the quadrants of the Fourier image so that the origin is at the center
		complex_image = complex_image(cv::Rect(0, 0, complex_image.cols & -2, complex_image.rows & -2));
		int cx = complex_image.cols / 2;
		int cy = complex_image.rows / 2;
		cv::Mat q0(complex_image, cv::Rect(0, 0, cx, cy));   // Top-Left
		cv::Mat q1(complex_image, cv::Rect(cx, 0, cx, cy));  // Top-Right
		cv::Mat q2(complex_image, cv::Rect(0, cy, cx, cy));  // Bottom-Left
		cv::Mat q3(complex_image, cv::Rect(cx, cy, cx, cy)); // Bottom-Right
		cv::Mat tmp; // temporary Mat for swapping quadrants
		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);
		q1.copyTo(tmp);
		q2.copyTo(q1);
		tmp.copyTo(q2);

		//since different type of images tends to have different pixel density we need to define dinamically the value of the high pass filter
		// Calculate dynamic high-frequency cutoff based on the image's dimensions, the cutoff is made on the shorter side
		int min_dim = std::min(padded.rows, padded.cols);
		int high_frequency_cutoff = static_cast<int>(cutoff_percentage * min_dim / 100.0);

		// Create a high-pass filter mask with the same size as complex_image
		cv::Mat mask = cv::Mat::zeros(complex_image.size(), CV_32F);
		cv::circle(mask, cv::Point(cx, cy), high_frequency_cutoff, cv::Scalar(1), -1);
		cv::Mat planes_mask[] = { mask, mask };
		cv::merge(planes_mask, 2, mask);

		// Ensure `complex_image` and `mask` have the same size before multiplication
		if (complex_image.size() != mask.size()) {
			std::cerr << "Error: Mismatched sizes between complex_image and mask. Skipping this image." << std::endl;
			continue;
		}

		// Apply high-pass filter by multiplying in frequency domain
		cv::Mat filtered_complex_image;
		cv::mulSpectrums(complex_image, mask, filtered_complex_image, 0);

		// Shift quadrants back before inverse DFT
		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);
		q1.copyTo(tmp);
		q2.copyTo(q1);
		tmp.copyTo(q2);

		// Inverse FFT to bring the filtered high-frequency components back into spatial domain
		cv::Mat inverse_transform;
		cv::idft(filtered_complex_image, inverse_transform, cv::DFT_REAL_OUTPUT);
		cv::normalize(inverse_transform, inverse_transform, 0, 255, cv::NORM_MINMAX);
		inverse_transform.convertTo(inverse_transform, CV_8U);

		// Crop to original image size and store as focus map
		focus_map[i] = inverse_transform(cv::Rect(0, 0, grayscale_images[i].cols, grayscale_images[i].rows));

	}

	return focus_map;
}



/*

	SUM OF MODIFIED LAPLACIAN
	this method is very similar to the laplacian variance but
	it computes the sum of the laplacian not in a general way
	but pixel for pixel and adjust by a metric, the rest is like
	the laplacian variance. The actual main difference is that
	instead of converting to absolute the global focus map we do
	so pixel by pixel

*/
std::vector<cv::Mat> FSTHM::calculateSML(const std::vector<cv::Mat>& images, const bool blur, const std::array<int, 2>& gaussian_blur_kernel) {
	//create the vector that holds the grayscale and the focus map
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);
	std::vector<cv::Mat> focus_map(images.size());

	//let's loop trough the images and perform our action
	for (size_t i = 0; i < grayscale_images.size(); i++) {
		//we apply a gaussian blur if necessary with a kernel size of ideally 3 bigger kernel gets us bigger blur
		if (blur) {
			cv::GaussianBlur(grayscale_images[i], grayscale_images[i], cv::Size(gaussian_blur_kernel[0], gaussian_blur_kernel[1]), 0, 0, cv::BORDER_DEFAULT);
		}

		//create a matrix to hold the laplacians
		cv::Mat laplacian;

		//perform the laplacian
		cv::Laplacian(grayscale_images[i], laplacian, CV_32F);

		//create a Matrix to hold the single pixel absolute
		cv::Mat pixels_focus_map = cv::Mat::zeros(laplacian.size(), CV_32F);

		//loop trough the image and convert to absolute
		for (int j = 0; j < laplacian.rows; j++) {
			for (int k = 0; k < laplacian.cols; k++) {
				pixels_focus_map.at<float>(j, k) = std::abs(laplacian.at<float>(j, k));
			}
		}
		//assign the focus map to the vector
		focus_map[i] = pixels_focus_map;

		//convert to focus map
		cv::convertScaleAbs(focus_map[i], focus_map[i]);
	}

	return focus_map;
}



/*

	DIFFERENCE OF GAUSSIAN
	this method is based on getting the high frequency area after
	the application of different gaussian filters, based on two values
	sigma1 and sigma2 this values are related to:
												fine detail
												large depth of field
												reduce noise
												high textured images
	the cited values need to be dynamically update based on the said parameters

*/
std::vector<cv::Mat> FSTHM::calculateGaussianDifference(const std::vector<cv::Mat>& images, const double sigma1, const double sigma2) {
	//create the vector that holds the focus map and the grayscales
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);
	std::vector<cv::Mat> focus_map(images.size());

	//let's loop trough all the images
	for (size_t i = 0; i < images.size(); i++) {
		//create the two blurred images to use
		cv::Mat blur1, blur2;
		cv::GaussianBlur(grayscale_images[i], blur1, cv::Size(0, 0), sigma1);
		cv::GaussianBlur(grayscale_images[i], blur2, cv::Size(0, 0), sigma2);

		//now we can compute the difference of gaussians
		cv::Mat difference_of_gaussians = blur1 - blur2;

		//then we can convert to focus map
		cv::convertScaleAbs(difference_of_gaussians, focus_map[i]);
	}

	return focus_map;
}



/*

	GAUSSIAN HIGH PASS FILTER
	the high pass filter consist in subtracting from the grayscale image
	a gaussian blurred image of it to obtain the high frequencies

*/
std::vector<cv::Mat> FSTHM::calculateGHPF(const std::vector<cv::Mat>& images, const double sigma) {
	//create the vector that holds the focus map and the grayscales
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);
	std::vector<cv::Mat> focus_map(images.size());

	//let's loop trough all the images
	for (size_t i = 0; i < images.size(); i++) {
		//lets create the blurred image
		cv::Mat blurred_image;
		cv::GaussianBlur(grayscale_images[i], blurred_image, cv::Size(0, 0), sigma);

		//create the high pass filtered image
		cv::Mat high_pass_filter_image = grayscale_images[i] - blurred_image;

		//convert to focus map
		cv::convertScaleAbs(high_pass_filter_image, focus_map[i]);
	}

	return focus_map;
}



/*

	MULTI SCALE GAUSSIAN FILTER
	this is a combinantion of some operation already implemented
	we basically first apply a gaussian filter then calculate the laplacian
	then we do this for each scale and combine the result of the various
	scale to obtain the focus map, we will also create a function that will perform
	the laplacian and the blur for clearer code

*/
cv::Mat FSTHM::calculateGaussianOfLaplacian(const cv::Mat& grayscale_image, const double sigma) {
	// Create the blurred image
	cv::Mat blurred_image;
	cv::GaussianBlur(grayscale_image, blurred_image, cv::Size(0, 0), sigma);

	// Compute the Laplacian; use CV_64F to avoid clipping
	cv::Mat laplacian;
	cv::Laplacian(blurred_image, laplacian, CV_64F, 3);

	return laplacian;
}

std::vector<cv::Mat> FSTHM::calculateMSG(const std::vector<cv::Mat>& images, const std::vector<int>& scales, const std::vector<double>& sigmas) {
	// Convert all images to grayscale
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Initialize the focus map for each image
	std::vector<cv::Mat> focus_map(images.size());

	// Loop through each image
	for (size_t i = 0; i < images.size(); i++) {
		// Initialize focus_map[i] with zeros, matching the grayscale image size and type
		focus_map[i] = cv::Mat::zeros(grayscale_images[i].size(), CV_32F);

		// Temporary vector to hold focus measures for current image
		std::vector<cv::Mat> focus_measures;

		// Loop through all scales
		for (size_t j = 0; j < scales.size(); j++) {
			// Compute the Laplacian for the given scale and sigma value
			cv::Mat laplacian = calculateGaussianOfLaplacian(grayscale_images[i], sigmas[j]);

			// Take the absolute value of the Laplacian
			cv::Mat abs_laplacian = cv::abs(laplacian);

			// Convert abs_laplacian to CV_32F for compatibility
			cv::Mat normalized;
			abs_laplacian.convertTo(normalized, CV_32F);

			// Save the focus measure
			focus_measures.push_back(normalized);
		}

		// Combine focus measures to compute the focus map
		for (const auto& fm : focus_measures) {
			//element wise matrix max
			focus_map[i] = cv::max(focus_map[i], fm);
		}

		// Normalize the final focus map to CV_8U for display or further processing
		focus_map[i].convertTo(focus_map[i], CV_8U, 255.0); // Scale to 0-255
	}

	return focus_map;
}



/*
*
	WAVELET FOCUS MAP
	function that converts the result of the wavelets transformation in to a focus map

*/
std::vector<cv::Mat> FSTHM::computeWaveletsFocusMap(const std::vector<cv::Mat>& wavelets) {
	std::vector<cv::Mat> focus_map(wavelets.size());

	for (size_t i = 0; i < wavelets.size(); ++i) {
		cv::Mat focus_map_single(wavelets[i].rows / 2, wavelets[i].cols / 2, CV_32F);

		// Extract high-frequency subbands
		cv::Mat LH = wavelets[i](cv::Rect(0, wavelets[i].rows / 2, wavelets[i].cols / 2, wavelets[i].rows / 2));
		cv::Mat HL = wavelets[i](cv::Rect(wavelets[i].cols / 2, 0, wavelets[i].cols / 2, wavelets[i].rows / 2));
		cv::Mat HH = wavelets[i](cv::Rect(wavelets[i].cols / 2, wavelets[i].rows / 2, wavelets[i].cols / 2, wavelets[i].rows / 2));

		// Calculate focus energy: Magnitude of high-frequency coefficients
		focus_map_single = LH.mul(LH) + HL.mul(HL) + HH.mul(HH);
		cv::sqrt(focus_map_single, focus_map_single);

		// Normalize the focus map for consistency
		cv::normalize(focus_map_single, focus_map_single, 0, 1, cv::NORM_MINMAX);

		// Store the result
		focus_map[i] = focus_map_single.clone();
	}
	return focus_map;
}



/*

	PADDED IMAGE CONSTRUCTOR
	function that adapt the single image to be divisible by two

*/
cv::Mat FSTHM::paddedImageConstructor(const cv::Mat& grayscale_image, int& rows, int& cols) {

	//make sure to be in float precision
	cv::Mat float_image;
	grayscale_image.convertTo(float_image, CV_32F);

	//just like we did for the haar wavelet we need to make sure it is divisible by two
	rows = float_image.rows;
	cols = float_image.cols;
	cv::Mat padded_image;
	cv::copyMakeBorder(float_image, padded_image, 0, rows % 2, 0, cols % 2, cv::BORDER_REFLECT_101);

	return padded_image;
}


/*

	FUNCTION THAT SHIFTS THE FFT

*/
void FSTHM::dftShift(const cv::Mat& input, cv::Mat& output) {
	output = input.clone();
	int cx = output.cols / 2;
	int cy = output.rows / 2;

	cv::Mat q0(output, cv::Rect(0, 0, cx, cy));        // Top-left
	cv::Mat q1(output, cv::Rect(cx, 0, cx, cy));       // Top-right
	cv::Mat q2(output, cv::Rect(0, cy, cx, cy));       // Bottom-left
	cv::Mat q3(output, cv::Rect(cx, cy, cx, cy));      // Bottom-right

	// Swap quadrants
	cv::Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
}


/*

	FUNCTION THAT CREATES THE MORLET KERNEL

*/
cv::Mat FSTHM::createMorletKernel(int rows, int cols, float center_frequency, float sigma) {
	cv::Mat morlet_kernel(rows, cols, CV_32FC2, cv::Scalar(0, 0));

	// Frequency-domain grid
	float fx, fy;
	for (int u = 0; u < rows; ++u) {
		fx = (u - rows / 2) / static_cast<float>(rows); // Normalized frequency (row)
		for (int v = 0; v < cols; ++v) {
			fy = (v - cols / 2) / static_cast<float>(cols); // Normalized frequency (col)

			// Morlet wavelet in frequency domain
			float magnitude = std::exp(-(fx * fx + fy * fy) / (2 * sigma * sigma)) *
				std::cos(2 * CV_PI * center_frequency * (fx + fy));
			float phase = 2 * CV_PI * center_frequency * (fx + fy);

			// Assign complex values
			morlet_kernel.at<cv::Vec2f>(u, v)[0] = magnitude * std::cos(phase); // Real part
			morlet_kernel.at<cv::Vec2f>(u, v)[1] = magnitude * std::sin(phase); // Imaginary part
		}
	}

	// Shift the kernel to center the frequency domain
	cv::Mat shifted_kernel;
	dftShift(morlet_kernel, shifted_kernel);

	return shifted_kernel;
}



/*

	CREATE THE MEXICAN HAT KERNEL

*/
cv::Mat FSTHM::generateMexicanHatKernel(int kernel_size, float sigma) {
	cv::Mat kernel(kernel_size, kernel_size, CV_32F);
	int half_size = kernel_size / 2;
	float sigma2 = sigma * sigma;
	float normalization = 1.0f / (std::sqrt(2.0f * CV_PI) * std::pow(sigma, 3));

	for (int y = -half_size; y <= half_size; ++y) {
		for (int x = -half_size; x <= half_size; ++x) {
			float r2 = x * x + y * y;
			kernel.at<float>(y + half_size, x + half_size) = normalization * (2 - r2 / sigma2) * std::exp(-r2 / (2 * sigma2));
		}
	}

	return kernel;
}



/*

	FUNCTION THAT GENERATE THE MEYER FILTER

*/
cv::Mat FSTHM::generateMeyerFilter(cv::Size size) {
	cv::Mat filter(size, CV_32F);
	int center_x = size.width / 2;
	int center_y = size.height / 2;

	for (int u = 0; u < size.height; ++u) {
		for (int v = 0; v < size.width; ++v) {
			float dist = std::sqrt((u - center_y) * (u - center_y) + (v - center_x) * (v - center_x));
			float omega = dist / std::max(size.width, size.height); // Normalized frequency

			if (omega <= 1.0 / 3.0) {
				filter.at<float>(u, v) = 1.0f; // Low-pass band
			}
			else if (omega > 1.0 / 3.0 && omega <= 2.0 / 3.0) {
				float transition = 0.5f * (1.0f + std::cos(CV_PI * (3.0f * omega - 1.0f)));
				filter.at<float>(u, v) = transition;
			}
			else {
				filter.at<float>(u, v) = 0.0f; // High frequencies are suppressed
			}
		}
	}

	return filter;
}



/*

	GENERATE THE SHANNON FILTER

*/
cv::Mat FSTHM::generateShannonFilter(cv::Size size) {
	cv::Mat filter(size, CV_32F, cv::Scalar(0));
	int center_x = size.width / 2;
	int center_y = size.height / 2;

	float low_cutoff = 0.25f; // Lower cutoff frequency (normalized, 0.0 - 1.0)
	float high_cutoff = 0.5f; // Higher cutoff frequency (normalized, 0.0 - 1.0)

	for (int u = 0; u < size.height; ++u) {
		for (int v = 0; v < size.width; ++v) {
			float dist = std::sqrt((u - center_y) * (u - center_y) + (v - center_x) * (v - center_x));
			float omega = dist / std::max(size.width, size.height); // Normalized frequency

			// Rectangular band-pass filter for Shannon wavelet
			if (omega >= low_cutoff && omega <= high_cutoff) {
				filter.at<float>(u, v) = 1.0f;
			}
		}
	}

	return filter;
}



/*

	FUNCTION THAT APPLY THE FREQUENCY FILTER

*/
void FSTHM::applyFrequencyFilter(const cv::Mat& complex_image, const cv::Mat& filter, cv::Mat& filtered_image) {
	cv::Mat planes[2];
	cv::split(complex_image, planes);

	// Apply the filter to both real and imaginary parts
	planes[0] = planes[0].mul(filter);
	planes[1] = planes[1].mul(filter);

	cv::merge(planes, 2, filtered_image);
}



/*

	 HAAR WAVELETS
	 this type of wavelets can extract the the higher sharpen
	 of an image trough it's high frequency component and the
	 less important trough the low frequency , this is done trough
	 the computation of the energy metric, the processed image must
	 be multiple of 2


*/
std::vector<cv::Mat> FSTHM::calculateHaarWaveletsFocus(const std::vector<cv::Mat>& images) {
	// Convert images to grayscale
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Create vector for wavelets
	std::vector<cv::Mat> wavelets(images.size());

	for (size_t i = 0; i < grayscale_images.size(); ++i) {
		// Ensure dimensions are divisible by 2
		int rows = 0;
		int cols = 0;
		cv::Mat padded_image = paddedImageConstructor(grayscale_images[i], rows, cols);

		// Temporary matrices for transformations
		cv::Mat temp_rows(padded_image.size(), CV_32F);
		cv::Mat temp_cols(padded_image.size(), CV_32F);

		// Row-wise Haar transform
		// - This loop processes each row of the padded image.
		// - For each pair of adjacent pixels in the row (at indices 2*k and 2*k+1),
		// - it computes an average (representing the "low-frequency" information)
		// - and a difference (representing the "high-frequency" information).
		// - The results are stored in the first and second halves of `temp_rows`, respectively.
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols / 2; ++c) {
				float avg = (padded_image.at<float>(r, 2 * c) + padded_image.at<float>(r, 2 * c + 1)) / 2.0f;
				float diff = (padded_image.at<float>(r, 2 * c) - padded_image.at<float>(r, 2 * c + 1)) / 2.0f;

				temp_rows.at<float>(r, c) = avg;
				temp_rows.at<float>(r, c + cols / 2) = diff;
			}
		}

		// Column-wise Haar transform
		// - This loop processes each column of `temp_rows`.
		// - For each pair of adjacent values in the column (at indices 2*k and 2*k+1),
		// - it computes an average and a difference, just like the row-wise operation.
		// - The results are stored in the first and second halves of `temp_cols`, respectively.
		// Column-wise transformation
		for (int c = 0; c < cols; ++c) {
			for (int r = 0; r < rows / 2; ++r) {
				float avg = (temp_rows.at<float>(2 * r, c) + temp_rows.at<float>(2 * r + 1, c)) / 2.0f;
				float diff = (temp_rows.at<float>(2 * r, c) - temp_rows.at<float>(2 * r + 1, c)) / 2.0f;

				temp_cols.at<float>(r, c) = avg;
				temp_cols.at<float>(r + rows / 2, c) = diff;
			}
		}

		// Crop to original size and save result
		wavelets[i] = temp_cols(cv::Rect(0, 0, grayscale_images[i].cols, grayscale_images[i].rows)).clone();
	}

	return wavelets;
}


/*

	DAUBECHIS WAVELETS
	similar to the Haar wavelet but with compact support more precise
	but computationally more expensive

*/
std::vector<cv::Mat> FSTHM::calculateDaubechisWavelets(const std::vector<cv::Mat>& images, const std::vector<float> low_pass, const std::vector<float> high_pass) {
	//create the grayscale images
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	//create the vector for the wavelets
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	for (size_t i = 0; i < grayscale_images.size(); i++) {
		//create variable to hold rows and cols
		int rows = 0;
		int cols = 0;

		//create the padded image
		cv::Mat padded_image = paddedImageConstructor(grayscale_images[i], rows, cols);

		//now create the temporary matrices for the transform
		cv::Mat temp_rows(padded_image.size(), CV_32F);
		cv::Mat temp_cols(padded_image.size(), CV_32F);

		// Row-wise Daubechies transform
		for (int r = 0; r < padded_image.rows; ++r) {
			for (int c = 0; c < padded_image.cols / 2; ++c) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < 4; ++k) {
					int idx = (2 * c + k) % padded_image.cols; // Circular convolution
					low += padded_image.at<float>(r, idx) * low_pass[k];
					high += padded_image.at<float>(r, idx) * high_pass[k];
				}
				temp_rows.at<float>(r, c) = low;
				temp_rows.at<float>(r, c + padded_image.cols / 2) = high;
			}
		}

		// Column-wise Daubechies transform
		for (int c = 0; c < temp_rows.cols; ++c) {
			for (int r = 0; r < temp_rows.rows / 2; ++r) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < 4; ++k) {
					int idx = (2 * r + k) % temp_rows.rows; // Circular convolution
					low += temp_rows.at<float>(idx, c) * low_pass[k];
					high += temp_rows.at<float>(idx, c) * high_pass[k];
				}
				temp_cols.at<float>(r, c) = low;
				temp_cols.at<float>(r + temp_rows.rows / 2, c) = high;
			}
		}

		// Crop back to original size and save result
		wavelets[i] = temp_cols(cv::Rect(0, 0, cols, rows)).clone();
	}

	return wavelets;
}


/*

	SYMLET WAVELETS
	It harness the power of the symmetry of the images

*/
std::vector<cv::Mat> FSTHM::calculateSymletWavelets(const std::vector<cv::Mat>& images, const std::vector<float> sym_low_pass, const std::vector<float> sym_high_pass) {
	//convert to grayscales
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	//create the vector that will contain the wavelets
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	for (size_t i = 0; i < grayscale_images.size(); i++) {
		//create variable to hold rows and columns
		int rows = 0;
		int cols = 0;
		cv::Mat padded_image = paddedImageConstructor(grayscale_images[i], rows, cols);

		// Temporary matrices for the transform
		cv::Mat temp_rows(padded_image.size(), CV_32F);
		cv::Mat temp_cols(padded_image.size(), CV_32F);

		// Row-wise Symlet transform
		for (int r = 0; r < padded_image.rows; ++r) {
			for (int c = 0; c < padded_image.cols / 2; ++c) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < sym_low_pass.size(); ++k) { // Adjust for Symlet filter length
					int idx = (2 * c + k) % padded_image.cols; // Circular convolution
					low += padded_image.at<float>(r, idx) * sym_low_pass[k];
					high += padded_image.at<float>(r, idx) * sym_high_pass[k];
				}
				temp_rows.at<float>(r, c) = low;
				temp_rows.at<float>(r, c + padded_image.cols / 2) = high;
			}
		}

		// Column-wise Symlet transform
		for (int c = 0; c < temp_rows.cols; ++c) {
			for (int r = 0; r < temp_rows.rows / 2; ++r) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < sym_low_pass.size(); ++k) { // Adjust for Symlet filter length
					int idx = (2 * r + k) % temp_rows.rows; // Circular convolution
					low += temp_rows.at<float>(idx, c) * sym_low_pass[k];
					high += temp_rows.at<float>(idx, c) * sym_high_pass[k];
				}
				temp_cols.at<float>(r, c) = low;
				temp_cols.at<float>(r + temp_rows.rows / 2, c) = high;
			}
		}

		// Crop back to original size and save result
		wavelets[i] = temp_cols(cv::Rect(0, 0, cols, rows)).clone();
	}

	return wavelets;
}



/*

	COIFLET WAVELET

*/
std::vector<cv::Mat> FSTHM::calculateCoifletWavelets(const std::vector<cv::Mat>& images, const std::vector<float> coif_low_pass, const std::vector<float> coif_high_pass) {
	// Convert to grayscale
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Create the vector that will contain the wavelets
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	for (size_t i = 0; i < grayscale_images.size(); i++) {
		// Variables to hold rows and columns
		int rows = 0;
		int cols = 0;

		// Pad the image to handle border effects
		cv::Mat padded_image = paddedImageConstructor(grayscale_images[i], rows, cols);

		// Temporary matrices for the transform
		cv::Mat temp_rows(padded_image.size(), CV_32F);
		cv::Mat temp_cols(padded_image.size(), CV_32F);

		// Row-wise Coiflet transform
		for (int r = 0; r < padded_image.rows; ++r) {
			for (int c = 0; c < padded_image.cols / 2; ++c) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < coif_low_pass.size(); ++k) {
					int idx = (2 * c + k) % padded_image.cols; // Circular convolution
					low += padded_image.at<float>(r, idx) * coif_low_pass[k];
					high += padded_image.at<float>(r, idx) * coif_high_pass[k];
				}
				temp_rows.at<float>(r, c) = low;
				temp_rows.at<float>(r, c + padded_image.cols / 2) = high;
			}
		}

		// Column-wise Coiflet transform
		for (int c = 0; c < temp_rows.cols; ++c) {
			for (int r = 0; r < temp_rows.rows / 2; ++r) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < coif_low_pass.size(); ++k) {
					int idx = (2 * r + k) % temp_rows.rows; // Circular convolution
					low += temp_rows.at<float>(idx, c) * coif_low_pass[k];
					high += temp_rows.at<float>(idx, c) * coif_high_pass[k];
				}
				temp_cols.at<float>(r, c) = low;
				temp_cols.at<float>(r + temp_rows.rows / 2, c) = high;
			}
		}

		// Crop back to original size and save the result
		wavelets[i] = temp_cols(cv::Rect(0, 0, cols, rows)).clone();
	}

	return wavelets;
}



/*

	BIORTHOGONAL WAVELETS

*/
std::vector<cv::Mat> FSTHM::calculateBiorthogonalWavelets(const std::vector<cv::Mat>& images, const std::vector<float>& low_decomp, const std::vector<float>& high_decomp) {

	// Convert images to grayscale
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Create a vector to store the wavelet results
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	for (size_t i = 0; i < grayscale_images.size(); ++i) {
		int rows = 0, cols = 0;
		cv::Mat padded_image = paddedImageConstructor(grayscale_images[i], rows, cols);

		// Temporary storage for row-wise and column-wise transforms
		cv::Mat temp_rows(padded_image.size(), CV_32F);
		cv::Mat temp_cols(padded_image.size(), CV_32F);

		// Row-wise transform
		for (int r = 0; r < padded_image.rows; ++r) {
			for (int c = 0; c < padded_image.cols / 2; ++c) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < low_decomp.size(); ++k) {
					int idx = (2 * c + k) % padded_image.cols; // Circular convolution
					low += padded_image.at<float>(r, idx) * low_decomp[k];
					high += padded_image.at<float>(r, idx) * high_decomp[k];
				}
				temp_rows.at<float>(r, c) = low;
				temp_rows.at<float>(r, c + padded_image.cols / 2) = high;
			}
		}

		// Column-wise transform
		for (int c = 0; c < temp_rows.cols; ++c) {
			for (int r = 0; r < temp_rows.rows / 2; ++r) {
				float low = 0.0f, high = 0.0f;
				for (int k = 0; k < low_decomp.size(); ++k) {
					int idx = (2 * r + k) % temp_rows.rows; // Circular convolution
					low += temp_rows.at<float>(idx, c) * low_decomp[k];
					high += temp_rows.at<float>(idx, c) * high_decomp[k];
				}
				temp_cols.at<float>(r, c) = low;
				temp_cols.at<float>(r + temp_rows.rows / 2, c) = high;
			}
		}

		// Crop back to the original size and save the result
		wavelets[i] = temp_cols(cv::Rect(0, 0, cols, rows)).clone();
	}

	return wavelets;
}

/*

	MORLET WAVELETS

*/
std::vector<cv::Mat> FSTHM::calculateMorletWavelets(const std::vector<cv::Mat>& images, float center_frequency, float sigma) {

	// Convert images to grayscale if needed
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Create a vector to store the wavelet-transformed images
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	// Iterate over each image
	for (size_t i = 0; i < grayscale_images.size(); ++i) {
		// Convert image to float and normalize
		cv::Mat float_image;
		grayscale_images[i].convertTo(float_image, CV_32F, 1.0 / 255.0);

		// Get image dimensions
		int rows = float_image.rows;
		int cols = float_image.cols;

		// Create a complex matrix to store the wavelet transform result
		cv::Mat wavelet_transform(rows, cols, CV_32FC2, cv::Scalar(0, 0));

		// Construct the Morlet kernel in frequency domain
		cv::Mat morlet_kernel = createMorletKernel(rows, cols, center_frequency, sigma);

		// Perform the wavelet transform via Fourier convolution
		cv::Mat image_fft;
		cv::dft(float_image, image_fft, cv::DFT_COMPLEX_OUTPUT); // Forward FFT

		cv::Mat result_fft;
		cv::mulSpectrums(image_fft, morlet_kernel, result_fft, cv::DFT_ROWS); // Convolution in frequency domain

		cv::idft(result_fft, wavelet_transform, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT); // Inverse FFT

		// Store the real part of the transform as the result
		cv::Mat magnitude;
		cv::magnitude(wavelet_transform, wavelet_transform, magnitude); // Compute magnitude
		wavelets[i] = magnitude.clone();
	}

	return wavelets;
}



/*

	MEXICAN HAT WAVELET/RICKER WAVELET

*/
std::vector<cv::Mat> FSTHM::calculateMexicanHatWavelets(const std::vector<cv::Mat>& images, float sigma) {
	// Convert to grayscale
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Create the vector that will contain the wavelets
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	// Define the size of the kernel based on sigma
	int kernel_size = static_cast<int>(std::ceil(6 * sigma)); // 3-sigma on each side
	if (kernel_size % 2 == 0) kernel_size += 1; // Ensure kernel size is odd

	// Generate the Mexican Hat kernel
	cv::Mat mexican_hat_kernel = generateMexicanHatKernel(kernel_size, sigma);

	for (size_t i = 0; i < grayscale_images.size(); i++) {
		// Pad the image to handle border effects
		cv::Mat padded_image;
		cv::copyMakeBorder(grayscale_images[i], padded_image, kernel_size / 2, kernel_size / 2, kernel_size / 2, kernel_size / 2, cv::BORDER_REFLECT);

		// Apply the Mexican Hat kernel
		cv::Mat filtered_image;
		cv::filter2D(padded_image, filtered_image, CV_32F, mexican_hat_kernel);

		// Crop back to the original size and save the result
		wavelets[i] = filtered_image(cv::Rect(kernel_size / 2, kernel_size / 2, grayscale_images[i].cols, grayscale_images[i].rows)).clone();
	}

	return wavelets;
}


/*

	MEYER WAVELET

*/
std::vector<cv::Mat> FSTHM::calculateMeyerWavelets(const std::vector<cv::Mat>& images) {
	// Convert to grayscale
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Create the vector that will contain the wavelets
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	for (size_t i = 0; i < grayscale_images.size(); i++) {
		// Original dimensions
		int orig_rows = grayscale_images[i].rows;
		int orig_cols = grayscale_images[i].cols;

		// Expand the image to the next power of 2 (optimal for FFT)
		cv::Mat padded_image;
		int padded_rows = cv::getOptimalDFTSize(orig_rows);
		int padded_cols = cv::getOptimalDFTSize(orig_cols);
		cv::copyMakeBorder(grayscale_images[i], padded_image, 0, padded_rows - orig_rows, 0, padded_cols - orig_cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

		// Perform FFT
		cv::Mat planes[] = { cv::Mat_<float>(padded_image), cv::Mat::zeros(padded_image.size(), CV_32F) };
		cv::Mat complex_image;
		cv::merge(planes, 2, complex_image);
		cv::dft(complex_image, complex_image);

		// Generate Meyer wavelet filter in frequency domain
		cv::Mat filter = generateMeyerFilter(complex_image.size());

		// Apply the Meyer wavelet filter
		cv::Mat filtered_image;
		applyFrequencyFilter(complex_image, filter, filtered_image);

		// Perform inverse FFT
		cv::Mat inverse_planes[] = { cv::Mat::zeros(padded_image.size(), CV_32F), cv::Mat::zeros(padded_image.size(), CV_32F) };
		cv::idft(filtered_image, complex_image, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
		cv::split(complex_image, inverse_planes);
		cv::Mat result = inverse_planes[0]; // Take the real part

		// Crop back to original dimensions
		wavelets[i] = result(cv::Rect(0, 0, orig_cols, orig_rows)).clone();
	}

	return wavelets;
}

/*

	SHANNON WAVELET

*/
std::vector<cv::Mat> FSTHM::calculateShannonWavelets(const std::vector<cv::Mat>& images) {
	// Convert to grayscale
	std::vector<cv::Mat> grayscale_images = convertToGrayscale(images);

	// Create the vector that will contain the wavelets
	std::vector<cv::Mat> wavelets(grayscale_images.size());

	for (size_t i = 0; i < grayscale_images.size(); i++) {
		// Original image size
		int orig_rows = grayscale_images[i].rows;
		int orig_cols = grayscale_images[i].cols;

		// Expand the image to the next power of 2 (optimal for FFT)
		cv::Mat padded_image;
		int padded_rows = cv::getOptimalDFTSize(orig_rows);
		int padded_cols = cv::getOptimalDFTSize(orig_cols);
		cv::copyMakeBorder(grayscale_images[i], padded_image, 0, padded_rows - orig_rows, 0, padded_cols - orig_cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

		// Perform FFT
		cv::Mat planes[] = { cv::Mat_<float>(padded_image), cv::Mat::zeros(padded_image.size(), CV_32F) };
		cv::Mat complex_image;
		cv::merge(planes, 2, complex_image);
		cv::dft(complex_image, complex_image);

		// Generate Shannon wavelet filter in frequency domain
		cv::Mat filter = generateShannonFilter(complex_image.size());

		// Apply the Shannon wavelet filter
		cv::Mat filtered_image;
		applyFrequencyFilter(complex_image, filter, filtered_image);

		// Perform inverse FFT
		cv::Mat inverse_planes[] = { cv::Mat::zeros(padded_image.size(), CV_32F), cv::Mat::zeros(padded_image.size(), CV_32F) };
		cv::idft(filtered_image, complex_image);
		cv::split(complex_image, inverse_planes);
		cv::Mat result;
		cv::magnitude(inverse_planes[0], inverse_planes[1], result);

		// Crop the image back to the original size
		wavelets[i] = result(cv::Rect(0, 0, orig_cols, orig_rows)).clone();
	}

	return wavelets;
}



/*

	FUNCTION THAT ALIGN THE IMAGES FOR A BETTER RESULT

*/
cv::Mat FSTHM::alignImages(const cv::Mat& image1, const cv::Mat& image2, const std::string& featureType = "ORB") {
	// Validate input images
	if (image1.empty() || image2.empty()) {
		throw std::invalid_argument("Input images must not be empty.");
	}

	// Initialize feature detector and descriptor extractor
	cv::Ptr<cv::Feature2D> featureExtractor;
	if (featureType == "ORB") {
		featureExtractor = cv::ORB::create();
	}
	else if (featureType == "SIFT") {
		featureExtractor = cv::SIFT::create();
	}
	else {
		throw std::invalid_argument("Invalid feature type. Supported types: 'ORB', 'SIFT'.");
	}

	// Detect keypoints and compute descriptors
	std::vector<cv::KeyPoint> keypoints1, keypoints2;
	cv::Mat descriptors1, descriptors2;
	featureExtractor->detectAndCompute(image1, cv::noArray(), keypoints1, descriptors1);
	featureExtractor->detectAndCompute(image2, cv::noArray(), keypoints2, descriptors2);

	// Match descriptors using BFMatcher or FLANN-based matcher
	std::vector<cv::DMatch> matches;
	if (featureType == "ORB") {
		cv::BFMatcher matcher(cv::NORM_HAMMING);
		matcher.match(descriptors1, descriptors2, matches);
	}
	else if (featureType == "SIFT") {
		cv::FlannBasedMatcher matcher;
		matcher.match(descriptors1, descriptors2, matches);
	}

	// Sort matches by distance
	std::sort(matches.begin(), matches.end(), [](const cv::DMatch& a, const cv::DMatch& b) {
		return a.distance < b.distance;
		});

	// Keep only the top matches
	const int numGoodMatches = static_cast<int>(0.15 * matches.size());
	matches.erase(matches.begin() + numGoodMatches, matches.end());

	// Extract matched keypoints
	std::vector<cv::Point2f> points1, points2;
	for (const auto& match : matches) {
		points1.push_back(keypoints1[match.queryIdx].pt);
		points2.push_back(keypoints2[match.trainIdx].pt);
	}

	// Find homography or affine transformation
	cv::Mat transformation;
	if (points1.size() >= 4) { // At least 4 points required for homography
		transformation = cv::findHomography(points2, points1, cv::RANSAC);
	}
	else {
		throw std::runtime_error("Not enough matches to compute transformation.");
	}

	// Align the second image
	cv::Mat alignedImage;
	cv::warpPerspective(image2, alignedImage, transformation, image1.size());

	return alignedImage;
}



/*

	FUNCTION THAT CREATES THE RESULTING IMAGE BY USING SINGLE PIXELS TO SEARCH FOR FOCUS

*/
cv::Mat FSTHM::createSinglePixelFocusStackedImage(const std::vector<cv::Mat>& images, std::vector<cv::Mat> focus_maps, bool use_alignment) {
	// Validate input
	if (images.empty() || focus_maps.empty() || images.size() != focus_maps.size()) {
		throw std::invalid_argument("Number of images and focus maps must be the same and non-zero.");
	}

	// Align images if requested
	std::vector<cv::Mat> aligned_images = images;
	if (use_alignment) {
		for (size_t i = 1; i < images.size(); ++i) {
			aligned_images[i] = alignImages(images[0], images[i], "ORB");
		}
	}

	// Resize focus maps to match the aligned image size
	cv::Size image_size = aligned_images[0].size();
	for (auto& focus_map : focus_maps) {
		if (focus_map.size() != image_size) {
			cv::resize(focus_map, focus_map, image_size, 0, 0, cv::INTER_LINEAR);
		}
	}

	// Create the output image (initialized to zeros)
	cv::Mat result(image_size, CV_8UC3, cv::Scalar(0, 0, 0));

	// Iterate through every pixel
	for (int y = 0; y < image_size.height; ++y) {
		for (int x = 0; x < image_size.width; ++x) {
			float max_focus_value = -1.0f;
			int best_image_index = -1;

			// Find the best focused image for this pixel
			for (size_t i = 0; i < focus_maps.size(); ++i) {
				float focus_value = focus_maps[i].at<float>(y, x);
				if (focus_value > max_focus_value && aligned_images[i].at<cv::Vec3b>(y, x) != cv::Vec3b(0, 0, 0)) {
					max_focus_value = focus_value;
					best_image_index = static_cast<int>(i);
				}
			}

			// Assign the pixel from the best-focused image
			if (best_image_index >= 0) {
				result.at<cv::Vec3b>(y, x) = aligned_images[best_image_index].at<cv::Vec3b>(y, x);
			}
		}
	}

	return result;
}



/*

	FUNCTION THAT CREATES THE RESULTING IMAGE BY USING PATCHES TO SEARCH FOR FOCUS

*/
cv::Mat FSTHM::createPatchesFocusStackedImage(const std::vector<cv::Mat>& images, std::vector<cv::Mat> focus_maps, int patch_size, bool use_alignment) {
	// Validate input
	if (images.empty() || focus_maps.empty() || images.size() != focus_maps.size()) {
		throw std::invalid_argument("Number of images and focus maps must be the same and non-zero.");
	}

	// Align images if requested
	std::vector<cv::Mat> aligned_images = images;
	if (use_alignment) {
		for (size_t i = 1; i < images.size(); ++i) {
			aligned_images[i] = alignImages(images[0], images[i], "ORB");
		}
	}

	// Resize focus maps to match the aligned image size and normalize
	cv::Size image_size = aligned_images[0].size();
	for (auto& focus_map : focus_maps) {
		if (focus_map.size() != image_size) {
			cv::resize(focus_map, focus_map, image_size, 0, 0, cv::INTER_LINEAR);
		}
		cv::normalize(focus_map, focus_map, 0, 1, cv::NORM_MINMAX); // Normalize focus map to [0, 1]
	}

	// Smooth focus maps using a patch-based average
	for (auto& focus_map : focus_maps) {
		cv::boxFilter(focus_map, focus_map, -1, cv::Size(patch_size, patch_size)); // Patch-based averaging
	}

	// Create the result image and the max focus map
	cv::Mat result(image_size, CV_8UC3, cv::Scalar(0, 0, 0));
	cv::Mat max_focus_map(image_size, CV_32F, cv::Scalar(-1.0f)); // Max focus value per pixel

	// Iterate through all images
	for (size_t i = 0; i < aligned_images.size(); ++i) {
		// Convert the aligned image to grayscale for black pixel check
		cv::Mat gray_image;
		cv::cvtColor(aligned_images[i], gray_image, cv::COLOR_BGR2GRAY);

		// Create a binary mask where the image is not black
		cv::Mat non_black_mask = (gray_image > 0);

		// Create the mask for the focus map comparison
		cv::Mat current_mask = (focus_maps[i] > max_focus_map);
		cv::bitwise_and(current_mask, non_black_mask, current_mask); // Combine with non-black mask

		// Update the max focus map only where the current mask is true
		for (int y = 0; y < image_size.height; ++y) {
			for (int x = 0; x < image_size.width; ++x) {
				if (current_mask.at<uchar>(y, x)) {
					max_focus_map.at<float>(y, x) = focus_maps[i].at<float>(y, x);
					result.at<cv::Vec3b>(y, x) = aligned_images[i].at<cv::Vec3b>(y, x);
				}
			}
		}
	}

	return result;
}


/*

	FUNCTION THAT CONVERTS THE FOCUS MAP TO CV_32F

*/
std::vector<cv::Mat> FSTHM::convertFocusMapsTo32F(const std::vector<cv::Mat>& focus_maps) {
	// Vector to store the converted focus maps
	std::vector<cv::Mat> converted_maps;

	for (const auto& focus_map : focus_maps) {
		cv::Mat converted;
		if (focus_map.type() != CV_32F) {
			focus_map.convertTo(converted, CV_32F, 1.0 / 255.0); // Normalize and convert to CV_32F
		}
		else {
			converted = focus_map.clone(); // Already CV_32F, just clone it
		}
		converted_maps.push_back(converted);
	}

	return converted_maps;
}



/*

	FUNCTION THAT SAVES THE RESULT AS A FILE

*/
void FSTHM::saveResult(const cv::Mat& image, const std::string& filename, const std::string& output_path) {


	//first we check if the image provided is empty if not we can continue
	if (image.empty()) {
		std::cerr << "the provided image is empty" << std::endl;
	}

	//we first build the final output path
	std::string final_path = output_path + "/" + filename;
	try {
		//then we can proceed to save the image 
		if (cv::imwrite(final_path, image)) {
			std::cout << "file saved succesfully" << std::endl;
		}
		else {
			std::cerr << "error saving the file to" << final_path << std::endl;
		}
	}
	catch (...) {
		std::cout << "error while trying to save the image" << std::endl;
	}

}
