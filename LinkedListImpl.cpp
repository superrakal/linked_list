#include <stdexcept>
#include <assert.h>
#include "LinkedListImpl.hpp"

struct Node;

int &LinkedListImpl::front() {
	if (head == last) 
		throw (std::range_error("Empty List"));
	return head->value;
}

const int &LinkedListImpl::front() const {
	if (head == last) 
		throw (std::range_error("Empty List"));
	return head->value;	
}

int &LinkedListImpl::back() {	
	Node *pTemp = head;
	for (size_t i = 0; i < (list_length - 1); i++)
		pTemp = pTemp->next;
	return pTemp->value;
}

const int &LinkedListImpl::back() const {	
	Node *pTemp = head;
    for (size_t i = 0; i < (list_length - 1); i++)
		pTemp = pTemp->next;
	return pTemp->value;
}

LinkedListImpl::IteratorImpl LinkedListImpl::begin() {
	if (head == last)
		throw (std::range_error("Empty List"));
	return IteratorImpl(head);
}

const LinkedListImpl::IteratorImpl LinkedListImpl::begin() const {
	if (head == last)
		throw (std::range_error("Empty List"));
    return LinkedListImpl::IteratorImpl(head);
}

LinkedListImpl::IteratorImpl LinkedListImpl::end() {
	if (head == last)
		throw (std::range_error("Empty List"));
    return LinkedListImpl::IteratorImpl(last);
}

const LinkedListImpl::IteratorImpl LinkedListImpl::end() const {
    if (head == last)
        throw (std::range_error("Empty List"));
    return LinkedListImpl::IteratorImpl(last);
}

void LinkedListImpl::push_back(const int &value) {
    insert(LinkedListImpl::IteratorImpl(last), value);
}

void LinkedListImpl::push_front(const int &value) {
	insert(begin(), value);
}

LinkedListImpl::IteratorImpl LinkedListImpl::insert(LinkedListImpl::IteratorImpl before, const int &value) {
	list_length++;

    Node *pNodePrev = before.pCurrentNode->prev;
	Node *pCurrentNode = before.pCurrentNode;
	Node *pNewNode = createNode(value);
	if (!pNodePrev) {
		pNewNode->next = head;
		head->prev = pNewNode;
		head = pNewNode;
		return LinkedListImpl::IteratorImpl(head);
	}

	pNodePrev->next = pNewNode;
	pNewNode->prev = pNodePrev;
	pNewNode->next = pCurrentNode;
	pCurrentNode->prev = pNewNode;
	return LinkedListImpl::IteratorImpl(pNewNode);
}

bool LinkedListImpl::contains(const int &value) const {
	for (auto &i : *this) {
		if (value == i)
			return true;
	}

	return false;
}

size_t LinkedListImpl::count(const int &value) const {
	size_t counter = 0;
	for (auto &i : *this) {
		if (value == i)
			counter++;
	}

	return counter;
}

LinkedListImpl::IteratorImpl LinkedListImpl::erase(LinkedListImpl::IteratorImpl pos) {
	Node *pUselessNode = pos.pCurrentNode;

	if (!pUselessNode)
		throw(std::range_error("Empty Iterrator"));

	Node *pPrevNode = pUselessNode->prev;
	Node *pNextNode = pUselessNode->next;
	if (pUselessNode == last)
		return end();

	list_length--;
	if (pUselessNode == head) {
		pNextNode->prev = nullptr;
		head = pNextNode;
		delete pUselessNode;
        if (list_length)
            return begin();
        else
            return IteratorImpl(nullptr);
	}

	pPrevNode->next = pNextNode;
	pNextNode->prev = pPrevNode;
	delete pUselessNode;
	return LinkedListImpl::IteratorImpl(pNextNode);
}

LinkedListImpl::IteratorImpl LinkedListImpl::erase(LinkedListImpl::IteratorImpl begin, LinkedListImpl::IteratorImpl end) {
	Node *pUselessNode = begin.pCurrentNode;
	Node *pLastUselessNode = end.pCurrentNode;

	if (!pUselessNode || !pLastUselessNode)
		throw(std::range_error("Empty Iterrator"));

    auto iter = begin;
    auto iter_backup = begin;
    for (; iter_backup != end;) {
        ++iter_backup;
        erase(iter);
        iter = iter_backup;
    }
    
   
	return LinkedListImpl::IteratorImpl(iter.pCurrentNode);
}

void LinkedListImpl::clear() {
    if (list_length)
	    erase(begin(), end());
}

size_t LinkedListImpl::remove_all(const int &value) {
    auto iterBackup = begin();
    size_t counter = 0;
	for (auto iter = begin(); iter != end();) {
		if (value == *iter) {
			iterBackup = iter;
            iterBackup++;
			erase(iter);
            counter++;
			iter = iterBackup;
        } else
            iter++;
	}

    return counter;
}

bool LinkedListImpl::remove_one(const int & value) {
    try {
        for (auto iter = begin(); iter != end(); iter++) {
            if (value == *iter) {
                erase(iter);
                return true;
            }
        }

        return false;
    }
    catch (...) {
        return false;
    }
}

void LinkedListImpl::pop_back() {
	erase(--end());
}

void LinkedListImpl::pop_front() {
	erase(begin());
}

bool LinkedListImpl::operator!=(const LinkedListImpl & other) const {
	return !(other == *this);
} 

bool LinkedListImpl::operator==(const LinkedListImpl &other) const {
	if (list_length != other.list_length)
		return false;

	auto iter2 = other.begin();
	for (auto &iter : *this) {
		if (iter != *iter2)
			return false;
        ++iter2;
	}

	return true;
}

LinkedListImpl LinkedListImpl::operator+(const LinkedListImpl &other) const {
	LinkedListImpl newList;

    newList += *this;
    newList += other;

    return newList;
} 

LinkedListImpl &LinkedListImpl::operator+=(const LinkedListImpl &other) {
	for (auto &i : other) {
		push_back(i);
	}

	return *this;
}

LinkedListImpl &LinkedListImpl::operator+=(const int &value) { push_back(value); return *this; }
LinkedListImpl &LinkedListImpl::operator=(const LinkedListImpl &other) {
	if (this == &other)
		return *this;

	clear();
    for (auto &i : other)
        this->push_back(i);
    
	return *this;
}

LinkedListImpl &LinkedListImpl::operator=(LinkedListImpl &&other) {
	clear();
	*this = other;
	other.clear();
	return *this;
}

void LinkedListImpl::BaseIteratorImpl::moveStraight() {
	if (!pCurrentNode->next) 
		throw (std::range_error("End of List"));
	pCurrentNode = pCurrentNode->next;
}

void LinkedListImpl::BaseIteratorImpl::moveBack() {
	if (!pCurrentNode->prev) 
		throw (std::range_error("End of List"));
	pCurrentNode = pCurrentNode->prev;
}
