//
// Created by admin on 10.09.2017.
//

#ifndef LAB_0_LISTSEQUENCE_H
#define LAB_0_LISTSEQUENCE_H

#include <stdexcept>
#include "sequence.h"


template <typename type>
class ListSequence : public Sequence<type> {
private:
    int _length;
    bool _isEmpty;

    struct SeqNode {
        SeqNode(const type &Item, SeqNode *_nextNode) : _value(Item), _next(_nextNode) {}
        explicit SeqNode(const type &Item) : _value(Item), _next(nullptr) {}

        SeqNode* _next;
        type _value;
    };

    SeqNode *_head, *_tail;
    // inserts newNode after currNode
    void _hiddenInsertToMiddle(SeqNode *currNode, SeqNode *newNode) {
        newNode->_next = currNode->_next;
        currNode->_next = newNode;

        _length++;
    }

    SeqNode *_hiddenIterFromNode(int index, SeqNode *startNode) const {
        auto iterNode = startNode;
        for (int i = 0; i < index; i++) { iterNode = iterNode->_next; }
        return iterNode;
    }

public:
    ListSequence() : _length(0), _isEmpty(true), _head(nullptr), _tail(nullptr) {}

    ~ListSequence() override {
        while (_head) {
            auto iterNode = _head;
            _head = _head->_next;
            delete iterNode;
        }
    }

    int getLength() const override { return _length; }

    bool getIsEmpty() const override { return _isEmpty; }

    type getFirst() const override {
        if (_isEmpty) { throw std::out_of_range("out of range"); }
        return _head->_value;
    }

    type getLast() const override {
        if (_isEmpty) { throw std::out_of_range("out of range"); }
        return _tail->_value;
    }

    type get(int index) const override {
        if (index < 0 || index >= _length) {
            throw std::out_of_range("out of range. index must be between 0 and sequence.getLength()"); }

        if (index == 0) { return getFirst(); }
        if (index == _length - 1) { return getLast(); }
        return _hiddenIterFromNode(index, _head)->_value;
    }

    void append(const type &newItem) override {
        auto newNode = new SeqNode(newItem, nullptr);
        auto *prevTail = _tail;
        _tail = newNode;

        if (!_head) {
            _head =  newNode;
            _isEmpty = false;
            _length++;
        } else { _hiddenInsertToMiddle(prevTail, newNode); }
    }

    void prepend(const type &newItem) override {
        auto newNode = new SeqNode(newItem, nullptr);

        if (!_head) {
            _head = _tail = newNode;
            _isEmpty = false;
        } else {
            newNode->_next = _head;
            _head = newNode;
        }
        _length++;
    }

    void insertAt(int index, const type &newItem) override {
        if (index < 0 || index > _length) {
            throw std::out_of_range("out of range. index must be between 0 and sequence.getLength()"); }

        if (index == 0) { prepend(newItem); }
        else if (index == _length) { append(newItem); }
        else {
            auto newNode = new SeqNode(newItem);
            _hiddenInsertToMiddle(_hiddenIterFromNode(index - 1, _head), newNode);
        }
    }

    void remove(const type &removableItem) override {
        if (_head->_value == removableItem) {
            auto *tempNode = _head;
            _head = _head->_next;
            delete tempNode;
        } else {
            auto *iterNode = _head;

            while (iterNode->_next && iterNode->_next->_value != removableItem)
                { iterNode = iterNode->_next; }
            if (!iterNode->_next) { return; }
            if (iterNode->_next == _tail) { _tail = iterNode; }

            auto *tempNode = iterNode->_next;
            iterNode->_next = tempNode->_next;
            delete tempNode;
        }
        _length--;
    }

    ListSequence<type> getSubsequence(int startIndex, int endIndex) const {
        if (startIndex > endIndex || startIndex < 0 || endIndex > _length) {
            throw std::out_of_range("index out of range"); }

        auto *nodePtr = _hiddenIterFromNode(startIndex, _head);
        ListSequence<type> newSeq;

        for (int i = 0; i < (endIndex - startIndex + 1); i++) {
            newSeq.append(nodePtr->_value);
            nodePtr = nodePtr->_next;
        }

        return newSeq;
    }
};

#endif //LAB_0_LISTSEQUENCE_H
