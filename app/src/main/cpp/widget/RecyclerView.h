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
            for (auto &child: children) {
                childHeightSum += child->getHeight();
            }

            if (childHeightSum > height) {
                //从头清理
                for (auto itr = adapter->currVHList.cbegin(); itr != adapter->currVHList.cend();) {
                    if (*itr == nullptr) {
                        break;
                    }
                    auto itemView = (*itr)->getItemView();
                    if (ignoreChildDraw(itemView)) {
                        adapter->recycleStartVH(*itr);
                        itr = adapter->currVHList.cbegin();
                        ScrollView::removeView(itemView);
                    } else {
                        itr++;
                        break;
                    }
                }
                //从尾清理
                for (auto itr = adapter->currVHList.cend(); itr != adapter->currVHList.cbegin();) {
                    if (*itr == nullptr) {
                        break;
                    }
                    auto itemView = (*itr)->getItemView();
                    if (ignoreChildDraw(itemView)) {
                        adapter->recyclerEndVH(*itr);
                        itr = adapter->currVHList.cend();
                        ScrollView::removeView(itemView);
                    } else {
                        itr--;
                        break;
                    }
                }
            }

            while (children.size() < adapter->getSize() &&
                   childHeightSum - abs(translateY) <= height) {
                RecyclerViewHolder<T> *vh = nullptr;
                if (lastScrollDown) {
                    vh = adapter->handleEndVH();
                } else {
                    vh = adapter->handleStartVH();
                }
                View *child = vh->getItemView();
                auto viewLayoutParams = LayoutParams::makeExactlyWidth(width);
                child->setConfig(getConfig());
                ScrollView::addView(child, viewLayoutParams);
                ALOGD("RecyclerView addView: %s", child->name())
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

    virtual bool canScroll() override {
        //todo 先写死无限滑动
        if (_direction == YGFlexDirectionColumn) {
            return true;
        } else {
            return true;
        }
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
