#include <stdexcept>
#include <assert.h>
#include "LinkedList.hpp"

struct Node;

int &LinkedList::front() {
	return list->front();
}

const int &LinkedList::front() const {
	return list->front();
}

int &LinkedList::back() {	
	return list->back();
}

const int &LinkedList::back() const {	
	return list->back();
}

LinkedList::Iterator LinkedList::begin() {
    Iterator iter;
    *(iter.iterImpl) = list->begin();

    return iter;
}

/*const LinkedList::Iterator LinkedList::begin() const {
    return list->begin();
}*/

LinkedList::Iterator LinkedList::end() {
    Iterator iter;
    *(iter.iterImpl) = list->end();

    return iter;
}

/*const LinkedList::Iterator LinkedList::end() const {
    
    return iter->end();
}*/

void LinkedList::push_back(const int &value) {
    list->push_back(value);
}

void LinkedList::push_front(const int &value) {
	list->push_front(value);
}

bool LinkedList::contains(const int &value) const {
	return list->contains(value);
}

size_t LinkedList::count(const int &value) const {
	return list->count(value);
}

LinkedList::Iterator LinkedList::erase(LinkedList::Iterator current) {
	Iterator tempIter;
    (*tempIter.iterImpl) = list->erase(*current.iterImpl);

	return tempIter;
}

LinkedList::Iterator LinkedList::erase(LinkedList::Iterator begin, LinkedList::Iterator end) {
	Iterator tempIter;
	(*tempIter.iterImpl) = list->erase(*begin.iterImpl, *end.iterImpl);

	return tempIter;
}

void LinkedList::clear() {
    list->clear();
}

size_t LinkedList::remove_all(const int &value) {
   return list->remove_all(value);
}

bool LinkedList::remove_one(const int &value) {
   return list->remove_one(value);
}

void LinkedList::pop_back() {
	list->pop_back();
}

void LinkedList::pop_front() {
	list->pop_front();
}

LinkedList::Iterator LinkedList::insert(Iterator before, const int&value) {
	Iterator iter;
	*(iter.iterImpl) = list->insert(*(before.iterImpl), value);

	return iter;
}

bool LinkedList::operator!=(const LinkedList &other) const {
    return list->operator!=(*(other.list));
}

bool LinkedList::operator==(const LinkedList &other) const {
	return list->operator==(*(other.list));
}

LinkedList LinkedList::operator+(const LinkedList &other) const {
	LinkedListImpl *implList = new LinkedListImpl(list->operator+(*(other.list)));
	LinkedList newList;

	delete (newList.list);
	newList.list = implList;

	return newList;
}

LinkedList &LinkedList::operator+=(const LinkedList &other) {
	LinkedList copy(*this);

	copy.list->operator+=(*(other.list));
	*this = std::move(copy);
	return *this;
}

LinkedList &LinkedList::operator+=(const int&value) {
    list->operator+=(value);

    return *this;
}

LinkedList &LinkedList::operator=(const LinkedList &other) {
	if (this == &other)
		return *this;

	LinkedList copyList(other);

	delete(list);
	list = copyList.list;
	copyList.list = nullptr;

	return *this;
}

LinkedList &LinkedList::operator=(LinkedList &&other) {
    delete(list);

    list = other.list;
    other.list = nullptr;

    return *this;
}