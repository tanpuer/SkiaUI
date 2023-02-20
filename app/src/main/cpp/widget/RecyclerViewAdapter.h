//
// Created by ByteDance on 2022/12/6.
//

#ifndef SKIAUI_RECYCLERVIEWADAPTER_H
#define SKIAUI_RECYCLERVIEWADAPTER_H

#include "vector"
#include "stack"
#include "RecyclerViewHolder.h"
#include "unordered_map"
#include "TextView.h"

template<typename T>
class RecyclerViewAdapter {

public:

    RecyclerViewAdapter() {

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

    virtual void putViewHolderToCache(int itemType, RecyclerViewHolder<T> *vh) {
        if (vhCache.find(itemType) == vhCache.end()) {
            ALOGD("RecyclerView init cache %d", itemType)
            vhCache.emplace(itemType, new std::stack<RecyclerViewHolder<T> *>());
        }
        auto vhStack = vhCache[itemType];
        vhStack->push(vh);
        ALOGD("RecyclerView push to cache %d %d", itemType, vhStack->size())
    }

    virtual RecyclerViewHolder<T> *getViewHolderFromCache(int itemType) {
        if (vhCache.find(itemType) == vhCache.end()) {
            ALOGD("RecyclerView init cache %d", itemType)
            vhCache.emplace(itemType, new std::stack<RecyclerViewHolder<T> *>());
            return nullptr;
        }
        auto vhStack = vhCache[itemType];
        if (vhStack->empty()) {
            return nullptr;
        } else {
            auto vh = vhStack->top();
            vhStack->pop();
            return vh;
        }
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
        auto text = static_cast<TextView *>(vh->getItemView())->getText();
        ALOGD("RecyclerView recycleStartVH %d %s", startIndex, text.c_str())
        putViewHolderToCache(getItemType(startIndex), vh);
        onRecycleViewHolder(vh, data[startIndex]);
        startIndex++;
        currVHList.erase(currVHList.begin());
    }

    /**
     * 向上滑动时，回收尾部的vh
     * @param vh
     */
    void recyclerEndVH(RecyclerViewHolder<T> *vh) {
        ALOGD("RecyclerView recyclerEndVH %d", endIndex)
        putViewHolderToCache(getItemType(endIndex), vh);
        endIndex--;
        onRecycleViewHolder(vh, data[endIndex]);
        currVHList.erase(currVHList.end() - 1);
    }

    /**
     * 向上滑动时，处理头部的vh
     */
    RecyclerViewHolder<T> *handleStartVH() {
        startIndex--;
        auto vh = getViewHolderFromCache(getItemType(startIndex));
        if (vh == nullptr) {
            auto itemType = getItemType(startIndex);
            vh = onCreateViewHolder(itemType);
            ALOGD("RecyclerView create new VH for start %d, itemType: %d", startIndex, getItemType(startIndex))
        } else {
            ALOGD("RecyclerView getVHFromCache for start: %d, itemType: %d", startIndex, getItemType(startIndex))
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
        auto vh = getViewHolderFromCache(getItemType(endIndex));
        if (vh == nullptr) {
            auto itemType = getItemType(endIndex);
            vh = onCreateViewHolder(itemType);
            ALOGD("RecyclerView create new VH for end %d, itemType: %d", endIndex, getItemType(endIndex))
        } else {
            ALOGD("RecyclerView get VH from Cache for end %d, itemType: %d", endIndex, getItemType(endIndex))
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
     * vh缓存，暂时用Map + Stack实现
     */
    std::unordered_map<int, std::stack<RecyclerViewHolder<T> *> *> vhCache;

public:
    /**
     * 当前RecyclerView所持有的vh集合
     */
    std::vector<RecyclerViewHolder<T> *> currVHList;

};

#endif //SKIAUI_RECYCLERVIEWADAPTER_H
