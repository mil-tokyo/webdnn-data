
#include <stdlib.h>
#include <math.h>

float weight_buffer[1820035];
float data_buffer[7686144];


void im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(const int * meta_buffer)
{
    const float *im = data_buffer + meta_buffer[0];
    float *col = data_buffer + meta_buffer[1];

    const int N = meta_buffer[2];
    const int C1 = meta_buffer[3];
    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int SH = meta_buffer[10];
    const int SW = meta_buffer[11];
    const int PH = meta_buffer[12];
    const int PW = meta_buffer[13];

    for (int gid = 0; gid < N*H2*W2*KH*KW*C1; gid += 1) {
        const int c1 = gid % C1;
        const int kw = gid / C1 % KW;
        const int kh = gid / C1 / KW % KH;
        const int w2 = gid / C1 / KW / KH % W2;
        const int h2 = gid / C1 / KW / KH / W2 % H2;
        const int  n = gid / C1 / KW / KH / W2 / H2;
        
        const int h1 = h2 * SH - PH + kh;
        const int w1 = w2 * SW - PW + kw;

        col[gid] = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n*H1+h1)*W1+w1)*C1+c1];
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_8a5dc813790b21d9ffa05166832aebd7604b67a171060ee3bbffc8c5(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 27648, 243);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 243, 32);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 27648, 32);
    //Eigen::Map<Eigen::Matrix<float, 27648, 243, Eigen::RowMajor> > a_mat(A, 27648, 243);
    //Eigen::Map<Eigen::Matrix<float, 243, 32, Eigen::RowMajor> > b_mat(B, 243, 32);
    //Eigen::Map<Eigen::Matrix<float, 27648, 32, Eigen::RowMajor> > c_mat(C, 27648, 32);

    c_mat.noalias() = a_mat * b_mat;
}


void axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];
    const float *B = weight_buffer + meta_buffer[2];
    const int N = meta_buffer[3];
    const int C = meta_buffer[4];
  
    for (int gid = 0; gid < N * C; gid += 1) {
        int c = gid % C;
        int n = gid / C;

        float result = X[gid] + B[c];
        Y[n * C + c] = result;
    }
}


void elu_6083d54ecfc443c4d119363723722765c40cb0a53431b05ec6b4f800(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];

    const int N = meta_buffer[2];
  
    for (int gid = 0; gid < N; gid += 1) {
        float result = X[gid];
        result = result < 0.0 ? (expf(result)-1) : result;      
        //Y[gid] = %%ELEMENTWISE_ATTACHABLE(result)%%;
        Y[gid] = result;
    }
}


void axiswise_scale_f4c6e4774a5fec2f7ebbcb201aaf8c2d8728b20a577730022db78bcb(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];
    const float *S = weight_buffer + meta_buffer[2];
    const int N = meta_buffer[3];
    const int C = meta_buffer[4];
  
    for (int gid = 0; gid < N; gid += 1) {
        int c = gid % C;

        float result = X[gid] * S[c];
        //Y[gid] = %%CHANNELWISE_ATTACHABLE(result, c)%%;
        Y[gid] = result;
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_81303a23815d16a44ee9dc122dd109d21aa7445a6e2f33c37ee237d4(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 6912, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 512, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 6912, 64);
    //Eigen::Map<Eigen::Matrix<float, 6912, 512, Eigen::RowMajor> > a_mat(A, 6912, 512);
    //Eigen::Map<Eigen::Matrix<float, 512, 64, Eigen::RowMajor> > b_mat(B, 512, 64);
    //Eigen::Map<Eigen::Matrix<float, 6912, 64, Eigen::RowMajor> > c_mat(C, 6912, 64);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_8c1ec379b1e3da95ab6ca493bce3eedde6990e713b1b139069817e15(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 1728, 1024);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 1024, 128);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 1728, 128);
    //Eigen::Map<Eigen::Matrix<float, 1728, 1024, Eigen::RowMajor> > a_mat(A, 1728, 1024);
    //Eigen::Map<Eigen::Matrix<float, 1024, 128, Eigen::RowMajor> > b_mat(B, 1024, 128);
    //Eigen::Map<Eigen::Matrix<float, 1728, 128, Eigen::RowMajor> > c_mat(C, 1728, 128);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 1728, 1152);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 1152, 128);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 1728, 128);
    //Eigen::Map<Eigen::Matrix<float, 1728, 1152, Eigen::RowMajor> > a_mat(A, 1728, 1152);
    //Eigen::Map<Eigen::Matrix<float, 1152, 128, Eigen::RowMajor> > b_mat(B, 1152, 128);
    //Eigen::Map<Eigen::Matrix<float, 1728, 128, Eigen::RowMajor> > c_mat(C, 1728, 128);

    c_mat.noalias() = a_mat * b_mat;
}


void relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];

    const int N = meta_buffer[2];
  
    for (int gid = 0; gid < N; gid += 1) {
        float result = X[gid];
        result = result < 0.0 ? 0.0 : result;      
        //Y[gid] = %%ELEMENTWISE_ATTACHABLE(result)%%;
        Y[gid] = result;
    }
}


void elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(const int * meta_buffer)
{
    const float *X0 = data_buffer + meta_buffer[0];
    const float *X1 = data_buffer + meta_buffer[1];
    float *Y = data_buffer + meta_buffer[2];
    const int N = meta_buffer[3];
  
    for (int gid = 0; gid < N; gid += 1) {
        float result = X0[gid] + X1[gid];
        //Y[gid] = %%CHANNELWISE_ATTACHABLE(result, c)%%;
        Y[gid] = result;
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_ffd51b3d49899a5dba2cd8faa87d014ff6c2cf5cac37e0f6e10466fa(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 1728, 128);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 128, 1024);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 1728, 1024);
    //Eigen::Map<Eigen::Matrix<float, 1728, 128, Eigen::RowMajor> > a_mat(A, 1728, 128);
    //Eigen::Map<Eigen::Matrix<float, 128, 1024, Eigen::RowMajor> > b_mat(B, 128, 1024);
    //Eigen::Map<Eigen::Matrix<float, 1728, 1024, Eigen::RowMajor> > c_mat(C, 1728, 1024);

    c_mat.noalias() = a_mat * b_mat;
}


void col2im_085c6157f908ef0c5ce49834baf86a62092a5fb7eade79e19107af95(const int * meta_buffer)
{
    const float *col = data_buffer + meta_buffer[1];
    float *im = data_buffer + meta_buffer[0];

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


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_6824fe8a7a5d804f801f3e1db8ca0ee8b2db3b25352c9956c3e1e7e0(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 6912, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 64, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 6912, 512);
    //Eigen::Map<Eigen::Matrix<float, 6912, 64, Eigen::RowMajor> > a_mat(A, 6912, 64);
    //Eigen::Map<Eigen::Matrix<float, 64, 512, Eigen::RowMajor> > b_mat(B, 64, 512);
    //Eigen::Map<Eigen::Matrix<float, 6912, 512, Eigen::RowMajor> > c_mat(C, 6912, 512);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_7cb7c4cffd9b906dbb6298298f44bb0118990fc9a4b7a670ec59b626(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 27648, 32);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 32, 243);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 27648, 243);
    //Eigen::Map<Eigen::Matrix<float, 27648, 32, Eigen::RowMajor> > a_mat(A, 27648, 32);
    //Eigen::Map<Eigen::Matrix<float, 32, 243, Eigen::RowMajor> > b_mat(B, 32, 243);
    //Eigen::Map<Eigen::Matrix<float, 27648, 243, Eigen::RowMajor> > c_mat(C, 27648, 243);

    c_mat.noalias() = a_mat * b_mat;
}


void tanh_a11f9e7504997e42430ed569998600addd25e2eb1ce2f3e65b72f920(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];

    const int N = meta_buffer[2];
  
    for (int gid = 0; gid < N; gid += 1) {
        float result = X[gid];
        result = tanhf(result);      
        //Y[gid] = %%ELEMENTWISE_ATTACHABLE(result)%%;
        Y[gid] = result;
    }
}


void scalar_affine_c7ec1d4765ba0a1136b77dc27e585a3c6cd5912ed75354b6ceaf9786(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];

    const float scale = *((const float *)(& meta_buffer[3]));
    const float bias = *((const float *)(& meta_buffer[4]));
    const int N = meta_buffer[2];

    for (int gid = 0; gid < N; gid += 1) {
        float result = X[gid];
        result = result * scale + bias;
        //Y[gid] = %%ELEMENTWISE_ATTACHABLE(result)%%;
        Y[gid] = result;
    }
}

extern "C" void init() {
    //weight_buffer = (float*)malloc(1820035 * sizeof(float));
    //data_buffer = (float*)malloc(7686144 * sizeof(float));
}

extern "C" float* get_weight_buffer(void) {
    return weight_buffer;
}

extern "C" float* get_data_buffer(void) {
    return data_buffer;
}



extern "C" void run() {
const int meta_buf_0[] = {0,967680,1,3,144,192,144,192,9,9,1,1,4,4};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_0);
const int meta_buf_1[] = {967680,295523,82944,27648,32,243};
sgemm_8a5dc813790b21d9ffa05166832aebd7604b67a171060ee3bbffc8c5(meta_buf_1);
const int meta_buf_2[] = {82944,82944,295232,27648,32};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_2);
const int meta_buf_3[] = {82944,82944,884736};
elu_6083d54ecfc443c4d119363723722765c40cb0a53431b05ec6b4f800(meta_buf_3);
const int meta_buf_4[] = {82944,82944,598275,884736,32};
axiswise_scale_f4c6e4774a5fec2f7ebbcb201aaf8c2d8728b20a577730022db78bcb(meta_buf_4);
const int meta_buf_5[] = {82944,82944,893987,27648,32};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_5);
const int meta_buf_6[] = {82944,967680,1,32,144,192,72,96,4,4,2,2,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_6);
const int meta_buf_7[] = {967680,598307,82944,6912,64,512};
sgemm_81303a23815d16a44ee9dc122dd109d21aa7445a6e2f33c37ee237d4(meta_buf_7);
const int meta_buf_8[] = {82944,82944,631331,6912,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_8);
const int meta_buf_9[] = {82944,82944,442368};
elu_6083d54ecfc443c4d119363723722765c40cb0a53431b05ec6b4f800(meta_buf_9);
const int meta_buf_10[] = {82944,82944,450755,442368,64};
axiswise_scale_f4c6e4774a5fec2f7ebbcb201aaf8c2d8728b20a577730022db78bcb(meta_buf_10);
const int meta_buf_11[] = {82944,82944,893795,6912,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_11);
const int meta_buf_12[] = {82944,525312,1,64,72,96,36,48,4,4,2,2,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_12);
const int meta_buf_13[] = {525312,631651,82944,1728,128,1024};
sgemm_8c1ec379b1e3da95ab6ca493bce3eedde6990e713b1b139069817e15(meta_buf_13);
const int meta_buf_14[] = {82944,82944,893859,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_14);
const int meta_buf_15[] = {82944,82944,221184};
elu_6083d54ecfc443c4d119363723722765c40cb0a53431b05ec6b4f800(meta_buf_15);
const int meta_buf_16[] = {82944,82944,295264,221184,128};
axiswise_scale_f4c6e4774a5fec2f7ebbcb201aaf8c2d8728b20a577730022db78bcb(meta_buf_16);
const int meta_buf_17[] = {82944,82944,631395,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_17);
const int meta_buf_18[] = {82944,525312,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_18);
const int meta_buf_19[] = {525312,894019,304128,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_19);
const int meta_buf_20[] = {304128,304128,32,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_20);
const int meta_buf_21[] = {304128,304128,221184};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_21);
const int meta_buf_22[] = {304128,525312,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_22);
const int meta_buf_23[] = {525312,1336643,2515968,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_23);
const int meta_buf_24[] = {2515968,2515968,1819907,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_24);
const int meta_buf_25[] = {2515968,82944,2515968,221184};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_25);
const int meta_buf_26[] = {2515968,304128,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_26);
const int meta_buf_27[] = {304128,147680,82944,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_27);
const int meta_buf_28[] = {82944,82944,631523,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_28);
const int meta_buf_29[] = {82944,82944,221184};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_29);
const int meta_buf_30[] = {82944,304128,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_30);
const int meta_buf_31[] = {304128,450819,82944,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_31);
const int meta_buf_32[] = {82944,82944,1336387,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_32);
const int meta_buf_33[] = {82944,2515968,82944,221184};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_33);
const int meta_buf_34[] = {82944,525312,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_34);
const int meta_buf_35[] = {525312,1188931,304128,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_35);
const int meta_buf_36[] = {304128,304128,1484099,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_36);
const int meta_buf_37[] = {304128,304128,221184};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_37);
const int meta_buf_38[] = {304128,525312,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_38);
const int meta_buf_39[] = {525312,1484227,2515968,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_39);
const int meta_buf_40[] = {2515968,2515968,631075,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_40);
const int meta_buf_41[] = {2515968,82944,2515968,221184};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_41);
const int meta_buf_42[] = {2515968,304128,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_42);
const int meta_buf_43[] = {304128,160,82944,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_43);
const int meta_buf_44[] = {82944,82944,1819779,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_44);
const int meta_buf_45[] = {82944,82944,221184};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_45);
const int meta_buf_46[] = {82944,304128,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_46);
const int meta_buf_47[] = {304128,303299,82944,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_47);
const int meta_buf_48[] = {82944,82944,295392,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_48);
const int meta_buf_49[] = {82944,2515968,82944,221184};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_49);
const int meta_buf_50[] = {82944,525312,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_50);
const int meta_buf_51[] = {525312,1041475,304128,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_51);
const int meta_buf_52[] = {304128,304128,631203,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_52);
const int meta_buf_53[] = {304128,304128,221184};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_53);
const int meta_buf_54[] = {304128,525312,1,128,36,48,36,48,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_54);
const int meta_buf_55[] = {525312,1631683,304128,1728,128,1152};
sgemm_f327e0533f510dca6a24854be8effe5c09c238ee7d46d89e916cf3a9(meta_buf_55);
const int meta_buf_56[] = {304128,304128,1336515,1728,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_56);
const int meta_buf_57[] = {304128,82944,304128,221184};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_57);
const int meta_buf_58[] = {304128,762723,525312,1728,1024,128};
sgemm_ffd51b3d49899a5dba2cd8faa87d014ff6c2cf5cac37e0f6e10466fa(meta_buf_58);
const int meta_buf_59[] = {82944,525312,1,36,48,64,72,96,4,4,2,2,1,1};
col2im_085c6157f908ef0c5ce49834baf86a62092a5fb7eade79e19107af95(meta_buf_59);
const int meta_buf_60[] = {82944,82944,147616,6912,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_60);
const int meta_buf_61[] = {82944,82944,442368};
elu_6083d54ecfc443c4d119363723722765c40cb0a53431b05ec6b4f800(meta_buf_61);
const int meta_buf_62[] = {82944,82944,1811939,442368,64};
axiswise_scale_f4c6e4774a5fec2f7ebbcb201aaf8c2d8728b20a577730022db78bcb(meta_buf_62);
const int meta_buf_63[] = {82944,82944,295136,6912,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_63);
const int meta_buf_64[] = {82944,1779139,967680,6912,512,64};
sgemm_6824fe8a7a5d804f801f3e1db8ca0ee8b2db3b25352c9956c3e1e7e0(meta_buf_64);
const int meta_buf_65[] = {82944,967680,1,72,96,32,144,192,4,4,2,2,1,1};
col2im_085c6157f908ef0c5ce49834baf86a62092a5fb7eade79e19107af95(meta_buf_65);
const int meta_buf_66[] = {82944,82944,295200,27648,32};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_66);
const int meta_buf_67[] = {82944,82944,884736};
elu_6083d54ecfc443c4d119363723722765c40cb0a53431b05ec6b4f800(meta_buf_67);
const int meta_buf_68[] = {82944,82944,1811907,884736,32};
axiswise_scale_f4c6e4774a5fec2f7ebbcb201aaf8c2d8728b20a577730022db78bcb(meta_buf_68);
const int meta_buf_69[] = {82944,82944,0,27648,32};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_69);
const int meta_buf_70[] = {82944,1812003,967680,27648,243,32};
sgemm_7cb7c4cffd9b906dbb6298298f44bb0118990fc9a4b7a670ec59b626(meta_buf_70);
const int meta_buf_71[] = {82944,967680,1,144,192,3,144,192,9,9,1,1,4,4};
col2im_085c6157f908ef0c5ce49834baf86a62092a5fb7eade79e19107af95(meta_buf_71);
const int meta_buf_72[] = {82944,82944,295520,27648,3};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_72);
const int meta_buf_73[] = {82944,82944,82944};
tanh_a11f9e7504997e42430ed569998600addd25e2eb1ce2f3e65b72f920(meta_buf_73);
const int meta_buf_74[] = {82944,82944,82944,1124007936,1124007936};
scalar_affine_c7ec1d4765ba0a1136b77dc27e585a3c6cd5912ed75354b6ceaf9786(meta_buf_74);

}

