//
// Created by DZSB-000848 on 2/15/22.
//

#ifndef SKIAUI_MEASURESPEC_H
#define SKIAUI_MEASURESPEC_H

#include <yoga/YGEnums.h>
#include <yoga/Utils.h>
#include "native_log.h"
#include "string"

static const auto MODE_SHIFT = 30;
static const auto MODE_MASK = 0x3 << MODE_SHIFT;
static const auto SPEC_MAX_SIZE = (1 << MODE_SHIFT) - 1;

static const auto UNSPECIFIED = 0 << MODE_SHIFT;
static const auto EXACTLY = 1 << MODE_SHIFT;
static const auto AT_MOST = 2 << MODE_SHIFT;

static const auto MATCH_PARENT = -1;
static const auto WRAP_CONTENT = -2;

/**
 * 模仿Android的MeasureSpec
 */
class MeasureSpec {

public:

    static int getMode(int measureSpec) {
        //正好和YGMeasureMode对应起来
        return measureSpec & MODE_MASK;
    }

    static int getSize(int measureSpec) {
        return measureSpec & ~MODE_MASK;
    }

    static int makeMeasureSpec(int size, int mode) {
        assert(size >= WRAP_CONTENT && size <= SPEC_MAX_SIZE);
        assert(mode == UNSPECIFIED || mode == EXACTLY || mode == AT_MOST);
        return (size & ~MODE_MASK) | (mode & MODE_SHIFT);
    }

    static bool isMatchParent(int size) {
        return size == MATCH_PARENT;
    }

    static bool isWrapContent(int size) {
        return size == WRAP_CONTENT;
    }

    static void toString(int measureSpec) {
        int size = getSize(measureSpec);
        int mode = getMode(measureSpec);
        std::string modeString = "";
        switch (mode) {
            case UNSPECIFIED: {
                modeString = "UNSPECIFIED";
                break;
            }
            case EXACTLY: {
                modeString = "EXACTLY";
                break;
            }
            case AT_MOST: {
                modeString = "AT_MOST";
                break;
            }
            default: {
                modeString = "illegal mode";
                break;
            }
        }
        ALOGD("MeasureSpec width: %d, mode: %s", size, modeString.c_str())
    }

};


#endif //SKIAUI_MEASURESPEC_H
