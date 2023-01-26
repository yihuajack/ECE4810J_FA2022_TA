#include "yuv_filter.h"

// The top-level function
void yuv_filter (
      image_t *in,
      image_t *out,
      yuv_scale_t Y_scale,
      yuv_scale_t U_scale,
      yuv_scale_t V_scale
      )
{
// Internal image buffers
#ifndef __SYNTHESIS__
   image_t *yuv = (image_t *)malloc(sizeof(image_t));
   image_t *scale = (image_t *)malloc(sizeof(image_t));
#else // Workaround malloc() calls w/o changing rest of code
   image_t _yuv;
   image_t _scale;
   image_t *yuv = &_yuv;
   image_t *scale = &_scale;
#endif

   rgb2yuv   (in, yuv);
   yuv_scale (    yuv, scale, Y_scale, U_scale, V_scale);
   yuv2rgb   (         scale, out);
}

// Convert RGB image to Y'UV format
void rgb2yuv (
      image_t *in,
      image_t *out
      )
{
   image_dim_t x, y;
   image_dim_t width, height;
   image_pix_t R, G, B, Y, U, V;
   const rgb2yuv_coef_t Wrgb[3][3] = {
      0
      
      // TODO
   };

   width = in->width;
   height = in->height;
   out->width = width;
   out->height = height;

RGB2YUV_LOOP_X:
   for (x=0; x<width; x++) {
//   #pragma HLS loop_tripcount min=200 max=1920
RGB2YUV_LOOP_Y:
      for (y=0; y<height; y++) {
//   #pragma HLS loop_tripcount min=200 max=1280
         R = in->channels.ch1[x][y];
         G = in->channels.ch2[x][y];
         B = in->channels.ch3[x][y];
         // TODO: Y = ;
         // U = ;
         // V = ;
         out->channels.ch1[x][y] = Y;
         out->channels.ch2[x][y] = U;
         out->channels.ch3[x][y] = V;
      }
   }
}

void yuv2rgb (
      image_t *in,
      image_t *out
      )
{
   image_dim_t x,y;
   image_dim_t width, height;
   image_pix_t R, G, B;
   image_pix_t Y, U, V;
   yuv_intrnl_t C, D, E;
   const yuv2rgb_coef_t Wyuv[3][3] = {
      0
      
      // TODO
   };

   width = in->width;
   height = in->height;
   out->width = width;
   out->height = height;

YUV2RGB_LOOP_X:
   for (x=0; x<width; x++) {
//   #pragma HLS loop_tripcount min=200 max=1920
YUV2RGB_LOOP_Y:
      for (y=0; y<height; y++) {
//   #pragma HLS loop_tripcount min=200 max=1280
         Y = in->channels.ch1[x][y];
         U = in->channels.ch2[x][y];
         V = in->channels.ch3[x][y];
         // TODO: C = ;
         // D = ;
         // E = ;
         // R = ;
         // G = ;
         // B = ;
         out->channels.ch1[x][y] = R;
         out->channels.ch2[x][y] = G;
         out->channels.ch3[x][y] = B;
      }
   }
}

void yuv_scale (
      image_t *in,
      image_t *out,
      yuv_scale_t Y_scale,
      yuv_scale_t U_scale,
      yuv_scale_t V_scale
      )
{
   image_dim_t x,y;
   image_dim_t width, height;
   image_pix_t Y, U, V;
   yuv_intrnl_t Yn, Un, Vn;

   width = in->width;
   height = in->height;
   out->width = width;
   out->height = height;

YUV_SCALE_LOOP_X:
   for (x=0; x<width; x++) {
//   #pragma HLS loop_tripcount min=200 max=1920
YUV_SCALE_LOOP_Y:
      for (y=0; y<height; y++) {
//   #pragma HLS loop_tripcount min=200 max=1280
         Y = in->channels.ch1[x][y];
         U = in->channels.ch2[x][y];
         V = in->channels.ch3[x][y];
         Yn = (Y * Y_scale) >> 7;
         Un = (U * U_scale) >> 7;
         Vn = (V * V_scale) >> 7;
         out->channels.ch1[x][y] = Yn;
         out->channels.ch2[x][y] = Un;
         out->channels.ch3[x][y] = Vn;
      }
   }
}
