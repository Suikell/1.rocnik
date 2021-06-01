//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		Matematická knižnica
//
// $NoKeywords: $ivs_project_2 $MathematicLibrary.cs
// $Author:     Pavol Cubinek <xcubin00@stud.fit.vutbr.cz>
// $Date:       $2021-04-10
//============================================================================//
/**
 * @file	PrioritySolver.cs
 * @author	Pavol Cubinek
 * 
 * @brief	Implementácia Priority Solveru
 */

using System;

namespace StarCalculator
{
	public static class OperatorPriority
	{
		/**
		* Funkcia pre spracovanie vstupneho stringu
		*
		* @param inputString Vstupný string
		* @return Vracia výsledok
		*/
		public static double Priority(string input, ref int error_code)
		{
			int left, right;
			double leftOp, rightOp;
			// definícia poradia priority operatorov
			char[] op1 = { '!' };
			char[] op2 = { '*', '/' };
			char[] op3 = { '^', '√', 'l' };
			char[] op4 = { '+', '-' };
			char[][] signPool = { op1, op2, op3, op4 };
			string[] minusCompinations = { "+-", "*-", "/-" };
			string calculated;
			input = input.Replace("log", "l");
			// hľadanie operátorov z jednotlivých skupín operátorov
			for (int j = 0; j < 4; j++)
			{
				// prechod stringom a vyhľadávanie operátorov z danej skupiny
				for (int i = input.Substring(1).IndexOfAny(signPool[j]); i != -1; i = input.Substring(1).IndexOfAny(signPool[j]))
				{
					i++;
					char currentSign = input[i]; // aktuálny operátor
					for (left = i - 1; left > -1 && (char.IsDigit(input[left]) || input[left] == '.' || Array.Exists(minusCompinations, element => element == input.Substring(left, 2)) || (input[left] == '-' && left == 0)); left--) { };
					left++; // zistenie dĺžky ľavého operátora
					for (right = i + 1; right < input.Length && (char.IsDigit(input[right]) || input[right] == '.' || input[i + 1] == '-'); right++) { };
					right--; // zistenie dĺžky pravého operátora
					leftOp = i - left != 0 ? Convert.ToDouble(input.Substring(left, i - left)) : 0; // nastavenie ľavého operátora
					rightOp = currentSign != '!' ? right - i != 0 ? Convert.ToDouble(input.Substring(i + 1, right - i)) : 0 : 0;
					// nastavenie pravého operátora pre binárne operácie
					switch (currentSign) //riešenie operátora
					{
						case '*':
							calculated = Convert.ToString(MathematicLibrary.Multiply(leftOp, rightOp));
							break;
						case '/':
							calculated = Convert.ToString(MathematicLibrary.Divide(leftOp, rightOp, ref error_code));
							break;
						case '+':
							calculated = Convert.ToString(MathematicLibrary.Add(leftOp, rightOp));
							break;
						case '-':
							calculated = Convert.ToString(MathematicLibrary.Sub(leftOp, rightOp));
							break;
						case '!':
							calculated = Convert.ToString(MathematicLibrary.GetFactorial(leftOp, ref error_code));
							break;
						case '^':
							calculated = Convert.ToString(MathematicLibrary.Pow(leftOp, rightOp, ref error_code));
							break;
						case '√':
							calculated = Convert.ToString(MathematicLibrary.Sqrt(rightOp, leftOp, ref error_code));
							break;
						case 'l':
							calculated = Convert.ToString(MathematicLibrary.Logarithm(rightOp, leftOp, ref error_code));
							break;
						default:
							return (error_code = 7);
					}
					if (error_code != 0) //ukončenie kalkulácie v prípade chyby
						return 1;
					// nahradenie operátora vypočítanou hodnotou
					input = input.Replace(input.Substring(left, right - left + 1), calculated);
				}
			}
			// návrat výslednej hodnoty
			return Convert.ToDouble(input);
		}
	}
}

/*** Koniec súboru OperatorPriority.cs ***/
