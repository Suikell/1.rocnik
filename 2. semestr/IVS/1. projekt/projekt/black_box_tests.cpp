//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2017-03-08
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Iveta Snášelová
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class NonEmptyTree : public ::testing::Test
{
	protected:
		virtual void SetUp()
		{
			int values[] = { 5, 10, 15, 20, 30, 40, 50, 55, 60, 65, 70, 80, 85, 90 };

			for(int i = 0; i < 14; i++)
				tree.InsertNode(values[i]);
				
		}
	BinaryTree tree;
};

class EmptyTree : public ::testing::Test
{
	protected:
		BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
            for(int i = 0; i < rand() % 20; i++)
            {
                int randomNum = rand() % 200;
                tree.InsertNode(randomNum);
            }
        }
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode)
{
    ASSERT_EQ(tree.GetRoot(), nullptr);

    int value = 5;
    auto res_1 = tree.InsertNode(value);
    ASSERT_TRUE(res_1.first);
    EXPECT_EQ(res_1.second->key, value);
    ASSERT_FALSE(tree.GetRoot() == nullptr);

    auto  res_2 = tree.InsertNode(value);
    EXPECT_FALSE(res_2.first);
    EXPECT_EQ(res_2.second->key,value);
    EXPECT_EQ(tree.GetRoot()->key, res_2.second->key);

}

TEST_F(EmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(5));
}

TEST_F(EmptyTree, FindNode)
{
    EXPECT_EQ(tree.FindNode(5), nullptr);
}

TEST_F(NonEmptyTree, InsertNode)
{
    int values[] = {1, 2, 100, 73};
    for (int i = 0; i < 4; i++)
    {
        auto res_1 = tree.InsertNode(values[i]);
        EXPECT_TRUE(res_1.first);
        EXPECT_EQ(res_1.second->key, values[i]);
    }
    for(int i = 0; i < 4; i++)
    {
        auto res_1 = tree.InsertNode(values[i]);
        EXPECT_FALSE(res_1.first);
        EXPECT_EQ(res_1.second->key, values[i]);
    }
}

TEST_F(NonEmptyTree, DeleteNode)
{
    int values[] = { 5, 10, 15, 20, 30, 40, 50, 55, 60, 65, 70, 80, 85, 90 };

    for(int i = 0; i < 14; i+=2)
    {
        EXPECT_TRUE(tree.DeleteNode(values[i]));
        EXPECT_FALSE(tree.DeleteNode(values[i]));
    }
    for(int i = 13; i>=0; i-=2)
    {
        EXPECT_TRUE(tree.DeleteNode(values[i]));
        EXPECT_FALSE(tree.DeleteNode(values[i]));
    }
    EXPECT_EQ(tree.GetRoot(), nullptr);
}

TEST_F(NonEmptyTree, FindNode)
{
    int valuesInTree[] = { 5, 10, 15, 20, 30, 40, 50, 55, 60, 65, 70, 80, 85, 90 };
    int valuesNotInTree [] = { 1, 2, 3, 31, 32, 41, 42, 66, 67, 79, 81, 92, 105, 200 };

    for(int i = 0; i < 14; i++)
    {
        EXPECT_EQ(tree.FindNode(valuesInTree[i])->key, valuesInTree[i]);
        EXPECT_EQ(tree.FindNode(valuesNotInTree[i]), nullptr);
    }
}

TEST_F(TreeAxioms, Axiom1)
{
    std::vector<Node_t *> leaves {};
    tree.GetLeafNodes(leaves);
    for(auto leaf : leaves)
        EXPECT_EQ(leaf->color, BinaryTree::BLACK);
}

TEST_F(TreeAxioms, Axiom2)
{
    std::vector<Node_t *> nodes {};
    for(auto node : nodes)
    {
        if(node->color == BinaryTree::RED)
        {
            EXPECT_EQ(node->pLeft->color, BinaryTree::BLACK);
            EXPECT_EQ(node->pRight->color, BinaryTree::BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3)
{
        std::vector<Node_t *> leaves {};
        tree.GetLeafNodes(leaves);

        int blackNodes = 0;
        int firstPath = 0;

        for(auto node : leaves)
        {
            int newBlackNodes = 0;
            while(node == tree.GetRoot())
            {
                if(node->color == BinaryTree::BLACK)
                {
                    if(firstPath == 0)
                        blackNodes++;
                    newBlackNodes++;
                }
                node = node->pParent;
            }
            firstPath++;
            EXPECT_EQ(blackNodes, newBlackNodes);
        }
}

/*** Konec souboru black_box_tests.cpp ***/
