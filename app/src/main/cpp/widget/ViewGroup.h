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

    virtual void layout() override;

    virtual void draw(SkCanvas *canvas) override;

#pragma mark ViewGroup api

    virtual bool addView(View *view);

    virtual bool removeView(View *view);

    virtual void removeAllViews();

    virtual void setAlignItems(YGAlign align);

    YGNodeRef root;

    std::vector<View *> children;

};


#endif //SKIAUI_VIEWGROUP_H
