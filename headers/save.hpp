#ifndef DRAUNE_DASCIIART_SAVE
#define DRAUNE_DASCIIART_SAVE

#include<string>

void d_save_img(std::string img_file,std::string output_file);
void d_save_video(std::string video_file,std::string output_file);
void d_save_cam(std::string output_file,unsigned int time_s);

#endif