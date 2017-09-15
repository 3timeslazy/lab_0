//
// Created by admin on 10.09.2017.
//

#ifndef LAB_0_SEQUENCE_H
#define LAB_0_SEQUENCE_H

template <typename type>
class Sequence {
public:
    virtual ~Sequence() = default;

    virtual int getLength() const = 0;
    virtual bool getIsEmpty() const = 0;

    virtual type get(int index) const = 0;
    virtual type getFirst() const = 0;
    virtual type getLast() const = 0;

    virtual void append(const type &newItem) = 0;
    virtual void prepend(const type& newItem) = 0;
    virtual void insertAt(int index, const type& newItem) = 0;
    virtual void remove(const type& removableItem) = 0;
};

#endif //LAB_0_SEQUENCE_H
