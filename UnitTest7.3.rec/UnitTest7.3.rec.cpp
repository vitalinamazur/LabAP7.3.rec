#include "pch.h"
#include "CppUnitTest.h"
#include "../LabAP7.3.rec/labAP7.3.rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlb73rec
{
    TEST_CLASS(UnitTestlb73rec)
    {
    public:


        TEST_METHOD(TestMinSumParallelDiagonals)
        {
            const int size = 3;
            int** a = new int* [size];
            for (int i = 0; i < size; i++)
                a[i] = new int[size];

            a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
            a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
            a[2][0] = 7; a[2][1] = 8; a[2][2] = 9;

            int minSum;
            MinSumParallelDiagonals(a, size, 1 - size, minSum);
            Assert::AreEqual(0, minSum);

            for (int i = 0; i < size; i++)
                delete[] a[i];
            delete[] a;
        }
    };
}