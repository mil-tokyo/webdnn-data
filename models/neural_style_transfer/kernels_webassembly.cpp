
#include <stdlib.h>
#include <math.h>

float static_buffer[56673667];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {56507779,56341891,27648,3,3,27648};
int meta_buf_1[] = {56341891,1985923,1,3,144,192,144,192,9,9,1,1,1,1,4,4};
int meta_buf_2[] = {1985923,0,48600451,27648,32,243};
int meta_buf_3[] = {7840,7776,7808,48600451,45946243,32,32,32,27648};
int meta_buf_4[] = {45946243,18961795,1,32,144,192,72,96,4,4,1,1,2,2,1,1};
int meta_buf_5[] = {18961795,7872,50369923,6912,64,512};
int meta_buf_6[] = {40704,40768,40640,50369923,50812291,64,64,64,6912};
int meta_buf_7[] = {50812291,42407299,1,64,72,96,36,48,4,4,1,1,2,2,1,1};
int meta_buf_8[] = {42407299,40832,55899523,1728,128,1024};
int meta_buf_9[] = {172032,172160,171904,55899523,56120707,128,1728,128,1728};
int meta_buf_10[] = {56120707,54351235,1728,128,128,1728};
int meta_buf_11[] = {54351235,22500739,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_12[] = {22500739,172288,54130051,1728,128,1152};
int meta_buf_13[] = {319744,54130051,54130051,128,128,128,1728};
int meta_buf_14[] = {54130051,28472707,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_15[] = {28472707,319872,52581763,1728,128,1152};
int meta_buf_16[] = {467328,56120707,52581763,56120707,1728,128,1728,128,1728};
int meta_buf_17[] = {56120707,55678339,1728,128,128,1728};
int meta_buf_18[] = {55678339,32454019,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_19[] = {32454019,467456,53466499,1728,128,1152};
int meta_buf_20[] = {614912,53466499,53024131,128,128,128,1728};
int meta_buf_21[] = {53024131,30463363,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_22[] = {30463363,615040,53687683,1728,128,1152};
int meta_buf_23[] = {762496,56120707,53687683,56120707,1728,128,1728,128,1728};
int meta_buf_24[] = {56120707,52802947,1728,128,128,1728};
int meta_buf_25[] = {52802947,24491395,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_26[] = {24491395,762624,51697027,1728,128,1152};
int meta_buf_27[] = {910080,51697027,51697027,128,128,128,1728};
int meta_buf_28[] = {51697027,34444675,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_29[] = {34444675,910208,55235971,1728,128,1152};
int meta_buf_30[] = {1057664,56120707,55235971,51918211,1728,128,1728,128,1728};
int meta_buf_31[] = {51918211,52360579,1728,128,128,1728};
int meta_buf_32[] = {52360579,26482051,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_33[] = {26482051,1057792,54572419,1728,128,1152};
int meta_buf_34[] = {1205248,54572419,53908867,128,128,128,1728};
int meta_buf_35[] = {53908867,36435331,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_36[] = {36435331,1205376,55014787,1728,128,1152};
int meta_buf_37[] = {1352832,55014787,51918211,53245315,128,1728,1728,128,1728};
int meta_buf_38[] = {53245315,52139395,1728,128,128,1728};
int meta_buf_39[] = {52139395,40416643,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_40[] = {40416643,1352960,54793603,1728,128,1152};
int meta_buf_41[] = {1500416,54793603,55457155,128,128,128,1728};
int meta_buf_42[] = {55457155,38425987,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_43[] = {38425987,1500544,51254659,1728,128,1152};
int meta_buf_44[] = {1648000,53245315,51254659,51475843,1728,128,128,128,1728};
int meta_buf_45[] = {51475843,1648128,44176771,1728,1024,128};
int meta_buf_46[] = {49927555,44176771,1,36,48,64,72,96,4,4,2,2,1,1};
int meta_buf_47[] = {1779328,1779200,1779264,49927555,49485187,64,64,64,6912};
int meta_buf_48[] = {49485187,1779392,15422851,6912,512,64};
int meta_buf_49[] = {46830979,15422851,1,72,96,32,144,192,4,4,2,2,1,1};
int meta_buf_50[] = {1812224,1812160,1812192,46830979,47715715,32,32,32,27648};
int meta_buf_51[] = {47715715,1812256,8704387,27648,243,32};
int meta_buf_52[] = {56424835,8704387,1,144,192,3,144,192,9,9,1,1,4,4};
int meta_buf_53[] = {1820035,1902979,1820032,56424835,56590723,27648,27648,3,27648,3,27648};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5,meta_buf_6,meta_buf_7,meta_buf_8,meta_buf_9,meta_buf_10,meta_buf_11,meta_buf_12,meta_buf_13,meta_buf_14,meta_buf_15,meta_buf_16,meta_buf_17,meta_buf_18,meta_buf_19,meta_buf_20,meta_buf_21,meta_buf_22,meta_buf_23,meta_buf_24,meta_buf_25,meta_buf_26,meta_buf_27,meta_buf_28,meta_buf_29,meta_buf_30,meta_buf_31,meta_buf_32,meta_buf_33,meta_buf_34,meta_buf_35,meta_buf_36,meta_buf_37,meta_buf_38,meta_buf_39,meta_buf_40,meta_buf_41,meta_buf_42,meta_buf_43,meta_buf_44,meta_buf_45,meta_buf_46,meta_buf_47,meta_buf_48,meta_buf_49,meta_buf_50,meta_buf_51,meta_buf_52,meta_buf_53};

extern "C" void init() {
    //static_buffer = (float*)malloc(56673667 * sizeof(float));
}

extern "C" float* get_static_buffer(void) {
    return static_buffer;
}

extern "C" float* allocate_dynamic_buffer(int count) {
    if (dynamic_buffer) {
        free(dynamic_buffer);
        dynamic_buffer = nullptr;
    }
    dynamic_buffer = (float*)malloc(count * sizeof(float));
    return dynamic_buffer;
}

extern "C" float* get_dynamic_buffer(void) {
    return dynamic_buffer;
}
extern "C" void set_placeholder_value(int kernel_order, int offset, int value) {
    meta_buffers[kernel_order][offset] = value;
}

void transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    float * v2 = (static_buffer + meta_buffer[1]);
    const int v3 = meta_buffer[2];
    const int v4 = meta_buffer[3];
    const int D0 = meta_buffer[4];
    const int D1 = meta_buffer[5];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v5 = v1[d0*v3 + d1];
            float v6;
            {
                v6 = v5;
            }
            v2[d0 + d1*v4] = v6;
        }
    }
}


void im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(const int * meta_buffer)
{
    const float *im = (static_buffer + meta_buffer[0]);
    float *col = (static_buffer + meta_buffer[1]);

    const int N = meta_buffer[2];
    const int C1 = meta_buffer[3];
    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int DH = meta_buffer[10];
    const int DW = meta_buffer[11];
    const int SH = meta_buffer[12];
    const int SW = meta_buffer[13];
    const int PH = meta_buffer[14];
    const int PW = meta_buffer[15];

    for (int gid = 0; gid < N*H2*W2*KH*KW*C1; gid += 1) {
        const int c1 = gid % C1;
        const int kw = gid / C1 % KW;
        const int kh = gid / C1 / KW % KH;
        const int w2 = gid / C1 / KW / KH % W2;
        const int h2 = gid / C1 / KW / KH / W2 % H2;
        const int  n = gid / C1 / KW / KH / W2 / H2;
        
        const int h1 = h2 * SH - PH + kh * DH;
        const int w1 = w2 * SW - PW + kw * DW;

        col[gid] = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n*H1+h1)*W1+w1)*C1+c1];
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(const int * meta_buffer)
{
    float *A = (static_buffer + meta_buffer[0]);
    float *B = (static_buffer + meta_buffer[1]);
    float *C = (static_buffer + meta_buffer[2]);

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, meta_buffer[3], meta_buffer[5]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> > b_mat(B, meta_buffer[5], meta_buffer[4]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, meta_buffer[3], meta_buffer[4]);

    c_mat.noalias() = a_mat * b_mat;
}


void fusedelementwise_7f285d0f62c2f9263a6b79c6a487adfa5b53099a48d21be8c937ccf3(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        const float v9 = v2[d0];
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v6];
            float v12;
            {
                v12 = v11 + v8;
            }
            float v13;
            {
                v13 = v12 < 0.0 ? (exp(v12)-1) : v12;
            }
            float v14;
            {
                v14 = v13 * v10;
            }
            float v15;
            {
                v15 = v14 + v9;
            }
            v5[d0 + d1*v7] = v15;
        }
    }
}


void fusedelementwise_9b393d9d0fab94e25020b2685a9faae45349e1997ff16896f9ae3081(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        const float v9 = v2[d0];
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v6];
            float v12;
            {
                v12 = v11 + v9;
            }
            float v13;
            {
                v13 = v12 < 0.0 ? (exp(v12)-1) : v12;
            }
            float v14;
            {
                v14 = v13 * v8;
            }
            float v15;
            {
                v15 = v14 + v10;
            }
            v5[d0 + d1*v7] = v15;
        }
    }
}


void fusedelementwise_ca7e0d3a93ba98228c1b1705fa2ad00fa6e22e327848573ac54e7264(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        const float v9 = v2[d0];
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v6];
            float v12;
            {
                v12 = v11 + v9;
            }
            float v13;
            {
                v13 = v12 < 0.0 ? (exp(v12)-1) : v12;
            }
            float v14;
            {
                v14 = v13 * v8;
            }
            float v15;
            {
                v15 = v14 + v10;
            }
            v5[d0*v7 + d1] = v15;
        }
    }
}


void fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int v4 = meta_buffer[3];
    const int v5 = meta_buffer[4];
    const int D0 = meta_buffer[5];
    const int D1 = meta_buffer[6];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v6 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v7 = v2[d0 + d1*v4];
            float v8;
            {
                v8 = v7 + v6;
            }
            float v9;
            {
                v9 = v8 > 0 ? v8 : 0;
            }
            v3[d0 + d1*v5] = v9;
        }
    }
}


void fusedelementwise_e277bbe409cd60201bb9ac6e958baa53566cc8cbafe32718b91293a2(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0*v5 + d1];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v10 + v9;
            }
            float v12;
            {
                v12 = v8 + v11;
            }
            v4[d0*v7 + d1] = v12;
        }
    }
}


void fusedelementwise_7c7a967fde8a4d7a5b35e05efe5b6c6bfec9533ed7a8f23d959ff8cd(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0 + d1*v5];
            const float v10 = v3[d0*v6 + d1];
            float v11;
            {
                v11 = v9 + v10;
            }
            float v12;
            {
                v12 = v8 + v11;
            }
            v4[d0*v7 + d1] = v12;
        }
    }
}


void fusedelementwise_4bb46c1ecf24503baf4c5281daa8fdf6b67e788c7d3bdb7b90b3d30b(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v2[d0*v5 + d1];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v10 + v9;
            }
            float v12;
            {
                v12 = v8 + v11;
            }
            v4[d0 + d1*v7] = v12;
        }
    }
}


void col2im_c27ba017d8daabdc8a3c3b2e9bf5f029051ad380aed0be391c790d0e(const int * meta_buffer)
{
    const float *col = (static_buffer + meta_buffer[1]);
    float *im = (static_buffer + meta_buffer[0]);

    const int N = meta_buffer[2];
    const int C1 = meta_buffer[5];
    const int H1 = meta_buffer[6];
    const int W1 = meta_buffer[7];
    const int H2 = meta_buffer[3];
    const int W2 = meta_buffer[4];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int SH = meta_buffer[10];
    const int SW = meta_buffer[11];
    const int PH = meta_buffer[12];
    const int PW = meta_buffer[13];

    for (int gid = 0; gid < N*H1*W1*C1; gid += 1) {
        const int c1 = gid % C1;
        const int w1 = gid / C1 % W1;
        const int h1 = gid / C1 / W1 % H1;
        const int n = gid / C1 / W1 / H1;

        float sum = 0;
        for (int kh = 0; kh < KH; kh++) {
            const int h2 = (h1 + PH - kh) / SH;
            if ((h1 + PH - kh) % SH != 0 || h2 < 0 || h2 >= H2) continue;

            for (int kw = 0; kw < KW; kw++) {
                const int w2 = (w1 + PW - kw) / SW;
                if ((w1 + PW - kw) % SW != 0 || w2 < 0 || w2 >= W2) continue;
                
                sum += col[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1 + c1];
            }
        }
        
        im[gid] = sum; 
    }
}


void fusedelementwise_39af75c022081a1275ffbb7f550b1ed8385dda649d7e951c0e743729(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int v8 = meta_buffer[7];
    const int v9 = meta_buffer[8];
    const int D0 = meta_buffer[9];
    const int D1 = meta_buffer[10];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v8];
            float v12;
            {
                v12 = v11 + v10;
            }
            float v13;
            {
                v13 = tanh(v12);
            }
            const float v14 = v2[d0*v7 + d1];
            float v15;
            {
                v15 = v13 * v14;
            }
            const float v16 = v1[d0*v6 + d1];
            float v17;
            {
                v17 = v15 + v16;
            }
            v5[d0*v9 + d1] = v17;
        }
    }
}

extern "C" void run() {
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_0);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_1);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_2);
fusedelementwise_7f285d0f62c2f9263a6b79c6a487adfa5b53099a48d21be8c937ccf3(meta_buf_3);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_4);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_5);
fusedelementwise_9b393d9d0fab94e25020b2685a9faae45349e1997ff16896f9ae3081(meta_buf_6);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_7);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_8);
fusedelementwise_ca7e0d3a93ba98228c1b1705fa2ad00fa6e22e327848573ac54e7264(meta_buf_9);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_10);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_11);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_12);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_13);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_14);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_15);
fusedelementwise_e277bbe409cd60201bb9ac6e958baa53566cc8cbafe32718b91293a2(meta_buf_16);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_17);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_18);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_19);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_20);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_21);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_22);
fusedelementwise_e277bbe409cd60201bb9ac6e958baa53566cc8cbafe32718b91293a2(meta_buf_23);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_24);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_25);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_26);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_27);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_28);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_29);
fusedelementwise_e277bbe409cd60201bb9ac6e958baa53566cc8cbafe32718b91293a2(meta_buf_30);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_31);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_32);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_33);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_34);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_35);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_36);
fusedelementwise_7c7a967fde8a4d7a5b35e05efe5b6c6bfec9533ed7a8f23d959ff8cd(meta_buf_37);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_38);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_39);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_40);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_41);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_42);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_43);
fusedelementwise_4bb46c1ecf24503baf4c5281daa8fdf6b67e788c7d3bdb7b90b3d30b(meta_buf_44);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_45);
col2im_c27ba017d8daabdc8a3c3b2e9bf5f029051ad380aed0be391c790d0e(meta_buf_46);
fusedelementwise_9b393d9d0fab94e25020b2685a9faae45349e1997ff16896f9ae3081(meta_buf_47);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_48);
col2im_c27ba017d8daabdc8a3c3b2e9bf5f029051ad380aed0be391c790d0e(meta_buf_49);
fusedelementwise_9b393d9d0fab94e25020b2685a9faae45349e1997ff16896f9ae3081(meta_buf_50);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_51);
col2im_c27ba017d8daabdc8a3c3b2e9bf5f029051ad380aed0be391c790d0e(meta_buf_52);
fusedelementwise_39af75c022081a1275ffbb7f550b1ed8385dda649d7e951c0e743729(meta_buf_53);

}

