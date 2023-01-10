//
// Created by ByteDance on 2022/12/6.
//

#ifndef SKIAUI_RECYCLERVIEWADAPTER_H
#define SKIAUI_RECYCLERVIEWADAPTER_H

#include "vector"
#include "stack"
#include "RecyclerViewHolder.h"

template<typename T>
class RecyclerViewAdapter {

public:

    RecyclerViewAdapter() {
        data = std::vector<T>();
        vhCache = std::stack<RecyclerViewHolder<T> *>();
        currVHList = std::vector<RecyclerViewHolder<T> *>();
    }

    virtual ~RecyclerViewAdapter() {
        //todo 析构 data 和 vh
    }

    virtual void setData(std::vector<T> data) {
        this->data = data;
    }

    virtual T getItem(int pos) {
        assert(pos >= 0 && pos < data.size());
        return data[pos];
    }

    virtual int getSize() {
        return data.size();
    }

    virtual int getItemType(int index) {
        return 0;
    }

#pragma mark ViewHolder

    virtual RecyclerViewHolder<T> *onCreateViewHolder(int viewType) = 0;

    virtual void onBindViewHolder(RecyclerViewHolder<T> *viewHolder, int index, T item) = 0;

    virtual void onRecycleViewHolder(RecyclerViewHolder<T> *viewHolder, T item) = 0;

    virtual void putViewHolderToCache(RecyclerViewHolder<T> *vh) {
        vhCache.push(vh);
    }

    virtual RecyclerViewHolder<T> *getViewHolderFromCache() {
        if (vhCache.empty()) {
            return nullptr;
        }
        auto vh = vhCache.top();
        vhCache.pop();
        return vh;
    }

#pragma mark notify

    virtual void notifyDataSetChanged() {

    }

    virtual void notifyItemChanged(int index) {

    }

#pragma mark index

    /**
     * 列表中对应的data的区间
     */
    int startIndex = 0;
    int endIndex = 0;

    /**
     * 向下滑动时，回收头部的vh
     * @param vh
     */
    void recycleStartVH(RecyclerViewHolder<T> *vh) {
        putViewHolderToCache(vh);
        onRecycleViewHolder(vh, data[startIndex]);
        startIndex++;
        currVHList.erase(currVHList.begin());
    }

    /**
     * 向上滑动时，回收尾部的vh
     * @param vh
     */
    void recyclerEndVH(RecyclerViewHolder<T> *vh) {
        putViewHolderToCache(vh);
        endIndex--;
        onRecycleViewHolder(vh, data[endIndex]);
        currVHList.erase(currVHList.end() - 1);
    }

    /**
     * 向上滑动时，处理头部的vh
     */
    RecyclerViewHolder<T> *handleStartVH() {
        auto vh = getViewHolderFromCache();
        startIndex--;
        if (vh == nullptr) {
            auto itemType = getItemType(startIndex);
            vh = onCreateViewHolder(itemType);
        }
        auto item = data[startIndex];
        onBindViewHolder(vh, startIndex, item);
        currVHList.insert(currVHList.begin(), vh);
        return vh;
    }

    /**
     * 向下滑动时，处理尾部的vh
     * @return
     */
    RecyclerViewHolder<T> *handleEndVH() {
        auto vh = getViewHolderFromCache();
        if (vh == nullptr) {
            auto itemType = getItemType(endIndex);
            vh = onCreateViewHolder(itemType);
        }
        auto item = data[endIndex];
        onBindViewHolder(vh, endIndex, item);
        endIndex++;
        currVHList.insert(currVHList.end(), vh);
        return vh;
    }

    virtual void setOnItemClickListener(std::function<void(T, View *)> callback) {
        this->itemClickListener = itemClickListener;
    }

    virtual void setConfig(YGConfigRef config) {
        if (this->config == nullptr) {
            this->config = config;
        }
    }

protected:

    std::vector<T> data;

    std::function<void(T, View *)> itemClickListener = nullptr;

    YGConfigRef config;

private:

    /**
     * vh缓存，暂时用Stack实现
     */
    std::stack<RecyclerViewHolder<T> *> vhCache;

public:
    /**
     * 当前RecyclerView所持有的vh集合
     */
    std::vector<RecyclerViewHolder<T> *> currVHList;

};

#endif //SKIAUI_RECYCLERVIEWADAPTER_H
