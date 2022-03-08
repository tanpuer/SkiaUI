//
// Created by DZSB-000848 on 2/15/22.
//

#include "FrameLayout.h"

void FrameLayout::layout(int l, int t, int r, int b) {
    for (auto child: children) {
        auto left = YGNodeLayoutGetLeft(child->node);
        auto top = YGNodeLayoutGetTop(child->node);
        auto width = YGNodeLayoutGetWidth(child->node);
        auto height = YGNodeLayoutGetHeight(child->node);
        child->layout(left + l, top + t, left + width, top + height);
    }
}
