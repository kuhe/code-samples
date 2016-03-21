#ifndef CPPREF_BINARYSEARCHTREE_H
#define CPPREF_BINARYSEARCHTREE_H

#include "./_bst_common.h"

namespace Lehr {

    template<typename K, typename V = bool>
    class BinarySearchTree {
    public:
        BinarySearchTree() {};
        BinarySearchTree(K key) {
            root = new BSTNode(key);
        }
        BinarySearchTree(K key, V val) {
            root = new BSTNode(key, val);
        }
        ~BinarySearchTree() {
            deletion(root);
        }
        V& operator [](K key) {
            return get(key, root, nullptr);
        }
    protected:
        struct BSTNode {
            friend class BinarySearchTree<K, V>;
            BSTNode(K key): key(key) {};
            BSTNode(K key, V value): key(key), value(value) {};
            BSTNode(K key, V value, BSTNode* parent): key(key), value(value), parent(parent) {};
            BSTNode(K key, V value, BSTNode* left, BSTNode* right):
                    key(key), value(value), left(left), right(right) {};
            BSTNode(K key, V value, BSTNode* parent, BSTNode* left, BSTNode* right):
                    key(key), value(value), parent(parent), left(left), right(right) {};
            K key;
            V value;
            BSTNode* parent = nullptr;
            BSTNode* left = nullptr;
            BSTNode* right = nullptr;
        };
        void deletion(BSTNode* node) {
            if (nullptr != node) {
                if (nullptr != node->left) {
                    deletion(node->left);
                }
                if (nullptr != node->left) {
                    deletion(node->left);
                }
                delete node;
            }
        }
        BSTNode* root = nullptr;
        V& get(K key, BSTNode*& context, BSTNode* parent) {
            if (nullptr == context) {
                context = new BSTNode(key);
                context->parent = parent;
            } else {
                if (context->key > key) {
                    return get(key, context->left, context);
                } else if (context->key < key) {
                    return get(key, context->right, context);
                }
            }
            return context->value;
        }

    };

}

#endif //CPPREF_BINARYSEARCHTREE_H
