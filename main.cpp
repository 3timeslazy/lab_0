#include "arraysequence.h"
#include "listsequence.h"
#include "unittest.h"


int main() {

    std::cout << "\n===========LIST SEQUENCE TEST===========\n";
    UnitTestForSequence<ListSequence<int>> listSeqTest;
    listSeqTest.fullTest();
    std::cin.get();

    std::cout << "\n===========ARRAY SEQUENCE TEST===========\n";
    UnitTestForSequence<ArraySequence<int>> arraySeqTest;
    arraySeqTest.fullTest();
    std::cin.get();

    return 0;
}