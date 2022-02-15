//
// Created by DZSB-000848 on 2/15/22.
//

#ifndef SKIAUI_MEASURESPEC_H
#define SKIAUI_MEASURESPEC_H

#include <yoga/YGEnums.h>
#include <yoga/Utils.h>

static const float MATCH_PARENT = -2.0f;
static const float WRAP_CONTENT = -1.0f;

/**
 * 模仿Android的MeasureSpec，但是不用一个Int，位运算。
 */
class MeasureSpec {

public:

    MeasureSpec(float _size, YGMeasureMode _mode) : size(_size), mode(_mode) {}

    ~MeasureSpec() {}

    float getSize() {
        return size;
    }

    YGMeasureMode getMode() {
        return mode;
    }

    bool isMatchParent() {
        return YGFloatsEqual(size, MATCH_PARENT);
    }

    bool isWrapContent() {
        return YGFloatsEqual(size, WRAP_CONTENT);
    }

    bool isExactly() {
        return size >= 0.0f;
    }

    static bool isMatchParent(float size) {
        return YGFloatsEqual(size, MATCH_PARENT);
    }

    static bool isWrapContent(float size) {
        return YGFloatsEqual(size, WRAP_CONTENT);
    }

    static MeasureSpec *makeMeasureSpec(float size, YGMeasureMode mode) {
        return new MeasureSpec(size, mode);
    }

private:

    float size;

    YGMeasureMode mode;

};


#endif //SKIAUI_MEASURESPEC_H
