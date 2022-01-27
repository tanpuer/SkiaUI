//
// Created by DZSB-000848 on 1/26/22.
//

#ifndef SKIAUI_LINEARLAYOUT_H
#define SKIAUI_LINEARLAYOUT_H


#include "ViewGroup.h"

class LinearLayout : public ViewGroup {

public:

    LinearLayout();

    virtual ~LinearLayout();

    virtual bool addView(View *view) override;

    virtual bool removeView(View *view) override;

#pragma mark LinearLayoyt api

    virtual void setOrientation(YGFlexDirection orientation);

    YGFlexDirection orientation = YGFlexDirectionRow;

};


#endif //SKIAUI_LINEARLAYOUT_H
