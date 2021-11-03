//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		TDD testy pre matematickú knižnicu
//
// $NoKeywords: $ivs_project_2 $MathLibraryTests.cs
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2021-03-29
//============================================================================//
/**
 * @file	MathLibraryTests.cs
 * @author	Iveta Snášelová
 * 
 * @brief	Implementácia testov pre matematickú knižnicu
 */

using MathLibrary;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;


namespace CalculatorTests
{
    public static class Utils
    {
        /** \DEVIATION - Konštantná premenná kvôli určeniu rovnosti desatinných čisel */
        public const double DEVIATION = 0.000001;

        /**
		* Funkcia pre kontrolu rovnosti pri testovaní funkcie Add
		*
		* @param a Prvý sčítanec
		* @param b Druhý sčítanec
		* @param testResult Výsledok testu
		* @return Vracia false alebo true podľa rovnosti výsledku
		*/
        public static bool CompareAdd(double a, double b, double testResult)
        {
            return Math.Abs(MathematicLibrary.Add(a,b) - testResult) < DEVIATION;
        }

        /**
		* Funkcia pre kontrolu rovnosti pri testovaní funkcie Sub
		*
		* @param a Prvý menšenec
		* @param b Druhý menšiteľ
		* @param testResult Výsledok testu
		* @return Vracia false alebo true podľa rovnosti výsledku
		*/
        public static bool CompareSub(double a, double b, double testResult)
        {
            return Math.Abs(MathematicLibrary.Sub(a, b) - testResult) < DEVIATION;
        }

        /**
		* Funkcia pre kontrolu rovnosti pri testovaní funkcie Mulpitly
		*
		* @param a Prvý činiteľ
		* @param b Druhý činiteľ
		* @param testResult Výsledok testu
		* @return Vracia false alebo true podľa rovnosti výsledku
		*/
        public static bool CompareMultiply(double a, double b, double testResult)
        {
            return Math.Abs(MathematicLibrary.Multiply(a, b) - testResult) < DEVIATION;
        }

        /**
		* Funkcia pre kontrolu rovnosti pri testovaní funkcie Divide
		*
		* @param a Prvý delenec
		* @param b Druhý deliteľ
		* @param testResult Výsledok testu
		* @return Vracia false alebo true podľa rovnosti výsledku
		*/
        public static bool CompareDivide(double a, double b, double testResult)
        {
            return Math.Abs(MathematicLibrary.Divide(a, b) - testResult) < DEVIATION;
        }

        /**
		* Funkcia pre kontrolu rovnosti pri testovaní funkcie GetFactorial
		*
		* @param a Číslo
		* @param testResult Výsledok testu
		* @return Vracia false alebo true podľa rovnosti výsledku
		*/
        public static bool CompareFactorial(double a, double testResult)
        {
            return Math.Abs(MathematicLibrary.GetFactorial(a) - testResult) < DEVIATION;
        }

        /**
		* Funkcia pre kontrolu rovnosti pri testovaní funkcie Pow
		*
		* @param number Mocnenec
		* @param pow Exponent (mocniny)
		* @param testResult Výsledok testu
		* @return Vracia false alebo true podľa rovnosti výsledku
		*/
        public static bool ComparePow(double a, double b, double testResult)
        {
            return Math.Abs(MathematicLibrary.Pow(a, b) - testResult) < DEVIATION;
        }

        /**
        * Funkcia pre kontrolu rovnosti pri testovaní funkcie Sqrt
        *
        * @param number Mocnenec
        * @param number Odmocnenec
	    * @param pow Exponent (odmocniny)
        * @return Vracia false alebo true podľa rovnosti výsledku
        */
        public static bool CompareSqrt(double a, double b, double testResult)
        {
            return Math.Abs(MathematicLibrary.Sqrt(a, b) - testResult) < DEVIATION;
        }

        /**
        * Funkcia pre kontrolu rovnosti pri testovaní funkcie Logarithm
        *
        * @param number Číslo
		* @param pow Základ
	    * @param pow Exponent (odmocniny)
        * @return Vracia false alebo true podľa rovnosti výsledku
        */
        public static bool CompareLog(double a, double b, double testResult)
        {
            return Math.Abs(MathematicLibrary.Logarithm(a, b) - testResult) < DEVIATION;
        }
    }
    /**
	* Trieda pre testy matematickej knižnice
	*/
    [TestClass]
    public class MathLibraryTests
    {
        /**
		* Funkcia pre testy na sčítanie dvoch hodnôt
		*/
        [TestMethod]
        public void Add()
        {
            Assert.IsTrue(Utils.CompareAdd(10, 20, 30));
            Assert.IsTrue(Utils.CompareAdd(20, 10, 30));
            Assert.IsTrue(Utils.CompareAdd(-10, 20, 10));

            Assert.IsTrue(Utils.CompareAdd(10, -20, (-10)));
            Assert.IsTrue(Utils.CompareAdd(-10, -20, (-30)));

            Assert.IsTrue(Utils.CompareAdd(0, double.MinValue, double.MinValue));
            Assert.IsTrue(Utils.CompareAdd(0, double.MaxValue, double.MaxValue));

            Assert.IsTrue(Utils.CompareAdd(0.5, 20, 20.5));
            Assert.IsTrue(Utils.CompareAdd(10, 0.555, 10.555));

            Assert.IsTrue(Utils.CompareAdd(12.546468, 0.555, 13.101468));
            Assert.IsTrue(Utils.CompareAdd(-0.555, -12.546468, (-13.101468)));
            Assert.IsTrue(Utils.CompareAdd(12.546468, -0.555, 11.991468));
            Assert.IsTrue(Utils.CompareAdd(0.555, -12.546468, (-11.991468)));

            Assert.IsTrue(Utils.CompareAdd(10, 20, MathematicLibrary.Add(20, 10)));
            Assert.IsTrue(Utils.CompareAdd(12.546468, 0.555, MathematicLibrary.Add(0.555, 12.546468)));

        }

        /**
		* Funkcia pre testy na odčítanie dvoch hodnôt
		*/
        [TestMethod]
        public void Sub()
        {
            Assert.IsTrue(Utils.CompareSub(20, 10, 10));
            Assert.IsTrue(Utils.CompareSub(10, 20, -10));

            Assert.IsTrue(Utils.CompareSub(20, -10, 30));
            Assert.IsTrue(Utils.CompareSub(-20, 10, -30));

            Assert.IsTrue(Utils.CompareSub(double.MinValue, 0, double.MinValue));
            Assert.IsTrue(Utils.CompareSub(double.MaxValue, 0, double.MaxValue));

            Assert.IsTrue(Utils.CompareSub(20, 0.5, 19.5));
            Assert.IsTrue(Utils.CompareSub(10, 10.5, -0.5));

            Assert.IsTrue(Utils.CompareSub(12.454845, 11.4848556, 0.9699894));
            Assert.IsTrue(Utils.CompareSub(11.4848556, 12.454845, -0.9699894));
            
            Assert.IsTrue(Utils.CompareSub(20, 10, MathematicLibrary.Sub(20, 10)));
            Assert.IsTrue(Utils.CompareSub(11.4848556, 12.454845, MathematicLibrary.Sub(11.4848556, 12.454845)));
        
        }

        /**
        * Funkcia pre testy na násobenie dvoch hodnôt
        */
        [TestMethod]
        public void Multiply()
        {
            Assert.IsTrue(Utils.CompareMultiply(10, 20, 200));
            Assert.IsTrue(Utils.CompareMultiply(20, 10, 200));
            Assert.IsTrue(Utils.CompareMultiply(-10, 20, (-200)));
            Assert.IsTrue(Utils.CompareMultiply(10, -20, (-200)));
            Assert.IsTrue(Utils.CompareMultiply(-10, -20, 200));

            Assert.IsTrue(Utils.CompareMultiply(double.MaxValue, 0, 0));
            Assert.IsTrue(Utils.CompareMultiply(double.MinValue, 0, 0));
            Assert.IsTrue(Utils.CompareMultiply(double.MaxValue, 1, double.MaxValue));
            Assert.IsTrue(Utils.CompareMultiply(double.MinValue, 1, double.MinValue));

            Assert.IsTrue(Utils.CompareMultiply(0.5, 20, 10));
            Assert.IsTrue(Utils.CompareMultiply(-0.5, 20, (-10)));

            Assert.IsTrue(Utils.CompareMultiply(0.5451, 1545.44512, 842.422134912));
            Assert.IsTrue(Utils.CompareMultiply(-0.5451, -1545.44512, 842.422134912));
            Assert.IsTrue(Utils.CompareMultiply(-0.5451, 1545.44512, (-842.422134912)));

            Assert.IsTrue(Utils.CompareMultiply(10, -20, MathematicLibrary.Multiply(-10, 20)));
            Assert.IsTrue(Utils.CompareMultiply(-0.5451, 1545.44512, MathematicLibrary.Multiply(0.5451, -1545.44512)));

        }

        /**
        * Funkcia pre testy na delenie dvoch hodnôt
        */
        [TestMethod]
        public void Divide()
        {
            Assert.IsTrue(Utils.CompareDivide(20, 10, 2));
            Assert.IsTrue(Utils.CompareDivide(20, -10, (-2)));
            Assert.IsTrue(Utils.CompareDivide(-20, -10, 2));
            Assert.IsTrue(Utils.CompareDivide(10, 20, 0.5));
            Assert.IsTrue(Utils.CompareDivide(-10, 20, -0.5));
            Assert.IsTrue(Utils.CompareDivide(-10, -20, 0.5));

            Assert.IsTrue(Utils.CompareDivide(double.MaxValue, 1, double.MaxValue));
            Assert.IsTrue(Utils.CompareDivide(double.MinValue, 1, double.MinValue));

            Assert.IsTrue(Utils.CompareDivide(0.5, 20, 0.025));
            Assert.IsTrue(Utils.CompareDivide(-0.5, 20, (-0.025)));
            Assert.IsTrue(Utils.CompareDivide(20, 0.5, 40));
            Assert.IsTrue(Utils.CompareDivide(20, -0.5, (-40)));

            Assert.IsTrue(Utils.CompareDivide(0.555, 0.025, 22.2));
            Assert.IsTrue(Utils.CompareDivide(-0.555, -0.025, 22.2));
            Assert.IsTrue(Utils.CompareDivide(0.555, -0.025, (-22.2)));

            Assert.IsTrue(Utils.CompareDivide(-10, 20, MathematicLibrary.Divide(10, -20)));
            Assert.IsTrue(Utils.CompareDivide(12.4585, -11.4854, MathematicLibrary.Divide(-12.4585, 11.4854)));

        }

        /**
        * Funkcia pre testy výnimky pri výpočte delenia dvoch hodnôt
        */
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void DivideByZero()
        {
            double number = -0.25;
            for(int i = 0; i < 10; i++)
            {
                number += 0.255;
                MathematicLibrary.Divide(number, 0);
            }
        }

        /**
        * Funkcia pre testy na výpočet faktoriálu
        */
        [TestMethod]
        public void Factorial()
        {
            Assert.IsTrue(Utils.CompareFactorial(0, 1));
            Assert.IsTrue(Utils.CompareFactorial(1, 1));
            Assert.IsTrue(Utils.CompareFactorial(2, 2));
            Assert.IsTrue(Utils.CompareFactorial(10, 3628800));
            Assert.IsTrue(Utils.CompareFactorial(20, 2432902008176640000));
        }

        /**
        * Funkcia pre testy výnimky pri výpočte faktoriálu
        */
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void FactorialError()
        {
            for(int i = -10; i < 0; i++)
            {
                MathematicLibrary.GetFactorial(i);
            }

            MathematicLibrary.GetFactorial(1.4);
            MathematicLibrary.GetFactorial(2.524);
            MathematicLibrary.GetFactorial(845.01);

        }

        /**
        * Funkcia pre testy na umocňovanie
        */
        [TestMethod]
        public void Pow()
        {
            Assert.IsTrue(Utils.ComparePow(4, -2, 0.0625));
            Assert.IsTrue(Utils.ComparePow(2, 3, 8));
            Assert.IsTrue(Utils.ComparePow(3, 3, 27));
            Assert.IsTrue(Utils.ComparePow(2, -3, 0.125));
            Assert.IsTrue(Utils.ComparePow(-2, 3, (-8)));
            Assert.IsTrue(Utils.ComparePow(-3, 3, (-27)));

            Assert.IsTrue(Utils.ComparePow(Double.MaxValue, 1, Double.MaxValue));
            Assert.IsTrue(Utils.ComparePow(Double.MaxValue, 0, 1));
            Assert.IsTrue(Utils.ComparePow(Double.MinValue, 1, Double.MinValue));

            Assert.IsTrue(Utils.ComparePow(4, 0.5, 2));
            Assert.IsTrue(Utils.ComparePow(4, -0.5, 0.5));

            Assert.IsTrue(Utils.ComparePow(0.25, 0.5, 0.5));
            Assert.IsTrue(Utils.ComparePow(0.25, -0.5, 2));

        }

        /**
        * Funkcia pre testy výnimky pri umocňovanie
        */
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void PowAsSqrtLessThanZero()
        {
            double pow = 0.5;
            for(int i = -20; i < 0; i++)
            {
                pow += 1.0;
                MathematicLibrary.Pow(i, pow);
            }
        }

        /**
        * Funkcia pre testy na odmocňovanie
        */
        [TestMethod]
        public void Sqrt()
        {
            Assert.IsTrue(Utils.CompareSqrt(25, 2, 5));
            Assert.IsTrue(Utils.CompareSqrt(25, -2, 0.2));
            Assert.IsTrue(Utils.CompareSqrt(27, 3, 3));
            Assert.IsTrue(Utils.CompareSqrt(-27, 3, (-3)));

            Assert.IsTrue(Utils.CompareSqrt(0.25, 2, 0.5));
            Assert.IsTrue(Utils.CompareSqrt(0.25, -2, 2));

            Assert.IsTrue(Utils.CompareSqrt(Double.MaxValue, 1, Double.MaxValue));
            Assert.IsTrue(Utils.CompareSqrt(Double.MinValue, 1, Double.MinValue));
            Assert.IsTrue(Utils.CompareSqrt(1, Double.MaxValue, 1));
            Assert.IsTrue(Utils.CompareSqrt(1, Double.MinValue, 1));
        }

        /**
        * Funkcia pre testy výnimky pri odmocňovanie
        */
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void SqrtLessThanZero()
        {
            for(int i = -20; i < 0; i+=2)
                MathematicLibrary.Sqrt(i, i);
        }

        /**
        * Funkcia pre testy na výpočet logaritmu
        */
        [TestMethod]
        public void Logarithm()
        {
            Assert.IsTrue(Utils.CompareLog(10, 10,1));
            Assert.IsTrue(Utils.CompareLog(10, 100, 0.5));
            Assert.IsTrue(Utils.CompareLog(100, 10, 2));

            Assert.IsTrue(Utils.CompareLog(10, 0.1, (-1)));
            Assert.IsTrue(Utils.CompareLog(0.1, 10, (-1)));

        }

        /**
        * Funkcie pre testy výnimky pri výpočte logaritmu
        */
        [TestMethod]
        [ExpectedException(typeof(ArgumentException))]
        public void LogZeroAndLess()
        {
            MathematicLibrary.Logarithm(10, 1);
            for (int i = -20; i <= 0; i++)
            {
                MathematicLibrary.Logarithm(i, 10);
                MathematicLibrary.Logarithm(10, i-1);
            }
        }
    }
}
/*** Koniec súboru MathLibraryTests.cs ***/