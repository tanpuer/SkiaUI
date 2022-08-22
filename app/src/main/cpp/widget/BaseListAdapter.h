//
// Created by ByteDance on 2022/8/5.
//

#ifndef SKIAUI_BASELISTADAPTER_H
#define SKIAUI_BASELISTADAPTER_H

#include "vector"
#include "View.h"
#include "set"

template<typename T>
class BaseListAdapter {

public:

    BaseListAdapter() {
        currentIndex = 0;
        mData = std::vector<T>();
        viewPool = std::set<View *>();
    }

    virtual ~BaseListAdapter() {

    }

    virtual void setData(std::vector<T> data) {
        this->mData = std::move(data);
        notifyDataSetChanged();
    }

    virtual void notifyDataSetChanged() {

    }

    virtual void notifyItemChanged() {

    }

    virtual int getItemCount() {
        return mData.size();
    }

    /**
     * 暂时不考虑多itemType，后续也好加
     * @return
     */
    virtual View *createView(int index) = 0;

    virtual bool canCreateView() {
        return currentIndex < mData.size();
    }

    virtual void bindView(View *view, T model) = 0;

    /**
     * view从缓存池中取出，加到屏幕上的ViewGroup里
     */
    virtual void attachView(View *view) {
        currentIndex++;
    }

    /**
     * 从ViewGroup里移除，放入到缓存池中
     * @param view
     */
    virtual void detachView(View *view) {
        currentIndex--;
    }

    T getItem(int index) {
        return mData[index];
    }

    int getCurrentIndex() {
        return currentIndex;
    }

protected:

    std::vector<T> mData;

    std::set<View *> viewPool;

    int currentIndex;

};


#endif //SKIAUI_BASELISTADAPTER_H
