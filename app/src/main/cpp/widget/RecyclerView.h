//
// Created by ByteDance on 2022/12/6.
//

#ifndef SKIAUI_RECYCLERVIEW_H
#define SKIAUI_RECYCLERVIEW_H


#include "ScrollView.h"
#include "RecyclerViewAdapter.h"
#include "RecyclerViewHolder.h"

template<typename T>
class RecyclerView : public ScrollView {

    enum class RecyclerOrientation {

    };

public:

    RecyclerView() {

    }

    virtual ~RecyclerView() {
        delete adapter;
    }

    virtual void measure(int widthMeasureSpec, int heightMeasureSpec) override {
        //简化处理RecyclerView必须指定宽高
        assert(layoutParams->_heightMode == EXACTLY);
        assert(layoutParams->_widthMode == EXACTLY);
        if (adapter == nullptr) {
            ALOGD("RecyclerView Adapter is null, ignore measure")
            ViewGroup::setMeasuredDimension(width, height);
            return;
        }
        if (_direction == YGFlexDirectionColumn) {
            int childHeightSum = 0;
            for (auto child: children) {
                childHeightSum += child->getHeight();
            }

            //todo childHeightSum < height * 3
            while (children.size() < adapter->getSize() && childHeightSum < height * 3) {
                auto vh = adapter->onCreateViewHolder();
                if (vh == nullptr) {
                    continue;
                }
                View *child = vh->getItemView();
                //todo 找到此时需要更添加的pos,
                int pos = children.size();
                //todo
                adapter->onBindViewHolder(vh, pos, adapter->getItem(pos));
                auto viewLayoutParams = LayoutParams::makeExactlyWidth(width);
                child->setConfig(getConfig());
                ScrollView::addView(child, viewLayoutParams);
                child->measure(widthMeasureSpec, heightMeasureSpec);
                childHeightSum += child->getHeight();
            }
        } else {
            //todo 横向滑动暂时忽略
        }
        ViewGroup::setMeasuredDimension(width, height);
        YGNodeCalculateLayout(node, YGNodeStyleGetWidth(node).value,
                              YGNodeStyleGetHeight(node).value,
                              YGDirectionLTR);
    }

    virtual void layout(int l, int t, int r, int b) override {
        ScrollView::layout(l, t, r, b);
    }

    virtual void draw(SkCanvas *canvas) override {
        ScrollView::draw(canvas);
    }

#pragma mark adapter

    virtual void setAdapter(RecyclerViewAdapter<T> *adapter) {
        this->adapter = adapter;
    }

    virtual RecyclerViewAdapter<T> *getAdapter() {
        return adapter;
    }

protected:

    RecyclerViewAdapter<T> *adapter;

};


#endif //SKIAUI_RECYCLERVIEW_H
