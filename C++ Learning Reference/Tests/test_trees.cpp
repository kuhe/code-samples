#ifndef CPPREF_TEST_TREES_CPP
#define CPPREF_TEST_TREES_CPP

#include "./test_trees.h"

using Lehr::BinarySearchTree;

int test_trees() {

    BinarySearchTree<int> tree(0);
    BinarySearchTree<string> str_tree("a");
    BinarySearchTree<int, string> map_tree2(12, "twelve");

    BinarySearchTree<int, int> itree;

    itree[2] = 22;
    itree[3] = 333;

    console_test(itree[2], 22);
    console_test(itree[3], 333);
    console_test(itree.contains(2), true);
    console_test(itree.contains(3), true);
    console_test(itree.contains(333), false);
    console_test(itree.contains(22), false);
    console_test(itree.contains_value(22), true);
    console_test(itree.contains_value(333), true);
    console_test(itree.contains_value(2), false);
    console_test(itree.contains_value(3), false);

    itree[4] = 4444;
    itree[5] = 55555;

    console_test(itree.contains_value(55555), true);
    itree.truncate(4);
    console_test(itree.contains_value(55555), false);
    console_test(itree.contains_value(4444), false);
    console_test(itree.contains_value(333), true);

    itree[6] = 666666;
    itree[7] = 7777777;
    itree[8] = 88888888;

//    itree.excise(7);
    console_test(itree.contains(8), true);
//    console_test(itree.contains(7), false);
    console_test(itree.contains(6), true);

    BinarySearchTree<int, string> map_tree;

    string fourteen = "fourteen";
    string twenty = "twenty";

    map_tree[14] = fourteen;
    map_tree[20] = twenty;

    string test1 = map_tree[14];
    string test2 = map_tree[20];

    console_test(fourteen, test1);
    console_test(twenty, test2);

    str_tree["excelsior!"];
    console_test(str_tree.contains("excelsior!"), true);

    cout << endl;
    return 0;
}

#endif //CPPREF_TEST_TREES_CPP