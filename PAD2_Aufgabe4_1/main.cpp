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


    return 0;
}
