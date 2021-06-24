#include <iostream>
#include "liste.h"

using namespace std;

int main()
{
    Liste<int> listeA;
    Liste<int> listeB;
    Liste<int> mergeSortList;

    //Two sorted lists
    listeA.sortIns(5);
    listeA.sortIns(3);
    listeA.sortIns(8);
    listeA.sortIns(9);

    listeA.print();

    listeB.sortIns(3);
    listeB.sortIns(1);
    listeB.sortIns(7);

    listeB.print();

    //Test if the new list has no shallow copies
   // listeB.del();
   // listeB.del();
  //  listeB.del();

   // listeB.print();
   // mergeSortList.print();
    mergeSortList = mergeSortList.merge(listeA, listeB);
    mergeSortList.print();
    mergeSortList.mergeSort();

    //HEAP SORT
    Liste<int> heapSortList;

    heapSortList.sortIns(5);
    heapSortList.sortIns(3);
    heapSortList.sortIns(8);
    heapSortList.sortIns(9);
    heapSortList.sortIns(2);
    heapSortList.sortIns(4);
    heapSortList.sortIns(9);
    heapSortList.sortIns(1);
    heapSortList.sortIns(4);
    heapSortList.sortIns(5);
    heapSortList.sortIns(6);
    heapSortList.sortIns(7);
    heapSortList.sortIns(0);
    heapSortList.sortIns(2);
    heapSortList.sortIns(1);

    heapSortList.print();
    heapSortList.printTree();

    //getParent test
    heapSortList.getParent(0);
    heapSortList.getParent(1);
    heapSortList.getParent(14);

    //getLeftChild test
    heapSortList.getLeftChild(0);
    heapSortList.getLeftChild(1);
    heapSortList.getLeftChild(6);
    heapSortList.getLeftChild(14);

    //getRightChild test
    heapSortList.getRightChild(0);
    heapSortList.getRightChild(1);
    heapSortList.getRightChild(6);
    heapSortList.getRightChild(14);

    heapSortList.heapSort();
    heapSortList.print();



    return 0;
}
