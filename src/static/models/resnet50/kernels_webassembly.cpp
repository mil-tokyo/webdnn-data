
#include <stdlib.h>
#include <math.h>

float weight_buffer[25530472];
float data_buffer[3161088];


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

void sgemm_e58448c8d8e9ab889dfd6a9e6298112d59e889332353b9405590c438(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 12544, 147);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 147, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 12544, 64);
    //Eigen::Map<Eigen::Matrix<float, 12544, 147, Eigen::RowMajor> > a_mat(A, 12544, 147);
    //Eigen::Map<Eigen::Matrix<float, 147, 64, Eigen::RowMajor> > b_mat(B, 147, 64);
    //Eigen::Map<Eigen::Matrix<float, 12544, 64, Eigen::RowMajor> > c_mat(C, 12544, 64);

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


void max_pooling_2d_d27c15c6131e10e697ea321d1d162eaf95702afa5946aac4dc69f2e1(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];
    const int N = meta_buffer[2];
    const int H1 = meta_buffer[3];
    const int W1 = meta_buffer[4];
    const int C = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int K = meta_buffer[8];
    const int S = meta_buffer[9];
    const int P = meta_buffer[10];
    
    //%%INITIALIZER_ATTACHABLE_PLACEHOLDER%%

    for (int gid = 0; gid < N * H2 * W2 * C; gid += 1) {
        const int c = gid % C;
        const int w2 = gid / C % W2;
        const int h2 = gid / C / W2 % H2;
        const int n = gid / C / W2 / H2;

        float v = -1e7;
        for (int kh = 0; kh < K; kh++) {
            const int h1 = h2 * S - P + kh;
            if (h1 < 0 || h1 >= H1) continue;
            
            for (int kw = 0; kw < K; kw++) {
                const int w1 = w2 * S - P + kw;
                if (w1 < 0 || w1 >= W1) continue;

                v = v > X[((n * H1 + h1) * W1 + w1) * C + c] ? v : X[((n * H1 + h1) * W1 + w1) * C + c];
            }
        }

        //Y[gid] = %%CHANNELWISE_ATTACHABLE(v, n)%%;
        Y[gid] = v;
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_e3ff083257b11857b7ea6e1ccc0c4e157a8c0fd0b64dc72877bba893(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 3136, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 64, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 3136, 64);
    //Eigen::Map<Eigen::Matrix<float, 3136, 64, Eigen::RowMajor> > a_mat(A, 3136, 64);
    //Eigen::Map<Eigen::Matrix<float, 64, 64, Eigen::RowMajor> > b_mat(B, 64, 64);
    //Eigen::Map<Eigen::Matrix<float, 3136, 64, Eigen::RowMajor> > c_mat(C, 3136, 64);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_793497983724ac3e85620a3ede2dddd6ef593b8a959aa7df5a7624a4(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 3136, 576);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 576, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 3136, 64);
    //Eigen::Map<Eigen::Matrix<float, 3136, 576, Eigen::RowMajor> > a_mat(A, 3136, 576);
    //Eigen::Map<Eigen::Matrix<float, 576, 64, Eigen::RowMajor> > b_mat(B, 576, 64);
    //Eigen::Map<Eigen::Matrix<float, 3136, 64, Eigen::RowMajor> > c_mat(C, 3136, 64);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_fe523763e4d9cded005681aa21cb2abf0805411df7f86af5e9b96760(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 3136, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 64, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 3136, 256);
    //Eigen::Map<Eigen::Matrix<float, 3136, 64, Eigen::RowMajor> > a_mat(A, 3136, 64);
    //Eigen::Map<Eigen::Matrix<float, 64, 256, Eigen::RowMajor> > b_mat(B, 64, 256);
    //Eigen::Map<Eigen::Matrix<float, 3136, 256, Eigen::RowMajor> > c_mat(C, 3136, 256);

    c_mat.noalias() = a_mat * b_mat;
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

void sgemm_4c35e62ad87fd1932782b4dfb6e46ff4b4f5c93ce1012c656e4d8387(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 3136, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 256, 64);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 3136, 64);
    //Eigen::Map<Eigen::Matrix<float, 3136, 256, Eigen::RowMajor> > a_mat(A, 3136, 256);
    //Eigen::Map<Eigen::Matrix<float, 256, 64, Eigen::RowMajor> > b_mat(B, 256, 64);
    //Eigen::Map<Eigen::Matrix<float, 3136, 64, Eigen::RowMajor> > c_mat(C, 3136, 64);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_1f108a3f8d9e719eae25d77371636820b30851cdc529e94331e71bd7(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 784, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 256, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 784, 512);
    //Eigen::Map<Eigen::Matrix<float, 784, 256, Eigen::RowMajor> > a_mat(A, 784, 256);
    //Eigen::Map<Eigen::Matrix<float, 256, 512, Eigen::RowMajor> > b_mat(B, 256, 512);
    //Eigen::Map<Eigen::Matrix<float, 784, 512, Eigen::RowMajor> > c_mat(C, 784, 512);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_097d69aac20b0d159ff0c8f13baabd2ba9aff56d96c369bbd500816f(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 784, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 256, 128);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 784, 128);
    //Eigen::Map<Eigen::Matrix<float, 784, 256, Eigen::RowMajor> > a_mat(A, 784, 256);
    //Eigen::Map<Eigen::Matrix<float, 256, 128, Eigen::RowMajor> > b_mat(B, 256, 128);
    //Eigen::Map<Eigen::Matrix<float, 784, 128, Eigen::RowMajor> > c_mat(C, 784, 128);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_fa14b22af8e9b02569656ee5ac2d742e0f15433adda2f5bb711c383f(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 784, 1152);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 1152, 128);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 784, 128);
    //Eigen::Map<Eigen::Matrix<float, 784, 1152, Eigen::RowMajor> > a_mat(A, 784, 1152);
    //Eigen::Map<Eigen::Matrix<float, 1152, 128, Eigen::RowMajor> > b_mat(B, 1152, 128);
    //Eigen::Map<Eigen::Matrix<float, 784, 128, Eigen::RowMajor> > c_mat(C, 784, 128);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_8d3839126336a9ac31ba9fa5e9fbf70f55c17898f76ad0c2edc95722(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 784, 128);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 128, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 784, 512);
    //Eigen::Map<Eigen::Matrix<float, 784, 128, Eigen::RowMajor> > a_mat(A, 784, 128);
    //Eigen::Map<Eigen::Matrix<float, 128, 512, Eigen::RowMajor> > b_mat(B, 128, 512);
    //Eigen::Map<Eigen::Matrix<float, 784, 512, Eigen::RowMajor> > c_mat(C, 784, 512);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_f654dd93f8b45dd41c34007f813732e2b64f91b0af95f426e0b0c8c6(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 784, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 512, 128);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 784, 128);
    //Eigen::Map<Eigen::Matrix<float, 784, 512, Eigen::RowMajor> > a_mat(A, 784, 512);
    //Eigen::Map<Eigen::Matrix<float, 512, 128, Eigen::RowMajor> > b_mat(B, 512, 128);
    //Eigen::Map<Eigen::Matrix<float, 784, 128, Eigen::RowMajor> > c_mat(C, 784, 128);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_f1743f9de37c6af6829900daec0893379fa08ff8f6f8c93124d10eb1(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 196, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 512, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 196, 256);
    //Eigen::Map<Eigen::Matrix<float, 196, 512, Eigen::RowMajor> > a_mat(A, 196, 512);
    //Eigen::Map<Eigen::Matrix<float, 512, 256, Eigen::RowMajor> > b_mat(B, 512, 256);
    //Eigen::Map<Eigen::Matrix<float, 196, 256, Eigen::RowMajor> > c_mat(C, 196, 256);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_50053403e1b5086ae3d6c797de007ce0ad46be5ebcb80b931b54221b(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 196, 2304);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 2304, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 196, 256);
    //Eigen::Map<Eigen::Matrix<float, 196, 2304, Eigen::RowMajor> > a_mat(A, 196, 2304);
    //Eigen::Map<Eigen::Matrix<float, 2304, 256, Eigen::RowMajor> > b_mat(B, 2304, 256);
    //Eigen::Map<Eigen::Matrix<float, 196, 256, Eigen::RowMajor> > c_mat(C, 196, 256);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_5fb117bdf380effcfa3d12930ea49b47cf96295104fd218136411400(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 196, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 256, 1024);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 196, 1024);
    //Eigen::Map<Eigen::Matrix<float, 196, 256, Eigen::RowMajor> > a_mat(A, 196, 256);
    //Eigen::Map<Eigen::Matrix<float, 256, 1024, Eigen::RowMajor> > b_mat(B, 256, 1024);
    //Eigen::Map<Eigen::Matrix<float, 196, 1024, Eigen::RowMajor> > c_mat(C, 196, 1024);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_f63164ed6f0e0aa3693180824170422171577f7f1a75c3f1537a3224(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 196, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 512, 1024);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 196, 1024);
    //Eigen::Map<Eigen::Matrix<float, 196, 512, Eigen::RowMajor> > a_mat(A, 196, 512);
    //Eigen::Map<Eigen::Matrix<float, 512, 1024, Eigen::RowMajor> > b_mat(B, 512, 1024);
    //Eigen::Map<Eigen::Matrix<float, 196, 1024, Eigen::RowMajor> > c_mat(C, 196, 1024);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_15a136307b66cd2af356e3a5f3dc09d35b89e241b808182ec69feea9(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 196, 1024);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 1024, 256);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 196, 256);
    //Eigen::Map<Eigen::Matrix<float, 196, 1024, Eigen::RowMajor> > a_mat(A, 196, 1024);
    //Eigen::Map<Eigen::Matrix<float, 1024, 256, Eigen::RowMajor> > b_mat(B, 1024, 256);
    //Eigen::Map<Eigen::Matrix<float, 196, 256, Eigen::RowMajor> > c_mat(C, 196, 256);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_2a0da29054116255434c11c5d19642eef202eeb7c7c39c4a53d6d8db(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 49, 1024);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 1024, 2048);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 49, 2048);
    //Eigen::Map<Eigen::Matrix<float, 49, 1024, Eigen::RowMajor> > a_mat(A, 49, 1024);
    //Eigen::Map<Eigen::Matrix<float, 1024, 2048, Eigen::RowMajor> > b_mat(B, 1024, 2048);
    //Eigen::Map<Eigen::Matrix<float, 49, 2048, Eigen::RowMajor> > c_mat(C, 49, 2048);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_66759a1708cb7319aa1e0f6d987a6fb208d414d0a54349c0c6f10cfe(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 49, 1024);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 1024, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 49, 512);
    //Eigen::Map<Eigen::Matrix<float, 49, 1024, Eigen::RowMajor> > a_mat(A, 49, 1024);
    //Eigen::Map<Eigen::Matrix<float, 1024, 512, Eigen::RowMajor> > b_mat(B, 1024, 512);
    //Eigen::Map<Eigen::Matrix<float, 49, 512, Eigen::RowMajor> > c_mat(C, 49, 512);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_4c0f4b7f4c9be0010411851f5b5f7b540e092e2381a2af513e8a6e4d(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 49, 4608);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 4608, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 49, 512);
    //Eigen::Map<Eigen::Matrix<float, 49, 4608, Eigen::RowMajor> > a_mat(A, 49, 4608);
    //Eigen::Map<Eigen::Matrix<float, 4608, 512, Eigen::RowMajor> > b_mat(B, 4608, 512);
    //Eigen::Map<Eigen::Matrix<float, 49, 512, Eigen::RowMajor> > c_mat(C, 49, 512);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_37151628e63c48c1d0b518ee4743c57d12caebcdc2c89d1514aab25b(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 49, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 512, 2048);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 49, 2048);
    //Eigen::Map<Eigen::Matrix<float, 49, 512, Eigen::RowMajor> > a_mat(A, 49, 512);
    //Eigen::Map<Eigen::Matrix<float, 512, 2048, Eigen::RowMajor> > b_mat(B, 512, 2048);
    //Eigen::Map<Eigen::Matrix<float, 49, 2048, Eigen::RowMajor> > c_mat(C, 49, 2048);

    c_mat.noalias() = a_mat * b_mat;
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_9ea5de6396a67dc8f7c6a27759f571bf1827a281f671da42f23c93eb(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 49, 2048);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 2048, 512);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 49, 512);
    //Eigen::Map<Eigen::Matrix<float, 49, 2048, Eigen::RowMajor> > a_mat(A, 49, 2048);
    //Eigen::Map<Eigen::Matrix<float, 2048, 512, Eigen::RowMajor> > b_mat(B, 2048, 512);
    //Eigen::Map<Eigen::Matrix<float, 49, 512, Eigen::RowMajor> > c_mat(C, 49, 512);

    c_mat.noalias() = a_mat * b_mat;
}


void average_pooling_2d_0f021c4dab36f6288e619b8a8ea4a9395a331f540eac78915e407985(const int * meta_buffer)
{
    const float *X = data_buffer + meta_buffer[0];
    float *Y = data_buffer + meta_buffer[1];
    const int N = meta_buffer[2];
    const int H1 = meta_buffer[3];
    const int W1 = meta_buffer[4];
    const int C = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int K = meta_buffer[8];
    const int S = meta_buffer[9];
    const int P = meta_buffer[10];
    
    //%%INITIALIZER_ATTACHABLE_PLACEHOLDER%%

    for (int gid = 0; gid < N * H2 * W2 * C; gid += 1) {
        const int c = gid % C;
        const int w2 = gid / C % W2;
        const int h2 = gid / C / W2 % H2;
        const int n = gid / C / W2 / H2;

        float v = 0;
        for (int kh = 0; kh < K; kh++) {
            const int h1 = h2 * S - P + kh;
            if (h1 < 0 || h1 >= H1) continue;
            
            for (int kw = 0; kw < K; kw++) {
                const int w1 = w2 * S - P + kw;
                if (w1 < 0 || w1 >= W1) continue;

                v += X[((n * H1 + h1) * W1 + w1) * C + c];
            }
        }
        v /= K * K;

        //Y[gid] = %%CHANNELWISE_ATTACHABLE(v, n)%%;
        Y[gid] = v;
    }
}


#ifndef INCLUDE_EIGEN
#define INCLUDE_EIGEN
#include <Eigen/Dense>
#endif

void sgemm_b1a8d8479055526f489ded887e3e5298245aa9cefcc0c4421321473d(const int * meta_buffer)
{
    float *A = data_buffer + meta_buffer[0];
    float *B = weight_buffer + meta_buffer[1];
    float *C = data_buffer + meta_buffer[2];

    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > a_mat(A, 1, 2048);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > b_mat(B, 2048, 1000);
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> > c_mat(C, 1, 1000);
    //Eigen::Map<Eigen::Matrix<float, 1, 2048, Eigen::RowMajor> > a_mat(A, 1, 2048);
    //Eigen::Map<Eigen::Matrix<float, 2048, 1000, Eigen::RowMajor> > b_mat(B, 2048, 1000);
    //Eigen::Map<Eigen::Matrix<float, 1, 1000, Eigen::RowMajor> > c_mat(C, 1, 1000);

    c_mat.noalias() = a_mat * b_mat;
}

extern "C" void init() {
    //weight_buffer = (float*)malloc(25530472 * sizeof(float));
    //data_buffer = (float*)malloc(3161088 * sizeof(float));
}

extern "C" float* get_weight_buffer(void) {
    return weight_buffer;
}

extern "C" float* get_data_buffer(void) {
    return data_buffer;
}



extern "C" void run() {
const int meta_buf_0[] = {0,953344,1,3,224,224,112,112,7,7,2,2,3,3};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_0);
const int meta_buf_1[] = {953344,1639680,150528,12544,64,147};
sgemm_e58448c8d8e9ab889dfd6a9e6298112d59e889332353b9405590c438(meta_buf_1);
const int meta_buf_2[] = {150528,150528,14369960,12544,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_2);
const int meta_buf_3[] = {150528,150528,802816};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_3);
const int meta_buf_4[] = {150528,2157568,1,112,112,64,56,56,3,2,0};
max_pooling_2d_d27c15c6131e10e697ea321d1d162eaf95702afa5946aac4dc69f2e1(meta_buf_4);
const int meta_buf_5[] = {2157568,11396072,150528,3136,64,64};
sgemm_e3ff083257b11857b7ea6e1ccc0c4e157a8c0fd0b64dc72877bba893(meta_buf_5);
const int meta_buf_6[] = {150528,150528,4599680,3136,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_6);
const int meta_buf_7[] = {150528,150528,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_7);
const int meta_buf_8[] = {150528,351232,1,64,56,56,56,56,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_8);
const int meta_buf_9[] = {351232,11828072,2358272,3136,64,576};
sgemm_793497983724ac3e85620a3ede2dddd6ef593b8a959aa7df5a7624a4(meta_buf_9);
const int meta_buf_10[] = {2358272,2358272,14369896,3136,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_10);
const int meta_buf_11[] = {2358272,2358272,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_11);
const int meta_buf_12[] = {2358272,13168616,150528,3136,256,64};
sgemm_fe523763e4d9cded005681aa21cb2abf0805411df7f86af5e9b96760(meta_buf_12);
const int meta_buf_13[] = {150528,150528,12233576,3136,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_13);
const int meta_buf_14[] = {2157568,6632640,953344,3136,256,64};
sgemm_fe523763e4d9cded005681aa21cb2abf0805411df7f86af5e9b96760(meta_buf_14);
const int meta_buf_15[] = {953344,953344,11401192,3136,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_15);
const int meta_buf_16[] = {150528,953344,150528,802816};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_16);
const int meta_buf_17[] = {150528,150528,802816};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_17);
const int meta_buf_18[] = {150528,9813056,953344,3136,64,256};
sgemm_4c35e62ad87fd1932782b4dfb6e46ff4b4f5c93ce1012c656e4d8387(meta_buf_18);
const int meta_buf_19[] = {953344,953344,18976488,3136,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_19);
const int meta_buf_20[] = {953344,953344,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_20);
const int meta_buf_21[] = {953344,1154048,1,64,56,56,56,56,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_21);
const int meta_buf_22[] = {1154048,9899304,953344,3136,64,576};
sgemm_793497983724ac3e85620a3ede2dddd6ef593b8a959aa7df5a7624a4(meta_buf_22);
const int meta_buf_23[] = {953344,953344,10198824,3136,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_23);
const int meta_buf_24[] = {953344,953344,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_24);
const int meta_buf_25[] = {953344,11313896,2358272,3136,256,64};
sgemm_fe523763e4d9cded005681aa21cb2abf0805411df7f86af5e9b96760(meta_buf_25);
const int meta_buf_26[] = {2358272,2358272,24481640,3136,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_26);
const int meta_buf_27[] = {2358272,150528,2358272,802816};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_27);
const int meta_buf_28[] = {2358272,2358272,802816};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_28);
const int meta_buf_29[] = {2358272,11811560,150528,3136,64,256};
sgemm_4c35e62ad87fd1932782b4dfb6e46ff4b4f5c93ce1012c656e4d8387(meta_buf_29);
const int meta_buf_30[] = {150528,150528,21073704,3136,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_30);
const int meta_buf_31[] = {150528,150528,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_31);
const int meta_buf_32[] = {150528,351232,1,64,56,56,56,56,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_32);
const int meta_buf_33[] = {351232,11933544,2157568,3136,64,576};
sgemm_793497983724ac3e85620a3ede2dddd6ef593b8a959aa7df5a7624a4(meta_buf_33);
const int meta_buf_34[] = {2157568,2157568,1649216,3136,64};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_34);
const int meta_buf_35[] = {2157568,2157568,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_35);
const int meta_buf_36[] = {2157568,12496616,150528,3136,256,64};
sgemm_fe523763e4d9cded005681aa21cb2abf0805411df7f86af5e9b96760(meta_buf_36);
const int meta_buf_37[] = {150528,150528,4993472,3136,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_37);
const int meta_buf_38[] = {150528,2358272,150528,802816};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_38);
const int meta_buf_39[] = {150528,150528,802816};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_39);
const int meta_buf_40[] = {150528,953344,1,256,56,56,28,28,1,1,2,2,0,0};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_40);
const int meta_buf_41[] = {953344,14436072,1254400,784,512,256};
sgemm_1f108a3f8d9e719eae25d77371636820b30851cdc529e94331e71bd7(meta_buf_41);
const int meta_buf_42[] = {1254400,1254400,7238976,784,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_42);
const int meta_buf_43[] = {150528,953344,1,256,56,56,28,28,1,1,2,2,0,0};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_43);
const int meta_buf_44[] = {953344,13596904,150528,784,128,256};
sgemm_097d69aac20b0d159ff0c8f13baabd2ba9aff56d96c369bbd500816f(meta_buf_44);
const int meta_buf_45[] = {150528,150528,9830568,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_45);
const int meta_buf_46[] = {150528,150528,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_46);
const int meta_buf_47[] = {150528,250880,1,128,28,28,28,28,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_47);
const int meta_buf_48[] = {250880,14221928,1154048,784,128,1152};
sgemm_fa14b22af8e9b02569656ee5ac2d742e0f15433adda2f5bb711c383f(meta_buf_48);
const int meta_buf_49[] = {1154048,1154048,10198888,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_49);
const int meta_buf_50[] = {1154048,1154048,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_50);
const int meta_buf_51[] = {1154048,14370024,150528,784,512,128};
sgemm_8d3839126336a9ac31ba9fa5e9fbf70f55c17898f76ad0c2edc95722(meta_buf_51);
const int meta_buf_52[] = {150528,150528,11400168,784,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_52);
const int meta_buf_53[] = {150528,1254400,150528,401408};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_53);
const int meta_buf_54[] = {150528,150528,401408};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_54);
const int meta_buf_55[] = {150528,14831336,551936,784,128,512};
sgemm_f654dd93f8b45dd41c34007f813732e2b64f91b0af95f426e0b0c8c6(meta_buf_55);
const int meta_buf_56[] = {551936,551936,11827944,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_56);
const int meta_buf_57[] = {551936,551936,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_57);
const int meta_buf_58[] = {551936,652288,1,128,28,28,28,28,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_58);
const int meta_buf_59[] = {652288,15421160,551936,784,128,1152};
sgemm_fa14b22af8e9b02569656ee5ac2d742e0f15433adda2f5bb711c383f(meta_buf_59);
const int meta_buf_60[] = {551936,551936,12495976,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_60);
const int meta_buf_61[] = {551936,551936,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_61);
const int meta_buf_62[] = {551936,9832744,1254400,784,512,128};
sgemm_8d3839126336a9ac31ba9fa5e9fbf70f55c17898f76ad0c2edc95722(meta_buf_62);
const int meta_buf_63[] = {1254400,1254400,13186024,784,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_63);
const int meta_buf_64[] = {1254400,150528,1254400,401408};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_64);
const int meta_buf_65[] = {1254400,1254400,401408};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_65);
const int meta_buf_66[] = {1254400,11330280,150528,784,128,512};
sgemm_f654dd93f8b45dd41c34007f813732e2b64f91b0af95f426e0b0c8c6(meta_buf_66);
const int meta_buf_67[] = {150528,150528,13629928,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_67);
const int meta_buf_68[] = {150528,150528,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_68);
const int meta_buf_69[] = {150528,250880,1,128,28,28,28,28,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_69);
const int meta_buf_70[] = {250880,11401448,1154048,784,128,1152};
sgemm_fa14b22af8e9b02569656ee5ac2d742e0f15433adda2f5bb711c383f(meta_buf_70);
const int meta_buf_71[] = {1154048,1154048,1649088,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_71);
const int meta_buf_72[] = {1154048,1154048,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_72);
const int meta_buf_73[] = {1154048,11866984,150528,784,512,128};
sgemm_8d3839126336a9ac31ba9fa5e9fbf70f55c17898f76ad0c2edc95722(meta_buf_73);
const int meta_buf_74[] = {150528,150528,4861888,784,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_74);
const int meta_buf_75[] = {150528,1254400,150528,401408};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_75);
const int meta_buf_76[] = {150528,150528,401408};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_76);
const int meta_buf_77[] = {150528,13103080,551936,784,128,512};
sgemm_f654dd93f8b45dd41c34007f813732e2b64f91b0af95f426e0b0c8c6(meta_buf_77);
const int meta_buf_78[] = {551936,551936,7238848,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_78);
const int meta_buf_79[] = {551936,551936,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_79);
const int meta_buf_80[] = {551936,652288,1,128,28,28,28,28,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_80);
const int meta_buf_81[] = {652288,13187048,551936,784,128,1152};
sgemm_fa14b22af8e9b02569656ee5ac2d742e0f15433adda2f5bb711c383f(meta_buf_81);
const int meta_buf_82[] = {551936,551936,9829440,784,128};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_82);
const int meta_buf_83[] = {551936,551936,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_83);
const int meta_buf_84[] = {551936,0,702464,784,512,128};
sgemm_8d3839126336a9ac31ba9fa5e9fbf70f55c17898f76ad0c2edc95722(meta_buf_84);
const int meta_buf_85[] = {702464,702464,9936168,784,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_85);
const int meta_buf_86[] = {702464,150528,702464,401408};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_86);
const int meta_buf_87[] = {702464,702464,401408};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_87);
const int meta_buf_88[] = {702464,200704,1,512,28,28,14,14,1,1,2,2,0,0};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_88);
const int meta_buf_89[] = {200704,4862400,150528,196,256,512};
sgemm_f1743f9de37c6af6829900daec0893379fa08ff8f6f8c93124d10eb1(meta_buf_89);
const int meta_buf_90[] = {150528,150528,11395816,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_90);
const int meta_buf_91[] = {150528,150528,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_91);
const int meta_buf_92[] = {150528,200704,1,256,14,14,14,14,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_92);
const int meta_buf_93[] = {200704,6649024,652288,196,256,2304};
sgemm_50053403e1b5086ae3d6c797de007ce0ad46be5ebcb80b931b54221b(meta_buf_93);
const int meta_buf_94[] = {652288,652288,11811304,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_94);
const int meta_buf_95[] = {652288,652288,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_95);
const int meta_buf_96[] = {652288,7502912,150528,196,1024,256};
sgemm_5fb117bdf380effcfa3d12930ea49b47cf96295104fd218136411400(meta_buf_96);
const int meta_buf_97[] = {150528,150528,11970408,196,1024};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_97);
const int meta_buf_98[] = {702464,551936,1,512,28,28,14,14,1,1,2,2,0,0};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_98);
const int meta_buf_99[] = {551936,10199528,351232,196,1024,512};
sgemm_f63164ed6f0e0aa3693180824170422171577f7f1a75c3f1537a3224(meta_buf_99);
const int meta_buf_100[] = {351232,351232,13185000,196,1024};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_100);
const int meta_buf_101[] = {150528,351232,150528,200704};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_101);
const int meta_buf_102[] = {150528,150528,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_102);
const int meta_buf_103[] = {150528,12233832,351232,196,256,1024};
sgemm_15a136307b66cd2af356e3a5f3dc09d35b89e241b808182ec69feea9(meta_buf_103);
const int meta_buf_104[] = {351232,351232,13629672,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_104);
const int meta_buf_105[] = {351232,351232,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_105);
const int meta_buf_106[] = {351232,401408,1,256,14,14,14,14,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_106);
const int meta_buf_107[] = {401408,13630056,351232,196,256,2304};
sgemm_50053403e1b5086ae3d6c797de007ce0ad46be5ebcb80b931b54221b(meta_buf_107);
const int meta_buf_108[] = {351232,351232,66560,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_108);
const int meta_buf_109[] = {351232,351232,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_109);
const int meta_buf_110[] = {351232,328960,702464,196,1024,256};
sgemm_5fb117bdf380effcfa3d12930ea49b47cf96295104fd218136411400(meta_buf_110);
const int meta_buf_111[] = {702464,702464,4598656,196,1024};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_111);
const int meta_buf_112[] = {702464,150528,702464,200704};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_112);
const int meta_buf_113[] = {702464,702464,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_113);
const int meta_buf_114[] = {702464,4599744,150528,196,256,1024};
sgemm_15a136307b66cd2af356e3a5f3dc09d35b89e241b808182ec69feea9(meta_buf_114);
const int meta_buf_115[] = {150528,150528,6632384,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_115);
const int meta_buf_116[] = {150528,150528,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_116);
const int meta_buf_117[] = {150528,200704,1,256,14,14,14,14,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_117);
const int meta_buf_118[] = {200704,6042560,652288,196,256,2304};
sgemm_50053403e1b5086ae3d6c797de007ce0ad46be5ebcb80b931b54221b(meta_buf_118);
const int meta_buf_119[] = {652288,652288,7502656,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_119);
const int meta_buf_120[] = {652288,652288,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_120);
const int meta_buf_121[] = {652288,7240512,150528,196,1024,256};
sgemm_5fb117bdf380effcfa3d12930ea49b47cf96295104fd218136411400(meta_buf_121);
const int meta_buf_122[] = {150528,150528,9898280,196,1024};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_122);
const int meta_buf_123[] = {150528,702464,150528,200704};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_123);
const int meta_buf_124[] = {150528,150528,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_124);
const int meta_buf_125[] = {150528,9936680,351232,196,256,1024};
sgemm_15a136307b66cd2af356e3a5f3dc09d35b89e241b808182ec69feea9(meta_buf_125);
const int meta_buf_126[] = {351232,351232,11313640,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_126);
const int meta_buf_127[] = {351232,351232,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_127);
const int meta_buf_128[] = {351232,401408,1,256,14,14,14,14,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_128);
const int meta_buf_129[] = {401408,10723816,351232,196,256,2304};
sgemm_50053403e1b5086ae3d6c797de007ce0ad46be5ebcb80b931b54221b(meta_buf_129);
const int meta_buf_130[] = {351232,351232,11811048,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_130);
const int meta_buf_131[] = {351232,351232,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_131);
const int meta_buf_132[] = {351232,11548904,702464,196,1024,256};
sgemm_5fb117bdf380effcfa3d12930ea49b47cf96295104fd218136411400(meta_buf_132);
const int meta_buf_133[] = {702464,702464,11932520,196,1024};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_133);
const int meta_buf_134[] = {702464,150528,702464,200704};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_134);
const int meta_buf_135[] = {702464,702464,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_135);
const int meta_buf_136[] = {702464,11971432,150528,196,256,1024};
sgemm_15a136307b66cd2af356e3a5f3dc09d35b89e241b808182ec69feea9(meta_buf_136);
const int meta_buf_137[] = {150528,150528,13102824,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_137);
const int meta_buf_138[] = {150528,150528,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_138);
const int meta_buf_139[] = {150528,200704,1,256,14,14,14,14,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_139);
const int meta_buf_140[] = {200704,12513000,652288,196,256,2304};
sgemm_50053403e1b5086ae3d6c797de007ce0ad46be5ebcb80b931b54221b(meta_buf_140);
const int meta_buf_141[] = {652288,652288,13596648,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_141);
const int meta_buf_142[] = {652288,652288,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_142);
const int meta_buf_143[] = {652288,13334504,150528,196,1024,256};
sgemm_5fb117bdf380effcfa3d12930ea49b47cf96295104fd218136411400(meta_buf_143);
const int meta_buf_144[] = {150528,150528,65536,196,1024};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_144);
const int meta_buf_145[] = {150528,702464,150528,200704};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_145);
const int meta_buf_146[] = {150528,150528,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_146);
const int meta_buf_147[] = {150528,66816,351232,196,256,1024};
sgemm_15a136307b66cd2af356e3a5f3dc09d35b89e241b808182ec69feea9(meta_buf_147);
const int meta_buf_148[] = {351232,351232,4598400,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_148);
const int meta_buf_149[] = {351232,351232,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_149);
const int meta_buf_150[] = {351232,401408,1,256,14,14,14,14,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_150);
const int meta_buf_151[] = {401408,4008576,852992,196,256,2304};
sgemm_50053403e1b5086ae3d6c797de007ce0ad46be5ebcb80b931b54221b(meta_buf_151);
const int meta_buf_152[] = {852992,852992,6042304,196,256};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_152);
const int meta_buf_153[] = {852992,852992,50176};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_153);
const int meta_buf_154[] = {852992,14567144,351232,196,1024,256};
sgemm_5fb117bdf380effcfa3d12930ea49b47cf96295104fd218136411400(meta_buf_154);
const int meta_buf_155[] = {351232,351232,7239488,196,1024};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_155);
const int meta_buf_156[] = {351232,150528,351232,200704};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_156);
const int meta_buf_157[] = {351232,351232,200704};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_157);
const int meta_buf_158[] = {351232,150528,1,1024,14,14,7,7,1,1,2,2,0,0};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_158);
const int meta_buf_159[] = {150528,18976552,551936,49,2048,1024};
sgemm_2a0da29054116255434c11c5d19642eef202eeb7c7c39c4a53d6d8db(meta_buf_159);
const int meta_buf_160[] = {551936,551936,9830696,49,2048};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_160);
const int meta_buf_161[] = {351232,175616,1,1024,14,14,7,7,1,1,2,2,0,0};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_161);
const int meta_buf_162[] = {175616,14896872,150528,49,512,1024};
sgemm_66759a1708cb7319aa1e0f6d987a6fb208d414d0a54349c0c6f10cfe(meta_buf_162);
const int meta_buf_163[] = {150528,150528,10199016,49,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_163);
const int meta_buf_164[] = {150528,150528,25088};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_164);
const int meta_buf_165[] = {150528,175616,1,512,7,7,7,7,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_165);
const int meta_buf_166[] = {175616,15568616,401408,49,512,4608};
sgemm_4c0f4b7f4c9be0010411851f5b5f7b540e092e2381a2af513e8a6e4d(meta_buf_166);
const int meta_buf_167[] = {401408,401408,11400680,49,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_167);
const int meta_buf_168[] = {401408,401408,25088};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_168);
const int meta_buf_169[] = {401408,17927912,150528,49,2048,512};
sgemm_37151628e63c48c1d0b518ee4743c57d12caebcdc2c89d1514aab25b(meta_buf_169);
const int meta_buf_170[] = {150528,150528,11864936,49,2048};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_170);
const int meta_buf_171[] = {150528,551936,150528,100352};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_171);
const int meta_buf_172[] = {150528,150528,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_172);
const int meta_buf_173[] = {150528,21073768,250880,49,512,2048};
sgemm_9ea5de6396a67dc8f7c6a27759f571bf1827a281f671da42f23c93eb(meta_buf_173);
const int meta_buf_174[] = {250880,250880,12496104,49,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_174);
const int meta_buf_175[] = {250880,250880,25088};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_175);
const int meta_buf_176[] = {250880,275968,1,512,7,7,7,7,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_176);
const int meta_buf_177[] = {275968,22122344,250880,49,512,4608};
sgemm_4c0f4b7f4c9be0010411851f5b5f7b540e092e2381a2af513e8a6e4d(meta_buf_177);
const int meta_buf_178[] = {250880,250880,13186536,49,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_178);
const int meta_buf_179[] = {250880,250880,25088};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_179);
const int meta_buf_180[] = {250880,24481896,426496,49,2048,512};
sgemm_37151628e63c48c1d0b518ee4743c57d12caebcdc2c89d1514aab25b(meta_buf_180);
const int meta_buf_181[] = {426496,426496,14219880,49,2048};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_181);
const int meta_buf_182[] = {426496,150528,426496,100352};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_182);
const int meta_buf_183[] = {426496,426496,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_183);
const int meta_buf_184[] = {426496,591104,150528,49,512,2048};
sgemm_9ea5de6396a67dc8f7c6a27759f571bf1827a281f671da42f23c93eb(meta_buf_184);
const int meta_buf_185[] = {150528,150528,14369384,49,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_185);
const int meta_buf_186[] = {150528,150528,25088};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_186);
const int meta_buf_187[] = {150528,175616,1,512,7,7,7,7,3,3,1,1,1,1};
im2col_bc00b53e478359c9136f25ec94004097a9f9a23b63fa471d7d94c024(meta_buf_187);
const int meta_buf_188[] = {175616,1649280,401408,49,512,4608};
sgemm_4c0f4b7f4c9be0010411851f5b5f7b540e092e2381a2af513e8a6e4d(meta_buf_188);
const int meta_buf_189[] = {401408,401408,14435560,49,512};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_189);
const int meta_buf_190[] = {401408,401408,25088};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_190);
const int meta_buf_191[] = {401408,4993728,150528,49,2048,512};
sgemm_37151628e63c48c1d0b518ee4743c57d12caebcdc2c89d1514aab25b(meta_buf_191);
const int meta_buf_192[] = {150528,150528,14829288,49,2048};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_192);
const int meta_buf_193[] = {150528,426496,150528,100352};
elementwise_sum_2de037c0a2a429b1ddee1b4f920ff6064addf54dcd9393cd330cf31e(meta_buf_193);
const int meta_buf_194[] = {150528,150528,100352};
relu_38b93c941d9be218213d7a4df3d61e01dc9bd9faccb952ee1d8e7527(meta_buf_194);
const int meta_buf_195[] = {150528,250880,1,7,7,2048,1,1,7,1,0};
average_pooling_2d_0f021c4dab36f6288e619b8a8ea4a9395a331f540eac78915e407985(meta_buf_195);
const int meta_buf_196[] = {250880,7765056,150528,1,1000,2048};
sgemm_b1a8d8479055526f489ded887e3e5298245aa9cefcc0c4421321473d(meta_buf_196);
const int meta_buf_197[] = {150528,150528,9829568,1,1000};
axiswise_bias_8f7059caf267f55d8f581647dc04a65fb4d4bf2a0c60e2f0d3dfd6d7(meta_buf_197);

}

