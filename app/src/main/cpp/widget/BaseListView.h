//
// Created by ByteDance on 2022/8/5.
//

#ifndef SKIAUI_BASELISTVIEW_H
#define SKIAUI_BASELISTVIEW_H

#include "BaseListAdapter.h"
#include "FlexboxLayout.h"

template<typename T>
class BaseListView : public FlexboxLayout {

public:

    BaseListView() : FlexboxLayout() {
        this->adapter = nullptr;
    }

    virtual ~BaseListView() {
        if (adapter != nullptr) {
            delete adapter;
        }
    }

#pragma mark ListView api

    virtual void setAdapter(BaseListAdapter<T> *adapter) {
        this->adapter = adapter;
    }

    /**
     * 当ListView可见区域还没放满时，应当通过adapter创建子View
     * @return
     */
    virtual View *createView(int index) = 0;

    /**
     * 将view添加到FlexboxLayout中
     * @param view
     */
    virtual void attachChild(View *view) {
        view->setConfig(config);
        adapter->attachView(view);
    }

    /**
     * 从FlexboxLayout中移除该view
     * @param view
     */
    virtual void detachChild(View *view) {

    }

    virtual void setVelocity(float x, float y) {
        xVelocity = x;
        yVelocity = y;
    }

#pragma mark View api

    /**
     * ListView的宽高要固定
     * 在onMeasure过程中发现还没铺满，要创建子view并添加进来
     * @param widthMeasureSpec
     * @param heightMeasureSpec
     */
    virtual void measure(int widthMeasureSpec, int heightMeasureSpec) override {
        SkASSERT(adapter != nullptr);
        SkASSERT(layoutParams->_widthMode == EXACTLY && layoutParams->_heightMode == EXACTLY);
        auto width = layoutParams->_width;
        auto height = layoutParams->_height;
        ViewGroup::setMeasuredDimension(width, height);
        while (height > getChildHeightSum() && children.size() < adapter->getItemCount()) {
            auto index = adapter->getCurrentIndex();
            auto child = adapter->createView(index);
            //加入view的时候要attach，remove的时候要detach
            attachChild(child);
            adapter->bindView(child, adapter->getItem(index));
            measureChild(child, widthMeasureSpec, heightMeasureSpec);
        }
        YGNodeCalculateLayout(node, width, height, YGDirectionLTR);
    }

protected:

    BaseListAdapter<T> *adapter;

    float xVelocity, yVelocity;

};


#endif //SKIAUI_BASELISTVIEW_H
