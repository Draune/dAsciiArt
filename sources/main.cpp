#include "../headers/display.hpp"
#include "../headers/save.hpp"

void display_help();

int main(int agrc, char *agrv[])
{
    bool save = false;     // -s
    bool display = false;  // -d
    bool video = false;    // -v
    bool image = false;    // -i
    bool cam = false;      // -c
    bool help = false;     // -h
    bool path_in = false;  // -ip
    bool path_out = false; // -op
    bool time = false;     // -t

    std::string input_file;
    std::string output_file;
    int time_s;

    for (int i = 1; i < agrc; i++)
    {
        if (agrv[i][0] != '-')
            help = true;
        else
        {
            if ((agrv[i][1] == 's') && (agrv[i][2] == '\0'))
            {
                save = true;
            }
            else if ((agrv[i][1] == 'd') && (agrv[i][2] == '\0'))
            {
                display = true;
            }
            else if ((agrv[i][1] == 'v') && (agrv[i][2] == '\0'))
            {
                video = true;
            }
            else if ((agrv[i][1] == 'i') && (agrv[i][2] == '\0'))
            {
                image = true;
            }
            else if ((agrv[i][1] == 'c') && (agrv[i][2] == '\0'))
            {
                cam = true;
            }
            else if ((agrv[i][1] == 'h') && (agrv[i][2] == '\0'))
            {
                help = true;
            }
            else if ((agrv[i][1] == 'i') && (agrv[i][2] == 'p') && (agrv[i][3] == '\0'))
            {
                i++;
                if (agrv[i][0] == '-')
                    help = true;
                else
                {
                    path_in = true;
                    input_file = std::string(agrv[i]);
                }
            }
            else if ((agrv[i][1] == 'o') && (agrv[i][2] == 'p') && (agrv[i][3] == '\0'))
            {
                i++;
                if (agrv[i][0] == '-')
                    help = true;
                else
                {
                    path_out = true;
                    output_file = std::string(agrv[i]);
                }
            }
            else if ((agrv[i][1] == 't') && (agrv[i][2] == '\0'))
            {
                i++;
                if (agrv[i][0] == '-')
                    help = true;
                else
                {
                    time_s = (int)strtol(agrv[i], NULL, 10);
                    if (time_s > 0)
                        time = true;
                    else
                        help = true;
                }
            }
            else 
                help = true;
        }
    }

    if ((save && display) || !(save || display))
        help = true;
    if ((video && image) || (video && cam) || (image && cam) || !(image || video || cam))
        help = true;
    if ((!path_in && (image || video)) || (path_in && cam))
        help = true;
    if ((!path_out && save) || (path_out && display))
        help = true;
    if ((!time && save && cam) || (time && (display || (save && (video || image)))))
        help = true;

    if (help)
        display_help();
    else if (display)
    {
        if (image)
            d_display_img(input_file);
        else if (video)
            d_display_video(input_file);
        else if (cam)
            d_display_cam();
        else
            display_help();
    }
    else if (save)
    {
        if (image)
            d_save_img(input_file, output_file);
        else if (video)
            d_save_video(input_file, output_file);
        else if (cam)
            d_save_cam(output_file, time_s);
        else
            display_help();
    }
    else
        display_help();

    return 0;
}

void display_help(){
    printf("Usage: dAsciiArt [options]\n");
    printf("Options:\n");

    printf("\t-h\t\tDisplay this information\n");
    printf("\t-d\t\tDisplay the result on terminal\n");
    printf("\t-s\t\tSave the result in the file specified with -op\n");
    printf("\t-c\t\tUse webcam as input\n");
    printf("\t-i\t\tUse the image specified with -ip as input\n");
    printf("\t-v\t\tUse the video specified with -ip as input\n");
    printf("\t-ip <file>\tSpecify the input file when using -i or -v\n");
    printf("\t-op <file>\tSpecify the output file to save\n");
    printf("\t-t <integer>\tSpecify the recording time in seconds when saving with -c\n");

    printf("\nFor more informations see: https://github.com/Draune/dAsciiArt\n");
    printf("Or contact me on: draune.prog@gmail.com\n");
}