
# Hybrid-Cryptosystem

## Structure

The purpose of this program is to encrypt and decrypt images. Please note that only .bmp images have been tested.

The program will first allow you to choose between encryption and a time trial.

If encryption is chosen, you can select which public algorithm you want to encrypt with, what private algorithm, and what mode of operation.
You may then choose to use your own image via inputting the path, or use a default image via d1, d2, and d3.
The program will then proceed to encrypt and decrypt the image for you, showing you both. You may save either by pressing s when they first appear.

If time trial is chosen, you will have the option to choose between running encryption and decryption on 1, 2, or 3 of the test images.
It will then run and report back the time taken for encryption and decryption on them.

The code is separated into 5 files: Hybrid Crypto Main.cpp is the main driver of the code, dealing with user interaction and calling the encryption objects.
The other 4 files are header files containing the code for each of the encryption algorithms, which may be called to run as objects.

ElGamal_.h is called by the driver to use a key size of 256 bits, but could be increased in the code.

DES_.h, TripDES_.h, and AES_.h receive their private keys after it has been encrypted by ElGamal, needing 64-, 192- and 256-bit keys, respectively.
Each private algorithm will divide up the given image into its 3 color channels and change the channels into flat arrays.
It will then reshape the color arrays to be compatible with the set block size, and then perform encryption and decryption on each block.
Both the ciphertext and plaintext are saved until the end so that the encrypted and decrypted color channels may be put together to show the encrypted and decrypted images.


## Installation

OpenCV and Crypto++ libraries are required.

### OpenCV

Download from https://sourceforge.net/projects/opencvlibrary/files/ (I used version 4.7.0) and extract.<br>
To set up with Visual Studio:<br>
1. In VS, go to Project -> Properties
2. Change Platform to Active(x64)
3. Go to Configuration Properties -> Debugging -> Merge Environment, change to Yes
4. Go to C/C++ -> General -> Additional Include Directories, edit to include the path to opencv > build > include
5. Go to Linker -> General -> Additional Library Directories, edit to include the path to opencv > build > x64 > vc15 > bin and > lib
6. Go to Linker -> General -> Use Library Dependency Inputs, change to Yes
7. Go to Linker -> Input -> Additional Dependencies, edit and type in opencv_world460d.lib
8. In opencv > build > x64 > vc15 > bin, copy opencv_world460d.dll and put it into the same directory as [solution directory] > x64 > Debug (or just > Debug there isn't an x64 folder). You may need to run the program once for this to show up.

### Crypto++

Download from https://www.cryptopp.com/#download (I used 8.7.0) and extract to the solution directory, it will not work if it is extracted elsewhere.<br>
To set up with Visual Studio:<br>
1. In VS, go to Project -> Properties
2. Change Platform to Active(x64)
3. Go to Configuration Properties -> Debugging -> Merge Environment, change to Yes
4. Go to C/C++ -> General -> Additional Include Directories, edit to include the path to the cryptopp870 folder
5. Go to Linker -> General -> Additional Library Directories, edit to include the path to cryptopp870 > x64 > Output > Debug and > Release
6. Go to Linker -> General -> Use Library Dependency Inputs, change to Yes
7. Go to Linker -> Input -> Additional Dependencies, edit and type in cryptlib.lib
8. Exit the Project Properties menu
9. Go to Solution Explorer, right-click on cryptlib, open Properties
10. Change Platform to Active(x64)
11. Go to Configuration Properties -> General -> Configuration Type, change to Static library (.lib)
12. Go to Configuration Properties -> Debugging -> Merge Environment, change to Yes
13. Go to C/C++ -> Code Generation -> Runtime Library, ensure it is set to Multi-threaded Debug DLL (/MDd)
14. Exit the Project Properties menu
    1. IF you had to change the box in Step 13, follow the next steps, otherwise you should be good
    2. In VS, go to Build -> Batch Build
    3. Check the boxes for (cryptlib, Debug, x64) and (cryptlib, Release, x64), do not check any others
    4. Select Clean
    5. Once finished, go back and ensure those records are selected again
    6. Select Build



