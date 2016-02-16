#include "LinkedListImpl.hpp"
#include <gtest/gtest.h>
#include <utility>

using namespace std;

class LinkedListTest : public ::testing::Test {
public:
    LinkedListImpl testList = LinkedListImpl();
    int *listData;
    const size_t count = 10;

    virtual void SetUp() {
        srand(time(NULL));
        listData = new int[count];
        randomGenerate();
        for (size_t i = 0; i < count; i++)
            testList.push_back(listData[i]);
    }
    
    void TearDown() {
        delete []listData;
    }

    void randomGenerate() {
        for (size_t i = 0; i < count; i++)
            listData[i] = rand();
    }
};

TEST_F (LinkedListTest, Constructor) {
    LinkedListImpl list;
    EXPECT_EQ (0, list.size());
}

TEST_F (LinkedListTest, Front) {
    EXPECT_EQ (listData[0], testList.front());
    testList.pop_front();
    EXPECT_EQ (listData[1], testList.front());
}

TEST_F (LinkedListTest, Back) {
    EXPECT_EQ (listData[count - 1], testList.back());
    testList.pop_back();
    EXPECT_EQ (listData[count - 2], testList.back());
}

TEST_F (LinkedListTest, Front_Const) {
    const LinkedListImpl list(testList);
    EXPECT_EQ (listData[0], list.front());
}

TEST_F (LinkedListTest, PushBack) {
    EXPECT_EQ (count, testList.size());
    testList.push_back(10);
    EXPECT_EQ (listData[0], testList.front());
    EXPECT_EQ (10, testList.back());
    EXPECT_EQ (count + 1, testList.size());
}

TEST_F (LinkedListTest, PushFront) {
    testList.push_front(10);
    EXPECT_EQ (testList.front(), 10);
    EXPECT_EQ (testList.size(), count + 1);
}

TEST_F (LinkedListTest, Begin) {
    LinkedListImpl::ConstIteratorImpl iter(testList.begin());
    EXPECT_EQ (listData[0], *iter);
    EXPECT_EQ (listData[1], *(++iter));
    EXPECT_EQ (listData[2], *(++iter));
}

TEST_F (LinkedListTest, End) {
    LinkedListImpl::ConstIteratorImpl iter = testList.end();
    EXPECT_EQ (listData[count - 1], *(--iter));
    EXPECT_EQ(listData[count - 2], *(--iter));
    EXPECT_EQ(listData[count - 3], *(--iter));
}

TEST_F (LinkedListTest, Begin_Const) {
    const LinkedListImpl list(testList);
    LinkedListImpl::IteratorImpl iter (list.begin());
    EXPECT_EQ (listData[0], *iter);
    EXPECT_EQ (listData[1], *(++iter));
}

TEST_F (LinkedListTest, End_Const) {
    const LinkedListImpl list(testList);
    LinkedListImpl::IteratorImpl iter (list.end());
    EXPECT_EQ (*(--iter), listData[count - 1]);
    EXPECT_EQ (*(--iter), listData[count - 2]);
}

TEST_F (LinkedListTest, EraseOne) {
    LinkedListImpl::IteratorImpl iter = testList.begin();
    testList.erase(iter);
    EXPECT_EQ (listData[1], testList.front());

    iter = testList.end();
    testList.erase(--iter);
    EXPECT_EQ (listData[count - 2], testList.back());
    testList.clear();
    EXPECT_EQ (0, testList.size());
}

TEST_F (LinkedListTest, EraseInterval) {
    testList.erase(testList.begin(), testList.end());
    EXPECT_TRUE (testList.empty());
}

TEST_F (LinkedListTest, Clear) {
    testList.clear();
    EXPECT_TRUE (testList.empty());
}

TEST_F (LinkedListTest, RemoveOne) {
    testList.clear();
    EXPECT_FALSE (testList.remove_one(1));
    EXPECT_TRUE (testList.empty());
    testList.push_back(listData[0]);
    EXPECT_TRUE (testList.remove_one(listData[0]));
    EXPECT_TRUE (testList.empty());

    for (size_t i = 0; i < count; i++)
        testList.push_back(listData[i]);

    EXPECT_TRUE (testList.remove_one(*testList.begin()));
    EXPECT_EQ (9, testList.size());
    EXPECT_EQ (listData[1], *(testList.begin()));
    EXPECT_EQ (listData[2], *(++testList.begin()));
}

TEST_F (LinkedListTest, Remove_All) {
    testList.clear();
    for (size_t i = 0; i < count - 1; i++)
        testList.push_back(1);

    testList.push_back(2);
    size_t removeCount = testList.remove_all(1);
    EXPECT_EQ (1, testList.size());
    EXPECT_EQ (9, removeCount);
    EXPECT_EQ (2, *testList.begin());
}

TEST_F (LinkedListTest, Contains) {
    int i = 0;
    for (auto iter = testList.begin(); iter != testList.end(); iter++) {
        EXPECT_EQ (listData[i++], *iter); 
   }
}

TEST_F (LinkedListTest, Count) {
    LinkedListImpl list;
    for (size_t i = 0; i < 10; i++)
        list.push_back(1);
    EXPECT_EQ(list.count(1), 10);
}

TEST_F (LinkedListTest, Size) {
    LinkedListImpl list;
    for (size_t i = 0; i < 10; i++)
        list.push_back(1);
    EXPECT_EQ(list.size(), 10);
}

TEST_F (LinkedListTest, Empty) {
    LinkedListImpl list;
    EXPECT_TRUE (list.empty());
    testList.clear();
    EXPECT_TRUE (testList.empty());
    testList.push_back(listData[0]);
    EXPECT_FALSE (testList.empty());
}

TEST_F (LinkedListTest, PopBack) {
    testList.pop_back();
    EXPECT_EQ (listData[count - 2], testList.back());
    EXPECT_EQ (9, testList.size());
}

TEST_F (LinkedListTest, PopFront) {
    testList.pop_front();
    EXPECT_EQ (listData[1], testList.front());
    EXPECT_EQ (9, testList.size());
}

TEST_F (LinkedListTest, Insert) {
    LinkedListImpl::IteratorImpl iter = testList.begin();
    iter = testList.insert(++iter, 10);
    EXPECT_EQ (10, *iter);
    EXPECT_EQ (10, *(++testList.begin()));
}

TEST_F (LinkedListTest, Operator_NotEqual) {
    LinkedListImpl list;
    EXPECT_TRUE (list != testList);
    for (size_t i = 0; i < count; i++)
        list.push_back(listData[i]);
    EXPECT_FALSE (list != testList);
}

TEST_F (LinkedListTest, Operator_Equal) {
    LinkedListImpl list;
    EXPECT_FALSE (list == testList);
    for (size_t i = 0; i < count; i++)
        list.push_back(listData[i]);
    EXPECT_TRUE (list == testList);
}

TEST_F (LinkedListTest, Operator_Plus) {
    LinkedListImpl list;

    int *arr = new int[10];

    for (size_t i = 0; i < 10; i++) {
        arr[i] = rand();
        list.push_back(arr[i]);
    }

    LinkedListImpl summary = list + testList;

    auto iter = summary.begin();

    for (size_t i = 0; i < 10; i++, iter++) {
        EXPECT_EQ (arr[i], *iter);
    }  

    for (size_t i = 10; i < 20; i++, iter++) {
        EXPECT_EQ (listData[i - 10], *iter);
    }

    delete arr; 
}

TEST_F (LinkedListTest, Operator_EQPlus) {
    LinkedListImpl list;
    list.push_back(10);
    list += testList;
    EXPECT_EQ(*list.begin(), 10);
    int i = 0;
    for (auto iter = ++list.begin(); iter != list.end(); iter++, i++)
        EXPECT_EQ(listData[i], *iter);
}

TEST_F (LinkedListTest, Operator_EQPlusValue) {
    LinkedListImpl list;
    for (size_t i = 0; i < count; i++)
        list += listData[i];
    EXPECT_TRUE (list == testList);
}

TEST_F (LinkedListTest, Operator_EQ) {
    LinkedListImpl list;
    list = testList;
    EXPECT_TRUE (list == testList);
    for (size_t i = 0; i < count; i++)
        list.push_back(i);

    EXPECT_FALSE (list == testList);
    testList = list;
    EXPECT_TRUE(testList == list);
}

TEST_F (LinkedListTest, IteratorImpl_copy_) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    LinkedListImpl::IteratorImpl iter1 (iter);
    EXPECT_TRUE (iter == iter1);
    EXPECT_TRUE (*iter == *iter1);
}

TEST_F (LinkedListTest, IteratorImpl_NodeConstructor) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    EXPECT_EQ (testList.front(), *iter);
}

TEST_F (LinkedListTest, IteratorImpl_OperatorEqual) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    LinkedListImpl::IteratorImpl iter1 = iter;
    EXPECT_TRUE (iter == iter1);
}

TEST_F (LinkedListTest, IteratorImpl_OperatorNotEqual) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    LinkedListImpl::IteratorImpl iter1 (--testList.end());
    EXPECT_TRUE (iter != iter1);
}

TEST_F (LinkedListTest, IteratorImpl_OperatorDereference) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    for (size_t i = 0; i < count; i++, iter++)
        EXPECT_EQ(listData[i], *iter);
}

TEST_F (LinkedListTest, IteratorImpl_OperatorArrow) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    EXPECT_EQ (listData[0], (iter.operator->())->value);
    iter = testList.end();
    EXPECT_EQ (listData[count - 1], ((--iter).operator->())->value);
}

TEST_F (LinkedListTest, IteratorImpl_PrefixInc) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    EXPECT_EQ (listData[0], *iter);
    EXPECT_EQ (listData[2], *(++(++iter)));
}

TEST_F (LinkedListTest, IteratorImpl_PostfixInc) {
    LinkedListImpl::IteratorImpl iter (testList.begin());
    for (size_t i = 0; i < count; i++, iter++)
        EXPECT_EQ(listData[i], *iter);
}

TEST_F (LinkedListTest, IteratorImpl_PrefixDec) {
    LinkedListImpl::IteratorImpl iter (testList.end());
    iter--;
    for (size_t i = count; i > 0 && iter != testList.begin(); i--, --iter)
        EXPECT_EQ(listData[i - 1], *iter);
}

TEST_F (LinkedListTest, IteratorImpl_PostfixDec) {
    LinkedListImpl::IteratorImpl iter (--testList.end());
    for (size_t i = count; i > 0 && iter != testList.begin(); i--, iter--)
        EXPECT_EQ(listData[i - 1], *iter);
}

TEST_F (LinkedListTest, ConstIteratorImpl_Copy) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    LinkedListImpl::ConstIteratorImpl iter1 (iter);
    EXPECT_TRUE (iter == iter1);
    EXPECT_TRUE (*iter == *iter1);
}

TEST_F (LinkedListTest, ConstIteratorImpl_NodeConstructor) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    EXPECT_EQ (testList.front(), *iter);
}

TEST_F (LinkedListTest, ConstIteratorImpl_OperatorEqual) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    LinkedListImpl::ConstIteratorImpl iter1 = iter;
    EXPECT_TRUE (iter == iter1);
}

TEST_F (LinkedListTest, ConstIteratorImpl_OperatorNotEqual) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    LinkedListImpl::ConstIteratorImpl iter1 (--testList.end());
    EXPECT_TRUE (iter != iter1);
}

TEST_F (LinkedListTest, ConstIteratorImpl_OperatorDereference) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    for (size_t i = 0; i < count; i++, iter++)
        EXPECT_EQ(listData[i], *iter);
}

TEST_F (LinkedListTest, ConstIteratorImpl_OperatorArrow) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    EXPECT_EQ (listData[0], (iter.operator->())->value);
    iter = testList.end();
    EXPECT_EQ (listData[count - 1], ((--iter).operator->())->value);
}

TEST_F (LinkedListTest, ConstIteratorImpl_PrefixInc) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    EXPECT_EQ (listData[0], *iter);
    EXPECT_EQ (listData[2], *(++(++iter)));
}

TEST_F (LinkedListTest, ConstIteratorImpl_PostfixInc) {
    LinkedListImpl::ConstIteratorImpl iter (testList.begin());
    for (size_t i = 0; i < count; i++, iter++)
        EXPECT_EQ(listData[i], *iter);
}

TEST_F (LinkedListTest, ConstIteratorImpl_PrefixDec) {
    LinkedListImpl::ConstIteratorImpl iter (testList.end());
    iter--;
    for (size_t i = count; i > 0 && iter != testList.begin(); i--, --iter)
        EXPECT_EQ(listData[i - 1], *iter);
}

TEST_F (LinkedListTest, ConstIteratorImpl_PostfixDec) {
    LinkedListImpl::ConstIteratorImpl iter (testList.end());
    --iter;
    for (size_t i = count; i > 0 && iter != testList.begin(); i--, iter--) 
        EXPECT_EQ(listData[i - 1], *iter);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << RUN_ALL_TESTS() << std::endl;
    return 0;
}
