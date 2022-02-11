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

LayoutParams LayoutParams::makeEmpty() {
    return LayoutParams();
}
