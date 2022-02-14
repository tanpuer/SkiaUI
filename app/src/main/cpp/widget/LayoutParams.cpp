//
// Created by DZSB-000848 on 2/11/22.
//

#include "LayoutParams.h"

LayoutParams::LayoutParams() : _width(0), _height(0),
                               _heightMode(YGMeasureModeUndefined),
                               _widthMode(YGMeasureModeUndefined),
                               _minWidth(0), _minHeight(0),
                               _margin(), _padding() {

}

LayoutParams::~LayoutParams() = default;

LayoutParams *LayoutParams::makeEmpty() {
    return new LayoutParams();
}

LayoutParams *LayoutParams::makeExactlyLayoutParams(float w, float h) {
    auto layoutParams = new LayoutParams();
    layoutParams->_width = w;
    layoutParams->_height = h;
    layoutParams->_widthMode = YGMeasureModeExactly;
    layoutParams->_heightMode = YGMeasureModeExactly;
    return layoutParams;
}

LayoutParams *LayoutParams::makeUndefinedLayoutPrams() {
    auto layoutParams = new LayoutParams();
    layoutParams->_widthMode = YGMeasureModeUndefined;
    layoutParams->_heightMode = YGMeasureModeUndefined;
    return layoutParams;
}

LayoutParams *LayoutParams::makeExactlyWidth(float w) {
    auto layoutParams = new LayoutParams();
    layoutParams->_width = w;
    layoutParams->_height = 0;
    layoutParams->_widthMode = YGMeasureModeExactly;
    layoutParams->_heightMode = YGMeasureModeUndefined;
    return layoutParams;
}

LayoutParams *LayoutParams::makeExactlyHeight(float h) {
    auto layoutParams = new LayoutParams();
    layoutParams->_width = 0;
    layoutParams->_height = h;
    layoutParams->_widthMode = YGMeasureModeUndefined;
    layoutParams->_heightMode = YGMeasureModeExactly;
    return layoutParams;
}
