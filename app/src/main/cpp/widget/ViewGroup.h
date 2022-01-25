//
// Created by DZSB-000848 on 1/24/22.
//

#ifndef SKIAUI_VIEWGROUP_H
#define SKIAUI_VIEWGROUP_H


#include "View.h"
#include "../flexbox/FlexLayout.h"

class ViewGroup : public View {

public:

    ViewGroup() {}

    virtual ~ViewGroup() {}

public:

    FlexDirection flexDirection;
    FlexWarp flexWarp;
    JustifyContent justifyContent;
    AlignItems alignItems;
    AlignContent alignContent;

};


#endif //SKIAUI_VIEWGROUP_H
