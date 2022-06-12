//
// Created by cw on 2022/6/4.
//

#ifndef SKIAUI_TOUCHEVENT_H
#define SKIAUI_TOUCHEVENT_H

#endif //SKIAUI_TOUCHEVENT_H

class TouchEvent {

public:

    enum MotionEvent {
        ACTION_DOWN = 0,
        ACTION_UP = 1,
        ACTION_MOVE = 2,
        ACTION_CANCEL = 3
    };

    TouchEvent(MotionEvent action, float x, float y): action(action), x(x), y(y) {

    }

    ~TouchEvent() {}

public:
    MotionEvent action;
    float x, y;

};
