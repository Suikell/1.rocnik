//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		Matematická knižnica
//
// $NoKeywords: $ivs_project_2 $MathematicLibrary.cs
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2021-03-29
//============================================================================//
/**
 * @file	MathematicLibrary.cs
 * @author	Iveta Snášelová
 * 
 * @brief	Implementácie matematických operácií
 */

using System;

namespace MathLibrary
{
	/**
	* Trieda pre implementáciu matematickej knižnice
	*/
	public static class MathematicLibrary
	{
		/**
		* Funkcia pre sčítanie dvoch hodnôt
		*
		* @param number1 Prvý sčítanec
		* @param number2 Druhý sčítanec
		* @return Vracia súčet dvoch čísel
		*/
		public static double Add(double number1, double number2)
		{
			return number1 + number2;
		}

		/**
		* Funkcia pre rozdiel dvoch hodnôt
		*
		* @param number1 Menšenec
		* @param number2 Menšiteľ
		* @return Vracia rozdiel dvoch čísel
		*/
		public static double Sub(double number1, double number2)
		{
			return number1 - number2;
		}

		/**
		* Funkcia pre násobenie dvoch hodnôt
		*
		* @param number1 Prvý činiteľ
		* @param number2 Druhý činiteľ
		* @return Vracia súčin dvoch čísel
		*/
		public static double Multiply(double number1, double number2)
		{
			return number1 * number2;
		}

		/**
		* Funkcia pre delenie dvoch hodnôt
		*
		* @throws Výnimka pre delenie nulou
		*
		* @param toDivide Delenec
		* @param dividedBy Deliteľ
		* @return Vracia podiel dvoch čísel
		*/
		public static double Divide(double toDivide, double dividedBy)
		{
			if (dividedBy == 0)
				throw new ArgumentException("Nulou sa nedá deliť!");
			else
				return toDivide / dividedBy;
		}

		/**
		* Funkcia pre výpočet faktoriálu
		*
		* @throws Výnimka pre číslo <0
		*
		* @param number Číslo
		* @return Vracia n faktoriál zadaného čísla
		*/
		public static double GetFactorial(double number)
		{
			Console.WriteLine("{0}", number);
			if (number < 0)
				throw new ArgumentException("Faktoriál nemôže byt <0!");
			else if (number % 1 != 0)
				throw new ArgumentException("Faktoriál je možné vypočítať len z kladného celého čísla!");
			else
			{
				if (number == 1 || number == 0)
					return 1;
				else
					return number * GetFactorial(number - 1);
			}
		}

		/**
		* Funkcia pre umocňovanie
		*
		* @throws Výnimka pre číslo <0 pod odmocninou
		*
		* @param number Mocnenec
		* @param pow Exponent (mocniny)
		* @return Vracia n-tou mocninu čísla
		*/
		public static double Pow(double number, double pow)
		{
			if (number < 0 && (pow % 1 != 0))
				throw new ArgumentException("Argument odmocniny nemôže byť <0!");
			else
				return Math.Pow(number, pow);
		}

		/**
		* Funkcia pre odmocňovanie
		*
		* @throws Výnimka pre číslo <0 pod párnou odmocninou
		*
		* @param number Odmocnenec
		* @param pow Exponent (odmocniny)
		* @return Vracia n-tou odmocninu čísla
		*/
		public static double Sqrt(double number, double root)
        {
			if (number < 0 && (root % 2 == 0))
				throw new ArgumentException("Argument odmocniny nemôže byť <0!");
			else
            {
				if (number >= 0)
					return Math.Pow(number, 1.0 / root);
				else
					return -Math.Pow(-number, 1.0 / root);
            }
        }

		/**
		* Funkcia pre výpočet logaritmu
		*
		* @throws Výnimka pre základ <0 alebo =1 alebo argument <0
		*
		* @param number Číslo
		* @param pow Základ
		* @return Vracia n-tý logaritmus čísla
		*/
		public static double Logarithm(double number, double baseNumber)
		{
			if (baseNumber < 0 || baseNumber == 1 || number <= 0)
				throw new ArgumentException("Nesprávne parametre odmocniny!");
			else
				return (Math.Log(number, baseNumber));
		}
	}
}

/*** Koniec súboru MathematicLibrary.cs ***/