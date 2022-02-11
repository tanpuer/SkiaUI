//
// Created by DZSB-000848 on 2/11/22.
//

#ifndef SKIAUI_LAYOUTPARAMS_H
#define SKIAUI_LAYOUTPARAMS_H

#include <yoga/YGEnums.h>
#include "array"


class LayoutParams {

public:

    LayoutParams();

    LayoutParams(LayoutParams &other) = delete;

    LayoutParams(LayoutParams &&other) = delete;

    LayoutParams &operator=(LayoutParams &other) = delete;

    LayoutParams &operator=(LayoutParams &&other) = delete;

    ~LayoutParams();

    static LayoutParams makeEmpty();

public:

    float _width, _height;

    float _minWidth, _minHeight; //todo 降低复杂度，暂时不考虑这个，默认是0f

    YGMeasureMode _widthMode, _heightMode;

    std::array<float, 4> _margin;

    std::array<float, 4> _padding;

};


#endif //SKIAUI_LAYOUTPARAMS_H
