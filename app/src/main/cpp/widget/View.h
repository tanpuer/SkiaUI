//
// Created by DZSB-000848 on 1/24/22.
//

#ifndef SKIAUI_VIEW_H
#define SKIAUI_VIEW_H

#include <cstdint>
#include "FlexLayout.h"
#include "array"

class View {

public:

    View() : margins{0, 0, 0, 0}, paddings{0, 0, 0, 0} {}

    virtual ~View() {}

public:

    Order order;
    FlexGrow flexGrow;
    FlexShrink flexShrink;
    FlexBias flexBias;
    Flex flex;
    AlignSelf alignSelf;

    std::array<int, 4> margins;
    std::array<int, 4> paddings;

    int minWidth = INT32_MIN;
    int minHeight = INT32_MIN;
    int maxWidth = INT32_MAX;
    int maxHeight = INT32_MAX;

};

#endif //SKIAUI_VIEW_H
