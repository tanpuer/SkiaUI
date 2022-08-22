//
// Created by ByteDance on 2022/8/18.
//

#include "HYListView.h"
#include "HYListAdapter.h"

HYListView::HYListView() : BaseListView<int>() {

}

HYListView::~HYListView() {

}

void HYListView::setAdapter(BaseListAdapter<int> *adapter) {
    BaseListView::setAdapter(adapter);
}

View *HYListView::createView(int index) {
    return adapter->createView(index);
}

void HYListView::attachChild(View *view) {
    BaseListView::attachChild(view);
    auto lp = LayoutParams::makeExactlyWidth(width);
    lp->setMargin({0, 20, 0, 20});
    FlexboxLayout::addView(view, lp);
}
