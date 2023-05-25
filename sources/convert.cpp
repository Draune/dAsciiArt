#include "../headers/convert.hpp"
#include <opencv2/opencv.hpp>
#include "../headers/sort_char.hpp"
#include "../headers/font.hpp"
extern "C"
{
#include "../dStruct/headers/vector.h"
}

typedef cv::Point3_<uint8_t> Pixel;

char **convert_img(cv::Mat image, unsigned int nb_pixel_per_char_line, unsigned int width, unsigned int height);
void redim(unsigned int *nb_pixel_per_char_line, unsigned int *width, unsigned int *height, unsigned int rows, unsigned int cols);
void nothing(void *) {}
float grayscale(Pixel pixel);

char **d_convert_img(std::string img_file, unsigned int *width, unsigned int *height)
{
    cv::Mat image = cv::imread(img_file);
    if (image.empty())
        return NULL;
    unsigned int nb_pixel_per_char_line;
    redim(&nb_pixel_per_char_line, width, height, image.rows, image.cols);
    char **return_ = (char **)convert_img(image, nb_pixel_per_char_line, *width, *height);
    return return_;
}

char ***d_convert_video(std::string video_file, unsigned int *width, unsigned int *height, float *fps, unsigned int *nb_frame)
{
    cv::VideoCapture cap(video_file);
    if (!cap.isOpened())
    {
        *nb_frame = 0;
        return NULL;
    }
    *fps = cap.get(cv::CAP_PROP_FPS);
    cv::Mat frame;
    dVector vector = d_init_vector(0);
    unsigned int nb_pixel_per_char_line;
    bool is_redim = false;
    while (cap.isOpened())
    {
        cap.read(frame);
        if (frame.empty())
            break;
        if (!is_redim)
        {
            if (!frame.empty())
            {
                is_redim = true;
                redim(&nb_pixel_per_char_line, width, height, frame.rows, frame.cols);
            }
        }
        d_push_back_vector(&vector, convert_img(frame, nb_pixel_per_char_line, *width, *height));
    }

    char ***return_ = (char ***)malloc(sizeof(char **) * vector.size);
    for (int i = 0; i < vector.size; i++)
        return_[i] = (char **)d_access_vector(&vector, i);
    *nb_frame = vector.size;
    d_clear_vector(&vector, nothing);
    return return_;
}

char **d_convert_cam(cv::VideoCapture *cam, int *is_redim, unsigned int *nb_pixel_per_char_line, unsigned int *width, unsigned int *height)
{
    if (!cam->isOpened())
        return NULL;
    cv::Mat frame;
    cam->read(frame);
    if (!frame.empty())
    {
        if (!(*is_redim))
        {
            *is_redim = 1;
            redim(nb_pixel_per_char_line, width, height, frame.rows, frame.cols);
        }
        return convert_img(frame, *nb_pixel_per_char_line, *width, *height);
    }
    return NULL;
}

char **convert_img(cv::Mat image, unsigned int nb_pixel_per_char_line, unsigned int width, unsigned int height)
{
    if (image.empty())
        return NULL;
    char **return_ = (char **)malloc(sizeof(char *) * height);
    for (int i = 0; i < height; i++)
        return_[i] = (char *)malloc(sizeof(char) * width);

    unsigned int nb_pixel_per_char_width = nb_pixel_per_char_line;
    unsigned int nb_pixel_per_char_height = nb_pixel_per_char_line;
    unsigned int nb_pixel_per_char = nb_pixel_per_char_width * nb_pixel_per_char_height;
    nb_pixel_per_char += (nb_pixel_per_char == 0) ? 1 : 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = 0;
            for (int k = 0; k < nb_pixel_per_char_height; k++)
            {
                for (int l = 0; l < nb_pixel_per_char_width; l++)
                {
                    average += grayscale(image.at<Pixel>(i * nb_pixel_per_char_height + k, j * nb_pixel_per_char_width + l));
                }
            }
            average /= (float)nb_pixel_per_char;
            return_[i][j] = d_find_char_shade(((int)average * DASCIIART_NB_SHADES) / 255);
        }
    }
    return return_;
}

float grayscale(Pixel pixel)
{
    return (float)pixel.x * 0.299f + (float)pixel.y * 0.587f + (float)pixel.z * 0.114f;
}

void redim(unsigned int *nb_pixel_per_char_line, unsigned int *width, unsigned int *height, unsigned int rows, unsigned int cols)
{
    if (*width == 0 && *height == 0)
    {
        *nb_pixel_per_char_line = (FONT_HEIGHT > FONT_WIDTH) ? FONT_HEIGHT : FONT_WIDTH;
        *height = rows / (*nb_pixel_per_char_line);
        *width = cols / (*nb_pixel_per_char_line);
    }
    else if (rows / (*height) > cols / (*width) || *width == 0)
    {
        *nb_pixel_per_char_line = rows / (*height);
        *width = cols / (*nb_pixel_per_char_line);
    }
    else
    {
        *nb_pixel_per_char_line = cols / (*width);
        *height = rows / (*nb_pixel_per_char_line);
    }
}