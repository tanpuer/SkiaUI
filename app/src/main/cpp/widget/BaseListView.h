//
// Created by ByteDance on 2022/8/5.
//

#ifndef SKIAUI_BASELISTVIEW_H
#define SKIAUI_BASELISTVIEW_H

#include "BaseListAdapter.h"

template<typename T>

class BaseListView {

public:

    BaseListView();

    virtual ~BaseListView();

    virtual void setAdapter(BaseListAdapter<T> adapter);

    virtual void attachChild(View *view);

    virtual void detachChild(View *view);

};


#endif //SKIAUI_BASELISTVIEW_H
