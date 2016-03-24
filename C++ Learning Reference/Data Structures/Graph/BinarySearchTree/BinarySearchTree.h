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
        size_t depth() {
            return this->begin().depth; // todo expensive
        }
        size_t size() {
            return this->begin().members.size(); // todo expensive
        }
        BinarySearchTree* balance() {
            // todo
            return this;
        }
        ArrayList<K> keys() {
            ArrayList<K> keys;
            iterator iter = begin();

            for (auto i : *this) {
                keys.push(i.first);
            }

            return keys;
        }
    protected:
        struct BSTNode;
    public:
        struct iterator {
            iterator(BSTNode* from_node): cursor(0) {
                members.empty();
                recurse(from_node, 1);
            };

            ArrayList<BSTNode*> members;
            int cursor;
            const int end = -1;
            size_t depth = 0;

            void recurse(BSTNode* node, size_t set_depth) {
                if (nullptr != node) {
                    depth = set_depth;

                    if (nullptr != node->left) {
                        recurse(node->left, set_depth + 1);
                    }
                    members.push(node); // in-order traversal
                    if (nullptr != node->right) {
                        recurse(node->right, set_depth + 1);
                    }
                }
            }
            BSTNode& operator ->() {
                return *members[cursor];
            }
            pair<K, V> operator *() {
                if (cursor == end) {
                    return pair<K, V>();
                }
                auto ref = (*members[cursor]);
                return pair<K, V>(ref.key, ref.value);
            }
            bool operator ==(iterator& right) {
                return cursor == right.cursor;
            }
            bool operator !=(iterator& right) {
                return !operator ==(right);
            }
            iterator operator ++() {

                int test1 = cursor;
                long int test2 = members.size() - 1;

                if (cursor >= members.size() - 1) {
                    cursor = end;
                } else {
                    cursor++;
                }
                return *this;
            }
            iterator operator --() {
                if (cursor <= 0) {
                    cursor = end;
                } else {
                    cursor--;
                }
                return *this;
            }
        };
        BinarySearchTree<K, V>::iterator begin() {
            return iterator(root);
        }
        BinarySearchTree<K, V>::iterator end() {
            iterator iterator1 = iterator(root);
            iterator1.cursor = iterator1.end;
            return iterator1;
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
            explicit operator K*() const { return key; };
//            explicit operator V*() const { return value; };
            K key;
            V value;
            BSTNode* parent = nullptr;
            BSTNode* left = nullptr;
            BSTNode* right = nullptr;
            bool operator ==(BSTNode& other) {
                return other.key == key;
            }
        };
        void ingest_copy(BSTNode* node) {
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
        }
        void attach(BSTNode* node) {
            if (nullptr != node) {
                node_at(node->key) = node;
            }
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
