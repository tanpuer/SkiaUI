//
// Created by DZSB-000848 on 2/11/22.
//

#ifndef SKIAUI_LAYOUTPARAMS_H
#define SKIAUI_LAYOUTPARAMS_H

#include <yoga/YGEnums.h>
#include "array"
#include "MeasureSpec.h"

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

    static LayoutParams *makeWrapContent(bool w = true, bool h = true);

    static LayoutParams *makeMatchParent(bool w = true, bool h = true);

    /**
     * 可以理解为wrap
     * @return
     */
    static LayoutParams *makeUndefinedLayoutPrams();

public:

    float _width, _height;

    float _minWidth, _minHeight; //todo 降低复杂度，暂时不考虑这个，默认是0f

    YGMeasureMode _widthMode, _heightMode;

    float _marginLeft, _marginRight, _marginTop, _marginBottom;

    float _paddingStart, _paddingEnd, _paddingTop, _paddingBottom;

    void setMargin(float margin);

    void setMargin(std::array<float, 4> margins);

    void setPadding(float padding);

    void setPadding(std::array<float, 4> paddings);

};


#endif //SKIAUI_LAYOUTPARAMS_H
