#ifndef CPPREF_BINARYSEARCHTREE_H
#define CPPREF_BINARYSEARCHTREE_H

#include "./_bst_common.h"

namespace Lehr {

    template<typename K, typename V = bool>
    class BinarySearchTree {
    public:
        BinarySearchTree();
        BinarySearchTree(K key);
        BinarySearchTree(K key, V val);
        BinarySearchTree(const BinarySearchTree& model);
        ~BinarySearchTree();

        V& operator [](K key);
        bool contains(K key);
        bool contains_value(V val);
        BinarySearchTree* truncate(K key);
        BinarySearchTree* truncate_value(V val);
        BinarySearchTree* excise(K key);
        BinarySearchTree* excise_value(V val);
        BinarySearchTree* slice(K key);
        BinarySearchTree* slice_value(V val);
        K root_key();
        size_t depth();
        size_t size();
        BinarySearchTree* balance();
        ArrayList<K> keys();

        struct iterator;
        iterator begin();
        iterator end();

    protected:
        struct BSTNode;
        void ingest_copy(BSTNode* node);
        void attach(BSTNode* node);
        void delete_from(BSTNode*& node);
        void delete_only(BSTNode*& node);
        BSTNode* root = nullptr;
        BSTNode*& node_at(K& key);
        BSTNode*& node_at(K& key, BSTNode*& context, BSTNode* parent);
        BSTNode*& node_with(V& val);
        BSTNode*& node_with(V& val, BSTNode*& context, BSTNode* parent);
        V& get(K key);
        V& get(K key, BSTNode*& context, BSTNode* parent = nullptr);
    };

}


namespace Lehr {
//    template<typename K, typename V>
//    typename BinarySearchTree<K, V>::iterator BinarySearchTree<K, V>::begin() {
//        return BinarySearchTree<K, V>::iterator(root);
//    }
};


#include "./BinarySearchTree.cpp.h"

#endif //CPPREF_BINARYSEARCHTREE_H
