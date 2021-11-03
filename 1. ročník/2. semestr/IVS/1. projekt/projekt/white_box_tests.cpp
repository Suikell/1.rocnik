//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2021-03-08
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Iveta Snášelová
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

using namespace std;

class mat_mxm : public ::testing::Test
{
    protected:
        Matrix mat{3,3};
        virtual void SetUp()
        {
            mat.set(vector<vector<double>> {{5,5,1},{3,-4,-3},{-2,1,1}});
        }

        Matrix get4x4()
        {
            Matrix mat_4x4(4,4);
            mat_4x4.set(vector<vector<double>> {{2,2,-3,1},{1,2,4,2},{-1,1,-1,1},{1,-1,2,-2}});
            return mat_4x4;
        }

        Matrix get3x3()
        {
            Matrix mat_3x3{3,3};
            mat_3x3.set(vector<vector<double>> {{1,2,-3},{0,1,2},{0,0,1}});
            return mat_3x3;
        }

        Matrix get2x2()
        {
            Matrix mat_2x2{2,2};
            mat_2x2.set(vector<vector<double>> {{1,2},{3,5}});
            return mat_2x2;
        }
};

class mat_mxn : public ::testing::Test
{
    protected:
        Matrix mat{2,4};
        vector<vector<double>> vec_2x4 {{5, 1, 7, 1},
                                    {2, 3, 4, -20} };
        virtual void SetUp()
        {
            mat.set(vec_2x4);
        }

        Matrix get4x2()
        {
            Matrix mat_2{4,2};
            mat_2.set(vector<vector<double>> {{-5, 11},
                                              {2, 1},
                                              {12, -13},
                                              {4, -5} });
            return mat_2;
        }

        Matrix get2x3()
        {
            Matrix mat_3{2,3};
            mat_3.set(vector<vector<double>> { {5, 1, 7},
                                                    {2, 3, 4} });
           return mat_3;
	}
};

TEST(mat, basicConstruct)
{
    EXPECT_NO_THROW(Matrix());
    EXPECT_NO_THROW(Matrix(1,1));
    EXPECT_NO_THROW(Matrix(2,5));
    EXPECT_NO_THROW(Matrix(7,3));

    EXPECT_ANY_THROW(Matrix(0,0));
    EXPECT_ANY_THROW(Matrix(0,5));
    EXPECT_ANY_THROW(Matrix(5,0));
}

TEST_F(mat_mxn, setValue)
{
    EXPECT_TRUE(mat.set(1,1,75));
    EXPECT_TRUE(mat.set(1,2,75));
    EXPECT_TRUE(mat.set(1,3,75));
    EXPECT_TRUE(mat.set(0,1,75));
    EXPECT_TRUE(mat.set(0,2,75));
    EXPECT_TRUE(mat.set(0,3,75));
    EXPECT_TRUE(mat.set(0,0,75));

    ASSERT_FALSE(mat.set(100, 1, 75));
    ASSERT_FALSE(mat.set(1, 100, 75));
    ASSERT_FALSE(mat.set(15, 1, 75));
    ASSERT_FALSE(mat.set(1, 15, 75));
    ASSERT_FALSE(mat.set(100, 100, 75));

    ASSERT_FALSE(mat.set(-5, 1, 75));
    ASSERT_FALSE(mat.set(1, -5, 75));
    ASSERT_FALSE(mat.set(-5, -1, 75));

}

TEST_F(mat_mxn, setValues)
{
    EXPECT_TRUE(mat.set(vector<vector<double>>  {{1,2,3,4},
                                                           {5,6,7,8} }));
    EXPECT_TRUE(mat.set(vector<vector<double>>  {{-1,-2,-3,-4},
                                                           {-5,-6,-7,-8} }));
    EXPECT_TRUE(mat.set(vector<vector<double>>  {{105, 100, 107, 111},
                                                           {-212, -123, -144, -120} }));


    ASSERT_FALSE(mat.set(vector<vector<double>> { {1, 1, 2, 3, 4 } }));
    ASSERT_FALSE(mat.set(vector<vector<double>> { {1},
                                                            {1},
                                                            {2},
                                                            {3},
                                                            {4} }));
    ASSERT_FALSE(mat.set(vector<vector<double>> { {1, 1, 2},
                                                            {3, 4} }));
    ASSERT_FALSE(mat.set(vector<vector<double>> { {1, 1},
                                                            {2, 3, 4} }));
}
TEST_F(mat_mxn, getValue)
{
    int k = 0;
    for(int i = 0; i < 2; i++)
    {
        for( int j = 0; j < 4; j++)
        {
            EXPECT_EQ(mat.get(i,j), vec_2x4[i][j]);
            k++;
        }
    }

   EXPECT_ANY_THROW(mat.get(100,1));
   EXPECT_ANY_THROW(mat.get(1,100));
   EXPECT_ANY_THROW(mat.get(100,100));
   EXPECT_ANY_THROW(mat.get(1,-1));
   EXPECT_ANY_THROW(mat.get(-1,1));

}

TEST_F(mat_mxn, equal)
{
    Matrix mat_1 = get4x2();
    Matrix mat_2 = get4x2();

    EXPECT_TRUE(mat==mat);
    EXPECT_TRUE(mat_1==mat_1);
    mat_2.set(0,0,-500);
    EXPECT_FALSE(mat_1 == mat_2);

    EXPECT_ANY_THROW(Matrix(1,2) == Matrix(2,3));
    EXPECT_ANY_THROW(Matrix(2,1) == Matrix(5,5));
}

TEST(matrix, plus)
{
    Matrix mat_1{2,4};
    mat_1.set(vector<vector<double>> {{5, 1, 7, 1}, {2, 3, 4, -20} });
    Matrix mat_2{2,4};
    mat_2.set(vector<vector<double>> {{-5, 11, 2, 1}, {12, -13, 4, -5} });

    Matrix exp{2,4};
    exp.set(vector<vector<double>> { {0, 12, 9, 2}, {14, -10, 8, -25} });

    EXPECT_EQ(mat_1 + mat_2, exp);
    EXPECT_EQ(mat_2 + mat_1, exp);

    EXPECT_ANY_THROW(mat_1 + Matrix(4,5));
    EXPECT_ANY_THROW(mat_1 + Matrix(2,2));

};

TEST(matrix, multiply)
{
    Matrix mat_1{2,4};
    mat_1.set(vector<vector<double>> {{5, 1, 7, 1},
                                             {2, 3, 4, -20} });
    Matrix mat_2{4,2};
    mat_2.set(vector<vector<double>> {{-5, 11},
                                              {2, 1},
                                              {12, -13},
                                              {4, -5} });

    Matrix exp_1{2,2};
    exp_1.set(vector<vector<double>> { {65, -40},
                                              {-36, 73} });
    Matrix exp_2{4,4};
    exp_2.set(vector<vector<double>> { { -3, 28, 9, -225},
                                              { 12, 5, 18, -18},
                                              { 34, -27, 32, 272},
                                              {10, -11, 8, 104}});

    EXPECT_EQ(mat_1*mat_2, exp_1);
    EXPECT_EQ(mat_2*mat_1, exp_2);

    EXPECT_ANY_THROW(Matrix(1,4) * Matrix(1, 4));
    EXPECT_ANY_THROW(Matrix(2,1) * Matrix(2,5));
}

TEST_F(mat_mxn, numMultiply)
{
    Matrix mat_2x3 = get2x3();

    Matrix exp{2,3};
    exp.set(vector<vector<double>> { {-10, -2, -14},
                                            {-4, -6, -8} });
    EXPECT_EQ(mat_2x3*(-2), exp);

    exp.set(vector<vector<double>> { {15, 3, 21},
                                            {6, 9, 12} });
    EXPECT_EQ(mat_2x3*(3), exp);
}

TEST_F(mat_mxm, equation)
{
    vector<double> rightSize_1 = {2, 1, -1};
    vector<double> res_1 = {1, -1, 2};

    EXPECT_EQ(mat.solveEquation(rightSize_1), res_1);

    Matrix mat2 = get4x4();
    vector<double> rightSize_2 = { 3, 5, 1, -4};
    vector<double> res_2 = { 1, -1, 0, 3};

    EXPECT_EQ(mat2.solveEquation(rightSize_2),res_2);

    Matrix mat3{1,1};
    mat3.set(0,0,1);
    vector<double> res_3 = {1};
    EXPECT_EQ(mat3.solveEquation({1}), res_3);

    EXPECT_ANY_THROW(mat.solveEquation(rightSize_2));

    EXPECT_ANY_THROW(Matrix(1,3).solveEquation(rightSize_1));

    Matrix m = Matrix{2,2};
    m.set(vector<vector<double>>{{1,2},{1,2}});
    EXPECT_ANY_THROW(m.solveEquation({2,3}));
}

TEST_F(mat_mxn, transpose)
{
    Matrix exp_1{4,2};
    exp_1.set(vector<vector<double>>{{5,2},{1,3},{7,4},{1, -20}});

    EXPECT_EQ(mat.transpose(), exp_1);

    Matrix exp_2{2,4};
    exp_2.set(vector<vector<double>>{{-5,2,12,4},{11,1,-13,-5}});

    EXPECT_EQ(get4x2().transpose(), exp_2);
}

TEST_F(mat_mxm, inverse)
{
    EXPECT_ANY_THROW(get4x4().inverse());
    EXPECT_ANY_THROW(Matrix(1,1).inverse());

    Matrix exp_1{2,2};
    exp_1.set(vector<vector<double>>{{-5,2},{3,-1}});
    EXPECT_EQ(get2x2().inverse(),exp_1);

    Matrix exp_2{3,3};
    exp_2.set(vector<vector<double>>{{1,-2,7},{0,1,-2},{0,0,1}});
    EXPECT_EQ(get3x3().inverse(),exp_2);

    Matrix wrong{2,2};
    wrong.set(vector<vector<double>> {{1,2},{1,2}});
    EXPECT_ANY_THROW(wrong.inverse());
}

/*** Konec souboru white_box_tests.cpp ***/
