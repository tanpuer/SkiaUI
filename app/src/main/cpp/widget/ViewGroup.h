//
// Created by DZSB-000848 on 1/24/22.
//

#ifndef SKIAUI_VIEWGROUP_H
#define SKIAUI_VIEWGROUP_H


#include "View.h"
#include "vector"

class ViewGroup : public View {

public:

    ViewGroup();

    virtual ~ViewGroup();

    virtual void measure() override;

    virtual void layout(float l, float t, float r, float b) override;

    virtual void draw(SkCanvas *canvas) override;

#pragma mark ViewGroup api

    virtual bool addView(View *view);

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

    YGNodeRef root;

    YGConfigRef config;

    std::vector<View *> children;

};


#endif //SKIAUI_VIEWGROUP_H
