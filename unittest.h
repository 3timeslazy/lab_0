//
// Created by admin on 14.09.2017.
//

#ifndef LAB_0_UNITTEST_H
#define LAB_0_UNITTEST_H

#include <iostream>
#include <vector>

template <typename type>
class UnitTestForSequence {
public:
    UnitTestForSequence() : _failed(0), _passed(0) {}

    void fullTest() {

        auto *testSeq = new type;
        std::cout << "===========INITIALIZING===========\n";

        check(testSeq->getLength() == 0, "Length is equal 0 after init");

        check(testSeq->getIsEmpty() == true, "isEmpty() is equal true after init");


        testSeq->append(23);
        std::cout << "\n===========APPEND 23===========\n";

        check(testSeq->getLength() == 1, "Length is equal 1 after append 23");

        check(testSeq->getFirst() == 23, "getFirst is equal 23");

        check(testSeq->getLast() == 23, "getLast is equal 23 after append 23");

        check(testSeq->get(0) == 23, "get(0) return 23");

        try { testSeq->get(-1); } catch (const std::exception&) {
            check(true, "get(-1) throws exception"); }

        try  { testSeq->get(1); } catch (const std::exception&) {
            check(true, "get(1) throws exception"); }


        testSeq->append(43);
        std::cout << "\n===========APPEND 43===========\n";

        check(testSeq->getLength() == 2, "Length is equal 2 after second append");

        check(testSeq->getFirst() == 23, "getFirst() return 23");

        check(testSeq->getLast() == 43, "getLast() return 43");

        check(testSeq->get(0) == 23, "get(0) return 23");

        check(testSeq->get(1) == 43, "get(1) return 43");

        try { testSeq->get(-1); } catch (const std::exception&) {
            check(true, "get(-1) throws exception"); }

        try { testSeq->get(2); } catch (const std::exception&) {
            check(true, "get(2) throws exception"); }


        testSeq->prepend(53);
        std::cout << "\n===========PREPEND 53===========\n";

        check(testSeq->getLength() == 3, "Length is equal 3 after prepend");

        check(testSeq->getFirst() == 53, "getFirst() is equal 53 after prepend");

        check(testSeq->getLast() == 43, "getLast() return 43");

        check(testSeq->get(0) == 53, "get(0) return 53");

        try { testSeq->get(-1); } catch (const std::exception&) {
            check(true, "get(-1) throws exception"); }

        try { testSeq->get(3); } catch (const std::exception&) {
            check(true, "get(3) throws exception"); }


        std::cout << "\n===========GETSUBSEQUENCE(1, 1)===========\n";

        check(testSeq->getSubsequence(1, 1).getLength() == 1, "Length is equal 1");

        check(testSeq->getSubsequence(1, 1).getFirst() == 23, "Subsequence.getFirst() is equal 23");



        testSeq->remove(53);
        std::cout << "\n===========REMOVE 53 (head)===========\n";

        check(testSeq->getFirst() == 23, "getFirst() is equal 23 after remove head (53)");

        testSeq->prepend(53);
        testSeq->remove(23);
        std::cout << "\n===========REMOVE 23 (middle)===========\n";

        check(testSeq->get(1) == testSeq->getLast(), "get(1) is equal getLast() after remove");

        testSeq->insertAt(1, 23);
        testSeq->remove(43);
        std::cout << "\n===========REMOVE 43 (tail)===========\n";

        check(testSeq->getLast() == 23, "tail is equal 23 after remove 43");


        testSeq->insertAt(0, 66);
        std::cout << "\n===========INSERTAT(0, 66)===========\n";

        check(testSeq->getFirst() == 66, "getFirst() is equal 66 after insertAt(0, 66)");


        testSeq->insertAt(1, 31);
        std::cout << "\n===========INSERTAT(1, 31)===========\n";

        check(testSeq->get(1) == 31, "get(1) is equal 31 after insertAt(1, 31)");

        std::cout << "\nfailed: " + std::to_string(_failed) + ", passed: " + std::to_string(_passed);
    }

private:
    int _failed;
    int _passed;
    std::vector<std::string> allTests;

    void check(bool result, std::string test) {
        if (result) { _passed++; } else { _failed++; }
        test += (result ? " - OK" : " - FAILED");
        std::cout << test << std::endl;
        allTests.push_back(test);
    }

};

#endif //LAB_0_UNITTEST_H
