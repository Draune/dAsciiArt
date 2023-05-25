#ifndef DRAUNE_DASCIIART_FONT
#define DRAUNE_DASCIIART_FONT

int* d_get_baseline();

#define FONT_HEIGHT 8
#define FONT_SCALE cv::getFontScaleFromHeight(cv::FONT_HERSHEY_SIMPLEX, 8)
#define FONT_WIDTH cv::getTextSize("X", cv::FONT_HERSHEY_SIMPLEX, FONT_SCALE, 1, d_get_baseline()).width

#endif