
#include <stdlib.h>
#include <math.h>

float static_buffer[9673347];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {9590403,8705667,27648,3,3,27648};
int meta_buf_1[] = {8705667,1987203,1,3,144,192,144,192,9,9,1,1,1,1,4,4};
int meta_buf_2[] = {1987203,0,8705667,27648,32,243};
int meta_buf_3[] = {7808,7776,7840,8705667,5526147,32,32,32,27648};
int meta_buf_4[] = {5526147,1987203,1,32,144,192,72,96,4,4,1,1,2,2,1,1};
int meta_buf_5[] = {1987203,7872,5968515,6912,64,512};
int meta_buf_6[] = {40704,40640,40768,5968515,5968515,64,64,64,6912};
int meta_buf_7[] = {5968515,1987203,1,64,72,96,36,48,4,4,1,1,2,2,1,1};
int meta_buf_8[] = {1987203,40832,5968515,1728,128,1024};
int meta_buf_9[] = {172032,171904,172160,5968515,6632067,128,1728,128,1728};
int meta_buf_10[] = {6632067,6189699,1728,128,128,1728};
int meta_buf_11[] = {6189699,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_12[] = {1987203,172288,7737987,1728,128,1152};
int meta_buf_13[] = {319872,319744,7737987,7737987,128,128,128,1728};
int meta_buf_14[] = {7737987,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_15[] = {1987203,320000,6853251,1728,128,1152};
int meta_buf_16[] = {467584,467456,6632067,6853251,6632067,1728,128,1728,128,1728};
int meta_buf_17[] = {6632067,6853251,1728,128,128,1728};
int meta_buf_18[] = {6853251,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_19[] = {1987203,467712,7074435,1728,128,1152};
int meta_buf_20[] = {615168,615296,7074435,7295619,128,128,128,1728};
int meta_buf_21[] = {7295619,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_22[] = {1987203,615424,7295619,1728,128,1152};
int meta_buf_23[] = {762880,763008,7295619,6632067,7516803,128,1728,1728,128,1728};
int meta_buf_24[] = {7516803,7737987,1728,128,128,1728};
int meta_buf_25[] = {7737987,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_26[] = {1987203,763136,5968515,1728,128,1152};
int meta_buf_27[] = {910592,910720,5968515,6189699,128,128,128,1728};
int meta_buf_28[] = {6189699,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_29[] = {1987203,910848,6189699,1728,128,1152};
int meta_buf_30[] = {1058432,1058304,7516803,6189699,6410883,1728,128,1728,128,1728};
int meta_buf_31[] = {6410883,6632067,1728,128,128,1728};
int meta_buf_32[] = {6632067,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_33[] = {1987203,1058560,6632067,1728,128,1152};
int meta_buf_34[] = {1206144,1206016,6632067,6853251,128,128,128,1728};
int meta_buf_35[] = {6853251,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_36[] = {1987203,1206272,6853251,1728,128,1152};
int meta_buf_37[] = {1353728,1353856,6853251,6410883,7074435,128,1728,1728,128,1728};
int meta_buf_38[] = {7074435,7295619,1728,128,128,1728};
int meta_buf_39[] = {7295619,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_40[] = {1987203,1353984,7295619,1728,128,1152};
int meta_buf_41[] = {1501568,1501440,7295619,7516803,128,128,128,1728};
int meta_buf_42[] = {7516803,1987203,1,128,36,48,36,48,3,3,1,1,1,1,1,1};
int meta_buf_43[] = {1987203,1501696,6632067,1728,128,1152};
int meta_buf_44[] = {1649280,1649152,7074435,6632067,5968515,1728,128,128,128,1728};
int meta_buf_45[] = {5968515,1649408,1987203,1728,1024,128};
int meta_buf_46[] = {5526147,1987203,1,36,48,64,72,96,4,4,2,2,1,1};
int meta_buf_47[] = {1780480,1780544,1780608,5526147,5968515,64,64,64,6912};
int meta_buf_48[] = {5968515,1780672,1987203,6912,512,64};
int meta_buf_49[] = {5526147,1987203,1,72,96,32,144,192,4,4,2,2,1,1};
int meta_buf_50[] = {1813504,1813440,1813472,5526147,8705667,32,32,32,27648};
int meta_buf_51[] = {8705667,1813536,1987203,27648,243,32};
int meta_buf_52[] = {8705667,1987203,1,144,192,3,144,192,9,9,1,1,4,4};
int meta_buf_53[] = {1904259,1821312,1821315,8705667,7737987,27648,27648,3,27648,3,27648};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5,meta_buf_6,meta_buf_7,meta_buf_8,meta_buf_9,meta_buf_10,meta_buf_11,meta_buf_12,meta_buf_13,meta_buf_14,meta_buf_15,meta_buf_16,meta_buf_17,meta_buf_18,meta_buf_19,meta_buf_20,meta_buf_21,meta_buf_22,meta_buf_23,meta_buf_24,meta_buf_25,meta_buf_26,meta_buf_27,meta_buf_28,meta_buf_29,meta_buf_30,meta_buf_31,meta_buf_32,meta_buf_33,meta_buf_34,meta_buf_35,meta_buf_36,meta_buf_37,meta_buf_38,meta_buf_39,meta_buf_40,meta_buf_41,meta_buf_42,meta_buf_43,meta_buf_44,meta_buf_45,meta_buf_46,meta_buf_47,meta_buf_48,meta_buf_49,meta_buf_50,meta_buf_51,meta_buf_52,meta_buf_53};

extern "C" void init() {
    //static_buffer = (float*)malloc(9673347 * sizeof(float));
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

void sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(const int * meta_buffer)
{
    float *A = (static_buffer + meta_buffer[0]);
    float *B = (static_buffer + meta_buffer[1]);
    float *C = (static_buffer + meta_buffer[2]);

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, meta_buffer[3], meta_buffer[5]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, meta_buffer[5], meta_buffer[4]);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, meta_buffer[3], meta_buffer[4]);

    c_mat.noalias() = a_mat * b_mat;
}


void fusedelementwise_ffdfa37b68409e82c963d1c9d3b54731c74202fc29be8296c1dc2a6e(const int * meta_buffer)
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
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 + v9;
            }
            float v14;
            {
                v14 = v13 < 0.0 ? (exp(v13)-1) : v13;
            }
            float v15;
            {
                v15 = v14 * v10;
            }
            float v16;
            {
                v16 = v15 + v8;
            }
            float v17;
            {
                v17 = v16;
            }
            v5[d0 + d1*v7] = v17;
        }
    }
}


void fusedelementwise_f8f827e08848fa438fc29ad5723fcb611c9438b77486ec0dfc0da8d5(const int * meta_buffer)
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
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 + v9;
            }
            float v14;
            {
                v14 = v13 < 0.0 ? (exp(v13)-1) : v13;
            }
            float v15;
            {
                v15 = v14 * v10;
            }
            float v16;
            {
                v16 = v15 + v8;
            }
            v5[d0*v7 + d1] = v16;
        }
    }
}


void fusedelementwise_76b9dc92c2fb5c2a9a65e1ad1b5a701bf4a62fb9bf57f1cb528782c1(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int D0 = meta_buffer[6];
    const int D1 = meta_buffer[7];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v7 = v1[d0];
        const float v8 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v3[d0 + d1*v5];
            float v10;
            {
                v10 = v9;
            }
            float v11;
            {
                v11 = v10 * v7;
            }
            float v12;
            {
                v12 = v11 + v8;
            }
            float v13;
            {
                v13 = v12 > 0 ? v12 : 0;
            }
            float v14;
            {
                v14 = v13;
            }
            v4[d0 + d1*v6] = v14;
        }
    }
}


void fusedelementwise_38c1ade3e3f960fda14ca2ef77953bd87bf628de20269b465824a1fd(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int v8 = meta_buffer[7];
    const int D0 = meta_buffer[8];
    const int D1 = meta_buffer[9];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v9 = v1[d0];
        const float v10 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v7];
            float v12;
            {
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 * v9;
            }
            const float v14 = v3[d0*v6 + d1];
            float v15;
            {
                v15 = v13 + v14;
            }
            float v16;
            {
                v16 = v15 + v10;
            }
            v5[d0*v8 + d1] = v16;
        }
    }
}


void fusedelementwise_26dd77e74b458d68edc3d003daf7cf86ada86d3bc47184d7d00922e1(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int D0 = meta_buffer[6];
    const int D1 = meta_buffer[7];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v7 = v1[d0];
        const float v8 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v9 = v3[d0 + d1*v5];
            float v10;
            {
                v10 = v9;
            }
            float v11;
            {
                v11 = v10 * v8;
            }
            float v12;
            {
                v12 = v11 + v7;
            }
            float v13;
            {
                v13 = v12 > 0 ? v12 : 0;
            }
            float v14;
            {
                v14 = v13;
            }
            v4[d0 + d1*v6] = v14;
        }
    }
}


void fusedelementwise_a5962ec1d3bd54da9eede10e738cd923bb8386141f377fba522808a4(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int v8 = meta_buffer[7];
    const int D0 = meta_buffer[8];
    const int D1 = meta_buffer[9];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v9 = v1[d0];
        const float v10 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v3[d0 + d1*v6];
            float v12;
            {
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 * v10;
            }
            const float v14 = v4[d0*v7 + d1];
            float v15;
            {
                v15 = v13 + v14;
            }
            float v16;
            {
                v16 = v15 + v9;
            }
            v5[d0*v8 + d1] = v16;
        }
    }
}


void fusedelementwise_151a5de81005b89644181e3dd3b97b17eef578f51fe1d573d0661048(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    const float * v3 = (static_buffer + meta_buffer[2]);
    const float * v4 = (static_buffer + meta_buffer[3]);
    float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int v8 = meta_buffer[7];
    const int D0 = meta_buffer[8];
    const int D1 = meta_buffer[9];
    int d0;
    for (d0 = ((1 > 8) ? (0 % (1 / 8)) : 0); d0 < D0; d0 += ((1 > 8) ? (1 / 8) : 1)) {
        const float v9 = v1[d0];
        const float v10 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v7];
            float v12;
            {
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 * v9;
            }
            const float v14 = v3[d0*v6 + d1];
            float v15;
            {
                v15 = v13 + v14;
            }
            float v16;
            {
                v16 = v15 + v10;
            }
            float v17;
            {
                v17 = v16;
            }
            v5[d0 + d1*v8] = v17;
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


void fusedelementwise_288374f19bbd372e8634439d6729b977401b8e90ecdc19fb62dfab87(const int * meta_buffer)
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
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 + v8;
            }
            float v14;
            {
                v14 = v13 < 0.0 ? (exp(v13)-1) : v13;
            }
            float v15;
            {
                v15 = v14 * v10;
            }
            float v16;
            {
                v16 = v15 + v9;
            }
            float v17;
            {
                v17 = v16;
            }
            v5[d0 + d1*v7] = v17;
        }
    }
}


void fusedelementwise_3a4ef8c9c147fce2d26f9f7d2455b87804e4b567e345be70573011f4(const int * meta_buffer)
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
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 + v9;
            }
            float v14;
            {
                v14 = v13 < 0.0 ? (exp(v13)-1) : v13;
            }
            float v15;
            {
                v15 = v14 * v8;
            }
            float v16;
            {
                v16 = v15 + v10;
            }
            float v17;
            {
                v17 = v16;
            }
            v5[d0 + d1*v7] = v17;
        }
    }
}


void fusedelementwise_151c290e3bd15d47780e2fcb623164b5f63edb4affd6893d8348b5c8(const int * meta_buffer)
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
        const float v10 = v2[d0];
        int d1;
        for (d1 = ((1 > 8) ? (0 / (1 / 8)) : 0); d1 < D1; d1 += ((1 > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v8];
            float v12;
            {
                v12 = v11;
            }
            float v13;
            {
                v13 = v12 + v10;
            }
            float v14;
            {
                v14 = tanh(v13);
            }
            const float v15 = v1[d0*v6 + d1];
            float v16;
            {
                v16 = v14 * v15;
            }
            const float v17 = v3[d0*v7 + d1];
            float v18;
            {
                v18 = v16 + v17;
            }
            v5[d0*v9 + d1] = v18;
        }
    }
}

extern "C" void run() {
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_0);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_1);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_2);
fusedelementwise_ffdfa37b68409e82c963d1c9d3b54731c74202fc29be8296c1dc2a6e(meta_buf_3);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_4);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_5);
fusedelementwise_ffdfa37b68409e82c963d1c9d3b54731c74202fc29be8296c1dc2a6e(meta_buf_6);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_7);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_8);
fusedelementwise_f8f827e08848fa438fc29ad5723fcb611c9438b77486ec0dfc0da8d5(meta_buf_9);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_10);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_11);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_12);
fusedelementwise_76b9dc92c2fb5c2a9a65e1ad1b5a701bf4a62fb9bf57f1cb528782c1(meta_buf_13);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_14);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_15);
fusedelementwise_38c1ade3e3f960fda14ca2ef77953bd87bf628de20269b465824a1fd(meta_buf_16);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_17);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_18);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_19);
fusedelementwise_26dd77e74b458d68edc3d003daf7cf86ada86d3bc47184d7d00922e1(meta_buf_20);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_21);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_22);
fusedelementwise_a5962ec1d3bd54da9eede10e738cd923bb8386141f377fba522808a4(meta_buf_23);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_24);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_25);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_26);
fusedelementwise_26dd77e74b458d68edc3d003daf7cf86ada86d3bc47184d7d00922e1(meta_buf_27);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_28);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_29);
fusedelementwise_38c1ade3e3f960fda14ca2ef77953bd87bf628de20269b465824a1fd(meta_buf_30);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_31);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_32);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_33);
fusedelementwise_76b9dc92c2fb5c2a9a65e1ad1b5a701bf4a62fb9bf57f1cb528782c1(meta_buf_34);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_35);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_36);
fusedelementwise_a5962ec1d3bd54da9eede10e738cd923bb8386141f377fba522808a4(meta_buf_37);
transpose_3ede431373fd6b14a21ca5a7f2fab289eb4c42220e346f22acc816e8(meta_buf_38);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_39);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_40);
fusedelementwise_76b9dc92c2fb5c2a9a65e1ad1b5a701bf4a62fb9bf57f1cb528782c1(meta_buf_41);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_42);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_43);
fusedelementwise_151a5de81005b89644181e3dd3b97b17eef578f51fe1d573d0661048(meta_buf_44);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_45);
col2im_c27ba017d8daabdc8a3c3b2e9bf5f029051ad380aed0be391c790d0e(meta_buf_46);
fusedelementwise_288374f19bbd372e8634439d6729b977401b8e90ecdc19fb62dfab87(meta_buf_47);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_48);
col2im_c27ba017d8daabdc8a3c3b2e9bf5f029051ad380aed0be391c790d0e(meta_buf_49);
fusedelementwise_3a4ef8c9c147fce2d26f9f7d2455b87804e4b567e345be70573011f4(meta_buf_50);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_51);
col2im_c27ba017d8daabdc8a3c3b2e9bf5f029051ad380aed0be391c790d0e(meta_buf_52);
fusedelementwise_151c290e3bd15d47780e2fcb623164b5f63edb4affd6893d8348b5c8(meta_buf_53);

}

