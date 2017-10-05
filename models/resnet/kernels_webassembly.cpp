
#include <stdlib.h>
#include <math.h>

float static_buffer[29289832];
float* dynamic_buffer = nullptr;

int meta_buf_0[] = {29139304,25526632,1,3,224,224,112,112,7,7,1,1,2,2,3,3};
int meta_buf_1[] = {25526632,0,28135784,12544,64,147};
int meta_buf_2[] = {9408,28135784,26329448,64,64,64,12544};
int meta_buf_3[] = {26329448,27132264,1,112,112,64,56,56,3,3,2,2,0,0};
int meta_buf_4[] = {27132264,9472,28135784,3136,256,64};
int meta_buf_5[] = {27132264,25856,27332968,3136,64,64};
int meta_buf_6[] = {29952,27332968,27332968,64,64,64,3136};
int meta_buf_7[] = {27332968,25526632,1,64,56,56,56,56,3,3,1,1,1,1,1,1};
int meta_buf_8[] = {25526632,30016,28938600,3136,64,576};
int meta_buf_9[] = {66880,28938600,28938600,64,64,64,3136};
int meta_buf_10[] = {28938600,66944,27332968,3136,256,64};
int meta_buf_11[] = {83328,27332968,28135784,27332968,256,256,256,256,3136};
int meta_buf_12[] = {27332968,83584,28737896,3136,64,256};
int meta_buf_13[] = {99968,28737896,28737896,64,64,64,3136};
int meta_buf_14[] = {28737896,25526632,1,64,56,56,56,56,3,3,1,1,1,1,1,1};
int meta_buf_15[] = {25526632,100032,28938600,3136,64,576};
int meta_buf_16[] = {136896,28938600,28938600,64,64,64,3136};
int meta_buf_17[] = {28938600,136960,28135784,3136,256,64};
int meta_buf_18[] = {153344,28135784,27332968,28135784,256,256,256,256,3136};
int meta_buf_19[] = {28135784,153600,27332968,3136,64,256};
int meta_buf_20[] = {169984,27332968,27332968,64,64,64,3136};
int meta_buf_21[] = {27332968,25526632,1,64,56,56,56,56,3,3,1,1,1,1,1,1};
int meta_buf_22[] = {25526632,170048,27332968,3136,64,576};
int meta_buf_23[] = {206912,27332968,27332968,64,64,64,3136};
int meta_buf_24[] = {27332968,206976,25526632,3136,256,64};
int meta_buf_25[] = {223360,25526632,28135784,26329448,256,256,256,256,3136};
int meta_buf_26[] = {26329448,27132264,1,256,56,56,28,28,1,1,1,1,2,2,0,0};
int meta_buf_27[] = {27132264,223616,28135784,784,512,256};
int meta_buf_28[] = {26329448,27132264,1,256,56,56,28,28,1,1,1,1,2,2,0,0};
int meta_buf_29[] = {27132264,354688,28737896,784,128,256};
int meta_buf_30[] = {387456,28737896,28737896,128,128,128,784};
int meta_buf_31[] = {28737896,25526632,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_32[] = {25526632,387584,27132264,784,128,1152};
int meta_buf_33[] = {535040,27132264,27132264,128,128,128,784};
int meta_buf_34[] = {27132264,535168,26429800,784,512,128};
int meta_buf_35[] = {600704,26429800,28135784,26429800,512,512,512,512,784};
int meta_buf_36[] = {26429800,601216,27132264,784,128,512};
int meta_buf_37[] = {666752,27132264,27132264,128,128,128,784};
int meta_buf_38[] = {27132264,25526632,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_39[] = {25526632,666880,27132264,784,128,1152};
int meta_buf_40[] = {814336,27132264,27232616,128,128,128,784};
int meta_buf_41[] = {27232616,814464,26831208,784,512,128};
int meta_buf_42[] = {880000,26831208,26429800,26831208,512,512,512,512,784};
int meta_buf_43[] = {26831208,880512,27232616,784,128,512};
int meta_buf_44[] = {946048,27232616,28737896,128,128,128,784};
int meta_buf_45[] = {28737896,25526632,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_46[] = {25526632,946176,27232616,784,128,1152};
int meta_buf_47[] = {1093632,27232616,27232616,128,128,128,784};
int meta_buf_48[] = {27232616,1093760,28135784,784,512,128};
int meta_buf_49[] = {1159296,28135784,26831208,28537192,512,512,512,512,784};
int meta_buf_50[] = {28537192,1159808,27232616,784,128,512};
int meta_buf_51[] = {1225344,27232616,27232616,128,128,128,784};
int meta_buf_52[] = {27232616,25526632,1,128,28,28,28,28,3,3,1,1,1,1,1,1};
int meta_buf_53[] = {25526632,1225472,27232616,784,128,1152};
int meta_buf_54[] = {1372928,27232616,27232616,128,128,128,784};
int meta_buf_55[] = {27232616,1373056,26831208,784,512,128};
int meta_buf_56[] = {1438592,26831208,28537192,27332968,512,512,512,512,784};
int meta_buf_57[] = {27332968,28737896,1,512,28,28,14,14,1,1,1,1,2,2,0,0};
int meta_buf_58[] = {28737896,1439104,27132264,196,1024,512};
int meta_buf_59[] = {27332968,28737896,1,512,28,28,14,14,1,1,1,1,2,2,0,0};
int meta_buf_60[] = {28737896,1963392,28838248,196,256,512};
int meta_buf_61[] = {2094464,28838248,28838248,256,256,256,196};
int meta_buf_62[] = {28838248,26329448,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_63[] = {26329448,2094720,28838248,196,256,2304};
int meta_buf_64[] = {2684544,28838248,28838248,256,256,256,196};
int meta_buf_65[] = {28838248,2684800,28537192,196,1024,256};
int meta_buf_66[] = {2946944,27132264,28537192,28737896,1024,1024,1024,1024,196};
int meta_buf_67[] = {28737896,2947968,27282792,196,256,1024};
int meta_buf_68[] = {3210112,27282792,27332968,256,256,256,196};
int meta_buf_69[] = {27332968,26329448,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_70[] = {26329448,3210368,27282792,196,256,2304};
int meta_buf_71[] = {3800192,27282792,27332968,256,256,256,196};
int meta_buf_72[] = {27332968,3800448,27132264,196,1024,256};
int meta_buf_73[] = {4062592,28737896,27132264,27332968,1024,1024,1024,1024,196};
int meta_buf_74[] = {27332968,4063616,27282792,196,256,1024};
int meta_buf_75[] = {4325760,27282792,27282792,256,256,256,196};
int meta_buf_76[] = {27282792,26329448,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_77[] = {26329448,4326016,27282792,196,256,2304};
int meta_buf_78[] = {4915840,27282792,28838248,256,256,256,196};
int meta_buf_79[] = {28838248,4916096,27132264,196,1024,256};
int meta_buf_80[] = {5178240,27332968,27132264,28737896,1024,1024,1024,1024,196};
int meta_buf_81[] = {28737896,5179264,27282792,196,256,1024};
int meta_buf_82[] = {5441408,27282792,27332968,256,256,256,196};
int meta_buf_83[] = {27332968,26329448,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_84[] = {26329448,5441664,27332968,196,256,2304};
int meta_buf_85[] = {6031488,27332968,27332968,256,256,256,196};
int meta_buf_86[] = {27332968,6031744,27132264,196,1024,256};
int meta_buf_87[] = {6293888,28737896,27132264,28737896,1024,1024,1024,1024,196};
int meta_buf_88[] = {28737896,6294912,27282792,196,256,1024};
int meta_buf_89[] = {6557056,27282792,27282792,256,256,256,196};
int meta_buf_90[] = {27282792,26329448,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_91[] = {26329448,6557312,27282792,196,256,2304};
int meta_buf_92[] = {7147136,27282792,27533672,256,256,256,196};
int meta_buf_93[] = {27533672,7147392,27332968,196,1024,256};
int meta_buf_94[] = {7409536,27332968,28737896,27332968,1024,1024,1024,1024,196};
int meta_buf_95[] = {27332968,7410560,27232616,196,256,1024};
int meta_buf_96[] = {7672704,27232616,27282792,256,256,256,196};
int meta_buf_97[] = {27282792,26329448,1,256,14,14,14,14,3,3,1,1,1,1,1,1};
int meta_buf_98[] = {26329448,7672960,27282792,196,256,2304};
int meta_buf_99[] = {8262784,27282792,28838248,256,256,256,196};
int meta_buf_100[] = {28838248,8263040,27132264,196,1024,256};
int meta_buf_101[] = {8525184,27132264,27332968,27132264,1024,1024,1024,1024,196};
int meta_buf_102[] = {27132264,28838248,1,1024,14,14,7,7,1,1,1,1,2,2,0,0};
int meta_buf_103[] = {28838248,8526208,28737896,49,2048,1024};
int meta_buf_104[] = {27132264,28838248,1,1024,14,14,7,7,1,1,1,1,2,2,0,0};
int meta_buf_105[] = {28838248,10623360,28888424,49,512,1024};
int meta_buf_106[] = {11147648,28888424,28913512,512,512,512,49};
int meta_buf_107[] = {28913512,26831208,1,512,7,7,7,7,3,3,1,1,1,1,1,1};
int meta_buf_108[] = {26831208,11148160,28913512,49,512,4608};
int meta_buf_109[] = {13507456,28913512,28938600,512,512,512,49};
int meta_buf_110[] = {28938600,13507968,27232616,49,2048,512};
int meta_buf_111[] = {14556544,27232616,28737896,27232616,2048,2048,2048,2048,49};
int meta_buf_112[] = {27232616,14558592,28913512,49,512,2048};
int meta_buf_113[] = {15607168,28913512,28938600,512,512,512,49};
int meta_buf_114[] = {28938600,26831208,1,512,7,7,7,7,3,3,1,1,1,1,1,1};
int meta_buf_115[] = {26831208,15607680,28913512,49,512,4608};
int meta_buf_116[] = {17966976,28913512,28938600,512,512,512,49};
int meta_buf_117[] = {28938600,17967488,28737896,49,2048,512};
int meta_buf_118[] = {19016064,27232616,28737896,28838248,2048,2048,2048,2048,49};
int meta_buf_119[] = {28838248,19018112,28938600,49,512,2048};
int meta_buf_120[] = {20066688,28938600,28963688,512,512,512,49};
int meta_buf_121[] = {28963688,26831208,1,512,7,7,7,7,3,3,1,1,1,1,1,1};
int meta_buf_122[] = {26831208,20067200,28963688,49,512,4608};
int meta_buf_123[] = {22426496,28963688,28988776,512,512,512,49};
int meta_buf_124[] = {28988776,22427008,27232616,49,2048,512};
int meta_buf_125[] = {23475584,27232616,28838248,27232616,2048,2048,2048,2048,49};
int meta_buf_126[] = {27232616,28913512,1,7,7,2048,1,1,7,7,7,7,0,0};
int meta_buf_127[] = {28913512,23477632,28915560,1,1000,2048};
int meta_buf_128[] = {25525632,28915560,28915560,1000};
int meta_buf_129[] = {28915560,28915560,1,1000};
int* meta_buffers[] = {meta_buf_0,meta_buf_1,meta_buf_2,meta_buf_3,meta_buf_4,meta_buf_5,meta_buf_6,meta_buf_7,meta_buf_8,meta_buf_9,meta_buf_10,meta_buf_11,meta_buf_12,meta_buf_13,meta_buf_14,meta_buf_15,meta_buf_16,meta_buf_17,meta_buf_18,meta_buf_19,meta_buf_20,meta_buf_21,meta_buf_22,meta_buf_23,meta_buf_24,meta_buf_25,meta_buf_26,meta_buf_27,meta_buf_28,meta_buf_29,meta_buf_30,meta_buf_31,meta_buf_32,meta_buf_33,meta_buf_34,meta_buf_35,meta_buf_36,meta_buf_37,meta_buf_38,meta_buf_39,meta_buf_40,meta_buf_41,meta_buf_42,meta_buf_43,meta_buf_44,meta_buf_45,meta_buf_46,meta_buf_47,meta_buf_48,meta_buf_49,meta_buf_50,meta_buf_51,meta_buf_52,meta_buf_53,meta_buf_54,meta_buf_55,meta_buf_56,meta_buf_57,meta_buf_58,meta_buf_59,meta_buf_60,meta_buf_61,meta_buf_62,meta_buf_63,meta_buf_64,meta_buf_65,meta_buf_66,meta_buf_67,meta_buf_68,meta_buf_69,meta_buf_70,meta_buf_71,meta_buf_72,meta_buf_73,meta_buf_74,meta_buf_75,meta_buf_76,meta_buf_77,meta_buf_78,meta_buf_79,meta_buf_80,meta_buf_81,meta_buf_82,meta_buf_83,meta_buf_84,meta_buf_85,meta_buf_86,meta_buf_87,meta_buf_88,meta_buf_89,meta_buf_90,meta_buf_91,meta_buf_92,meta_buf_93,meta_buf_94,meta_buf_95,meta_buf_96,meta_buf_97,meta_buf_98,meta_buf_99,meta_buf_100,meta_buf_101,meta_buf_102,meta_buf_103,meta_buf_104,meta_buf_105,meta_buf_106,meta_buf_107,meta_buf_108,meta_buf_109,meta_buf_110,meta_buf_111,meta_buf_112,meta_buf_113,meta_buf_114,meta_buf_115,meta_buf_116,meta_buf_117,meta_buf_118,meta_buf_119,meta_buf_120,meta_buf_121,meta_buf_122,meta_buf_123,meta_buf_124,meta_buf_125,meta_buf_126,meta_buf_127,meta_buf_128,meta_buf_129};

extern "C" void init() {
    //static_buffer = (float*)malloc(29289832 * sizeof(float));
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


void fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(const int * meta_buffer)
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
                v8 = v7;
            }
            float v9;
            {
                v9 = v8 + v6;
            }
            float v10;
            {
                v10 = v9 > 0 ? v9 : 0;
            }
            v3[d0 + d1*v5] = v10;
        }
    }
}


void maxpooling2d_6f91142d9d2142f2bf5f971bbd42a9177ff9f0a3847ed38923b3b331(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const int N = meta_buffer[2];
    const int H1 = meta_buffer[3];
    const int W1 = meta_buffer[4];
    const int C = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int SH = meta_buffer[10];
    const int SW = meta_buffer[11];
    const int PH = meta_buffer[12];
    const int PW = meta_buffer[13];

    for (int gid = 0; gid < N * H2 * W2 * C; gid += 1) {
        const int c = gid % C;
        const int w2 = gid / C % W2;
        const int h2 = gid / C / W2 % H2;
        const int n = gid / C / W2 / H2;

        float v = -1e7;
        for (int kh = 0; kh < KH; kh++) {
            const int h1 = h2 * SH - PH + kh;
            if (h1 < 0 || h1 >= H1) continue;
            
            for (int kw = 0; kw < KW; kw++) {
                const int w1 = w2 * SW - PW + kw;
                if (w1 < 0 || w1 >= W1) continue;

                v = v > X[((n * H1 + h1) * W1 + w1) * C + c] ? v : X[((n * H1 + h1) * W1 + w1) * C + c];
            }
        }

        Y[gid] = v;
    }
}


void fusedelementwise_2ce093d93ac0b5d3b6d3b73b17c7bade3312dc25470170fb44f8cc4d(const int * meta_buffer)
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
            const float v9 = v3[d0 + d1*v6];
            float v10;
            {
                v10 = v9;
            }
            const float v11 = v2[d0 + d1*v5];
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
                v14 = v13 + v8;
            }
            float v15;
            {
                v15 = v14 > 0 ? v14 : 0;
            }
            v4[d0 + d1*v7] = v15;
        }
    }
}


void fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(const int * meta_buffer)
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
            float v10;
            {
                v10 = v9;
            }
            const float v11 = v3[d0 + d1*v6];
            float v12;
            {
                v12 = v10 + v11;
            }
            float v13;
            {
                v13 = v12 + v8;
            }
            float v14;
            {
                v14 = v13 > 0 ? v13 : 0;
            }
            v4[d0 + d1*v7] = v14;
        }
    }
}


void fusedelementwise_62663821b309f709821c2bed3c8b27237224b92c6870c152eb790fde(const int * meta_buffer)
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
            float v10;
            {
                v10 = v9;
            }
            const float v11 = v3[d0 + d1*v6];
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
                v14 = v13 + v8;
            }
            float v15;
            {
                v15 = v14 > 0 ? v14 : 0;
            }
            v4[d0 + d1*v7] = v15;
        }
    }
}


void fusedelementwise_5cd7f15149232801a873ef52623c3d929daedba01df91cf3644dee78(const int * meta_buffer)
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
            const float v9 = v3[d0 + d1*v6];
            float v10;
            {
                v10 = v9;
            }
            const float v11 = v2[d0 + d1*v5];
            float v12;
            {
                v12 = v10 + v11;
            }
            float v13;
            {
                v13 = v12 + v8;
            }
            float v14;
            {
                v14 = v13 > 0 ? v13 : 0;
            }
            v4[d0 + d1*v7] = v14;
        }
    }
}


void averagepooling2d_0dbf99a782fff01a6fc6f857e42168c01fb90520d3d4151eba450a23(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const int N = meta_buffer[2];
    const int H1 = meta_buffer[3];
    const int W1 = meta_buffer[4];
    const int C = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
    const int SH = meta_buffer[10];
    const int SW = meta_buffer[11];
    const int PH = meta_buffer[12];
    const int PW = meta_buffer[13];
    
    for (int gid = 0; gid < N * H2 * W2 * C; gid += 1) {
        const int c = gid % C;
        const int w2 = gid / C % W2;
        const int h2 = gid / C / W2 % H2;
        const int n = gid / C / W2 / H2;

        float v = 0;
        for (int kh = 0; kh < KH; kh++) {
            const int h1 = h2 * SH - PH + kh;
            if (h1 < 0 || h1 >= H1) continue;
            
            for (int kw = 0; kw < KW; kw++) {
                const int w1 = w2 * SW - PW + kw;
                if (w1 < 0 || w1 >= W1) continue;

                v += X[((n * H1 + h1) * W1 + w1) * C + c];
            }
        }
        v /= KH * KW;

        Y[gid] = v;
    }
}


void elementwiseadd_98450d361d3b8b06ad718e1e961bda61506f2baab3157c18aecbf897(const int * meta_buffer)
{
    const float * v1 = (static_buffer + meta_buffer[0]);
    const float * v2 = (static_buffer + meta_buffer[1]);
    float * v3 = (static_buffer + meta_buffer[2]);
    const int D0 = meta_buffer[3];
    int d0;
    for (d0 = 0; d0 < D0; d0 += 1) {
        const float v4 = v1[d0];
        const float v5 = v2[d0];
        float v6;
        {
            v6 = v5 + v4;
        }
        v3[d0] = v6;
    }
}


void softmax_be4c2fae32b9326b0ca891226ac9234de828aecba508a30394d8a57e(const int * meta_buffer)
{
    const float *X = (static_buffer + meta_buffer[0]);
    float *Y = (static_buffer + meta_buffer[1]);
    const int N = meta_buffer[2];
    const int C = meta_buffer[3];

    for (int n = 0; n < N; n++) {
        float set_max = X[n * C];
        for (int c = 0; c < C; c++) {
            float val = X[n * C + c];
            if (val > set_max) {
                set_max = val;
            }
        }

        float sum_exp = 0.0F;
        for (int c = 0; c < C; c++) {
            float val = X[n * C + c];
            float exp_x = expf(val - set_max);
            sum_exp += exp_x;
            Y[n * C + c] = exp_x;
        }

        for (int c = 0; c < C; c++) {
            Y[n * C + c] /= sum_exp;
        }
    }
}

extern "C" void run() {
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_0);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_1);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_2);
maxpooling2d_6f91142d9d2142f2bf5f971bbd42a9177ff9f0a3847ed38923b3b331(meta_buf_3);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_4);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_5);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_6);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_7);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_8);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_9);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_10);
fusedelementwise_2ce093d93ac0b5d3b6d3b73b17c7bade3312dc25470170fb44f8cc4d(meta_buf_11);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_12);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_13);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_14);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_15);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_16);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_17);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_18);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_19);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_20);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_21);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_22);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_23);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_24);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_25);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_26);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_27);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_28);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_29);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_30);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_31);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_32);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_33);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_34);
fusedelementwise_2ce093d93ac0b5d3b6d3b73b17c7bade3312dc25470170fb44f8cc4d(meta_buf_35);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_36);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_37);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_38);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_39);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_40);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_41);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_42);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_43);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_44);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_45);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_46);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_47);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_48);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_49);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_50);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_51);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_52);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_53);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_54);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_55);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_56);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_57);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_58);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_59);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_60);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_61);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_62);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_63);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_64);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_65);
fusedelementwise_62663821b309f709821c2bed3c8b27237224b92c6870c152eb790fde(meta_buf_66);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_67);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_68);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_69);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_70);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_71);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_72);
fusedelementwise_5cd7f15149232801a873ef52623c3d929daedba01df91cf3644dee78(meta_buf_73);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_74);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_75);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_76);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_77);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_78);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_79);
fusedelementwise_5cd7f15149232801a873ef52623c3d929daedba01df91cf3644dee78(meta_buf_80);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_81);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_82);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_83);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_84);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_85);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_86);
fusedelementwise_5cd7f15149232801a873ef52623c3d929daedba01df91cf3644dee78(meta_buf_87);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_88);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_89);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_90);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_91);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_92);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_93);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_94);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_95);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_96);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_97);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_98);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_99);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_100);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_101);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_102);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_103);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_104);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_105);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_106);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_107);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_108);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_109);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_110);
fusedelementwise_2ce093d93ac0b5d3b6d3b73b17c7bade3312dc25470170fb44f8cc4d(meta_buf_111);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_112);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_113);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_114);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_115);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_116);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_117);
fusedelementwise_5cd7f15149232801a873ef52623c3d929daedba01df91cf3644dee78(meta_buf_118);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_119);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_120);
im2col_1dc147a294d043a7b2199b007777978656dfb88774a7a9bb20a1039c(meta_buf_121);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_122);
fusedelementwise_836cf370bfcccd97dc25f15a4aa6eb8f09c13876333d031c3a5af5c8(meta_buf_123);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_124);
fusedelementwise_f6680ffb6d13eb69fe8ee704786ebc77ca98cc9c69d1d437564d2413(meta_buf_125);
averagepooling2d_0dbf99a782fff01a6fc6f857e42168c01fb90520d3d4151eba450a23(meta_buf_126);
sgemm_49ee440e78a4467f5e364896610c9bdbdd5dbf08d70b98a210d579d8(meta_buf_127);
elementwiseadd_98450d361d3b8b06ad718e1e961bda61506f2baab3157c18aecbf897(meta_buf_128);
softmax_be4c2fae32b9326b0ca891226ac9234de828aecba508a30394d8a57e(meta_buf_129);

}

