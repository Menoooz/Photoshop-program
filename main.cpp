
// FCAI – Structured Programming – 2024 - Assignment 2
// Program Name: CS112_A3_Part2B_S17-S18_20230461_20230584_20230421.cpp
// Program Description: This program develops an image processing tool that can apply different filters (changes) to a given image of any size and the four popular image formats.
// Author1 and ID and Group: Helana Wageh Edward Soltan - 20230461 - Group B - S17
// Author2 and ID and Group: Malak Reda Mohamed Esmail - 20230584 - Group B - S18
// Author3 and ID and Group: Menna Talla Gamal Mahmoud - 20230421 - Group B - S18
// Teaching Assistant: Ahmed Foad
// Who did what: Menna Talla Gamal: filters 1,4,7,10 and the main menu (bonus: filter 17: Samurai infrared photography filter , filter 15: Wano villagers old Den Den Mushi)
//               Malak Reda: filters 3,6,9,12 (bonus: filter 16: Purple effect)
//               Helana Wageh: filters 2,5,8,11
//Gihub accounts: Menna :https://github.com/Menoooz
//                Malak :https://github.com/malakreda
//                Hilana:https://github.com/H-Edward39

#include <iostream>
#include <vector>
#include "image_class.h"
#include <string>
#include <cmath>
#include <limits> // For numeric_limits
#include <algorithm> // for find
using namespace std;

// Function for Grayscale Conversion
void grayscaleConversion(Image& image) {
    // Loop over each pixel in the image
    for(int i=0; i<image.width ;i++){
        for(int j=0; j<image.height ;j++){
            // Calculate the average of the RGB values of the current pixel
            unsigned int avg=0;
            for(int k=0; k<3 ;k++){
                avg+=image(i,j,k);
            }
            avg/=3;
            // Set the new value for the current pixel
            for(int k=0; k<3 ;k++){
                image(i,j,k)=avg;
            }}}}
//__________________________________________
// Function for Darken and Lighten Image
void darkenAndLightenImage(Image& image) {
    int light;
    while (true) {
        // Display menu
        cout << "What do you want to do? \n"
             << "1- make the image darker\n"
             << "2- make the image lighter\n";
        // Check if input is valid
        if (!(cin >> light)) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue; // Skip the rest of the loop iteration
        }
        // Check user's choice
        if (light == 1) {
            // Darken the pixel by reducing its intensity by 50%
            // To achieve this, we multiply the intensity by 0.5
            for(int i=0; i<image.width ;i++){
                for(int j=0; j<image.height ;j++){
                    for(int k=0; k<3 ;k++){
                        image(i, j, k) = max(0.0, image(i, j, k) * 0.5); // Darken
                    }}}
            break; // Exit the loop
        } else if (light == 2) {
            // Lighten the pixel by increasing its intensity by 50%
            // To achieve this, we multiply the intensity by 1.5
            for(int i=0; i<image.width ;i++){
                for(int j=0; j<image.height ;j++){
                    for(int k=0; k<3 ;k++){
                        image(i, j, k) = min(255.0, image(i, j, k) * 1.5); // Lighten
                    }}}
            break; // Exit the loop
        } else {
            cout << "Invalid input. Please enter 1 or 2.\n";
        }}}
//__________________________________________
// Function for Invert Image
void invertImage(Image& image) {
    // Loop over each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Invert the RGB values of the current pixel
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }}}}
//__________________________________________
// Function for Adding a Frame to the Picture
void addFrameToPicture(Image& image, int frameChoice) {
    // Define frame width (number of pixels)
    int frameWidth = image.width * 0.02; // Set frame width to 2% of image width
    cout << "Choose frame type:\n";
    cout << "1. Simple Frame\n";
    cout << "2. Fancy Frame\n";
    while (true) {
        cin >> frameChoice;
        // Check if the user's input is valid
        if (cin.fail() || frameChoice < 1 || frameChoice > 2) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue; // Skip the rest of the loop iteration
        }
        if (frameChoice == 1) {
            // Simple Frame
            // Make the user to choose frame color
            int colorChoice;
            cout << "Choose frame color:\n"<< "1. Red\n"<< "2. Green\n"<< "3. Blue\n"<< "4. Yellow\n"<< "5. Orange\n"<<"6. Purple\n";
            while (true) {
                cin >> colorChoice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter  a number from 1 to 6.\n";
                    continue;
                }
                if (colorChoice >= 1 && colorChoice <= 6) {
                    break;
                } else {
                    cout << "Invalid choice. Please enter a number from 1 to 6.\n";
                }}
            // Define frame color based on user's choice
            int frameColor[3] = {0, 0, 0}; // Initialize to black
            switch (colorChoice) {
                case 1: // Red
                    frameColor[0] = 255;
                    break;
                case 2: // Green
                    frameColor[1] = 255;
                    break;
                case 3: // Blue
                    frameColor[2] = 255;
                    break;
                case 4: // Yellow
                    frameColor[0] = 255; frameColor[1] = 255;
                    break;
                case 5: // Orange
                    frameColor[0] = 255; frameColor[1] = 165; frameColor[2] = 0;
                    break;
                case 6: // Purple
                    frameColor[0] = 128; frameColor[1] = 0; frameColor[2] = 128;
                    break;
                default:
                    cout << "Invalid choice. Using default color (black).\n";
                    break;
            }
            // Add frame to the image
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    if (i < frameWidth || i >= image.width - frameWidth || j < frameWidth || j >= image.height - frameWidth) {
                        // If within frame border
                        for (int k = 0; k < 3; ++k) {
                            image(i, j, k) = frameColor[k];
                        }}}}
        } else if (frameChoice == 2) {
            // Fancy Frame
            // Define frame colors
            int frameColors[4][3] = {
                    {0, 255, 0},    // Green
                    {0, 0, 255},    // Blue
                    {255, 255, 0}   // Yellow
            };
            // Add frame to the image
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    if (i < frameWidth || i >= image.width - frameWidth || j < frameWidth || j >= image.height - frameWidth) {
                        // If within frame border
                        // Determine frame color based on position
                        int colorIndex = ((i / 20) + (j / 20)) % 4;
                        int frameColor[3] = {frameColors[colorIndex][0], frameColors[colorIndex][1], frameColors[colorIndex][2]};

                        for (int k = 0; k < 3; ++k) {
                            image(i, j, k) = frameColor[k];
                        }}}}
        }  break; // Exit the loop once a valid frameChoice is entered
    }}
//__________________________________________
// Function for Black and White
void blackAndWhite(Image& image) {
    int threshold = 128; // Set the threshold value(the threshold is used to determine whether a pixel should be turned black or white.)
    //The value 128 is used as a threshold in the black and white filter because it's the middle point in the grayscale range (0-255).
    // Loop over each pixel in the image
    for(int i=0; i<image.width ;i++){
        for(int j=0; j<image.height ;j++){
            // Calculate the grayscale value of the current pixel
            // This is done by averaging the red, green, and blue values of the pixel
            int pixelValue = 0;
            for(int k=0; k<3 ;k++){
                pixelValue += image(i,j,k);
            }
            pixelValue /= 3; // Average to get grayscale intensity
            // Set the new value for the current pixel
            // If the grayscale value is less than the threshold, set the pixel to black
            // If the grayscale value is greater than or equal to the threshold, set the pixel to white
            for(int k=0; k<3 ;k++){
                if (pixelValue < threshold) {
                    image(i,j,k) = 0; // If the grayscale value is less than the threshold, set the pixel to black
                } else {
                    image(i,j,k) = 255; // If the grayscale value is greater than or equal to the threshold, set the pixel to white
                }}}}}
//__________________________________________
// Functions for merging images
// Function for resizing an image
void resize(Image& image,int newWidth,int newHeight) {
    // Create a temporary buffer to store the resized image data
    unsigned char* tempData = new unsigned char[newWidth * newHeight * 3];
    // Loop over each pixel in the new image
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            // Calculate the corresponding coordinates in the original image
            double oldI = i * static_cast<double>(image.width) / newWidth;
            double oldJ = j * static_cast<double>(image.height) / newHeight;
            // Find the coordinates of the four pixels to interpolate in the original image
            int x1 = static_cast<int>(oldI);
            int y1 = static_cast<int>(oldJ);
            int x2 = min(static_cast<int>(oldI) + 1, image.width - 1);
            int y2 = min(static_cast<int>(oldJ) + 1, image.height - 1);
            // Loop over each color channel
            for (int k = 0; k < 3; ++k) {
                // Perform bilinear interpolation of the color
                double q11 = image(x1, y1, k);
                double q12 = image(x1, y2, k);
                double q21 = image(x2, y1, k);
                double q22 = image(x2, y2, k);

                double r1 = ((x2 - oldI) * q11 + (oldI - x1) * q21) / (x2 - x1);
                double r2 = ((x2 - oldI) * q12 + (oldI - x1) * q22) / (x2 - x1);

                tempData[(j * newWidth + i) * 3 + k] = (y2 - oldJ) * r1 + (oldJ - y1) * r2;
            }}}
    // Delete the old image data
    delete[] image.imageData;
    // Assign the new image data and dimensions to the image
    image.imageData = tempData;
    image.width = newWidth;
    image.height = newHeight;
}
// Function for merging two images
void mergeImages(Image& image, Image& image2, int option) {
    // Ask the user to choose the merge option
    cout << "Choose the merge option:\n"
         << "1- Resize the smaller image or both images to the biggest height and width and then merge\n"
         << "2- Merge the common area of the smaller width and the smaller height\n";
    while (true) {
        cin >> option;
        // Check if the user's input is valid
        if (!cin.fail() && (option == 1 || option == 2)) {
            break; // Exit the loop if the input is valid
        }
        cout << "Invalid input. Please enter 1 or 2.\n";
        cin.clear(); // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }
    if (option == 1) {
        // Determine the dimensions of the new image
        int newWidth = max(image.width, image2.width);
        int newHeight = max(image.height, image2.height);
        // Resize the images
        resize(image, newWidth, newHeight); // Resize the first image
        resize(image2, newWidth, newHeight); // Resize the second image
        // Loop over each pixel in the new image
        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                // For each pixel, if it is within the dimensions of the original images,
                // calculate the average of the corresponding pixels in the input images
                for (int k = 0; k < 3; ++k) {
                    if (i < image.width && j < image.height && i < image2.width && j < image2.height) {
                        (image)(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                    } else if (i < image.width && j < image.height) {
                        (image)(i, j, k) = image(i, j, k);
                    } else if (i < image2.width && j < image2.height) {
                        (image)(i, j, k) = image2(i, j, k);
                    } else {
                        (image)(i, j, k) = 0; // Fill the rest of the image with black
                    }}}}
    } else if (option == 2) {
        // Determine the dimensions of the common area
        int newWidth = min(image.width, image2.width);
        int newHeight = min(image.height, image2.height);
        // Resize the images
        resize(image, newWidth, newHeight); // Resize the first image
        resize(image2, newWidth, newHeight); // Resize the second image
        // Loop over each pixel in the new image
        for (int i = 0; i < newWidth; ++i) {
            for (int j = 0; j < newHeight; ++j) {
                // For each pixel, calculate the average of the corresponding pixels in the input images
                for (int k = 0; k < 3; ++k) {
                    (image)(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                }}}
    } else {
        cout << "Invalid option. Please enter 1 or 2.\n";
    }}

//__________________________________________
// Function for Detect Image Edges
void detectImageEdges(Image& image) {
    // Convert the image to grayscale
    grayscaleConversion(image);
    // Define the Sobel kernels
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Create a matrix to store the gradient magnitudes
    std::vector<std::vector<int>> gradients(image.width, std::vector<int>(image.height));
    // Apply the Sobel operator and calculate the gradient magnitudes
    int minGradient = std::numeric_limits<int>::max();
    int maxGradient = std::numeric_limits<int>::min();
    // Loop over each pixel in the image
    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {
            int gx = 0, gy = 0;
            // Apply the Sobel kernels to the pixel and its neighbors
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    gx += Gx[x + 1][y + 1] * image(i + x, j + y, 0);
                    gy += Gy[x + 1][y + 1] * image(i + x, j + y, 0);
                }}
            // Calculate the gradient magnitude
            int magnitude = sqrt(gx * gx + gy * gy);
            gradients[i][j] = magnitude;

            // Update the minimum and maximum gradients
            minGradient = std::min(minGradient, magnitude);
            maxGradient = std::max(maxGradient, magnitude);
        }}
    // Check if the minimum and maximum gradients are the same
    if (minGradient == maxGradient) {
        // If they are the same, set all pixel values to 0
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = 0;
                }}}
    } else {
        // If they are not the same, normalize the gradient magnitudes and set the pixel values in the result image
        for (int i = 1; i < image.width - 1; ++i) {
            for (int j = 1; j < image.height - 1; ++j) {
                int normalizedMagnitude = 255 * (gradients[i][j] - minGradient) / (maxGradient - minGradient);
                for (int k = 0; k < 3; ++k) {
                    image(i, j, k) = normalizedMagnitude;
                }}}}
    // Invert the colors to highlight the edges
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }}}

//__________________________________________
// Function for resizing images
void resizeImage(Image& image) {
    int choice;
    // Prompt the user to choose the resize option
    cout << "Choose the resize option:\n"
         << "1- Enter new dimensions\n"
         << "2- Enter a ratio of reduction or increase\n";
    while (true) {
        cin >> choice;
        // Check if the user's input is valid
        if (!cin.fail() && (choice == 1 || choice == 2)) {
            break; // Exit the loop if the input is valid
        }
        // If the input is invalid, prompt the user to enter a valid input
        cout << "Invalid input. Please enter 1 or 2.\n";
        cin.clear(); // Clear the fail state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
    }
    int newWidth, newHeight;
    double ratio;
    // If the user chooses to enter new dimensions
    if (choice == 1) {
        cout << "Enter new width: ";
        cin >> newWidth;
        cout << "Enter new height: ";
        cin >> newHeight;
    }
        // If the user chooses to enter a ratio of reduction or increase
    else if (choice == 2) {
        cout << "Enter ratio: ";
        cin >> ratio;
        // Calculate the new dimensions based on the ratio
        newWidth = static_cast<int>(image.width * ratio);
        newHeight = static_cast<int>(image.height * ratio);
    }
        // If the user enters an invalid choice
    else {
        cout << "Invalid choice. Please enter 1 or 2.\n";
        return;
    }
    // Create a temporary buffer to store the resized image data
    unsigned char* tempData = new unsigned char[newWidth * newHeight * 3];
    // Loop over each pixel in the new image
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            // Calculate the corresponding coordinates in the original image
            double oldI = i * static_cast<double>(image.width) / newWidth;
            double oldJ = j * static_cast<double>(image.height) / newHeight;

            // Find the coordinates of the four pixels to interpolate in the original image
            int x1 = static_cast<int>(oldI);
            int y1 = static_cast<int>(oldJ);
            int x2 = min(static_cast<int>(oldI) + 1, image.width - 1);
            int y2 = min(static_cast<int>(oldJ) + 1, image.height - 1);

            // Loop over each color channel
            for (int k = 0; k < 3; ++k) {
                // Perform bilinear interpolation of the color
                double q11 = image(x1, y1, k);
                double q12 = image(x1, y2, k);
                double q21 = image(x2, y1, k);
                double q22 = image(x2, y2, k);

                double r1 = ((x2 - oldI) * q11 + (oldI - x1) * q21) / (x2 - x1);
                double r2 = ((x2 - oldI) * q12 + (oldI - x1) * q22) / (x2 - x1);

                tempData[(j * newWidth + i) * 3 + k] = (y2 - oldJ) * r1 + (oldJ - y1) * r2;
            }}}
    // Delete the old image data
    delete[] image.imageData;
    // Assign the new image data and dimensions to the image
    image.imageData = tempData;
    image.width = newWidth;
    image.height = newHeight;
}

//__________________________________________
// Function for Samurai infrared photography filter
void addInfraredFilter(Image& image) {
    // Define the shadow threshold
    int shadowThreshold = 100; // Not used in this function
    // Define the white threshold
    int whiteThreshold = 205; // Threshold for determining if a pixel is close to white
    // Loop over each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Set the red channel to maximum and slightly decrease the green and blue channels
            // This gives the image a red tint
            image(i, j, 0) = 255; // Red channel
            image(i, j, 1) = max(image(i, j, 1) - 50, 0); // Green channel
            image(i, j, 2) = max(image(i, j, 2) - 50, 0); // Blue channel
        }}
    // Invert the colors of the image
    invertImage(image);
    // Loop over each pixel in the image again
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Set the red channel to maximum and slightly decrease the green and blue channels
            // This gives the inverted image a red tint
            image(i, j, 0) = 255; // Red channel
            image(i, j, 1) = max(image(i, j, 1) - 50, 0); // Green channel
            image(i, j, 2) = max(image(i, j, 2) - 50, 0); // Blue channel
            // If the pixel is close to white (i.e., its red, green, and blue values are all greater than whiteThreshold),
            // increase its brightness by increasing each color channel by 50, but not above 255
            // This makes the white areas of the image even brighter
            if (image(i, j, 0) > whiteThreshold && image(i, j, 1) > whiteThreshold && image(i, j, 2) > whiteThreshold) {
                image(i, j, 0) = min(image(i, j, 0) + 50, 255); // Red channel
                image(i, j, 1) = min(image(i, j, 1) + 50, 255); // Green channel
                image(i, j, 2) = min(image(i, j, 2) + 50, 255); // Blue channel
            }}}}

//__________________________________________
// Function for Rotate Image
void rotateImage(Image& image, int rotationChoice) {
    cout << "Choose the rotation angle:\n"
         << "1. 90 degrees clockwise\n"
         << "2. 180 degrees clockwise\n"
         << "3. 270 degrees clockwise\n"
         << "Enter your choice (1,2 or 3): ";
    while (true) {
        if (!(cin >> rotationChoice) || rotationChoice < 1 || rotationChoice > 3) {
            cout << "Invalid input. Please enter 1,2 or 3.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        } else {
            break; // Exit the loop once a valid choice is entered
        }}
    unsigned char* tempData;
    int newWidth, newHeight;
    if (rotationChoice == 1 || rotationChoice == 3) {
        newWidth = image.height;
        newHeight = image.width;
        tempData = new unsigned char[newWidth * newHeight * 3];
    } else {
        newWidth = image.width;
        newHeight = image.height;
        tempData = new unsigned char[newWidth * newHeight * 3];
    }
    if (rotationChoice == 1) {
        for (int j = 0; j < image.height; ++j) {
            for (int i = 0; i < image.width; ++i) {
                for (int k = 0; k < image.channels; ++k) {
                    int new_i = image.height - 1 - j;
                    int new_j = i;
                    tempData[(new_j * newWidth + new_i) * 3 + k] = image.getPixel(i, j, k);
                }}}
    } else if (rotationChoice == 2) {
        for (int j = 0; j < image.height; ++j) {
            for (int i = 0; i < image.width; ++i) {
                for (int k = 0; k < image.channels; ++k) {
                    int new_i = image.width - 1 - i;
                    int new_j = image.height - 1 - j;
                    tempData[(new_j * newWidth + new_i) * 3 + k] = image.getPixel(i, j, k);
                }}}
    } else if (rotationChoice == 3) {
        for (int j = 0; j < image.height; ++j) {
            for (int i = 0; i < image.width; ++i) {
                for (int k = 0; k < image.channels; ++k) {
                    int new_i = j;
                    int new_j = image.width - 1 - i;
                    tempData[(new_j * newWidth + new_i) * 3 + k] = image.getPixel(i, j, k);
                }}}
    } else {
        cout << "Invalid choice!";
        return;
    }
    delete[] image.imageData;
    image.imageData = tempData;
    image.width = newWidth;
    image.height = newHeight;
}
//__________________________________________
// Function for Blur Filter
void blurImage(Image& image) {
    // Create a temporary buffer to store the blurred pixel values
    unsigned char* tempData = new unsigned char[image.width * image.height * 3];

// Iterate over each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int sum = 0;
                int count = 0;

                // Iterate over a 12-pixel square around the current pixel with blur radius = 8
                for (int x = i - 8; x <= i + 8; ++x) {
                    for (int y = j - 8; y <= j + 8; ++y) {
                        if (x >= 0 && x < image.width && y >= 0 && y < image.height) {
                            sum += image(x, y, k);
                            count++;
                        }
                    }
                }

                // Average the pixel values and store in the temporary buffer
                tempData[(j * image.width + i) * 3 + k] = sum / count;
            }
        }
    }

// Replace the original image data with the blurred data
    delete[] image.imageData;
    image.imageData = tempData;}

//__________________________________________
// Functions for Flipping the Image
// Function to perform horizontal flipping of the image
void HFLIP(Image& image) {
    int width = image.width; // Use width attribute directly
    int height = image.height; // Use height attribute directly
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width / 2; x++) {
            for (int c = 0; c < image.channels; ++c) { // Iterate over each color channel
                unsigned char temp = image.getPixel(x, y, c); // Use unsigned char instead of Color
                image.setPixel(x, y, c, image.getPixel(width - x - 1, y, c));
                image.setPixel(width - x - 1, y, c, temp);
            }}}}
// Function to perform vertical flipping of the image
void VFLIP(Image& image) {
    int width = image.width; // Use width attribute directly
    int height = image.height; // Use height attribute directly
    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < image.channels; ++c) { // Iterate over each color channel
                unsigned char temp = image.getPixel(x, y, c); // Use unsigned char instead of Color
                image.setPixel(x, y, c, image.getPixel(x, height - y - 1, c));
                image.setPixel(x, height - y - 1, c, temp);
            }}}}
// Function to flip the image
void FLIP(Image& image , int Fchoice){
    cout<<"Choose the flip direction:\n"
        <<"1- Horizontal flip\n"
        <<"2- Vertical flip\n"
        <<"Enter your choice:";
    while (true) {
        // Check if the user's input is valid
        if (!(cin >> Fchoice) || Fchoice < 1 || Fchoice > 2) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        } else {
            break; // Exit the loop once a valid choice is entered
        }}
    if (Fchoice==1){
        HFLIP(image);
    }
    else if (Fchoice==2){
        VFLIP(image);
    }
    else{
        cout << "Invalid input. Please enter 1 or 2.\n";
    }}

//__________________________________________
// Function for Purple night effect
void purpleeffect(Image& image) {
    // Define brightness factor
    float brightnessFactor = 1.2;
    // Loop over each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Retrieve original RGB values
            int originalR = image(i, j, 0);
            int originalG = image(i, j, 1);
            int originalB = image(i, j, 2);
            // Blend original RGB values with night purple color
            image(i, j, 0) = (originalR);
            image(i, j, 1) = (originalG * 0.7);
            image(i, j, 2) = (originalB);
            // Increase the RGB values by multiplying with the brightness factor
            image(i, j, 0) = min(255, static_cast<int>(image(i, j, 0) * brightnessFactor)); // Red
            image(i, j, 1) = min(255, static_cast<int>(image(i, j, 1) * brightnessFactor)); // Green
            image(i, j, 2) = min(255, static_cast<int>(image(i, j, 2) * brightnessFactor)); // Blue
        }}}

//__________________________________________
// Function for cropping the image
void cropImage(Image& image) {
    int x, y, width, height;
    bool validInput = false;

    while (!validInput) {
        cout << "Enter the starting point (x, y): ";
        cin >> x >> y;
        cout << "Enter the dimensions (width, height): ";
        cin >> width >> height;
        // Check if the entered coordinates are valid
        if (x < 0 || y < 0 || x >= image.width || y >= image.height) {
            cout << "Invalid starting point. Please try again.\n";
        }
        // Check if the entered dimensions are valid
        else if (width <= 0 || height <= 0 || x + width > image.width || y + height > image.height) {
            cout << "Invalid dimensions. Please try again.\n";
        }
        else {
            validInput = true;
        }}
    // Create a temporary buffer to store the cropped image data
    unsigned char* tempData = new unsigned char[width * height * 3];
    // Copy the pixels from the specified area in the original image to the temporary buffer
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < 3; ++k) {
                tempData[(j * width + i) * 3 + k] = image(x + i, y + j, k);
            }}}
    // Delete the old image data
    delete[] image.imageData;
    // Assign the temporary buffer to the image data and update the image dimensions
    image.imageData = tempData;
    image.width = width;
    image.height = height;
}

//__________________________________________
// Function for old TV effect
void noiseFilter(Image& image, double intensity) {
    // Seed the random number generator
    srand(time(0));

    // Loop over each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Loop over each color channel
            for (int k = 0; k < 3; ++k) {
                // Generate a random noise value
                int noise = (rand() % 256) - 128; // Random number in the range [-128, 127]

                // Add the noise to the current pixel value, scaled by the intensity
                int newValue = image(i, j, k) + static_cast<int>(noise * intensity);

                // Clamp the new value to the range [0, 255]
                newValue = max(0, min(255, newValue));

                // Assign the new value to the pixel
                image(i, j, k) = static_cast<unsigned char>(newValue);
            }
        }
    }
}
void oldTvFilter(Image& image) {
    // Apply a noise filter
    noiseFilter(image, 0.5); // 0.1 is the noise intensity, adjust as needed
}

//__________________________________________
// Function for Save Image
bool saveImage(Image& image, string& pathOrName) {
    cout << "Do you want to save in a new file or overwrite the old one?\n"
         << "1- Save in a new file\n"
         << "2- Overwrite the old one\n";
    while (true){
        int saveChoice;
        // Check if the user's input is valid
        if (!(cin >> saveChoice) || saveChoice < 1 || saveChoice > 2) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue; // Skip the rest of the loop iteration
        }
        string outputFilename;
        if (saveChoice == 1) { // If the user chooses to save in a new file
            cout << "Enter the new image name: ";
            cin >> outputFilename;
            string oldExtension = pathOrName.substr(pathOrName.find_last_of(".")); // Extract the extension from the old image name
            outputFilename += oldExtension; // Add the same extension as the old image
        } else if (saveChoice == 2) { // If the user chooses to overwrite the old file
            outputFilename = pathOrName; // Use the same name as the old image
        } else {
            cout << "Invalid input. Please enter 1 or 2.\n";
            continue; // Skip the rest of the loop iteration
        }
        // Save the image
        try {
            image.saveImage(outputFilename);
            cout << "Image has been saved as " << outputFilename << ".\n"<<"__________________________________________\n\n";
            return true; // Set the flag to true after saving the image
        } catch (const std::exception& e) { //exception handling block is used to catch and handle exceptions that might be thrown during the execution of the program.  In this specific case, it's catching exceptions of type std::exception or any of its derived classes.
            //When an exception is caught, the code inside the catch block is executed
            //This line is outputting an error message to the standard error stream (std::cerr). The e.what() part is calling the what() member function of the caught exception, which returns a null-terminated character sequence (a C-string) that can be used to identify the exception. This is typically a user-friendly error message.
            std::cerr << "Failed to save image: " << e.what() << '\n';
            return false; // This line is causing the function to immediately return with a value of false. In many programming conventions, returning a non-zero value from a function or program indicates that an error occurred.
        }}}
//__________________________________________


int main() {
    // Welcome message
    cout<<"___Welcome to 'Photoshop' program___\n";
    int choice;
    while (true) {
        // Display menu
        cout << "What do you want to do?\n"
             << "1-Edit an image\n"
             << "2-Exit the program\n";
        // Check if input is valid
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter 1 or 2.\n";
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            continue; // Skip the rest of the loop iteration
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline character
        // Check user's choice
        if (choice == 1) {
            string pathOrName;
            bool validInput = false;
            // Loop until the user enters a valid image name
            while (!validInput) {
                // Ask the user to enter the name or full path to the image
                cout << "Enter the name or full path to the image: ";
                getline(cin, pathOrName);
                try {
                    // Try to create an Image object with the entered image name or path
                    Image image(pathOrName);
                    validInput = true; // If the image opening is successful, exit the loop
                } catch (const std::exception& e) { // If the image opening fails, catch the exception and ask the user to enter a valid image name or path
                    cout << "Invalid image name or path. Please try again.\n";
                }
            }
            Image image(pathOrName); // Create an Image object with the chosen image
            int filter;
            bool imageSaved = false; // Add this line before the filter selection loop
            bool return_back = false; //using this bool to return back to the main menu after saving the image
            while (return_back == false){
            // Display menu
            cout << "Choose the filter: \n"
                 << "1 - Grayscale Conversion       2 - Black and White           3 - Invert Image                   4 - Merge Images\n"
                 << "5 - Flip Image                 6 - Rotate Image              7 - Darken and Lighten Image       8 - Crop Images\n"
                 << "9 - Adding a Frame             10- Detect Image Edges        11- Resizing Images                12- Blur Images\n"
                 << "13- Infrared Photography       14- Purple night effect       15- Old TV effect\n";
            while (true) {
                // Check if input is valid
                if (!(cin >> filter) || filter < 1 || filter > 15) {
                    cout << "Invalid input. Please enter a number from 1 to 15.\n";
                    cin.clear(); // Clear the fail state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    continue; // Skip the rest of the loop iteration
                }

                // Check user's choice
                if (filter == 1) {
                    // Call the grayscaleConversion function
                    grayscaleConversion(image);

                } else if (filter == 2) {
                    // Call the blackAndWhite function
                    blackAndWhite(image);

                } else if (filter == 3) {
                    // Call the invertImage function
                    invertImage(image);

                } else if (filter == 4) {
                    //allow the user to enter the second image
                    string pathOrName2;
                    bool validInput2 = false;
                    cout<<"Enter the second image\n";
                    while (!validInput2) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear newline character
                        // Ask the user to enter the name or full path to the image
                        cout << "Enter the name or full path to the second image: ";
                        getline(cin, pathOrName2);
                        try {
                            // Try to create an Image object with the entered image name or path
                            Image image2(pathOrName2);
                            validInput2 = true; // If the image opening is successful, exit the loop
                        } catch (const std::exception& e) {
                            cout << "Invalid image name or path. Please try again.\n";
                        }
                    }
                    Image image2(pathOrName2); // Create an Image object with the chosen image
                    int option;
                    // Call the mergeImages function with the chosen option
                    mergeImages(image, image2, option);

                } else if (filter == 5) {
                    // Call the Flipping function
                    int Fchoice;
                    FLIP( image , Fchoice);

                } else if (filter == 6) {
                    //Call the ratation function
                    int rotationChoice;
                    rotateImage( image , rotationChoice);

                } else if (filter == 7) {
                    // Call the darkenAndLightenImage function
                    darkenAndLightenImage(image);

                } else if (filter == 8) {
                    //Call the cropping the image function
                    Image croppedImage;
                    cropImage( image);

                } else if (filter == 9) {
                    // Call the addFrameToPicture function
                    int frameChoice;
                    addFrameToPicture(image, frameChoice);

                } else if (filter == 10) {
                    // Call the detectImageEdges function
                    detectImageEdges( image);

                } else if (filter == 11) {
                    //Call the resize function
                    resizeImage( image);

                } else if (filter == 12) {
                    //Call the Blur Filter function
                    blurImage(image);

                } else if (filter == 13) {
                    //Call the Samurai infrared photography filter
                    addInfraredFilter( image);

                } else if (filter == 14) {
                    //Call the Purple night effect function
                    purpleeffect( image);


                } else if (filter == 15) {
                    // Call the old TV filter function
                    oldTvFilter(image);

                }else {
                    cout << "Invalid input. Please enter a number from 1 to 15.\n";
                }
                // Prompt the user to either add another filter or save the image
                cout << "Do you want to add another filter or save the image?\n"
                     << "1- Add another filter\n"
                     << "2- Save the image\n";
                while (true) {
                    int choose;
                    // Check if the user's input is valid
                    if (!(cin >> choose) || choose < 1 || choose > 2) {
                        cout << "Invalid input. Please enter 1 or 2.\n";
                        cin.clear(); // Clear the fail state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                        continue; // Skip the rest of the loop iteration
                    }
                    if (choose == 1) { // If the user chooses to add another filter
                        break; // Exit the loop and display the filter menu again

                    } else if (choose == 2) { // If the user chooses to save the image
                        // Call the saveImage function
                        imageSaved = saveImage(image, pathOrName);
                        if (imageSaved) {
                            return_back = true;
                            break; // If the image is saved successfully, exit the loop
                        } else {
                            cout << "Failed to save image.\n";
                        }
                    } else {
                        cout << "Invalid input. Please enter 1 or 2.\n";
                    }}
                break;
            }}
        } else if (choice == 2) { //If the user chooses to exit the program
            cout << "Thanks for using the program. Goodbye!\n";
            break; // Exit the loop
        } else { //If the user enters an invalid choice
            cout << "Invalid input. Please enter 1 or 2.\n";
        }
    }


    return 0;
}
