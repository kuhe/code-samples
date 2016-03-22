#ifndef CPPREF_BINARYSEARCHTREE_H
#define CPPREF_BINARYSEARCHTREE_H

#include "./_bst_common.h"

namespace Lehr {

    /**
     * todo: Should be self-balancing
     */
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
        BinarySearchTree(const BinarySearchTree& model) {
            ingest_copy(model.root);
        }
        ~BinarySearchTree() {
            delete_from(root);
        }
        V& operator [](K key) {
            return get(key);
        }
        bool contains(K key) {
            return node_at(key) != nullptr;
        }
        bool contains_value(V val) {
            return node_with(val) != nullptr;
        }
        BinarySearchTree* truncate(K key) {
            delete_from(node_at(key));
            return this;
        }
        BinarySearchTree* truncate_value(V val) {
            delete_from(node_with(val));
            return this;
        }
        BinarySearchTree* excise(K key) {
            delete_only(node_at(key));
            return this;
        }
        BinarySearchTree* excise_value(V val) {
            delete_only(node_with(val));
            return this;
        }
        BinarySearchTree* slice(K key) {
            BinarySearchTree<K, V> copy;
            copy.ingest_copy(node_at(key));
            delete_from(root);
            ingest_copy(copy.root);
            return this;
        }
        BinarySearchTree* slice_value(V val) {
            BinarySearchTree<K, V> copy;
            copy.ingest_copy(node_with(val));
            delete_from(root);
            ingest_copy(copy.root);
            return this;
        }
        K root_key() {
            return root->key;
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
            BSTNode(const BSTNode& node) {
                parent = node.parent;
                left = node.left;
                right = node.right;
                key = node.key;
                value = node.value;
            }
            K key;
            V value;
            BSTNode* parent = nullptr;
            BSTNode* left = nullptr;
            BSTNode* right = nullptr;
            bool operator ==(BSTNode& other) {
                return other.key == key;
            }
        };
        BinarySearchTree* ingest_copy(BSTNode* node) {
            if (nullptr != node) {
                get(node->key);
                BSTNode* own_node_at = node_at(node->key);
                get(node->key) = node->value;
                if (nullptr != node->left) {
                    ingest_copy(node->left);
                }
                if (nullptr != node->right) {
                    ingest_copy(node->right);
                }
            }
            return this;
        }
        BinarySearchTree* attach(BSTNode* node) {
            if (nullptr != node) {
                node_at(node->key) = node;
            }
            return this;
        }
        void delete_from(BSTNode*& node) {
            if (nullptr != node) {
                if (nullptr != node->left) {
                    delete_from(node->left);
                }
                if (nullptr != node->left) {
                    delete_from(node->left);
                }
                delete node;
                node = nullptr;
            }
        }
        void delete_only(BSTNode*& node) {
            if (nullptr != node) {
                BSTNode* left = node->left;
                BSTNode* right = node->right;
                delete node;
                node = nullptr;
                attach(left);
                attach(right);
            }
        }
        BSTNode* root = nullptr;
        BSTNode*& node_at(K& key) {
            return node_at(key, root, nullptr);
        }
        BSTNode*& node_at(K& key, BSTNode*& context, BSTNode* parent) {
            if (nullptr == context) {

            } else {
                if (context->key > key) {
                    return node_at(key, context->left, context);
                } else if (context->key < key) {
                    return node_at(key, context->right, context);
                }
            }
            return context;
        }
        BSTNode*& node_with(V& val) {
            return node_with(val, root, nullptr);
        }
        BSTNode*& node_with(V& val, BSTNode*& context, BSTNode* parent) {
            if (nullptr == context) {

            } else {
                if (context->value > val) {
                    return node_with(val, context->left, context);
                } else if (context->value < val) {
                    return node_with(val, context->right, context);
                }
            }
            return context;
        }
        V& get(K key) {
            return get(key, root, nullptr);
        }
        V& get(K key, BSTNode*& context, BSTNode* parent = nullptr) {
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
