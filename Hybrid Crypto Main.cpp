// Hybrid Crypto Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <iomanip>
#include "opencv2/core/utils/logger.hpp"    // logging output
#include "cryptopp870/integer.h"    // Integer
#include "cryptopp870/osrng.h"  // AutoPool rng
#include "cryptopp870/misc.h"   // Integer to String
#include "DES_.h"
#include "AES_.h"
#include "ElGamal_.h"
#include "TripDES_.h"

using namespace std;

/*
    * @param dec the decimal you want to convert
    * @param binary[] a holder of sufficient length for binary conversion
    * @param len the length of binary[]
    * @param rev if you want the binary to come out reversed or not
    */
void dec_to_binary(Integer dec, /*int binary[]*/vector<Integer>& binary, Integer len, bool rev) {
    Integer r;
    Integer q;

    //int* binary_rev = new int[len];
    vector< Integer> binary_rev(len.ConvertToLong());

    for (int i = 0; i < len; i++) {
        r = dec % 2;
        q = dec / 2;    // int division

        binary_rev[i] = r;
        dec = q;
    }

    if (rev == false) {
        Integer end = len - 1;
        for (int i = 0; i < len; i++) {
            binary[i] = binary_rev[end.ConvertToLong()];
            end--;
        }
    }
    else {
        for (int i = 0; i < len; i++) {
            binary[i] = binary_rev[i];
        }
    }

    //delete[] binary_rev;
}

/*
    * @param binary[] the binary to be converted
    * @param bin_len the length of the binary to be converted
    * @return the converted decimal number
    */
Integer binary_to_dec(/*int binary[]*/vector< Integer>& binary, int bin_len) {
    Integer dec = 0;

    for (int i = 0; i < bin_len; i++) {
        Integer power;
        //dec += binary[i] * int(pow(2, (bin_len - 1 - i)));
        dec += binary[i] * power.Power2(bin_len - 1 - i);
    }

    return dec;
}

/*
    * @param binary[] the binary to be converted
    * @param len the length of the binary to be converted
    * @return converted hexadecimal
    */
string binary_to_hex(/*int binary[]*/vector< Integer>& binary, int bin_len) {
    string hex = "";
    //int bin_group[16][4] = { 0 };
    int len = bin_len / 4;
    /*int** bin_group = new int* [len];
    for (int i = 0; i < len; i++) {
        bin_group[i] = new int[4];
    }*/
    vector<vector< Integer>> bin_group(len, vector< Integer>(4));

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 4; j++) {
            bin_group[i][j] = binary[(i * 4) + j];
        }
    }

    for (int i = 0; i < len; i++) {
        Integer num = binary_to_dec(bin_group[i], 4);

        if (num > 9) {
            num = num - 10 + 65;
            char num_hex = char(num.ConvertToLong());
            hex += num_hex;
        }
        else {
            hex += to_string(num.ConvertToLong());
        }
    }

    return hex;
}

bool pre_menu() {
    cout << "Would you like to test encryption or run a time trial with the default image?" << endl;
    cout << "...1 for encryption" << endl;
    cout << "...2 for time trial" << endl;
    int choice;
    cin >> choice;
    cout << endl << endl;

    if (choice == 1) {
        return 0;
    }
    else if (choice == 2) {
        return 1;
    }
    else {
        cout << "Invalid choice, choosing time trial." << endl << endl;
        return 1;
    }
}

int chrono_menu() {
    int option;
    cout << "Which images to test?" << endl;
    cout << "...1 for the small image" << endl;
    cout << "...2 for the small and medium images" << endl;
    cout << "...3 for the small, medium, and large images" << endl;
    cin >> option;

    if (1 > option || option > 3) {
        cout << "Invalid choice, selecting small image only.";
        option = 1;
    }

    cout << endl << endl;
    return option;
}

void main_menu(int &pub, int &priv, int &mode, string &impath) {
    cout << "Choose your public encryption algorithm..." << endl;
    cout << "...1 for ElGamal" << endl;
    cin >> pub;

    if (pub != 1) {
        cout << "Invalid choice, choosing ElGamal" << endl;
        pub = 1;
    }

    cout << endl << "Choose your private encryption algorithm..." << endl;
    cout << "...1 for DES" << endl;
    cout << "...2 for AES" << endl;
    cout << "...3 for 3DES" << endl;
    cin >> priv;

    if (priv != 1 && priv != 2 && priv !=3) {
        cout << "Invalid choice, choosing DES" << endl;
        priv = 1;
    }

    cout << endl << "Choose your mode of operation..." << endl;
    cout << "...1 for ECB" << endl;
    cout << "...2 for CBC" << endl;
    cin >> mode;

    if (mode != 1 && mode != 2) {
        cout << "Invalid choice, choosing DES" << endl;
        mode = 1;
    }

    cout << endl << "Enter your image's name with its path, or enter 'd1', 'd2', or 'd3' to use a default image." << endl;
    cin >> impath;

    cout << endl << endl;
}

string create_priv_key(int priv) {
    cout << "Generating private key..." << endl;

    string key_hex;
    int key_len = 0;
    AutoSeededRandomPool prng;
    Integer key_dec;

    if (priv == 1) {
        key_len = 64;
    }
    else if (priv == 2) {
        key_len = 256;
    }
    else if (priv == 3) {
        key_len = 192;
    }

    key_dec.Randomize(prng, key_len);
    vector<Integer> key_bin(key_len);
    dec_to_binary(key_dec, key_bin, key_len, false);
    key_hex = binary_to_hex(key_bin, key_len);

    cout << "..." << key_hex << endl << endl;
    return key_hex;
}

int main()
{
    utils::logging::setLogLevel(utils::logging::LogLevel::LOG_LEVEL_SILENT);    // do not show debug output

    bool time_trial = pre_menu();

    if (time_trial == 0) {
        int pub = 0;
        int priv = 0;
        int mode = 0;
        string impath;
        main_menu(pub, priv, mode, impath);

        string priv_key = create_priv_key(priv);
        string decoded_key;

        if (pub == 1) {
            cout << "Calling ElGamal" << endl;
            ElGamal_ eg(priv_key, 256);
            decoded_key = eg.ElGamal_main();
            cout << endl;
        }

        if (priv == 1) {
            //cout << "Calling DES" << endl;
            DES_ des(decoded_key, impath, mode, time_trial);
            cout << endl;
        }
        else if (priv == 2) {
            //cout << "Calling AES" << endl;
            AES_ aes(decoded_key, impath, mode, time_trial);
            cout << endl;
        }
        else if (priv == 3) {
            //cout << "Calling 3DES" << endl;
            string key_arr[3];

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 16; j++) {
                    key_arr[i] += decoded_key[(16 * i) + j];
                }
            }

            TripDES_ des3(key_arr, impath, mode, time_trial);
        }
    }
    else {
        int limit = chrono_menu();
        chrono::steady_clock::time_point beg[3][9];
        chrono::steady_clock::time_point end[3][9];
        chrono::steady_clock::time_point overall_beg[3];
        chrono::steady_clock::time_point overall_end[3];
        string trial[9] = {
                "ElGamal (64-bit msg)",
                "ElGamal (256-bit msg)",
                "ElGamal (192-bit msg)",
                "DES (ECB)",
                "DES (CBC)",
                "AES (ECB)",
                "AES (CBC)",
                "3DES (ECB)",
                "3DES (CBC)"
        };

        for (int d = 0; d < limit; d++) {

            string img_path;
            if (d == 0) {
                img_path = "d1";
            }
            else if (d == 1) {
                img_path = "d2";
            }
            else {
                img_path = "d3";
            }

            cout << "DEFAULT IMAGE " << d + 1 << endl;

            cout << "Clock has begun" << endl << endl;
            overall_beg[d] = chrono::steady_clock::now();

            /*cout << "Calling " << trial[0] << endl;
            beg[d][0] = chrono::steady_clock::now();
            string priv_key1 = create_priv_key(1);
            string decoded_key1;
            ElGamal_ eg1(priv_key1, 256);
            decoded_key1 = eg1.ElGamal_main();
            end[d][0] = chrono::steady_clock::now();

            cout << endl << "Calling " << trial[1] << endl;
            beg[d][1] = chrono::steady_clock::now();
            string priv_key2 = create_priv_key(2);
            string decoded_key2;
            ElGamal_ eg2(priv_key2, 256);
            decoded_key2 = eg2.ElGamal_main();
            end[d][1] = chrono::steady_clock::now();

            cout << endl << "Calling " << trial[2] << endl;
            beg[d][2] = chrono::steady_clock::now();
            DES_ des1(decoded_key1, img_path, 1, time_trial);
            end[d][2] = chrono::steady_clock::now();

            cout << endl << "Calling " << trial[3] << endl;
            beg[d][3] = chrono::steady_clock::now();
            DES_ des2(decoded_key1, img_path, 2, time_trial);
            end[d][3] = chrono::steady_clock::now();

            cout << endl << "Calling " << trial[4] << endl;
            beg[d][4] = chrono::steady_clock::now();
            AES_ aes1(decoded_key2, img_path, 1, time_trial);
            end[d][4] = chrono::steady_clock::now();

            cout << endl << "Calling " << trial[5] << endl;
            beg[d][5] = chrono::steady_clock::now();
            AES_ aes2(decoded_key2, img_path, 2, time_trial);
            end[d][5] = chrono::steady_clock::now();*/

            string decoded_key1, decoded_key2;
            string decoded_key3;
            string decoded_key3_split[3];
            for (int i = 0; i < 9; i++) {
                cout << endl << "Calling " << trial[i] << endl;
                beg[d][i] = chrono::steady_clock::now();
                if (i == 0) {
                    string priv_key1 = create_priv_key(1);
                    //string decoded_key1;
                    ElGamal_ eg1(priv_key1, 256);
                    decoded_key1 = eg1.ElGamal_main();
                }
                else if (i == 1) {
                    string priv_key2 = create_priv_key(2);
                    //string decoded_key2;
                    ElGamal_ eg2(priv_key2, 256);
                    decoded_key2 = eg2.ElGamal_main();
                }
                else if (i == 2) {
                    string priv_key2 = create_priv_key(3);
                    //string decoded_key2;
                    ElGamal_ eg2(priv_key2, 256);
                    decoded_key3 = eg2.ElGamal_main();
                    for (int k = 0; k < 3; k++) {
                        for (int j = 0; j < 16; j++) {
                            decoded_key3_split[k] += decoded_key3[(16 * k) + j];
                        }
                    }
                }
                else if (i == 3) { DES_ des1(decoded_key1, img_path, 1, time_trial); }
                else if (i == 4) { DES_ des2(decoded_key1, img_path, 2, time_trial); }
                else if (i == 5) { AES_ aes1(decoded_key2, img_path, 1, time_trial); }
                else if (i == 6) { AES_ aes2(decoded_key2, img_path, 2, time_trial); }
                else if (i == 7) { TripDES_ des3(decoded_key3_split, img_path, 1, time_trial); }
                else if (i == 8) { TripDES_ des3(decoded_key3_split, img_path, 2, time_trial); }

                end[d][i] = chrono::steady_clock::now();
            }

            overall_end[d] = chrono::steady_clock::now();
            cout << endl << "Clock has stopped" << endl;

            
        }

        for (int d = 0; d < limit; d++) {
            if (d == 0) {
                cout << endl << "Small image results" << endl;
            }
            else if (d == 1) {
                cout << endl << "Medium image results" << endl;
            }
            else {
                cout << endl << "Large image results" << endl;
            }
            cout << left << setw(25) << "Function" << left << setw(5) << "Time" << endl;
            for (int i = 0; i < 9; i++) {
                cout << left << setw(25) << trial[i] << left << setw(5) << chrono::duration_cast<std::chrono::seconds>(end[d][i] - beg[d][i]).count() << "[s]" << endl;
            }
            cout << endl << "Overall time: " << chrono::duration_cast<std::chrono::seconds>(overall_end[d] - overall_beg[d]).count() << "[s]" << endl;
        }
    }

    //system("Pause");
    return 0;
}
