//
// Created by ByteDance on 2022/7/15.
//

#ifndef SKIAUI_SCROLLVIEW_H
#define SKIAUI_SCROLLVIEW_H


#include "FlexboxLayout.h"
#include "Scroller.h"

/**
 * 高度=子View高度之和，不支持嵌套ScrollView
 */
class ScrollView : public FlexboxLayout {

public:

    ScrollView();

    virtual ~ScrollView();

    virtual void measure(int widthMeasureSpec, int heightMeasureSpec) override;

    virtual void layout(int l, int t, int r, int b) override;
    
protected:

    Scroller *scroller;

};


#endif //SKIAUI_SCROLLVIEW_H
