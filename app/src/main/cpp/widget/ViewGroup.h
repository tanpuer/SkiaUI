//
// Created by DZSB-000848 on 1/24/22.
//

#ifndef SKIAUI_VIEWGROUP_H
#define SKIAUI_VIEWGROUP_H


#include "View.h"
#include "vector"
#include "LayoutParams.h"

class ViewGroup : public View {

public:

    ViewGroup();

    virtual ~ViewGroup();

    const char * name() override;

    void measure(int widthMeasureSpec, int heightMeasureSpec) override;

    void measureChild(View *child, int parentWidthMeasureSpec, int parentHeightMeasureSpec);

    int getChildMeasureSpec(int parentMeasureSpec, int padding, int childDimension);

    void setMeasuredDimension(int _measuredWidth, int _measuredHeight) override;

    /**
     * 子类ViewGroup必须复写
     */
    virtual void layout(int l, int t, int r, int b) override = 0;

    virtual void draw(SkCanvas *canvas) override;

    bool isViewGroup() override;

    virtual int getWidth() override;

    virtual int getHeight() override;

    int getMaxHeightInChildren();

    int getMaxWidthInChildren();

#pragma mark ViewGroup api

    virtual bool addView(View *view, LayoutParams *layoutParams);

    virtual bool removeView(View *view);

    virtual void removeAllViews();

    /**
     * 子视图在主轴上的排列对齐方式
     * @param justify
     */
    virtual void setJustifyContent(YGJustify justify);

    /**
     * 子视图在侧轴上的排列方式
     * @param align
     */
    virtual void setAlignItems(YGAlign align);

    /**
     * 子视图行与行之间在侧轴上的对齐方式
     * @param align
     */
    virtual void setAlignContent(YGAlign align);

    /**
     * wrap类型
     * @param wrap
     */
    virtual void setFlexWrap(YGWrap wrap);

    /**
     * flex的方向
     * @param direction
     */
    virtual void setFlexDirection(YGFlexDirection direction);

    /**
     * 注意不能搞混，View实用node，ViewGroup实用root
     */
    YGNodeRef root;

    YGConfigRef config;

    std::vector<View *> children;

    float maxChildWidth, maxChildHeight;

};


#endif //SKIAUI_VIEWGROUP_H
