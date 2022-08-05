//
// Created by ByteDance on 2022/8/5.
//

#include "BaseListAdapter.h"

template<typename T>
BaseListAdapter<T>::BaseListAdapter() {
    mData = std::vector<T>();
}

template<typename T>
BaseListAdapter<T>::~BaseListAdapter() {

}

template<typename T>
void BaseListAdapter<T>::setData(std::vector<T> data) {
    this->mData = std::move(data);
    notifyDataSetChanged();
}

template<typename T>
void BaseListAdapter<T>::notifyDataSetChanged() {

}

template<typename T>
void BaseListAdapter<T>::notifyItemChanged() {

}

template<typename T>
int BaseListAdapter<T>::getItemCount() {
    return mData.size();
}

template<typename T>
View *BaseListAdapter<T>::createView() {
    return nullptr;
}

template<typename T>
void BaseListAdapter<T>::bindView(View *view, T model) {

}

template<typename T>
void BaseListAdapter<T>::attachView(View *view) {

}

template<typename T>
void BaseListAdapter<T>::detachView(View *view) {

}
