/* This file is automatically generated */
/* ----------------------------------------------------------------------
 * Project:      TinyEngine
 * Description:  for sparse in-place 7x7 depth-wise convolution (HWC->CHW->HWC)
 * Target ISA:  ARMv7E-M
 * Author: wmchen@mit.edu
 * -------------------------------------------------------------------- */
#include <arm_cmsis/arm_nnsupportfunctions.h> //TODO: remove this in the future for self-contained
#include "tinyengine_function.h"
void depthwise_kernel7x7_stride2_inplace_kernel_CHW_fpreq_bitmask(
    const uint16_t output_y, const uint16_t output_x,
    const int32_t *bias, const int32_t *biasR, const q7_t *ksrc, const float *scales,
    q7_t *output, q7_t *output_mask, const int mask_idx, const int32_t output_offset,
    const int32_t activation_min, const int32_t activation_max,
    q7_t *cols_8b_iterptr, const uint16_t column_x, int channel_offset);
tinyengine_status depthwise_kernel7x7_stride2_inplace_CHW_fpreq_bitmask(q7_t *input, const uint16_t input_x, const uint16_t input_y,
            const uint16_t input_ch, const q7_t *kernel, const int32_t *bias, const int32_t *biasR,
            const float *scales,
            const int32_t output_offset, const int32_t input_offset,
            const int32_t output_activation_min,
            const int32_t output_activation_max, q7_t *output, q7_t *output_mask,
            const uint16_t output_x, const uint16_t output_y,
            const uint16_t output_ch, q15_t *runtime_buf, q7_t pad_value)
{

    uint16_t c,i,j;
    q7_t *cols_8b_start = (q7_t *)runtime_buf;
    q7_t* cols_8b = (q7_t* )cols_8b_start;

    //Set padding value
    q7_t PAD8 = pad_value;
    /* setup the padding regions for Im2col buffers */
    //top region: 8bit x (input_x + pad_w * 2) x pad_h: unroll by pad value
    for(i = 0; i < input_x + 6; i++){
        *cols_8b++ = PAD8;
        *cols_8b++ = PAD8;
        *cols_8b++ = PAD8;
    }

    //middle regions: left and right regions
    for(i = 0; i < input_y; i++){
        *cols_8b++ = PAD8;//left
        *cols_8b++ = PAD8;//left
        *cols_8b++ = PAD8;//left
        cols_8b += input_x; //skip middle
        *cols_8b++ = PAD8;//right
        *cols_8b++ = PAD8;//right
        *cols_8b++ = PAD8;//right
    }

    //bottom region: 8bit x (input_x + pad_w * 2) x pad_h: unroll by pad value
    for(i = 0; i < input_x + 6; i++){
        *cols_8b++ = PAD8;
        *cols_8b++ = PAD8;
        *cols_8b++ = PAD8;
    }

    const q7_t *src;
    const q7_t *ksrc = kernel;

    for (c = 0; c < input_ch; c++){
        cols_8b = (q7_t*)(cols_8b_start + 3 * (input_x) + 18); //skip 3 rows
        src = input;
        for(i = 0; i < input_y; i++){
            cols_8b += 3;//skip front
            for(j = 0; j < input_x; j++){
                *cols_8b++ = *src;// + input_offset;
                src += input_ch;
            }
            cols_8b += 3;//skip end
        }
        q7_t *inplace_out = input;
        if (c % 8 == 0 && c > 1) output_mask++;
        depthwise_kernel7x7_stride2_inplace_kernel_CHW_fpreq_bitmask(output_y, output_x, bias++, biasR++, ksrc, scales++, inplace_out, output_mask, c % 8, output_offset,output_activation_min, output_activation_max,cols_8b_start, input_x, input_ch);
        ksrc += 49;
        input++;

    }

}
void depthwise_kernel7x7_stride2_inplace_kernel_CHW_fpreq_bitmask(
    const uint16_t output_y, const uint16_t output_x,
    const int32_t *bias, const int32_t *biasR, const q7_t *ksrc, const float *scales,
    q7_t *output, q7_t *output_mask, const int mask_idx, const int32_t output_offset,
    const int32_t activation_min, const int32_t activation_max,
    q7_t *cols_8b_iterptr, const uint16_t column_x, int channel_offset)
{
    #define STRIDE 2
    int i, j;
    q7_t mask_value;
    /* MACs for each output */
    for (i = 0; i < output_y; i++) {
        for (j = 0; j < output_x / 2; j++) {
            q7_t *cols_8b = cols_8b_iterptr;

            q31_t sum0 = bias[0] + biasR[0];
            q31_t sum1 = bias[0] + biasR[0];
            
            /* computation */
            sum0 += cols_8b[0]*ksrc[0];
            sum1 += cols_8b[2]*ksrc[0];
            sum0 += cols_8b[1]*ksrc[1];
            sum1 += cols_8b[3]*ksrc[1];
            sum0 += cols_8b[2]*ksrc[2];
            sum1 += cols_8b[4]*ksrc[2];
            sum0 += cols_8b[3]*ksrc[3];
            sum1 += cols_8b[5]*ksrc[3];
            sum0 += cols_8b[4]*ksrc[4];
            sum1 += cols_8b[6]*ksrc[4];
            sum0 += cols_8b[5]*ksrc[5];
            sum1 += cols_8b[7]*ksrc[5];
            sum0 += cols_8b[6]*ksrc[6];
            sum1 += cols_8b[8]*ksrc[6];
            cols_8b += column_x + 6;
            sum0 += cols_8b[0]*ksrc[7];
            sum1 += cols_8b[2]*ksrc[7];
            sum0 += cols_8b[1]*ksrc[8];
            sum1 += cols_8b[3]*ksrc[8];
            sum0 += cols_8b[2]*ksrc[9];
            sum1 += cols_8b[4]*ksrc[9];
            sum0 += cols_8b[3]*ksrc[10];
            sum1 += cols_8b[5]*ksrc[10];
            sum0 += cols_8b[4]*ksrc[11];
            sum1 += cols_8b[6]*ksrc[11];
            sum0 += cols_8b[5]*ksrc[12];
            sum1 += cols_8b[7]*ksrc[12];
            sum0 += cols_8b[6]*ksrc[13];
            sum1 += cols_8b[8]*ksrc[13];
            cols_8b += column_x + 6;
            sum0 += cols_8b[0]*ksrc[14];
            sum1 += cols_8b[2]*ksrc[14];
            sum0 += cols_8b[1]*ksrc[15];
            sum1 += cols_8b[3]*ksrc[15];
            sum0 += cols_8b[2]*ksrc[16];
            sum1 += cols_8b[4]*ksrc[16];
            sum0 += cols_8b[3]*ksrc[17];
            sum1 += cols_8b[5]*ksrc[17];
            sum0 += cols_8b[4]*ksrc[18];
            sum1 += cols_8b[6]*ksrc[18];
            sum0 += cols_8b[5]*ksrc[19];
            sum1 += cols_8b[7]*ksrc[19];
            sum0 += cols_8b[6]*ksrc[20];
            sum1 += cols_8b[8]*ksrc[20];
            cols_8b += column_x + 6;
            sum0 += cols_8b[0]*ksrc[21];
            sum1 += cols_8b[2]*ksrc[21];
            sum0 += cols_8b[1]*ksrc[22];
            sum1 += cols_8b[3]*ksrc[22];
            sum0 += cols_8b[2]*ksrc[23];
            sum1 += cols_8b[4]*ksrc[23];
            sum0 += cols_8b[3]*ksrc[24];
            sum1 += cols_8b[5]*ksrc[24];
            sum0 += cols_8b[4]*ksrc[25];
            sum1 += cols_8b[6]*ksrc[25];
            sum0 += cols_8b[5]*ksrc[26];
            sum1 += cols_8b[7]*ksrc[26];
            sum0 += cols_8b[6]*ksrc[27];
            sum1 += cols_8b[8]*ksrc[27];
            cols_8b += column_x + 6;
            sum0 += cols_8b[0]*ksrc[28];
            sum1 += cols_8b[2]*ksrc[28];
            sum0 += cols_8b[1]*ksrc[29];
            sum1 += cols_8b[3]*ksrc[29];
            sum0 += cols_8b[2]*ksrc[30];
            sum1 += cols_8b[4]*ksrc[30];
            sum0 += cols_8b[3]*ksrc[31];
            sum1 += cols_8b[5]*ksrc[31];
            sum0 += cols_8b[4]*ksrc[32];
            sum1 += cols_8b[6]*ksrc[32];
            sum0 += cols_8b[5]*ksrc[33];
            sum1 += cols_8b[7]*ksrc[33];
            sum0 += cols_8b[6]*ksrc[34];
            sum1 += cols_8b[8]*ksrc[34];
            cols_8b += column_x + 6;
            sum0 += cols_8b[0]*ksrc[35];
            sum1 += cols_8b[2]*ksrc[35];
            sum0 += cols_8b[1]*ksrc[36];
            sum1 += cols_8b[3]*ksrc[36];
            sum0 += cols_8b[2]*ksrc[37];
            sum1 += cols_8b[4]*ksrc[37];
            sum0 += cols_8b[3]*ksrc[38];
            sum1 += cols_8b[5]*ksrc[38];
            sum0 += cols_8b[4]*ksrc[39];
            sum1 += cols_8b[6]*ksrc[39];
            sum0 += cols_8b[5]*ksrc[40];
            sum1 += cols_8b[7]*ksrc[40];
            sum0 += cols_8b[6]*ksrc[41];
            sum1 += cols_8b[8]*ksrc[41];
            cols_8b += column_x + 6;
            sum0 += cols_8b[0]*ksrc[42];
            sum1 += cols_8b[2]*ksrc[42];
            sum0 += cols_8b[1]*ksrc[43];
            sum1 += cols_8b[3]*ksrc[43];
            sum0 += cols_8b[2]*ksrc[44];
            sum1 += cols_8b[4]*ksrc[44];
            sum0 += cols_8b[3]*ksrc[45];
            sum1 += cols_8b[5]*ksrc[45];
            sum0 += cols_8b[4]*ksrc[46];
            sum1 += cols_8b[6]*ksrc[46];
            sum0 += cols_8b[5]*ksrc[47];
            sum1 += cols_8b[7]*ksrc[47];
            sum0 += cols_8b[6]*ksrc[48];
            sum1 += cols_8b[8]*ksrc[48];

            /* requantize */
            sum0 = (float) sum0 * *scales;
            sum0 += output_offset;
            mask_value = 1;
            if (sum0 < activation_min){
                sum0 = activation_min;
                mask_value = 0;
            }
            if (sum0 > activation_max){
                sum0 = activation_max;
                mask_value = 0;
            }
            output[(i * output_x + j * 2) * channel_offset] = sum0;
            if (mask_value == 1)
                BIT_SET(output_mask[(i * output_x + j * 2) * channel_offset / 8], mask_idx);
            else
                BIT_CLEAR(output_mask[(i * output_x + j * 2) * channel_offset / 8], mask_idx);

            sum1 = (float) sum1 * *scales;
            sum1 += output_offset;
            mask_value = 1;
            if (sum1 < activation_min){
                sum1 = activation_min;
                mask_value = 0;
            }
            if (sum1 > activation_max){
                sum1 = activation_max;
                mask_value = 0;
            }
            output[(i * output_x + (j * 2 + 1)) * channel_offset] = sum1;
            if (mask_value == 1)
                BIT_SET(output_mask[(i * output_x + (j * 2 + 1)) * channel_offset / 8], mask_idx);
            else
                BIT_CLEAR(output_mask[(i * output_x + (j * 2 + 1)) * channel_offset / 8], mask_idx);

            cols_8b_iterptr += STRIDE * 2;
        }
        if (output_x & 1) {
            q7_t * cols_8b = cols_8b_iterptr;
            q31_t sum = bias[0] + biasR[0];
            sum += cols_8b[0]*ksrc[0];
            sum += cols_8b[1]*ksrc[1];
            sum += cols_8b[2]*ksrc[2];
            sum += cols_8b[3]*ksrc[3];
            sum += cols_8b[4]*ksrc[4];
            sum += cols_8b[5]*ksrc[5];
            sum += cols_8b[6]*ksrc[6];
            cols_8b += column_x + 6;
            sum += cols_8b[0]*ksrc[7];
            sum += cols_8b[1]*ksrc[8];
            sum += cols_8b[2]*ksrc[9];
            sum += cols_8b[3]*ksrc[10];
            sum += cols_8b[4]*ksrc[11];
            sum += cols_8b[5]*ksrc[12];
            sum += cols_8b[6]*ksrc[13];
            cols_8b += column_x + 6;
            sum += cols_8b[0]*ksrc[14];
            sum += cols_8b[1]*ksrc[15];
            sum += cols_8b[2]*ksrc[16];
            sum += cols_8b[3]*ksrc[17];
            sum += cols_8b[4]*ksrc[18];
            sum += cols_8b[5]*ksrc[19];
            sum += cols_8b[6]*ksrc[20];
            cols_8b += column_x + 6;
            sum += cols_8b[0]*ksrc[21];
            sum += cols_8b[1]*ksrc[22];
            sum += cols_8b[2]*ksrc[23];
            sum += cols_8b[3]*ksrc[24];
            sum += cols_8b[4]*ksrc[25];
            sum += cols_8b[5]*ksrc[26];
            sum += cols_8b[6]*ksrc[27];
            cols_8b += column_x + 6;
            sum += cols_8b[0]*ksrc[28];
            sum += cols_8b[1]*ksrc[29];
            sum += cols_8b[2]*ksrc[30];
            sum += cols_8b[3]*ksrc[31];
            sum += cols_8b[4]*ksrc[32];
            sum += cols_8b[5]*ksrc[33];
            sum += cols_8b[6]*ksrc[34];
            cols_8b += column_x + 6;
            sum += cols_8b[0]*ksrc[35];
            sum += cols_8b[1]*ksrc[36];
            sum += cols_8b[2]*ksrc[37];
            sum += cols_8b[3]*ksrc[38];
            sum += cols_8b[4]*ksrc[39];
            sum += cols_8b[5]*ksrc[40];
            sum += cols_8b[6]*ksrc[41];
            cols_8b += column_x + 6;
            sum += cols_8b[0]*ksrc[42];
            sum += cols_8b[1]*ksrc[43];
            sum += cols_8b[2]*ksrc[44];
            sum += cols_8b[3]*ksrc[45];
            sum += cols_8b[4]*ksrc[46];
            sum += cols_8b[5]*ksrc[47];
            sum += cols_8b[6]*ksrc[48];

            sum = (float) sum * *scales;
            sum += output_offset;
            mask_value = 1;
            if (sum < activation_min){
                sum = activation_min;
                mask_value = 0;
            }
            if (sum > activation_max){
                sum = activation_max;
                mask_value = 0;
            }
            output[(i * output_x + output_x - 1) * channel_offset] = sum;
            if (mask_value == 1)
                BIT_SET(output_mask[(i * output_x + output_x - 1) * channel_offset / 8], mask_idx);
            else
                BIT_CLEAR(output_mask[(i * output_x + output_x - 1) * channel_offset / 8], mask_idx);

            cols_8b_iterptr += STRIDE;
        }
        cols_8b_iterptr += 3 * 2 - (column_x & 1);
        cols_8b_iterptr += (STRIDE - 1) * (column_x + 3 * 2);
    }
}