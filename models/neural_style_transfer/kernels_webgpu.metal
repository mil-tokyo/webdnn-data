
#include <metal_stdlib>
using namespace metal;

#define OPTIMIZE 1

kernel void transpose_1a0fbadea0475062956fc679399ce2f40129cb877aec049982efb309(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    device float * v2 = (static_buffer + meta_buffer[1]);
    const int v3 = meta_buffer[2];
    const int v4 = meta_buffer[3];
    const int D0 = meta_buffer[4];
    const int D1 = meta_buffer[5];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
            const float v5 = v1[d0*v3 + d1];
            float v6;
            {
                v6 = v5;
            }
            v2[d0 + d1*v4] = v6;
        }
    }
}


kernel void im2col_610ebacc9760fdde8961a1533fc2d59c49f32624ba5fb391f7e5c57a(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index_thread[[thread_position_in_threadgroup]],
                          uint index_group[[threadgroup_position_in_grid]])
{
#define SH_EQUAL_1 1
#define SW_EQUAL_1 1
#define DH_EQUAL_1 1
#define DW_EQUAL_1 1
#define C1_DIVIDABLE_BY_4 0


#if OPTIMIZE && C1_DIVIDABLE_BY_4
    const device float4 *im4 = (const device float4 *)((static_buffer + meta_buffer[0]));
    device float4 *col4 = (device float4 *)((static_buffer + meta_buffer[1]));
    const int C1_4 = (meta_buffer[3]) >> 2;
#else
    const device float *im = (static_buffer + meta_buffer[0]);
    device float *col = (static_buffer + meta_buffer[1]);
    const int C1 = meta_buffer[3];
#endif

    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
#if !DH_EQUAL_1
    const int DH = meta_buffer[10];
#endif
#if !DW_EQUAL_1
    const int DW = meta_buffer[11];
#endif
    const int PH = meta_buffer[14];
    const int PW = meta_buffer[15];

#if !OPTIMIZE || !SH_EQUAL_1
    const int SH = meta_buffer[12];
#endif

#if !OPTIMIZE || !SW_EQUAL_1
    const int SW = meta_buffer[13];
#endif

    const int H1P = H1 + 2 * PH;
    const int W1P = W1 + 2 * PW;

    const int w1 = (index_group % W1P) - PW;
    const int h1 = (index_group / W1P % H1P) - PH;
    const int  n = index_group / W1P / H1P;

#if OPTIMIZE && C1_DIVIDABLE_BY_4
    for (int c1_4 = index_thread; c1_4 < C1_4; c1_4 += 64) {
        const float4 v4 = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im4[((n * H1 + h1) * W1 + w1) * C1_4 + c1_4];
#else
    for (int c1 = index_thread; c1 < C1; c1 += 64) {
        const float v = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n * H1 + h1) * W1 + w1) * C1 + c1];
#endif

#if OPTIMIZE && SH_EQUAL_1
        for (int kh = 0; kh < KH; kh++) {
    #if DH_EQUAL_1
            const int h2 = h1 + PH - kh;
    #else
            const int h2 = h1 + PH - kh * DH;
    #endif
    
#else
        for (int kh = (h1 + PH) % SH; kh < KH; kh += SH) {
    #if DH_EQUAL_1
            const int h2 = (h1 + PH - kh) / SH;
    #else
            const int h2 = (h1 + PH - kh * DH) / SH;
    #endif
#endif
            if (h2 < 0 || h2 >= H2) continue;

#if OPTIMIZE && SH_EQUAL_1
            for (int kw = 0; kw < KW; kw++) {
    #if DW_EQUAL_1
                const int w2 = w1 + PW - kw;
    #else
                const int w2 = w1 + PW - kw * DW;
    #endif
#else
            for (int kw = (w1 + PW) % SW; kw < KW; kw += SW) {
    #if DW_EQUAL_1
                const int w2 = (w1 + PW - kw) / SW;
    #else
                const int w2 = (w1 + PW - kw * DW) / SW;
    #endif
#endif
                if (w2 < 0 || w2 >= W2) continue;

#if OPTIMIZE && C1_DIVIDABLE_BY_4
                col4[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1_4 + c1_4] = v4;
#else
                col[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1 + c1] = v;
#endif
            }
        }
    }


#undef SH_EQUAL_1
#undef SW_EQUAL_1
#undef DH_EQUAL_1
#undef DW_EQUAL_1
#undef C1_DIVIDABLE_BY_4
}


kernel void sgemm_5c3040bbee8733926dddc2cc14cdc9216209a32d39c7874cd0198110(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index[[thread_index_in_threadgroup]],
                          uint2 group_position[[threadgroup_position_in_grid]])
{
#define TRANSPOSE_A 1
#define TRANSPOSE_B 1
#define M_DIVIDABLE_BY_64 1
#define N_DIVIDABLE_BY_64 0
#define K_DIVIDABLE_BY_8 0

#if TRANSPOSE_A
    #define A_STRIDE_K 1
    #define A_STRIDE_M K
#else
    #define A_STRIDE_K M
    #define A_STRIDE_M 1
#endif

#if TRANSPOSE_B
    #define B_STRIDE_K N
    #define B_STRIDE_N 1
#else
    #define B_STRIDE_K 1
    #define B_STRIDE_N K
#endif

#if K_DIVIDABLE_BY_8 && M_DIVIDABLE_BY_64  && N_DIVIDABLE_BY_64 && !TRANSPOSE_A && TRANSPOSE_B && OPTIMIZE
    const device float4 *load_target4 = (index & 32) 
        ? (const device float4 *)((static_buffer + meta_buffer[1])) 
        : (const device float4 *)((static_buffer + meta_buffer[0]));
#else
    const device float *load_target = (index & 32) 
        ? ((static_buffer + meta_buffer[1])) 
        : ((static_buffer + meta_buffer[0]));
#endif

    const int M = meta_buffer[3];
    const int N = meta_buffer[4];

    const int K = meta_buffer[5];

    threadgroup float4 shared4[32 * 8 * 2];

    const int stride_k = (index & 32) ? B_STRIDE_K : A_STRIDE_K;
    const int stride_mn = (index & 32) ? B_STRIDE_N : A_STRIDE_M;

    const int m_offset = index & 7;
    const int n_offset = index >> 3;

    const int mn_load_offset = ((index & 32) ? group_position.y : group_position.x) * 64 + (index & 15) * 4;
    const int k_load_offset = ((index & 16) ? 1 : 0);

    int track0 = mn_load_offset * stride_mn + (k_load_offset + 0) * stride_k;
    int track2 = track0 + 2 * stride_k;
    int track4 = track0 + 4 * stride_k;
    int track6 = track0 + 6 * stride_k;

#if !OPTIMIZE || !M_DIVIDABLE_BY_64 || !N_DIVIDABLE_BY_64
    const int max_MN = (index & 32) ? N : M;
#endif

    int shared_offset4 = ((index & 32) ? 16 : 0) + k_load_offset * 32 + (index & 15);
    int read_A_offset4 = m_offset * 2;
    int read_B_offset4 = n_offset * 2 + 16;

    float4 result[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int k = 0;

    while (k < K)
    {
        {
#if OPTIMIZE && K_DIVIDABLE_BY_8
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
        #if OPTIMIZE && !TRANSPOSE_A && TRANSPOSE_B
            shared4[shared_offset4 + 32 * 0] = load_target4[track0 >> 2];
            shared4[shared_offset4 + 32 * 2] = load_target4[track2 >> 2];
            shared4[shared_offset4 + 32 * 4] = load_target4[track4 >> 2];
            shared4[shared_offset4 + 32 * 6] = load_target4[track6 >> 2];
        #else
            shared4[shared_offset4 + 32 * 0] = float4(
                load_target[track0 + stride_mn * 0],
                load_target[track0 + stride_mn * 1],
                load_target[track0 + stride_mn * 2],
                load_target[track0 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 2] = float4(
                load_target[track2 + stride_mn * 0],
                load_target[track2 + stride_mn * 1],
                load_target[track2 + stride_mn * 2],
                load_target[track2 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 4] = float4(
                load_target[track4 + stride_mn * 0],
                load_target[track4 + stride_mn * 1],
                load_target[track4 + stride_mn * 2],
                load_target[track4 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 6] = float4(
                load_target[track6 + stride_mn * 0],
                load_target[track6 + stride_mn * 1],
                load_target[track6 + stride_mn * 2],
                load_target[track6 + stride_mn * 3]
            ); 
        #endif
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 2] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 4] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 6] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
    #endif

            k += 8;
#else
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
            k += 2;
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
            k += 2;
    #endif
#endif
        }

        threadgroup_barrier(mem_flags::mem_threadgroup);

        {
            for (int k_sub = 0; k_sub < 8; k_sub++)
            {
                float4 a00 = shared4[32 * k_sub + read_A_offset4 + 0];
                float4 a01 = shared4[32 * k_sub + read_A_offset4 + 1];
                float4 b00 = shared4[32 * k_sub + read_B_offset4 + 0];
                float4 b01 = shared4[32 * k_sub + read_B_offset4 + 1];

                result[4][0]  += b00[0] * a00[2];
                result[4][1]  += b00[1] * a00[2];
                result[0][1]  += b00[1] * a00[0];
                result[0][0]  += b00[0] * a00[0];
                result[6][0]  += b00[0] * a00[3];
                result[6][1]  += b00[1] * a00[3];
                result[2][1]  += b00[1] * a00[1];
                result[2][0]  += b00[0] * a00[1];
                result[12][0] += b00[0] * a01[2];
                result[12][1] += b00[1] * a01[2];
                result[8][1]  += b00[1] * a01[0];
                result[8][0]  += b00[0] * a01[0];
                result[14][0] += b00[0] * a01[3];
                result[14][1] += b00[1] * a01[3];
                result[10][1] += b00[1] * a01[1];
                result[10][0] += b00[0] * a01[1];

                result[14][2] += b00[2] * a01[3];
                result[14][3] += b00[3] * a01[3];
                result[10][3] += b00[3] * a01[1];
                result[10][2] += b00[2] * a01[1];
                result[12][2] += b00[2] * a01[2];
                result[12][3] += b00[3] * a01[2];
                result[8][3]  += b00[3] * a01[0];
                result[8][2]  += b00[2] * a01[0];
                result[6][2]  += b00[2] * a00[3];
                result[6][3]  += b00[3] * a00[3];
                result[2][3]  += b00[3] * a00[1];
                result[2][2]  += b00[2] * a00[1];
                result[4][2]  += b00[2] * a00[2];
                result[4][3]  += b00[3] * a00[2];
                result[0][3]  += b00[3] * a00[0];
                result[0][2]  += b00[2] * a00[0];

                result[5][0]  += b01[0] * a00[2];
                result[5][1]  += b01[1] * a00[2];
                result[1][1]  += b01[1] * a00[0];
                result[1][0]  += b01[0] * a00[0];
                result[7][0]  += b01[0] * a00[3];
                result[7][1]  += b01[1] * a00[3];
                result[3][1]  += b01[1] * a00[1];
                result[3][0]  += b01[0] * a00[1];
                result[13][0] += b01[0] * a01[2];
                result[13][1] += b01[1] * a01[2];
                result[9][1]  += b01[1] * a01[0];
                result[9][0]  += b01[0] * a01[0];
                result[15][0] += b01[0] * a01[3];
                result[15][1] += b01[1] * a01[3];
                result[11][1] += b01[1] * a01[1];
                result[11][0] += b01[0] * a01[1];

                result[15][2] += b01[2] * a01[3];
                result[15][3] += b01[3] * a01[3];
                result[11][3] += b01[3] * a01[1];
                result[11][2] += b01[2] * a01[1];
                result[13][2] += b01[2] * a01[2];
                result[13][3] += b01[3] * a01[2];
                result[9][3]  += b01[3] * a01[0];
                result[9][2]  += b01[2] * a01[0];
                result[7][2]  += b01[2] * a00[3];
                result[7][3]  += b01[3] * a00[3];
                result[3][3]  += b01[3] * a00[1];
                result[3][2]  += b01[2] * a00[1];
                result[5][2]  += b01[2] * a00[2];
                result[5][3]  += b01[3] * a00[2];
                result[1][3]  += b01[3] * a00[0];
                result[1][2]  += b01[2] * a00[0];
            }
        }

        shared_offset4 ^= 32 * 8;
        read_A_offset4 ^= 32 * 8;
        read_B_offset4 ^= 32 * 8;
        track0 += stride_k * 8;
        track2 += stride_k * 8;
        track4 += stride_k * 8;
        track6 += stride_k * 8;
    }

    {
    
#if OPTIMIZE && N_DIVIDABLE_BY_64
        device float4 *C4 = (device float4 *)((static_buffer + meta_buffer[2]));
        const int N4 = N >> 2;
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {

    #if !M_DIVIDABLE_BY_64
            if (m >= M) continue;
    #endif

            const int n = group_position.y * 16 + n_offset * 2;
            float4 result0 = result[m_sub * 2 + 0];
            float4 result1 = result[m_sub * 2 + 1];

            C4[m * N4 + n + 0] = result0;
            C4[m * N4 + n + 1] = result1;
            
            m++;
        }
#else
        device float *C = (static_buffer + meta_buffer[2]);
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {
            int n = group_position.y * 64 + n_offset * 8;

            for (int n_sub1 = 0; n_sub1 < 2; n_sub1++)
            {
                for (int n_sub2 = 0; n_sub2 < 4; n_sub2++)
                {

    #if OPTIMIZE && M_DIVIDABLE_BY_64
                    (         n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #else
                    (m < M && n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #endif
                    n++;
                }
            }
            
            m++;
        }
#endif

    }


#undef M_DIVIDABLE_BY_64
#undef N_DIVIDABLE_BY_64
#undef K_DIVIDABLE_BY_8
#undef TRANSPOSE_A
#undef TRANSPOSE_B
#undef A_STRIDE_K
#undef B_STRIDE_K
#undef A_STRIDE_M
#undef A_STRIDE_M
}


kernel void fusedelementwise_d041c22ae43431794a0abd277c1ffa8e454fa672f424c95bd9db04b8(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    const device float * v4 = (static_buffer + meta_buffer[3]);
    device float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v8 = v1[d0];
        const float v9 = v2[d0];
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
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


kernel void im2col_a73d6417028f0b285d50e54757b90b31d98ada1211f66bd0af5efb97(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index_thread[[thread_position_in_threadgroup]],
                          uint index_group[[threadgroup_position_in_grid]])
{
#define SH_EQUAL_1 0
#define SW_EQUAL_1 0
#define DH_EQUAL_1 1
#define DW_EQUAL_1 1
#define C1_DIVIDABLE_BY_4 1


#if OPTIMIZE && C1_DIVIDABLE_BY_4
    const device float4 *im4 = (const device float4 *)((static_buffer + meta_buffer[0]));
    device float4 *col4 = (device float4 *)((static_buffer + meta_buffer[1]));
    const int C1_4 = (meta_buffer[3]) >> 2;
#else
    const device float *im = (static_buffer + meta_buffer[0]);
    device float *col = (static_buffer + meta_buffer[1]);
    const int C1 = meta_buffer[3];
#endif

    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
#if !DH_EQUAL_1
    const int DH = meta_buffer[10];
#endif
#if !DW_EQUAL_1
    const int DW = meta_buffer[11];
#endif
    const int PH = meta_buffer[14];
    const int PW = meta_buffer[15];

#if !OPTIMIZE || !SH_EQUAL_1
    const int SH = meta_buffer[12];
#endif

#if !OPTIMIZE || !SW_EQUAL_1
    const int SW = meta_buffer[13];
#endif

    const int H1P = H1 + 2 * PH;
    const int W1P = W1 + 2 * PW;

    const int w1 = (index_group % W1P) - PW;
    const int h1 = (index_group / W1P % H1P) - PH;
    const int  n = index_group / W1P / H1P;

#if OPTIMIZE && C1_DIVIDABLE_BY_4
    for (int c1_4 = index_thread; c1_4 < C1_4; c1_4 += 64) {
        const float4 v4 = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im4[((n * H1 + h1) * W1 + w1) * C1_4 + c1_4];
#else
    for (int c1 = index_thread; c1 < C1; c1 += 64) {
        const float v = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n * H1 + h1) * W1 + w1) * C1 + c1];
#endif

#if OPTIMIZE && SH_EQUAL_1
        for (int kh = 0; kh < KH; kh++) {
    #if DH_EQUAL_1
            const int h2 = h1 + PH - kh;
    #else
            const int h2 = h1 + PH - kh * DH;
    #endif
    
#else
        for (int kh = (h1 + PH) % SH; kh < KH; kh += SH) {
    #if DH_EQUAL_1
            const int h2 = (h1 + PH - kh) / SH;
    #else
            const int h2 = (h1 + PH - kh * DH) / SH;
    #endif
#endif
            if (h2 < 0 || h2 >= H2) continue;

#if OPTIMIZE && SH_EQUAL_1
            for (int kw = 0; kw < KW; kw++) {
    #if DW_EQUAL_1
                const int w2 = w1 + PW - kw;
    #else
                const int w2 = w1 + PW - kw * DW;
    #endif
#else
            for (int kw = (w1 + PW) % SW; kw < KW; kw += SW) {
    #if DW_EQUAL_1
                const int w2 = (w1 + PW - kw) / SW;
    #else
                const int w2 = (w1 + PW - kw * DW) / SW;
    #endif
#endif
                if (w2 < 0 || w2 >= W2) continue;

#if OPTIMIZE && C1_DIVIDABLE_BY_4
                col4[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1_4 + c1_4] = v4;
#else
                col[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1 + c1] = v;
#endif
            }
        }
    }


#undef SH_EQUAL_1
#undef SW_EQUAL_1
#undef DH_EQUAL_1
#undef DW_EQUAL_1
#undef C1_DIVIDABLE_BY_4
}


kernel void sgemm_94f0c54b77dcb1fbad06f386c4665ef898e786f3080ae97e8195afb1(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index[[thread_index_in_threadgroup]],
                          uint2 group_position[[threadgroup_position_in_grid]])
{
#define TRANSPOSE_A 1
#define TRANSPOSE_B 1
#define M_DIVIDABLE_BY_64 1
#define N_DIVIDABLE_BY_64 1
#define K_DIVIDABLE_BY_8 1

#if TRANSPOSE_A
    #define A_STRIDE_K 1
    #define A_STRIDE_M K
#else
    #define A_STRIDE_K M
    #define A_STRIDE_M 1
#endif

#if TRANSPOSE_B
    #define B_STRIDE_K N
    #define B_STRIDE_N 1
#else
    #define B_STRIDE_K 1
    #define B_STRIDE_N K
#endif

#if K_DIVIDABLE_BY_8 && M_DIVIDABLE_BY_64  && N_DIVIDABLE_BY_64 && !TRANSPOSE_A && TRANSPOSE_B && OPTIMIZE
    const device float4 *load_target4 = (index & 32) 
        ? (const device float4 *)((static_buffer + meta_buffer[1])) 
        : (const device float4 *)((static_buffer + meta_buffer[0]));
#else
    const device float *load_target = (index & 32) 
        ? ((static_buffer + meta_buffer[1])) 
        : ((static_buffer + meta_buffer[0]));
#endif

    const int M = meta_buffer[3];
    const int N = meta_buffer[4];

    const int K = meta_buffer[5];

    threadgroup float4 shared4[32 * 8 * 2];

    const int stride_k = (index & 32) ? B_STRIDE_K : A_STRIDE_K;
    const int stride_mn = (index & 32) ? B_STRIDE_N : A_STRIDE_M;

    const int m_offset = index & 7;
    const int n_offset = index >> 3;

    const int mn_load_offset = ((index & 32) ? group_position.y : group_position.x) * 64 + (index & 15) * 4;
    const int k_load_offset = ((index & 16) ? 1 : 0);

    int track0 = mn_load_offset * stride_mn + (k_load_offset + 0) * stride_k;
    int track2 = track0 + 2 * stride_k;
    int track4 = track0 + 4 * stride_k;
    int track6 = track0 + 6 * stride_k;

#if !OPTIMIZE || !M_DIVIDABLE_BY_64 || !N_DIVIDABLE_BY_64
    const int max_MN = (index & 32) ? N : M;
#endif

    int shared_offset4 = ((index & 32) ? 16 : 0) + k_load_offset * 32 + (index & 15);
    int read_A_offset4 = m_offset * 2;
    int read_B_offset4 = n_offset * 2 + 16;

    float4 result[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int k = 0;

    while (k < K)
    {
        {
#if OPTIMIZE && K_DIVIDABLE_BY_8
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
        #if OPTIMIZE && !TRANSPOSE_A && TRANSPOSE_B
            shared4[shared_offset4 + 32 * 0] = load_target4[track0 >> 2];
            shared4[shared_offset4 + 32 * 2] = load_target4[track2 >> 2];
            shared4[shared_offset4 + 32 * 4] = load_target4[track4 >> 2];
            shared4[shared_offset4 + 32 * 6] = load_target4[track6 >> 2];
        #else
            shared4[shared_offset4 + 32 * 0] = float4(
                load_target[track0 + stride_mn * 0],
                load_target[track0 + stride_mn * 1],
                load_target[track0 + stride_mn * 2],
                load_target[track0 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 2] = float4(
                load_target[track2 + stride_mn * 0],
                load_target[track2 + stride_mn * 1],
                load_target[track2 + stride_mn * 2],
                load_target[track2 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 4] = float4(
                load_target[track4 + stride_mn * 0],
                load_target[track4 + stride_mn * 1],
                load_target[track4 + stride_mn * 2],
                load_target[track4 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 6] = float4(
                load_target[track6 + stride_mn * 0],
                load_target[track6 + stride_mn * 1],
                load_target[track6 + stride_mn * 2],
                load_target[track6 + stride_mn * 3]
            ); 
        #endif
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 2] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 4] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 6] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
    #endif

            k += 8;
#else
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
            k += 2;
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
            k += 2;
    #endif
#endif
        }

        threadgroup_barrier(mem_flags::mem_threadgroup);

        {
            for (int k_sub = 0; k_sub < 8; k_sub++)
            {
                float4 a00 = shared4[32 * k_sub + read_A_offset4 + 0];
                float4 a01 = shared4[32 * k_sub + read_A_offset4 + 1];
                float4 b00 = shared4[32 * k_sub + read_B_offset4 + 0];
                float4 b01 = shared4[32 * k_sub + read_B_offset4 + 1];

                result[4][0]  += b00[0] * a00[2];
                result[4][1]  += b00[1] * a00[2];
                result[0][1]  += b00[1] * a00[0];
                result[0][0]  += b00[0] * a00[0];
                result[6][0]  += b00[0] * a00[3];
                result[6][1]  += b00[1] * a00[3];
                result[2][1]  += b00[1] * a00[1];
                result[2][0]  += b00[0] * a00[1];
                result[12][0] += b00[0] * a01[2];
                result[12][1] += b00[1] * a01[2];
                result[8][1]  += b00[1] * a01[0];
                result[8][0]  += b00[0] * a01[0];
                result[14][0] += b00[0] * a01[3];
                result[14][1] += b00[1] * a01[3];
                result[10][1] += b00[1] * a01[1];
                result[10][0] += b00[0] * a01[1];

                result[14][2] += b00[2] * a01[3];
                result[14][3] += b00[3] * a01[3];
                result[10][3] += b00[3] * a01[1];
                result[10][2] += b00[2] * a01[1];
                result[12][2] += b00[2] * a01[2];
                result[12][3] += b00[3] * a01[2];
                result[8][3]  += b00[3] * a01[0];
                result[8][2]  += b00[2] * a01[0];
                result[6][2]  += b00[2] * a00[3];
                result[6][3]  += b00[3] * a00[3];
                result[2][3]  += b00[3] * a00[1];
                result[2][2]  += b00[2] * a00[1];
                result[4][2]  += b00[2] * a00[2];
                result[4][3]  += b00[3] * a00[2];
                result[0][3]  += b00[3] * a00[0];
                result[0][2]  += b00[2] * a00[0];

                result[5][0]  += b01[0] * a00[2];
                result[5][1]  += b01[1] * a00[2];
                result[1][1]  += b01[1] * a00[0];
                result[1][0]  += b01[0] * a00[0];
                result[7][0]  += b01[0] * a00[3];
                result[7][1]  += b01[1] * a00[3];
                result[3][1]  += b01[1] * a00[1];
                result[3][0]  += b01[0] * a00[1];
                result[13][0] += b01[0] * a01[2];
                result[13][1] += b01[1] * a01[2];
                result[9][1]  += b01[1] * a01[0];
                result[9][0]  += b01[0] * a01[0];
                result[15][0] += b01[0] * a01[3];
                result[15][1] += b01[1] * a01[3];
                result[11][1] += b01[1] * a01[1];
                result[11][0] += b01[0] * a01[1];

                result[15][2] += b01[2] * a01[3];
                result[15][3] += b01[3] * a01[3];
                result[11][3] += b01[3] * a01[1];
                result[11][2] += b01[2] * a01[1];
                result[13][2] += b01[2] * a01[2];
                result[13][3] += b01[3] * a01[2];
                result[9][3]  += b01[3] * a01[0];
                result[9][2]  += b01[2] * a01[0];
                result[7][2]  += b01[2] * a00[3];
                result[7][3]  += b01[3] * a00[3];
                result[3][3]  += b01[3] * a00[1];
                result[3][2]  += b01[2] * a00[1];
                result[5][2]  += b01[2] * a00[2];
                result[5][3]  += b01[3] * a00[2];
                result[1][3]  += b01[3] * a00[0];
                result[1][2]  += b01[2] * a00[0];
            }
        }

        shared_offset4 ^= 32 * 8;
        read_A_offset4 ^= 32 * 8;
        read_B_offset4 ^= 32 * 8;
        track0 += stride_k * 8;
        track2 += stride_k * 8;
        track4 += stride_k * 8;
        track6 += stride_k * 8;
    }

    {
    
#if OPTIMIZE && N_DIVIDABLE_BY_64
        device float4 *C4 = (device float4 *)((static_buffer + meta_buffer[2]));
        const int N4 = N >> 2;
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {

    #if !M_DIVIDABLE_BY_64
            if (m >= M) continue;
    #endif

            const int n = group_position.y * 16 + n_offset * 2;
            float4 result0 = result[m_sub * 2 + 0];
            float4 result1 = result[m_sub * 2 + 1];

            C4[m * N4 + n + 0] = result0;
            C4[m * N4 + n + 1] = result1;
            
            m++;
        }
#else
        device float *C = (static_buffer + meta_buffer[2]);
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {
            int n = group_position.y * 64 + n_offset * 8;

            for (int n_sub1 = 0; n_sub1 < 2; n_sub1++)
            {
                for (int n_sub2 = 0; n_sub2 < 4; n_sub2++)
                {

    #if OPTIMIZE && M_DIVIDABLE_BY_64
                    (         n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #else
                    (m < M && n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #endif
                    n++;
                }
            }
            
            m++;
        }
#endif

    }


#undef M_DIVIDABLE_BY_64
#undef N_DIVIDABLE_BY_64
#undef K_DIVIDABLE_BY_8
#undef TRANSPOSE_A
#undef TRANSPOSE_B
#undef A_STRIDE_K
#undef B_STRIDE_K
#undef A_STRIDE_M
#undef A_STRIDE_M
}


kernel void fusedelementwise_64f6578ea8356a79e688fff775e0187ada7357cadb2634c6994b6f15(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    const device float * v4 = (static_buffer + meta_buffer[3]);
    device float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v8 = v1[d0];
        const float v9 = v2[d0];
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
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


kernel void fusedelementwise_a2a930f4af84e50dafd992d1d0ad7d711a096597302d47acf9a735ed(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    const device float * v4 = (static_buffer + meta_buffer[3]);
    device float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v8 = v1[d0];
        const float v9 = v2[d0];
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
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


kernel void im2col_dd5a967a90f95059d05657fb827f839569ee043c5e56cbfeb987f6f8(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index_thread[[thread_position_in_threadgroup]],
                          uint index_group[[threadgroup_position_in_grid]])
{
#define SH_EQUAL_1 1
#define SW_EQUAL_1 1
#define DH_EQUAL_1 1
#define DW_EQUAL_1 1
#define C1_DIVIDABLE_BY_4 1


#if OPTIMIZE && C1_DIVIDABLE_BY_4
    const device float4 *im4 = (const device float4 *)((static_buffer + meta_buffer[0]));
    device float4 *col4 = (device float4 *)((static_buffer + meta_buffer[1]));
    const int C1_4 = (meta_buffer[3]) >> 2;
#else
    const device float *im = (static_buffer + meta_buffer[0]);
    device float *col = (static_buffer + meta_buffer[1]);
    const int C1 = meta_buffer[3];
#endif

    const int H1 = meta_buffer[4];
    const int W1 = meta_buffer[5];
    const int H2 = meta_buffer[6];
    const int W2 = meta_buffer[7];
    const int KH = meta_buffer[8];
    const int KW = meta_buffer[9];
#if !DH_EQUAL_1
    const int DH = meta_buffer[10];
#endif
#if !DW_EQUAL_1
    const int DW = meta_buffer[11];
#endif
    const int PH = meta_buffer[14];
    const int PW = meta_buffer[15];

#if !OPTIMIZE || !SH_EQUAL_1
    const int SH = meta_buffer[12];
#endif

#if !OPTIMIZE || !SW_EQUAL_1
    const int SW = meta_buffer[13];
#endif

    const int H1P = H1 + 2 * PH;
    const int W1P = W1 + 2 * PW;

    const int w1 = (index_group % W1P) - PW;
    const int h1 = (index_group / W1P % H1P) - PH;
    const int  n = index_group / W1P / H1P;

#if OPTIMIZE && C1_DIVIDABLE_BY_4
    for (int c1_4 = index_thread; c1_4 < C1_4; c1_4 += 64) {
        const float4 v4 = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im4[((n * H1 + h1) * W1 + w1) * C1_4 + c1_4];
#else
    for (int c1 = index_thread; c1 < C1; c1 += 64) {
        const float v = (h1 < 0 || h1 >= H1 || w1 < 0 || w1 >= W1) ? 0 : im[((n * H1 + h1) * W1 + w1) * C1 + c1];
#endif

#if OPTIMIZE && SH_EQUAL_1
        for (int kh = 0; kh < KH; kh++) {
    #if DH_EQUAL_1
            const int h2 = h1 + PH - kh;
    #else
            const int h2 = h1 + PH - kh * DH;
    #endif
    
#else
        for (int kh = (h1 + PH) % SH; kh < KH; kh += SH) {
    #if DH_EQUAL_1
            const int h2 = (h1 + PH - kh) / SH;
    #else
            const int h2 = (h1 + PH - kh * DH) / SH;
    #endif
#endif
            if (h2 < 0 || h2 >= H2) continue;

#if OPTIMIZE && SH_EQUAL_1
            for (int kw = 0; kw < KW; kw++) {
    #if DW_EQUAL_1
                const int w2 = w1 + PW - kw;
    #else
                const int w2 = w1 + PW - kw * DW;
    #endif
#else
            for (int kw = (w1 + PW) % SW; kw < KW; kw += SW) {
    #if DW_EQUAL_1
                const int w2 = (w1 + PW - kw) / SW;
    #else
                const int w2 = (w1 + PW - kw * DW) / SW;
    #endif
#endif
                if (w2 < 0 || w2 >= W2) continue;

#if OPTIMIZE && C1_DIVIDABLE_BY_4
                col4[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1_4 + c1_4] = v4;
#else
                col[((((n * H2 + h2) * W2 + w2) * KH + kh) * KW + kw) * C1 + c1] = v;
#endif
            }
        }
    }


#undef SH_EQUAL_1
#undef SW_EQUAL_1
#undef DH_EQUAL_1
#undef DW_EQUAL_1
#undef C1_DIVIDABLE_BY_4
}


kernel void fusedelementwise_3cfde4edccf2d157c64e8a5e39f8ee66e10ec80af20ca9d5ae076bca(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    device float * v3 = (static_buffer + meta_buffer[2]);
    const int v4 = meta_buffer[3];
    const int v5 = meta_buffer[4];
    const int D0 = meta_buffer[5];
    const int D1 = meta_buffer[6];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v6 = v1[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
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


kernel void fusedelementwise_a0470ecbf11c7513e3b8527a2337bcc20d682405fa9132406c85d96a(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    device float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
            const float v9 = v2[d0 + d1*v5];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v9 + v10;
            }
            float v12;
            {
                v12 = v11 + v8;
            }
            v4[d0 + d1*v7] = v12;
        }
    }
}


kernel void fusedelementwise_f2e7c3b0f54722d02845aa5b8ad7d56b1f543fd41ee3c3fe3583099d(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    device float * v4 = (static_buffer + meta_buffer[3]);
    const int v5 = meta_buffer[4];
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v8 = v1[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
            const float v9 = v2[d0 + d1*v5];
            const float v10 = v3[d0 + d1*v6];
            float v11;
            {
                v11 = v10 + v9;
            }
            float v12;
            {
                v12 = v11 + v8;
            }
            v4[d0 + d1*v7] = v12;
        }
    }
}


kernel void col2im_8a1be4f38d62554df5813223c19078e9dec475d3123d422dd2cbee28(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float *col = (static_buffer + meta_buffer[1]);
    device float *im = (static_buffer + meta_buffer[0]);

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

    for (int gid = index; gid < N*H1*W1*C1; gid += num_threads) {
        const int c1 = gid % C1;
        const int w1 = gid / C1 % W1;
        const int h1 = gid / C1 / W1 % H1;
        const int n  = gid / C1 / W1 / H1;

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


kernel void fusedelementwise_855ad3208167b85cd53ecff129502284363603cb8bd77639f64c5c88(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    const device float * v4 = (static_buffer + meta_buffer[3]);
    device float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int D0 = meta_buffer[7];
    const int D1 = meta_buffer[8];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v8 = v1[d0];
        const float v9 = v2[d0];
        const float v10 = v3[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
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


kernel void sgemm_2f5fb17c61936ed97c3b40058a42f14de9b21cb6b4208d457114dbc7(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint index[[thread_index_in_threadgroup]],
                          uint2 group_position[[threadgroup_position_in_grid]])
{
#define TRANSPOSE_A 1
#define TRANSPOSE_B 1
#define M_DIVIDABLE_BY_64 1
#define N_DIVIDABLE_BY_64 0
#define K_DIVIDABLE_BY_8 1

#if TRANSPOSE_A
    #define A_STRIDE_K 1
    #define A_STRIDE_M K
#else
    #define A_STRIDE_K M
    #define A_STRIDE_M 1
#endif

#if TRANSPOSE_B
    #define B_STRIDE_K N
    #define B_STRIDE_N 1
#else
    #define B_STRIDE_K 1
    #define B_STRIDE_N K
#endif

#if K_DIVIDABLE_BY_8 && M_DIVIDABLE_BY_64  && N_DIVIDABLE_BY_64 && !TRANSPOSE_A && TRANSPOSE_B && OPTIMIZE
    const device float4 *load_target4 = (index & 32) 
        ? (const device float4 *)((static_buffer + meta_buffer[1])) 
        : (const device float4 *)((static_buffer + meta_buffer[0]));
#else
    const device float *load_target = (index & 32) 
        ? ((static_buffer + meta_buffer[1])) 
        : ((static_buffer + meta_buffer[0]));
#endif

    const int M = meta_buffer[3];
    const int N = meta_buffer[4];

    const int K = meta_buffer[5];

    threadgroup float4 shared4[32 * 8 * 2];

    const int stride_k = (index & 32) ? B_STRIDE_K : A_STRIDE_K;
    const int stride_mn = (index & 32) ? B_STRIDE_N : A_STRIDE_M;

    const int m_offset = index & 7;
    const int n_offset = index >> 3;

    const int mn_load_offset = ((index & 32) ? group_position.y : group_position.x) * 64 + (index & 15) * 4;
    const int k_load_offset = ((index & 16) ? 1 : 0);

    int track0 = mn_load_offset * stride_mn + (k_load_offset + 0) * stride_k;
    int track2 = track0 + 2 * stride_k;
    int track4 = track0 + 4 * stride_k;
    int track6 = track0 + 6 * stride_k;

#if !OPTIMIZE || !M_DIVIDABLE_BY_64 || !N_DIVIDABLE_BY_64
    const int max_MN = (index & 32) ? N : M;
#endif

    int shared_offset4 = ((index & 32) ? 16 : 0) + k_load_offset * 32 + (index & 15);
    int read_A_offset4 = m_offset * 2;
    int read_B_offset4 = n_offset * 2 + 16;

    float4 result[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int k = 0;

    while (k < K)
    {
        {
#if OPTIMIZE && K_DIVIDABLE_BY_8
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
        #if OPTIMIZE && !TRANSPOSE_A && TRANSPOSE_B
            shared4[shared_offset4 + 32 * 0] = load_target4[track0 >> 2];
            shared4[shared_offset4 + 32 * 2] = load_target4[track2 >> 2];
            shared4[shared_offset4 + 32 * 4] = load_target4[track4 >> 2];
            shared4[shared_offset4 + 32 * 6] = load_target4[track6 >> 2];
        #else
            shared4[shared_offset4 + 32 * 0] = float4(
                load_target[track0 + stride_mn * 0],
                load_target[track0 + stride_mn * 1],
                load_target[track0 + stride_mn * 2],
                load_target[track0 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 2] = float4(
                load_target[track2 + stride_mn * 0],
                load_target[track2 + stride_mn * 1],
                load_target[track2 + stride_mn * 2],
                load_target[track2 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 4] = float4(
                load_target[track4 + stride_mn * 0],
                load_target[track4 + stride_mn * 1],
                load_target[track4 + stride_mn * 2],
                load_target[track4 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 6] = float4(
                load_target[track6 + stride_mn * 0],
                load_target[track6 + stride_mn * 1],
                load_target[track6 + stride_mn * 2],
                load_target[track6 + stride_mn * 3]
            ); 
        #endif
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 2] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 4] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            shared4[shared_offset4 + 32 * 6] = float4(
                (mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
    #endif

            k += 8;
#else
    #if OPTIMIZE && M_DIVIDABLE_BY_64 && N_DIVIDABLE_BY_64
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
            k += 2;
    #else
            shared4[shared_offset4 + 32 * 0] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track0 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track0 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track0 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track0 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 2] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track2 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track2 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track2 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track2 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 4] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track4 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track4 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track4 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track4 + stride_mn * 3]
            ); 
            k += 2;

            shared4[shared_offset4 + 32 * 6] = float4(
                (k + k_load_offset >= K || mn_load_offset + 0 >= max_MN) ? 0 : load_target[track6 + stride_mn * 0],
                (k + k_load_offset >= K || mn_load_offset + 1 >= max_MN) ? 0 : load_target[track6 + stride_mn * 1],
                (k + k_load_offset >= K || mn_load_offset + 2 >= max_MN) ? 0 : load_target[track6 + stride_mn * 2],
                (k + k_load_offset >= K || mn_load_offset + 3 >= max_MN) ? 0 : load_target[track6 + stride_mn * 3]
            ); 
            k += 2;
    #endif
#endif
        }

        threadgroup_barrier(mem_flags::mem_threadgroup);

        {
            for (int k_sub = 0; k_sub < 8; k_sub++)
            {
                float4 a00 = shared4[32 * k_sub + read_A_offset4 + 0];
                float4 a01 = shared4[32 * k_sub + read_A_offset4 + 1];
                float4 b00 = shared4[32 * k_sub + read_B_offset4 + 0];
                float4 b01 = shared4[32 * k_sub + read_B_offset4 + 1];

                result[4][0]  += b00[0] * a00[2];
                result[4][1]  += b00[1] * a00[2];
                result[0][1]  += b00[1] * a00[0];
                result[0][0]  += b00[0] * a00[0];
                result[6][0]  += b00[0] * a00[3];
                result[6][1]  += b00[1] * a00[3];
                result[2][1]  += b00[1] * a00[1];
                result[2][0]  += b00[0] * a00[1];
                result[12][0] += b00[0] * a01[2];
                result[12][1] += b00[1] * a01[2];
                result[8][1]  += b00[1] * a01[0];
                result[8][0]  += b00[0] * a01[0];
                result[14][0] += b00[0] * a01[3];
                result[14][1] += b00[1] * a01[3];
                result[10][1] += b00[1] * a01[1];
                result[10][0] += b00[0] * a01[1];

                result[14][2] += b00[2] * a01[3];
                result[14][3] += b00[3] * a01[3];
                result[10][3] += b00[3] * a01[1];
                result[10][2] += b00[2] * a01[1];
                result[12][2] += b00[2] * a01[2];
                result[12][3] += b00[3] * a01[2];
                result[8][3]  += b00[3] * a01[0];
                result[8][2]  += b00[2] * a01[0];
                result[6][2]  += b00[2] * a00[3];
                result[6][3]  += b00[3] * a00[3];
                result[2][3]  += b00[3] * a00[1];
                result[2][2]  += b00[2] * a00[1];
                result[4][2]  += b00[2] * a00[2];
                result[4][3]  += b00[3] * a00[2];
                result[0][3]  += b00[3] * a00[0];
                result[0][2]  += b00[2] * a00[0];

                result[5][0]  += b01[0] * a00[2];
                result[5][1]  += b01[1] * a00[2];
                result[1][1]  += b01[1] * a00[0];
                result[1][0]  += b01[0] * a00[0];
                result[7][0]  += b01[0] * a00[3];
                result[7][1]  += b01[1] * a00[3];
                result[3][1]  += b01[1] * a00[1];
                result[3][0]  += b01[0] * a00[1];
                result[13][0] += b01[0] * a01[2];
                result[13][1] += b01[1] * a01[2];
                result[9][1]  += b01[1] * a01[0];
                result[9][0]  += b01[0] * a01[0];
                result[15][0] += b01[0] * a01[3];
                result[15][1] += b01[1] * a01[3];
                result[11][1] += b01[1] * a01[1];
                result[11][0] += b01[0] * a01[1];

                result[15][2] += b01[2] * a01[3];
                result[15][3] += b01[3] * a01[3];
                result[11][3] += b01[3] * a01[1];
                result[11][2] += b01[2] * a01[1];
                result[13][2] += b01[2] * a01[2];
                result[13][3] += b01[3] * a01[2];
                result[9][3]  += b01[3] * a01[0];
                result[9][2]  += b01[2] * a01[0];
                result[7][2]  += b01[2] * a00[3];
                result[7][3]  += b01[3] * a00[3];
                result[3][3]  += b01[3] * a00[1];
                result[3][2]  += b01[2] * a00[1];
                result[5][2]  += b01[2] * a00[2];
                result[5][3]  += b01[3] * a00[2];
                result[1][3]  += b01[3] * a00[0];
                result[1][2]  += b01[2] * a00[0];
            }
        }

        shared_offset4 ^= 32 * 8;
        read_A_offset4 ^= 32 * 8;
        read_B_offset4 ^= 32 * 8;
        track0 += stride_k * 8;
        track2 += stride_k * 8;
        track4 += stride_k * 8;
        track6 += stride_k * 8;
    }

    {
    
#if OPTIMIZE && N_DIVIDABLE_BY_64
        device float4 *C4 = (device float4 *)((static_buffer + meta_buffer[2]));
        const int N4 = N >> 2;
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {

    #if !M_DIVIDABLE_BY_64
            if (m >= M) continue;
    #endif

            const int n = group_position.y * 16 + n_offset * 2;
            float4 result0 = result[m_sub * 2 + 0];
            float4 result1 = result[m_sub * 2 + 1];

            C4[m * N4 + n + 0] = result0;
            C4[m * N4 + n + 1] = result1;
            
            m++;
        }
#else
        device float *C = (static_buffer + meta_buffer[2]);
        int m = group_position.x * 64 + m_offset * 8;
        for (int m_sub = 0; m_sub < 8; m_sub++)
        {
            int n = group_position.y * 64 + n_offset * 8;

            for (int n_sub1 = 0; n_sub1 < 2; n_sub1++)
            {
                for (int n_sub2 = 0; n_sub2 < 4; n_sub2++)
                {

    #if OPTIMIZE && M_DIVIDABLE_BY_64
                    (         n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #else
                    (m < M && n < N) ? (C[m * N + n] = result[m_sub * 2 + n_sub1][n_sub2]) : 0;
    #endif
                    n++;
                }
            }
            
            m++;
        }
#endif

    }


#undef M_DIVIDABLE_BY_64
#undef N_DIVIDABLE_BY_64
#undef K_DIVIDABLE_BY_8
#undef TRANSPOSE_A
#undef TRANSPOSE_B
#undef A_STRIDE_K
#undef B_STRIDE_K
#undef A_STRIDE_M
#undef A_STRIDE_M
}


kernel void fusedelementwise_b25ccdde24c28ffe070ed082512bd1c7c1afa0657bd494eb618c6b98(device float * static_buffer[[buffer(0)]],
                          device float * dynamic_buffer[[buffer(1)]],
                          const device int * meta_buffer [[buffer(2)]],
                          uint gid[[thread_position_in_grid]],
                          uint num_threads[[threads_per_grid]])
{
    const device float * v1 = (static_buffer + meta_buffer[0]);
    const device float * v2 = (static_buffer + meta_buffer[1]);
    const device float * v3 = (static_buffer + meta_buffer[2]);
    const device float * v4 = (static_buffer + meta_buffer[3]);
    device float * v5 = (static_buffer + meta_buffer[4]);
    const int v6 = meta_buffer[5];
    const int v7 = meta_buffer[6];
    const int v8 = meta_buffer[7];
    const int v9 = meta_buffer[8];
    const int D0 = meta_buffer[9];
    const int D1 = meta_buffer[10];
    int d0;
    for (d0 = ((num_threads > 8) ? (gid % (num_threads / 8)) : 0); d0 < D0; d0 += ((num_threads > 8) ? (num_threads / 8) : 1)) {
        const float v10 = v2[d0];
        int d1;
        for (d1 = ((num_threads > 8) ? (gid / (num_threads / 8)) : 0); d1 < D1; d1 += ((num_threads > 8) ? 8 : 1)) {
            const float v11 = v4[d0 + d1*v8];
            float v12;
            {
                v12 = v11 + v10;
            }
            float v13;
            {
                v13 = (v12 >= 10.0 ? 1.0 : tanh(v12));
            }
            const float v14 = v3[d0*v7 + d1];
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
