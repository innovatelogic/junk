#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace tree_traverse
    {
        //       A
        //     B    C
        //    D E  F G 

        TEST(BTree, TreeTraverse_Preorder)
        {
            Node<char> *A = new Node<char>('A');
            Node<char> *B = new Node<char>('B');
            Node<char> *C = new Node<char>('C');
            Node<char> *D = new Node<char>('D');
            Node<char> *E = new Node<char>('E');
            Node<char> *F = new Node<char>('F');
            Node<char> *G = new Node<char>('G');

            A->left = B; A->right = C;
            B->left = D; B->right = E;
            C->left = F; C->right = G;

            std::vector<char> sequence;
            BTree<char> tree(A);

            tree.traverse_preorder(
                [&](const char &out)
            {
                sequence.push_back(out);
            });

            //       A
            //     B    C
            //    D E  F G 

            std::vector<char> comp = { 'A', 'B', 'D', 'E', 'C', 'F', 'G' };

            EXPECT_EQ(sequence, comp);

            delete A;
            delete B;
            delete C;
            delete D;
            delete E;
            delete F;
            delete G;
        }

        TEST(BTree, TreeTraverse_Simmetrical)
        {
            Node<char> *A = new Node<char>('A');
            Node<char> *B = new Node<char>('B');
            Node<char> *C = new Node<char>('C');
            Node<char> *D = new Node<char>('D');
            Node<char> *E = new Node<char>('E');
            Node<char> *F = new Node<char>('F');
            Node<char> *G = new Node<char>('G');

            A->left = B; A->right = C;
            B->left = D; B->right = E;
            C->left = F; C->right = G;

            std::vector<char> sequence;
            BTree<char> tree(A);

            tree.traverse_inorder(
                [&](const char &out)
            {
                sequence.push_back(out);
            });

            //       A
            //     B    C
            //    D E  F G 

            std::vector<char> comp = { 'D', 'B', 'E', 'A', 'F', 'C', 'G' };

            EXPECT_EQ(sequence, comp);

            delete A;
            delete B;
            delete C;
            delete D;
            delete E;
            delete F;
            delete G;
        }

        TEST(BTree, TreeTraverse_Postorder)
        {
            Node<char> *A = new Node<char>('A');
            Node<char> *B = new Node<char>('B');
            Node<char> *C = new Node<char>('C');
            Node<char> *D = new Node<char>('D');
            Node<char> *E = new Node<char>('E');
            Node<char> *F = new Node<char>('F');
            Node<char> *G = new Node<char>('G');

            A->left = B; A->right = C;
            B->left = D; B->right = E;
            C->left = F; C->right = G;

            std::vector<char> sequence;
            BTree<char> tree(A);

            tree.traverse_postorder(
                [&](const char &out)
            {
                sequence.push_back(out);
            });

            //       A
            //     B    C
            //    D E  F G 

            std::vector<char> comp = { 'D', 'E', 'B', 'F', 'G', 'C', 'A' };

            EXPECT_EQ(sequence, comp);

            delete A;
            delete B;
            delete C;
            delete D;
            delete E;
            delete F;
            delete G;
        }
    }
}