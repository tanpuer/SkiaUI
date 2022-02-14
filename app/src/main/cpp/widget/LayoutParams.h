//
// Created by DZSB-000848 on 2/11/22.
//

#ifndef SKIAUI_LAYOUTPARAMS_H
#define SKIAUI_LAYOUTPARAMS_H

#include <yoga/YGEnums.h>
#include "array"

/**
 * 布局相关参数尽量都放在LayoutParams中
 */
class LayoutParams {

public:

    LayoutParams();

    LayoutParams(LayoutParams &other) = delete;

    LayoutParams(LayoutParams &&other) = delete;

    LayoutParams &operator=(LayoutParams &other) = delete;

    LayoutParams &operator=(LayoutParams &&other) = delete;

    ~LayoutParams();

    static LayoutParams *makeEmpty();

    static LayoutParams *makeExactlyLayoutParams(float w, float h);

    static LayoutParams *makeExactlyWidth(float w);

    static LayoutParams *makeExactlyHeight(float h);

    /**
     * 可以理解为wrap
     * @return
     */
    static LayoutParams *makeUndefinedLayoutPrams();

public:

    float _width, _height;

    float _minWidth, _minHeight; //todo 降低复杂度，暂时不考虑这个，默认是0f

    YGMeasureMode _widthMode, _heightMode;

    std::array<float, 4> _margin;

    std::array<float, 4> _padding;

};


#endif //SKIAUI_LAYOUTPARAMS_H
