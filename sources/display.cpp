#include "../headers/display.hpp"
#include "../headers/convert.hpp"
extern "C"
{
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
}

void display_img(char **char_img, unsigned int width, unsigned int height);

void d_display_img(std::string img_file)
{
    initscr();
    unsigned int width = COLS;
    unsigned int height = LINES;
    endwin();

    display_img(d_convert_img(img_file, &width, &height), width, height);
}

void d_display_video(std::string video_file)
{
    initscr();
    float fps;
    unsigned int width = COLS;
    unsigned int height = LINES;
    unsigned int nb_frame;
    endwin();

    char ***char_video = d_convert_video(video_file, &width, &height, &fps, &nb_frame);
    float delay = 1.0f / fps * 1000000.0f;
    for (int frame = 0; frame < nb_frame; frame++)
    {
        display_img(char_video[frame], width, height);
        usleep(delay);
    }
}

void d_display_cam()
{
    initscr();
    cv::VideoCapture cam(0);
    int is_redim = 0;
    unsigned int width = COLS;
    unsigned int height = LINES;
    unsigned int nb_pixel_per_char_line;
    endwin();
    while (1)
        display_img(d_convert_cam(&cam, &is_redim, &nb_pixel_per_char_line, &width, &height), width, height);
}

void display_img(char **char_img, unsigned int width, unsigned int height)
{
    if (char_img != NULL)
    {
        system("clear");
        printf("\n");
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("%c", char_img[i][j]);
            }
            printf("\n");
        }
        fflush(stdout);
    }
}