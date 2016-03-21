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

    BinarySearchTree<int, string> map_tree;

    string fourteen = "fourteen";
    string twenty = "twenty";

    map_tree[14] = fourteen;
    map_tree[20] = twenty;

    string test1 = map_tree[14];
    string test2 = map_tree[20];

    console_test(fourteen, test1);
    console_test(twenty, test2);

    return 0;
}

#endif //CPPREF_TEST_TREES_CPP