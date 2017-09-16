//
// Created by admin on 15.09.2017.
//

#ifndef LAB_0_ARRAYSEQUENCE_H
#define LAB_0_ARRAYSEQUENCE_H

#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include "sequence.h"

template <typename type>
class ArraySequence : public Sequence<type> {
private:
    int _length;
    bool _isEmpty;

    type *_arrPtr;

public:
    ArraySequence() : _length(0), _isEmpty(true), _arrPtr(nullptr) {}

    ArraySequence(std::initializer_list<type> list)
            : _length(0), _isEmpty(true), _arrPtr(nullptr) {
        if (list.size()) {
            _arrPtr = new type[list.size()];
            _length = list.size();
            int i = 0;
            for (auto &item : list) { _arrPtr[i++] = item; }
        }
    }

    ~ArraySequence() {
        delete _arrPtr;
        _arrPtr = nullptr;
        _length = 0;
    }

    int getLength() const override { return _length; }

    bool getIsEmpty() const override { return _isEmpty; }

    type getFirst() const override {
        if (_isEmpty) { throw std::out_of_range("out of range"); }
        return _arrPtr[0];
    }

    type getLast() const override {
        if (_isEmpty) { throw std::out_of_range("out of range"); }
        return _arrPtr[_length - 1];
    }

    type get(int index) const override {
        if (index < 0 || index >= _length) {
            throw std::out_of_range("out of range. index must be between 0 and sequence.getLength()"); }
        if (index == 0) { return getFirst(); }
        if (index == _length - 1) { return getLast(); }
        return _arrPtr[index];
    }

    void  print() {
        for (auto i = 0; i < _length; i++) {std::cout << _arrPtr[i] << std::endl;}
    }

    void append(const type &newItem) override {
        insertAt(_length, newItem);
    }

    void prepend(const type &newItem) override  {
        auto tempPtr = new type[_length++];
        for (auto i = 0; i < _length - 1; i++) { tempPtr[i + 1] = std::move(_arrPtr[i]); }
        tempPtr[0] = newItem;
        delete _arrPtr;
        _arrPtr = tempPtr;
        _isEmpty = false;
    }

    void insertAt(int index, const type &newItem) override {
        if (index < 0 || index > _length) {
            throw std::out_of_range("out of range. index must be between 0 and sequence.getLength()"); }

        if (index == 0) {
            prepend(newItem);
            return;
        }
        auto tempPtr = new type[_length++];
        for (auto i = 0, stepDiff = 0; i < _length; i++) {
            tempPtr[i] = std::move(_arrPtr[i + stepDiff]);
            if (i == index) {
                tempPtr[i] = newItem;
                --stepDiff;
            }
        }
        delete _arrPtr;
        _arrPtr = tempPtr;
        _isEmpty = false;
    }

    void remove(const type &removableItem) override {
        bool isIn = false;
        for (auto i = 0; i < _length && !isIn; i++) {
            if ( _arrPtr[i] == removableItem) { isIn = true; }
        }
        if (isIn) {
            auto tempPtr = new type[_length--];
            for (auto i = 0, stepDiff = 0; i < _length; i++) {
                tempPtr[i] = std::move(_arrPtr[i + stepDiff]);
                if (_arrPtr[i] == removableItem) {
                    tempPtr[i] = _arrPtr[i + 1];
                    ++stepDiff; }
            }
            delete _arrPtr;
            _arrPtr = tempPtr;
        }
        if (!_length) { _isEmpty = true; }
    }

    ArraySequence<type> getSubsequence(int startIndex, int endIndex) const {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= _length) {
            throw std::out_of_range("index out of range"); }

        ArraySequence<type> newSeq;
        for (auto i = 0; i < endIndex - startIndex + 1; i++) { newSeq.append(_arrPtr[startIndex + i]); }
        return newSeq;
    }

};

#endif //LAB_0_ARRAYSEQUENCE_H
