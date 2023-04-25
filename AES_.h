#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"       // core library
#include "opencv2/imgcodecs.hpp"    // read/write ims
#include "opencv2/highgui.hpp"      // show ims in a window

using namespace std;
using namespace cv;

class PublicData
{
public:
    // only 7 coefficients are used for 14 rounds
    //int round_coeff[7] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 };
    int round_coeff[7][8] = {
        { 0, 0, 0, 0, 0, 0, 0, 1},
        { 0, 0, 0, 0, 0, 0, 1, 0},
        { 0, 0, 0, 0, 0, 1, 0, 0},
        { 0, 0, 0, 0, 1, 0, 0, 0},
        { 0, 0, 0, 1, 0, 0, 0, 0},
        { 0, 0, 1, 0, 0, 0, 0, 0},
        { 0, 1, 0, 0, 0, 0, 0, 0}
    };
    int forward_s_box[256] = {
        /*00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F*/
        /*00*/   0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        /*10*/   0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        /*20*/   0xb7 ,0xfd ,0x93 ,0x26 ,0x36 ,0x3f ,0xf7 ,0xcc ,0x34 ,0xa5 ,0xe5 ,0xf1 ,0x71 ,0xd8 ,0x31 ,0x15,
        /*30*/   0x04 ,0xc7 ,0x23 ,0xc3 ,0x18 ,0x96 ,0x05 ,0x9a ,0x07 ,0x12 ,0x80 ,0xe2 ,0xeb ,0x27 ,0xb2 ,0x75,
        /*40*/   0x09 ,0x83 ,0x2c ,0x1a ,0x1b ,0x6e ,0x5a ,0xa0 ,0x52 ,0x3b ,0xd6 ,0xb3 ,0x29 ,0xe3 ,0x2f ,0x84,
        /*50*/   0x53 ,0xd1 ,0x00 ,0xed ,0x20 ,0xfc ,0xb1 ,0x5b ,0x6a ,0xcb ,0xbe ,0x39 ,0x4a ,0x4c ,0x58 ,0xcf,
        /*60*/   0xd0 ,0xef ,0xaa ,0xfb ,0x43 ,0x4d ,0x33 ,0x85 ,0x45 ,0xf9 ,0x02 ,0x7f ,0x50 ,0x3c ,0x9f ,0xa8,
        /*70*/   0x51 ,0xa3 ,0x40 ,0x8f ,0x92 ,0x9d ,0x38 ,0xf5 ,0xbc ,0xb6 ,0xda ,0x21 ,0x10 ,0xff ,0xf3 ,0xd2,
        /*80*/   0xcd ,0x0c ,0x13 ,0xec ,0x5f ,0x97 ,0x44 ,0x17 ,0xc4 ,0xa7 ,0x7e ,0x3d ,0x64 ,0x5d ,0x19 ,0x73,
        /*90*/   0x60 ,0x81 ,0x4f ,0xdc ,0x22 ,0x2a ,0x90 ,0x88 ,0x46 ,0xee ,0xb8 ,0x14 ,0xde ,0x5e ,0x0b ,0xdb,
        /*A0*/   0xe0 ,0x32 ,0x3a ,0x0a ,0x49 ,0x06 ,0x24 ,0x5c ,0xc2 ,0xd3 ,0xac ,0x62 ,0x91 ,0x95 ,0xe4 ,0x79,
        /*B0*/   0xe7 ,0xc8 ,0x37 ,0x6d ,0x8d ,0xd5 ,0x4e ,0xa9 ,0x6c ,0x56 ,0xf4 ,0xea ,0x65 ,0x7a ,0xae ,0x08,
        /*C0*/   0xba ,0x78 ,0x25 ,0x2e ,0x1c ,0xa6 ,0xb4 ,0xc6 ,0xe8 ,0xdd ,0x74 ,0x1f ,0x4b ,0xbd ,0x8b ,0x8a,
        /*D0*/   0x70 ,0x3e ,0xb5 ,0x66 ,0x48 ,0x03 ,0xf6 ,0x0e ,0x61 ,0x35 ,0x57 ,0xb9 ,0x86 ,0xc1 ,0x1d ,0x9e,
        /*E0*/   0xe1 ,0xf8 ,0x98 ,0x11 ,0x69 ,0xd9 ,0x8e ,0x94 ,0x9b ,0x1e ,0x87 ,0xe9 ,0xce ,0x55 ,0x28 ,0xdf,
        /*F0*/   0x8c ,0xa1 ,0x89 ,0x0d ,0xbf ,0xe6 ,0x42 ,0x68 ,0x41 ,0x99 ,0x2d ,0x0f ,0xb0 ,0x54 ,0xbb ,0x16
    };
    int inverse_s_box[256] = {
        /*00    01    02    03    04    05    06    07    08    09    0A    0B    0C    0D    0E    0F*/
        /*00*/   0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        /*10*/   0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        /*20*/   0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        /*30*/   0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        /*40*/   0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        /*50*/   0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        /*60*/   0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        /*70*/   0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        /*80*/   0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        /*90*/   0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        /*A0*/   0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        /*B0*/   0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        /*C0*/   0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        /*D0*/   0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        /*E0*/   0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        /*F0*/   0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
    };
    int mix_col_mtx[4][4] = {
        { 2, 3, 1, 1},
        { 1, 2, 3, 1},
        { 1, 1, 2, 3},
        { 3, 1, 1, 2}
    };
    int inv_mix_col_mtx[4][4] = {
        {14, 11, 13, 9},
        {9, 14, 11, 13},
        {13, 9, 14, 11},
        {11, 13, 9, 14}
    };

    PublicData() = default;
    ~PublicData() = default;
};

class AES_ {
private:
    /*
* @param subkeys "returns" the subkeys in binary
* @param master_key the original key in binary
*/
    void generate_subkeys(int subkeys[][256], int master_key[]) {
        int temp_key[256] = { 0 };

        for (int i = 0; i < 15; i++) {
            // fill first subkey with master
            if (i == 0) {
                for (int j = 0; j < 256; j++) {
                    subkeys[0][j] = master_key[j];
                }
            }
            // fill rest of subkeys with result of operations
            else {
                for (int j = 0; j < 256; j++) {
                    subkeys[i][j] = temp_key[j];
                }
            }

            // fill words of key for processing
            int words[8][32] = { 0 };
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 32; k++) {
                    words[j][k] = subkeys[i][(32 * j) + k];
                }
            }

            // make a copy of the last section
            int last_word_cpy[32] = { 0 };
            for (int j = 0; j < 32; j++) {
                last_word_cpy[j] = words[7][j];
            }

            // perform g function on last section
            g_function(last_word_cpy, i);

            // perform xors
            for (int j = 0; j < 8; j++) {
                if (j == 0) {
                    bitwise_xor(last_word_cpy, words[0], 32);
                }
                else {
                    bitwise_xor(words[j - 1], words[j], 32);
                }
            }

            // save results
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 32; k++) {
                    temp_key[(32 * j) + k] = words[j][k];
                }
            }
        }
    }

    /*
    * @param last_word a copy of the last word in the subkey section
    * @param round_num subkey idx
    */
    void g_function(int last_word[32], int round_num) {
        PublicData gfx;

        int orig[32];
        for (int i = 0; i < 32; i++) {
            orig[i] = last_word[i];
        }

        // left shift
        for (int i = 0; i < 32; i++) {
            if (i < 24) {
                last_word[i] = orig[8 + i];
            }
            else {
                last_word[i] = orig[i - 24];
            }
        }

        // break into 8-bit sections
        int section_bin[4][8] = { 0 };
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                section_bin[i][j] = last_word[(8 * i) + j];
            }
        }

        // transform sections to decimal
        int section_dec[4] = { 0 };
        for (int i = 0; i < 4; i++) {
            section_dec[i] = binary_to_dec(section_bin[i], 8);
        }

        // s-box transform
        //if (forward = 1) {
        for (int i = 0; i < 4; i++) {
            section_dec[i] = gfx.forward_s_box[section_dec[i]];
        }
        //}
        //else {
        //    for (int i = 0; i < 4; i++) {
        //        section_dec[i] = gfx.inverse_s_box[section_dec[i]];
        //    }
        //}

        // tranfrom back into bin
        for (int i = 0; i < 4; i++) {
            dec_to_binary(section_dec[i], section_bin[i]);
        }

        // xor first section with round coefficient
        bitwise_xor(gfx.round_coeff[round_num % 7], section_bin[0], 8);

        // combine to g function output
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                last_word[(8 * i) + j] = section_bin[i][j];
            }
        }
    }

    /*
    * @param input_sections_bin the input broken into 16 8-bit sections
    * @param subkeys_section a subkey broken into 16 8-bit sections
    */
    void key_addition(int input_section_bin[][8], int subkeys_section[][8]) {
        for (int i = 0; i < 16; i++) {
            bitwise_xor(subkeys_section[i], input_section_bin[i], 8);
        }
    }

    /*
    * @param input_sections_bin the input broken into 16 8-bit sections
    */
    void byte_sub(int input_sections_bin[][8], bool forward = 1) {
        PublicData pd;

        // transform sections to decimal
        int sections_dec[16] = { 0 };
        for (int i = 0; i < 16; i++) {
            sections_dec[i] = binary_to_dec(input_sections_bin[i], 8);
        }

        // s-box transform
        if (forward == 1) {
            for (int i = 0; i < 16; i++) {
                sections_dec[i] = pd.forward_s_box[sections_dec[i]];
            }
        }
        else {
            for (int i = 0; i < 16; i++) {
                sections_dec[i] = pd.inverse_s_box[sections_dec[i]];
            }
        }

        // transform back into bin
        for (int i = 0; i < 16; i++) {
            dec_to_binary(sections_dec[i], input_sections_bin[i]);
        }
    }

    /*
    * @param input_sections_bin the input broken into 16 8-bit sections
    */
    void shiftrow(int input_sections_bin[][8], bool forward=1) {
        if (forward) {
            int temp4[8] = { 0 };
            int temp8[8] = { 0 };
            int temp9[8] = { 0 };
            int temp15[8] = { 0 };
            for (int i = 0; i < 8; i++) {
                temp4[i] = input_sections_bin[4][i];
                temp8[i] = input_sections_bin[8][i];
                temp9[i] = input_sections_bin[9][i];
                temp15[i] = input_sections_bin[15][i];
            }

            for (int i = 0; i < 8; i++) {
                // 1 shift left
                input_sections_bin[4][i] = input_sections_bin[5][i];
                input_sections_bin[5][i] = input_sections_bin[6][i];
                input_sections_bin[6][i] = input_sections_bin[7][i];
                input_sections_bin[7][i] = temp4[i];

                // 2 shifts left
                input_sections_bin[8][i] = input_sections_bin[10][i];
                input_sections_bin[9][i] = input_sections_bin[11][i];
                input_sections_bin[10][i] = temp8[i];
                input_sections_bin[11][i] = temp9[i];

                // 3 shifts left
                input_sections_bin[15][i] = input_sections_bin[14][i];
                input_sections_bin[14][i] = input_sections_bin[13][i];
                input_sections_bin[13][i] = input_sections_bin[12][i];
                input_sections_bin[12][i] = temp15[i];
            }
        }
        else {
            int temp7[8] = { 0 };
            int temp8[8] = { 0 };
            int temp9[8] = { 0 };
            int temp12[8] = { 0 };
            for (int i = 0; i < 8; i++) {
                temp7[i] = input_sections_bin[7][i];
                temp8[i] = input_sections_bin[8][i];
                temp9[i] = input_sections_bin[9][i];
                temp12[i] = input_sections_bin[12][i];
            }
            for (int i = 0; i < 8; i++) {
                // 3 shifts left
                input_sections_bin[7][i] = input_sections_bin[6][i];
                input_sections_bin[6][i] = input_sections_bin[5][i];
                input_sections_bin[5][i] = input_sections_bin[4][i];
                input_sections_bin[4][i] = temp7[i];

                // 2 shifts left
                input_sections_bin[8][i] = input_sections_bin[10][i];
                input_sections_bin[9][i] = input_sections_bin[11][i];
                input_sections_bin[10][i] = temp8[i];
                input_sections_bin[11][i] = temp9[i];

                // 1 shift left
                input_sections_bin[12][i] = input_sections_bin[13][i];
                input_sections_bin[13][i] = input_sections_bin[14][i];
                input_sections_bin[14][i] = input_sections_bin[15][i];
                input_sections_bin[15][i] = temp12[i];
            }
        }

    }

    /*
    * @param input_sections_bin the input broken into 16 8-bit sections
    */
    void mix_col(int input_sections_bin[][8], bool forward = 1) {
        PublicData pd;

        // transform sections to decimal
        int sections_dec[16] = { 0 };
        for (int i = 0; i < 16; i++) {
            sections_dec[i] = binary_to_dec(input_sections_bin[i], 8);
        }

        // transpose mtx
        int cols_dec[4][4] = {
            { sections_dec[0], sections_dec[4], sections_dec[8], sections_dec[12]},
            { sections_dec[1], sections_dec[5], sections_dec[9], sections_dec[13]},
            { sections_dec[2], sections_dec[6], sections_dec[10], sections_dec[14]},
            { sections_dec[3], sections_dec[7], sections_dec[11], sections_dec[15]}
        };

        // multiply against public matrix
        if (forward == 1) {
            for (int i = 0; i < 4; i++) {
                matrix_mult(pd.mix_col_mtx, cols_dec[i]);
            }
        }
        else {
            for (int i = 0; i < 4; i++) {
                matrix_mult(pd.inv_mix_col_mtx, cols_dec[i]);
            }
        }

        // ensure cell confined to 8 bits
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cols_dec[i][j] %= 255;
            }
        }

        // transpose mtx
        int sections_dec2[16] = {
            cols_dec[0][0], cols_dec[1][0], cols_dec[2][0], cols_dec[3][0],
            cols_dec[0][1], cols_dec[1][1], cols_dec[2][1], cols_dec[3][1],
            cols_dec[0][2], cols_dec[1][2], cols_dec[2][2], cols_dec[3][2],
            cols_dec[0][3], cols_dec[1][3], cols_dec[2][3], cols_dec[3][3]
        };

        // transform sections to bin
        for (int i = 0; i < 16; i++) {
            dec_to_binary(sections_dec2[i], input_sections_bin[i]);
        }
    }

    /*
    * @param keys the subkeys
    * @param rev_keys "returns" keys in reverse order
    */
    void key_reverse(int keys[][256], int rev_keys[][256]) {
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 256; j++) {
                rev_keys[14 - i][j] = keys[i][j];
            }
        }
    }

    /*
    * @param hex the string to be converted to binary
    * @param binary "returns" the key in binary
    */
    void hex_to_binary(string hex, int binary[]) {
        string num;
        int binary_rev[256];
        int num_split;
        int r;
        int q;

        for (int i = 0; i < 64; i++) {
            num = hex[i];

            // convert letters to ints via ascii
            if (num == "A" || num == "B" || num == "C" || num == "D" || num == "E" || num == "F") {
                num_split = int(hex[i] - 65 + 10);
            }
            else {
                num_split = hex[i] - '0';
            }

            for (int j = 0; j < 4; j++) {
                r = num_split % 2;
                q = num_split / 2;

                binary_rev[(4 * i) + j] = r;
                num_split = q;
            }

            int end = (4 * i) + 3;
            for (int k = (4 * i); k < (4 * i) + 4; k++) {
                binary[k] = binary_rev[end];
                end--;
            }

        }
    }

    /*
    * @param binary the binary array to be converted
    * @param len the length of the binary array
    */
    int binary_to_dec(int binary[], int bin_len) {
        int dec = 0;

        for (int i = 0; i < bin_len; i++) {
            dec += binary[i] * int(pow(2, (bin_len - 1 - i)));
        }

        return dec;
    }

    /*
    * @param dec the decimal number to convert
    * @param binary "returns" the binary conversion
    */
    void dec_to_binary(int dec, int binary[]) {
        int r;
        int q;
        //int init_dec = dec;
        int binary_rev[8] = { 0 };

        for (int i = 0; i < 8; i++) {
            r = dec % 2;
            q = dec / 2;    // int division

            binary_rev[i] = r;
            dec = q;
        }

        int end = 7;
        for (int i = 0; i < 8; i++) {
            binary[i] = binary_rev[end];
            end--;
        }
    }

    /*
    * @param binary the binary array to be converted
    * @param charac "returns" the converted uchar array
    */
    void binary_to_char(int binary[], uchar charac[]) {
        int dec[16] = { 0 };
        //int end = 15;

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 8; j++) {
                dec[i] += binary[(i * 8) + j] * int(pow(2, 8 - 1 - j));
            }
            charac[i] = (uchar)dec[i];
            //end--;
        }
    }

    /*
    * @param dec the characters to be converted
    * @param binary "returns" the binary conversion
    */
    void char_to_bin(/*uchar dec[]*/vector<uchar>& dec, int binary[]) {
        int r;
        int q;
        int binary_rev[16][8] = { 0 };
        int binary_rev_flat[128] = { 0 };

        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 8; j++) {
                //cout << "dec[i] is " << +dec[i] << endl;
                r = (int)dec[i] % 2;
                q = (int)dec[i] / 2;

                binary_rev[i][j] = r;
                dec[i] = q;
            }
        }

        //cout << "binary_rev is ";
        for (int i = 0; i < 16; i++) {
            int end = 7;
            for (int j = 0; j < 8; j++) {
                binary_rev_flat[(i * 8) + j] = binary_rev[i][end];
                end--;
            }
        }

        //int end = 127;
        for (int i = 0; i < 128; i++) {
            binary[i] = binary_rev_flat[i];
            //end--;
        }
    }

    /*
    * @param arr1 the first values to xor with
    * @param arr2 second values to xor with; "returns" xor result
    * @param len the length of the arrays
    */
    void bitwise_xor(int arr1[], int arr2[], int len) {
        for (int i = 0; i < len; i++) {
            if (arr1[i] == arr2[i]) {
                arr2[i] = 0;
            }
            else {
                arr2[i] = 1;
            }
        }
    }

    /*
    * @param arr1 the first array to be multiplied
    * @param arr2 the second array to be multiplied; "returns" result
    */
    void matrix_mult(int arr1[][4], int arr2[4]) {
        int result[4] = { 0 };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 1; j++) {
                for (int k = 0; k < 4; k++) {
                    result[i] += arr1[i][k] * arr2[k];
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            arr2[i] = result[i];
        }
    }

    string binary_to_hex(int binary[], int hex_len) {
        string hex = "";
        //int bin_group[64][4] = { 0 };
        int** bin_group = new int* [hex_len];
        for (int i = 0; i < hex_len; i++) {
            bin_group[i] = new int[4];
        }

        for (int i = 0; i < hex_len; i++) {
            for (int j = 0; j < 4; j++) {
                bin_group[i][j] = binary[(i * 4) + j];
            }
        }

        for (int i = 0; i < hex_len; i++) {
            int num = binary_to_dec(bin_group[i], 4);

            if (num > 9) {
                num = num - 10 + 65;
                char num_hex = char(num);
                hex += num_hex;
            }
            else {
                hex += to_string(num);
            }
        }

        for (int i = 0; i < hex_len; i++) {
            delete[] bin_group[i];
        }
        delete[] bin_group;

        return hex;
    }

    string key;
    string imname;
    int mode;
    bool time_trial;

public:
    AES_(string key, string imname, int mode, bool time_trial) {
        set_key(key);
        set_imname(imname);
        set_mode(mode);
        set_time_trial(time_trial);
        AES_main();
    }

    ~AES_() = default;

    void set_key(string k) {
        if (k == "d") {
            k = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
        }
        else if (k.length() != 64) {
            cout << "Key not of length 64; default key will be used." << endl;
            k = "0123456789ABCDEF";
        }
        else {
            for (int i = 0; i < 16; i++) {
                k[i] = toupper(k[i]);
            }
        }

        key = k;
    }
    void set_imname(string imn) {
        if (imn == "d1") {
            imn = "bmp_small.bmp";
        }
        else if (imn == "d2") {
            imn = "bmp_med.bmp";
        }
        else if (imn == "d3") {
            imn = "bmp_large.bmp";
        }
        imname = imn;
    }
    void set_mode(int m) {
        if (m != 1 && m != 2) {
            cout << "Invalid mode, ECB will be used." << endl;
            m = 1;
        }
        mode = m;
    }
    void set_time_trial(bool tt) {
        time_trial = tt;
    }

    void AES_main() {
        string impath = samples::findFile(imname);
        Mat img = imread(impath, IMREAD_COLOR);

        int binary_key[256] = { 0 };
        hex_to_binary(key, binary_key);

        // 15 keys, 8 words each * 32 bits per word
        int subkeys[15][256] = { 0 };
        generate_subkeys(subkeys, binary_key);

        // convert into 16 sections of 8 bits per key
        int subkeys_sections[15][16][8] = { 0 };
        for (int i = 0; i < 15; i++) {
            for (int j = 0; j < 16; j++) {
                for (int k = 0; k < 8; k++) {
                    subkeys_sections[i][j][k] = subkeys[i][(8 * j) + k];
                }
            }
        }

        int ttl_pix = img.rows * img.cols;
        // split im into 3 channels
        Mat bgr[3];
        split(img, bgr);

        // flat array
        vector < vector<uchar>> bgr_cpy(3, vector<uchar>(ttl_pix));
        for (int c = 0; c < 3; c++) {
            for (int i = 0; i < img.rows; i++) {
                for (int j = 0; j < img.cols; j++) {
                    bgr_cpy[c][(img.cols * (long long)i) + j] = bgr[c].at<uchar>(i, j);
                }
            }
        }

        vector<vector<uchar>> cipher_char(3, vector<uchar>(ttl_pix));
        vector<vector<uchar>> decode_char(3, vector<uchar>(ttl_pix));

        int num_blocks = ceil(ttl_pix / 16.0);
        vector<vector<uchar>> input_arr(num_blocks, vector<uchar>(16));

        for (int c = 0; c < 3; c++) {
            cout << "AES: Processing Channel " << c + 1 << "..." << endl;

            int ttl_inp_remaining = ttl_pix;

            // fill all blocks
            for (int k = 0; k < num_blocks; k++) {
                if (ttl_inp_remaining <= 16) {
                    for (int i = 0; i < ttl_inp_remaining; i++) {
                        input_arr[k][i] = bgr_cpy[c][(16 * k) + i];
                        //input_arr[k] += input[(32 * k) + i];
                    }

                    for (int i = ttl_inp_remaining; i < 16; i++) {
                        input_arr[k][i] = (uchar)0;
                        //input_arr[k] += '0';
                    }
                }
                else {
                    for (int i = 0; i < 16; i++) {
                        input_arr[k][i] = bgr_cpy[c][(16 * k) + i];
                        //input_arr[k] += input[(32 * k) + i];
                    }
                    ttl_inp_remaining -= 16;
                }
            } // end of block fill for

            int CBC_storage[128];
            int IV[128] = { 0 };

            for (int k = 0; k < num_blocks; k++) {
                /********************** encrypt **********************/
                // convert input to bin
                int binary_input[128] = { 0 };
                char_to_bin(input_arr[k], binary_input);

                if (mode == 2) {
                    if (k == 0) {
                        bitwise_xor(IV, binary_input, 128);
                    }
                    else {
                        bitwise_xor(CBC_storage, binary_input, 128);
                    }
                }

                // convert into 16 sections of 8 bits
                int input_sections_bin[16][8] = { 0 };
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 8; j++) {
                        input_sections_bin[i][j] = binary_input[(8 * i) + j];
                    }
                }

                // 14 rounds
                key_addition(input_sections_bin, subkeys_sections[0]);
                for (int r = 0; r < 14; r++) {
                    byte_sub(input_sections_bin);
                    shiftrow(input_sections_bin);
                    if (r != 14) {
                        //mix_col(input_sections_bin);
                    }
                    key_addition(input_sections_bin, subkeys_sections[r + 1]);
                }   // end of round for

                // flatten ciphertext array
                int ciphertext_bin[128] = { 0 };
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 8; j++) {
                        ciphertext_bin[(8 * i) + j] = input_sections_bin[i][j];
                    }
                }

                uchar partial_ciphertext[16];
                binary_to_char(ciphertext_bin, partial_ciphertext);

                for (int i = 0; i < 16; i++) {
                    if ((k * 16) + i < ttl_pix) {
                        cipher_char[c][(k * 16) + i] = partial_ciphertext[i];
                    }
                }

                /********************** decrypt **********************/
                int rev_subkeys[15][256] = { 0 };
                key_reverse(subkeys, rev_subkeys);

                // convert into 16 sections of 8 bits per key
                int rev_subkeys_sections[15][16][8] = { 0 };
                for (int i = 0; i < 15; i++) {
                    for (int j = 0; j < 16; j++) {
                        for (int k = 0; k < 8; k++) {
                            rev_subkeys_sections[i][j][k] = rev_subkeys[i][(8 * j) + k];
                        }
                    }
                }

                // convert into 16 sections of 8 bits
                int cipher_sections_bin[16][8] = { 0 };
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 8; j++) {
                        cipher_sections_bin[i][j] = ciphertext_bin[(8 * i) + j];
                    }
                }

                // 14 rounds
                for (int r = 0; r < 14; r++) {
                    key_addition(cipher_sections_bin, rev_subkeys_sections[r]);
                    if (r != 0) {
                        //mix_col(cipher_sections_bin, false);
                    }
                    shiftrow(cipher_sections_bin, false);
                    byte_sub(cipher_sections_bin, false);
                } // end of round for
                key_addition(cipher_sections_bin, rev_subkeys_sections[14]);

                // flatten plaintext array
                int plaintext_bin[128] = { 0 };
                for (int i = 0; i < 16; i++) {
                    for (int j = 0; j < 8; j++) {
                        plaintext_bin[(8 * i) + j] = cipher_sections_bin[i][j];
                    }
                }

                if (mode == 2) {
                    if (k == 0) {
                        bitwise_xor(IV, plaintext_bin, 128);
                    }
                    else {
                        bitwise_xor(CBC_storage, plaintext_bin, 128);
                    }
                }

                uchar partial_plaintext[16];
                binary_to_char(plaintext_bin, partial_plaintext);

                for (int i = 0; i < 16; i++) {
                    if ((k * 16) + i < ttl_pix) {
                        decode_char[c][(k * 16) + i] = partial_plaintext[i];
                    }
                }

                for (int i = 0; i < 128; i++) {
                    CBC_storage[i] = ciphertext_bin[i];
                }

            }   // end of enc/dec
            cout << "...complete" << endl;
        }   // end of color channel for

        if (!time_trial) {
            Mat cipher_channels_arr[3];
            for (int i = 0; i < 3; i++) {
                cipher_channels_arr[i] = Mat(img.rows, img.cols, CV_8U, cipher_char[i].data());
            }

            Mat cipher_img;
            vector<Mat> cipher_channels = { cipher_channels_arr[0], cipher_channels_arr[1], cipher_channels_arr[2] };
            merge(cipher_channels, cipher_img);
            namedWindow("cipherimage", WINDOW_AUTOSIZE);
            imshow("cipherimage", cipher_img);
            int k = waitKey(0); // Wait for a keystroke in the window
            if (k == 's')
            {
                imwrite("enc.bmp", cipher_img);
            }

            Mat decode_channels_arr[3];
            for (int i = 0; i < 3; i++) {
                decode_channels_arr[i] = Mat(img.rows, img.cols, CV_8U, decode_char[i].data());
            }

            Mat decode_img;
            vector<Mat> decode_channels = { decode_channels_arr[0], decode_channels_arr[1], decode_channels_arr[2] };
            merge(decode_channels, decode_img);
            namedWindow("decodeimage", WINDOW_AUTOSIZE);
            imshow("decodeimage", decode_img);
            int l = waitKey(0); // Wait for a keystroke in the window
            if (l == 's')
            {
                imwrite("dec.bmp", decode_img);
            }
        }

    }   // end of AES_main()

};