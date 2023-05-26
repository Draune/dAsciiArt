#ifndef DRAUNE_DASCIIART_CONVERT
#define DRAUNE_DASCIIART_CONVERT

#include <opencv2/opencv.hpp>
#include<string>

char*** d_convert_video(std::string video_file,unsigned int *width,unsigned int *height,float* frame_rate,unsigned int* nb_frame);
char** d_convert_cam(cv::VideoCapture* cam,int* is_redim,unsigned int* nb_pixel_per_char_line,unsigned int *width,unsigned int *height);

#endif