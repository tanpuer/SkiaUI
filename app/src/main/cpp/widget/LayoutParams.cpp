//
// Created by DZSB-000848 on 2/11/22.
//

#include "LayoutParams.h"

LayoutParams::LayoutParams() : _width(0), _height(0),
                               _heightMode(YGMeasureModeUndefined),
                               _widthMode(YGMeasureModeUndefined),
                               _minWidth(0), _minHeight(0),
                               _marginLeft(0), _marginRight(0), _marginTop(0), _marginBottom(0),
                               _paddingStart(0), _paddingEnd(0), _paddingTop(0), _paddingBottom(0) {

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

LayoutParams *LayoutParams::makeWrapContent(bool w, bool h) {
    auto layoutParams = new LayoutParams();
    return layoutParams;
}

LayoutParams *LayoutParams::makeMatchParent(bool w, bool h) {
    auto layoutParams = new LayoutParams();
    return layoutParams;
}

void LayoutParams::setMargin(float margin) {
    _marginLeft = margin;
    _marginRight = margin;
    _marginTop = margin;
    _marginBottom = margin;
}

void LayoutParams::setMargin(std::array<float, 4> margins) {
    _marginLeft = margins[0];
    _marginTop = margins[1];
    _marginRight = margins[2];
    _marginBottom = margins[3];
}

void LayoutParams::setPadding(float padding) {
    _paddingStart = padding;
    _paddingEnd = padding;
    _paddingTop = padding;
    _paddingBottom = padding;
}

void LayoutParams::setPadding(std::array<float, 4> paddings) {
    _paddingStart = paddings[0];
    _paddingTop = paddings[1];
    _paddingEnd = paddings[2];
    _paddingBottom = paddings[3];
}
