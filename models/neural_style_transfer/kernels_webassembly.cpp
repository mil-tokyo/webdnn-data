
#include <stdlib.h>
#include <math.h>

float static_buffer[56010115];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {55761283,55927171,27648,3,3,27648};
int meta_buf_1[] = {55927171,8704387,1,3,144,192,144,192,9,9,1,1,1,1,4,4};
int meta_buf_2[] = {8704387,0,46830979,27648,32,243};
int meta_buf_3[] = {7808,7840,7776,46830979,47715715,32,32,32,27648};
int meta_buf_4[] = {47715715,15422851,1,32,144,192,72,96,4,4,1,1,2,2,1,1};
int meta_buf_5[] = {15422851,7872,49485187,6912,64,512};
int meta_buf_6[] = {40768,40704,40640,49485187,49485187,64,64,64,6912};
int meta_buf_7[] = {49485187,42407299,1,64,72,96,36,48,4,4,1,1,2,2,1,1};
int meta_buf_8[] = {42407299,40832,54130051,1728,128,1024};
int meta_buf_9[] = {171904,172160,172032,54130051,55457155,128,1728,128,1728};
int meta_buf_10[] = {55457155,54572419,1728,128,128,1728};
int meta_buf_11[] = {54572419,40416643,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_12[] = {40416643,172288,53687683,1728,128,1152};
int meta_buf_13[] = {319744,53687683,53687683,128,128,128,1728};
int meta_buf_14[] = {53687683,22500739,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_15[] = {22500739,319872,50812291,1728,128,1152};
int meta_buf_16[] = {467328,55457155,50812291,55457155,1728,128,1728,128,1728};
int meta_buf_17[] = {55457155,51697027,1728,128,128,1728};
int meta_buf_18[] = {51697027,28472707,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_19[] = {28472707,467456,52139395,1728,128,1152};
int meta_buf_20[] = {614912,52139395,52360579,128,128,128,1728};
int meta_buf_21[] = {52360579,30463363,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_22[] = {30463363,615040,52802947,1728,128,1152};
int meta_buf_23[] = {762496,52802947,55457155,55014787,128,1728,1728,128,1728};
int meta_buf_24[] = {55014787,53466499,1728,128,128,1728};
int meta_buf_25[] = {53466499,36435331,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_26[] = {36435331,762624,51254659,1728,128,1152};
int meta_buf_27[] = {910080,51254659,51254659,128,128,128,1728};
int meta_buf_28[] = {51254659,38425987,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_29[] = {38425987,910208,54793603,1728,128,1152};
int meta_buf_30[] = {1057664,55014787,54793603,55014787,1728,128,1728,128,1728};
int meta_buf_31[] = {55014787,55235971,1728,128,128,1728};
int meta_buf_32[] = {55235971,24491395,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_33[] = {24491395,1057792,51033475,1728,128,1152};
int meta_buf_34[] = {1205248,51033475,51475843,128,128,128,1728};
int meta_buf_35[] = {51475843,26482051,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_36[] = {26482051,1205376,51918211,1728,128,1152};
int meta_buf_37[] = {1352832,55014787,51918211,55014787,1728,128,1728,128,1728};
int meta_buf_38[] = {55014787,52581763,1728,128,128,1728};
int meta_buf_39[] = {52581763,32454019,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_40[] = {32454019,1352960,53024131,1728,128,1152};
int meta_buf_41[] = {1500416,53024131,53245315,128,128,128,1728};
int meta_buf_42[] = {53245315,34444675,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_43[] = {34444675,1500544,53908867,1728,128,1152};
int meta_buf_44[] = {1648000,55014787,53908867,54351235,1728,128,128,128,1728};
int meta_buf_45[] = {54351235,1648128,44176771,1728,1024,128};
int meta_buf_46[] = {49927555,44176771,1,36,48,64,72,96,4,4,2,2,1,1};
int meta_buf_47[] = {1779328,1779264,1779200,49927555,50369923,64,64,64,6912};
int meta_buf_48[] = {50369923,1779392,18961795,6912,512,64};
int meta_buf_49[] = {48600451,18961795,1,72,96,32,144,192,4,4,2,2,1,1};
int meta_buf_50[] = {1812224,1812192,1812160,48600451,45946243,32,32,32,27648};
int meta_buf_51[] = {45946243,1812256,1985923,27648,243,32};
int meta_buf_52[] = {55678339,1985923,1,144,192,3,144,192,9,9,1,1,4,4};
int meta_buf_53[] = {1820032,1902979,1820035,55678339,55844227,27648,27648,3,27648,3,27648};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5,meta_buf_6,meta_buf_7,meta_buf_8,meta_buf_9,meta_buf_10,meta_buf_11,meta_buf_12,meta_buf_13,meta_buf_14,meta_buf_15,meta_buf_16,meta_buf_17,meta_buf_18,meta_buf_19,meta_buf_20,meta_buf_21,meta_buf_22,meta_buf_23,meta_buf_24,meta_buf_25,meta_buf_26,meta_buf_27,meta_buf_28,meta_buf_29,meta_buf_30,meta_buf_31,meta_buf_32,meta_buf_33,meta_buf_34,meta_buf_35,meta_buf_36,meta_buf_37,meta_buf_38,meta_buf_39,meta_buf_40,meta_buf_41,meta_buf_42,meta_buf_43,meta_buf_44,meta_buf_45,meta_buf_46,meta_buf_47,meta_buf_48,meta_buf_49,meta_buf_50,meta_buf_51,meta_buf_52,meta_buf_53};

extern "C" void init() {
    //static_buffer = (float*)malloc(56010115 * sizeof(float));
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


void im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(const int * meta_buffer)
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


void fusedelementwise_65103cc08144e30af8e8fc36eefb3e503e891d0e16c924d596099d2b(const int * meta_buffer)
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
                v12 = v11 + v10;
            }
            float v13;
            {
                v13 = v12 < 0.0 ? (exp(v12)-1) : v12;
            }
            float v14;
            {
                v14 = v13 * v9;
            }
            float v15;
            {
                v15 = v14 + v8;
            }
            v5[d0 + d1*v7] = v15;
        }
    }
}


void fusedelementwise_7b13be09769198a212aeef961987061901ccbdd15c4b2ba5d894ae86(const int * meta_buffer)
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
                v12 = v11 + v10;
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
                v15 = v14 + v9;
            }
            v5[d0 + d1*v7] = v15;
        }
    }
}


void fusedelementwise_9b674ab2245bc82ef3051776861c2d2abb8631d97840be07733c7987(const int * meta_buffer)
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
                v14 = v13 * v9;
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


void col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(const int * meta_buffer)
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


void fusedelementwise_56ca5795fe00ce775fda07d409cff3b926d3c78ebda9d035b1638b4c(const int * meta_buffer)
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
                v14 = v13 * v9;
            }
            float v15;
            {
                v15 = v14 + v10;
            }
            v5[d0 + d1*v7] = v15;
        }
    }
}


void fusedelementwise_53ead169c7750031ee68a27ea19713c5a06ab6f1d3954345add48e2e(const int * meta_buffer)
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
        const float v10 = v1[d0];
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
            const float v14 = v2[d0*v6 + d1];
            float v15;
            {
                v15 = v13 * v14;
            }
            const float v16 = v3[d0*v7 + d1];
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
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_1);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_2);
fusedelementwise_65103cc08144e30af8e8fc36eefb3e503e891d0e16c924d596099d2b(meta_buf_3);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_4);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_5);
fusedelementwise_7b13be09769198a212aeef961987061901ccbdd15c4b2ba5d894ae86(meta_buf_6);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_7);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_8);
fusedelementwise_9b674ab2245bc82ef3051776861c2d2abb8631d97840be07733c7987(meta_buf_9);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_10);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_11);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_12);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_13);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_14);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_15);
fusedelementwise_e277bbe409cd60201bb9ac6e958baa53566cc8cbafe32718b91293a2(meta_buf_16);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_17);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_18);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_19);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_20);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_21);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_22);
fusedelementwise_7c7a967fde8a4d7a5b35e05efe5b6c6bfec9533ed7a8f23d959ff8cd(meta_buf_23);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_24);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_25);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_26);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_27);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_28);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_29);
fusedelementwise_e277bbe409cd60201bb9ac6e958baa53566cc8cbafe32718b91293a2(meta_buf_30);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_31);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_32);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_33);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_34);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_35);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_36);
fusedelementwise_e277bbe409cd60201bb9ac6e958baa53566cc8cbafe32718b91293a2(meta_buf_37);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_38);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_39);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_40);
fusedelementwise_39f491a753592bd6d9a83c6f76917012b5eb3c0ac597e095aa174319(meta_buf_41);
im2col_54f86552263d1a348fd988a8122143d1a6ec1c1aa7867ba5833442fb(meta_buf_42);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_43);
fusedelementwise_4bb46c1ecf24503baf4c5281daa8fdf6b67e788c7d3bdb7b90b3d30b(meta_buf_44);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_45);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_46);
fusedelementwise_56ca5795fe00ce775fda07d409cff3b926d3c78ebda9d035b1638b4c(meta_buf_47);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_48);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_49);
fusedelementwise_7b13be09769198a212aeef961987061901ccbdd15c4b2ba5d894ae86(meta_buf_50);
tensordot_b0c87b9ad9c24d5c638538a68fd9e1ad2b472c70c0e98883fad5c6af(meta_buf_51);
col2im_73909fb9a6e4f41fa36d633023909781659562b6438922487c8f9efc(meta_buf_52);
fusedelementwise_53ead169c7750031ee68a27ea19713c5a06ab6f1d3954345add48e2e(meta_buf_53);

}

