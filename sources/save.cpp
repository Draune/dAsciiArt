#include "../headers/save.hpp"
#include "../headers/convert.hpp"
#include "../headers/font.hpp"
#include <opencv2/opencv.hpp>
extern "C"{
#include "../dStruct/headers/queue.h"
}

cv::Mat create_img(char **char_img, unsigned int width, unsigned int height);

void d_save_video(std::string video_file, std::string output_file)
{
    unsigned int max_width = 0;
    unsigned int max_height = 0;
    float fps;
    unsigned int nb_frames;
    char ***char_video = d_convert_video(video_file, &max_width, &max_height, &fps, &nb_frames);
    cv::VideoWriter video_writer;
    video_writer.open(output_file, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, cv::Size(FONT_WIDTH * max_width, FONT_HEIGHT * max_height), true);
    if (video_writer.isOpened())
    {
        for (int i = 0; i < nb_frames; i++)
        {
            video_writer.write(create_img(char_video[i], max_width, max_height));
        }
    }
}

void d_save_cam(std::string output_file, unsigned int time_s)
{
    unsigned int max_width = 0;
    unsigned int max_height = 0;
    int is_redim = 0;
    unsigned int nb_pixel_per_char_line;
    cv::VideoCapture cam(0);
    dQueue frame_queue = d_init_queue();
    unsigned int nb_frames = 0;
    time_t start = time(NULL);
    while (time(NULL) - start <= time_s){
        d_push_queue(&frame_queue,d_convert_cam(&cam, &is_redim, &nb_pixel_per_char_line, &max_width, &max_height));
        nb_frames++;
    }
    double fps = ((double)nb_frames)/((double)time_s);
    cv::VideoWriter video_writer;
    video_writer.open(output_file, cv::VideoWriter::fourcc('m', 'p', '4', 'v'), fps, cv::Size(FONT_WIDTH * max_width, FONT_HEIGHT * max_height), true);
    if (video_writer.isOpened())
    {
        for (int i = 0; i < nb_frames; i++)
        {
            char **char_img = (char**)d_pop_queue(&frame_queue);
            video_writer.write(create_img(char_img, max_width, max_height));
        }
    }
}

cv::Mat create_img(char **char_img, unsigned int width, unsigned int height)
{
    cv::Mat return_ = cv::Mat::zeros(cv::Size(FONT_WIDTH * width, FONT_HEIGHT * height), CV_8UC3);
    if (char_img == NULL)
        return return_;
    unsigned int font_height = FONT_HEIGHT;
    unsigned int font_width = FONT_WIDTH;
    for (int i = 0; i < height; i++)
    {
        if (char_img[i] == NULL)
            printf("NULL");
        for (int j = 0; j < width; j++)
        {

            cv::putText(return_, cv::format("%c", char_img[i][j]), cv::Point(j * font_width, i * font_height), cv::FONT_HERSHEY_SIMPLEX, FONT_SCALE, cv::Scalar(255, 255, 255));
        }
    }
    return return_;
}