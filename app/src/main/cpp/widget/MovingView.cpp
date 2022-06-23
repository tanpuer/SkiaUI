//
// Created by ByteDance on 2022/6/22.
//

#include "MovingView.h"

bool MovingView::onTouchEvent(TouchEvent *touchEvent) {
    switch (touchEvent->action) {
        case TouchEvent::ACTION_DOWN: {
            translateX = 0.0f;
            translateY = 0.0f;
            lastX = touchEvent->x;
            lastY = touchEvent->y;
            break;
        }
        case TouchEvent::ACTION_MOVE: {
            translateX += touchEvent->x - lastX;
            translateY += touchEvent->y - lastY;
            lastX = touchEvent->x;
            lastY = touchEvent->y;
            break;
        }
        default: {
            translateX = 0.0f;
            translateY = 0.0f;
            lastX = 0.0f;
            lastY = 0.0f;
            break;
        }
    }
    return true;
}

void MovingView::layout(int l, int t, int r, int b) {
    ALOGD("MovingView %f %f", translateX, translateY)
    skRect.setLTRB(l + translateX, t + translateY, r + translateX, b + translateY);
    width = r - l;
    height = b - t;
}

MovingView::MovingView() : View() {
    lastX = 0.0f;
    lastY = 0.0f;
}

MovingView::~MovingView() = default;

const char *MovingView::name() {
    return "MovingView";
}
