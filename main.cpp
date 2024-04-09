// FCAI – Structured Programming – 2024 - Assignment 2
// Program Name: CS112_A3_Part1_S17-S18_20230461_20230584_20230421.cpp
// Program Description: This program develops an image processing tool that can apply different filters (changes) to a given image of any size and the four popular image formats.
// Author1 and ID and Group: Helana Wageh Edward Soltan - 20230461 - Group B - S17
// Author2 and ID and Group: Malak Reda Mohamed Esmail - 20230584 - Group B - S18
// Author3 and ID and Group: Menna Talla Gamal Mahmoud - 20230421 - Group B - S18
// Teaching Assistant: Ahmed Foad
// Who did what: Menna Talla Gamal: filter 1,4,7,10 and the main menu
// Malak Reda: filter 3,4
// Helana Wageh: filter 5

#include <iostream>
#include "image_class.h"
#include <string>
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
// Function for merge images
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
    Image* outputImage; // Pointer to the output image
    if (option==1) {
        // Determine the dimensions of the new image
        int maxWidth = max(image.width, image2.width);
        int maxHeight = max(image.height, image2.height);

        // Create a new Image object with the maximum dimensions
        outputImage = new Image(maxWidth, maxHeight);

        // Loop over each pixel in the new image
        for (int i = 0; i < maxWidth; ++i) {
            for (int j = 0; j < maxHeight; ++j) {
                // For each pixel, if it is within the dimensions of the original images,
                // calculate the average of the corresponding pixels in the input images
                for (int k = 0; k < 3; ++k) {
                    if (i < image.width && j < image.height && i < image2.width && j < image2.height) {
                        (*outputImage)(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                    } else if (i < image.width && j < image.height) {
                        (*outputImage)(i, j, k) = image(i, j, k);
                    } else if (i < image2.width && j < image2.height) {
                        (*outputImage)(i, j, k) = image2(i, j, k);
                    } else {
                        (*outputImage)(i, j, k) = 0; // Fill the rest of the image with black
                    }
                }
            }
        }

        // Replace the first image with the merged image
        image = *outputImage;
    }else if (option==2) {
        // Merge the common area of the smaller width and the smaller height
        // This is the same as the original function
        // Determine the dimensions of the common area
        int commonWidth = min(image.width, image2.width);
        int commonHeight = min(image.height, image2.height);

        // Create a new Image object with the maximum dimensions
        outputImage = new Image(commonWidth, commonHeight);

        // Loop over each pixel in the new image
        for (int i = 0; i < commonWidth; ++i) {
            for (int j = 0; j < commonHeight; ++j) {
                // For each pixel, calculate the average of the corresponding pixels in the input images
                for (int k = 0; k < 3; ++k) {
                    (*outputImage)(i, j, k) = (image(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }

        // Replace the first image with the merged image
        image = *outputImage;
    }else{
        cout << "Invalid option. Please enter 1 or 2.\n";
    }
}


//__________________________________________
// Function for Detect Image Edges

//__________________________________________
// Function for

//__________________________________________
// Function for

//__________________________________________
// Function for

//__________________________________________
// Function for

//__________________________________________
// Function for

//__________________________________________
// Function for

//__________________________________________
// Function for

//__________________________________________
// Function for

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
                 << "13-                            14-                           15- \n";
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

                } else if (filter == 6) {

                } else if (filter == 7) {
                    // Call the darkenAndLightenImage function
                    darkenAndLightenImage(image);

                } else if (filter == 8) {

                } else if (filter == 9) {
                    // Call the addFrameToPicture function
                    int frameChoice;
                    addFrameToPicture(image, frameChoice);

                } else if (filter == 10) {
                    // Call the detectImageEdges function


                } else if (filter == 11) {

                } else if (filter == 12) {

                } else if (filter == 13) {

                } else if (filter == 14) {

                } else if (filter == 15) {

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