
# Hybrid-Cryptosystem

## Structure

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



