//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		Profilovanie chodu programu
//
// $NoKeywords: $ivs_project_2 $StandardDeviaton.cs
// $Author:     Karolína Radačovská <xradac00@stud.fit.vutbr.cz>
// $Date:       $2021-04-25
//============================================================================//
/**
 * @file	StandardDeviation.cs
 * @author  Karolína Radačovská
 * 
 * @brief	Profilovanie chodu programu
 */

using System;
using System.Globalization;
using System.Collections.Generic;
using MathLibrary;
using System.Threading;
//using System.Diagnostics;

namespace stddev
{
    /**
     *  Trieda pre implemetáciu profilovania časovej zložitosti programu
     */
    class StandardDeviation
    {
        static int Main(string[] args)
        {
             
            // Implementácie súvisia s nastavením desatinnej čiarky  
            NumberStyles style = NumberStyles.Number;
            CultureInfo culture = CultureInfo.CreateSpecificCulture("en-US");


            /**
             *  Implementácia slúži pre načítanie štandardného vstupu a spracovanie čísel v súbore 
             */

            List<double> values = new List<double>();
            
            // podmienka pre prípad chýbajúceho súboru na stdin 
            if (!Console.IsInputRedirected)
            {
                Console.WriteLine("As input is required list of values from stdin.");
                return 1;
            }

            char[] delim_chars = { ' ', '\t', '\n' }; // oddeľovače čísel
            String string_line; // načítaný súbor sa vloží do stringu
            do
            {
                string_line = Console.ReadLine(); // načítanie vstupu

                // podmienka pre prázdny súbor
                if (string_line == null)
                    continue;

                // parsovanie načítaného súboru na slová podľa oddeľovačov
                string[] words = string_line.Split(delim_chars);
                foreach (var word in words) // prechádzanie číslami v stringu, pridávanie do listu
                {
                    double number;
                    Double.TryParse(word, style, culture, out number);
                    values.Add(number);
                }

            } while (string_line != null); // prechádzanie načítaným stringom


            /**
             *  Implementácia pre výpočet vzorca výberovej smerodajnej odchýlky  
             */

            double sum = 0;
            foreach (var num in values)
            {
                sum = MathematicLibrary.Add(sum, num);
            }
            double count = values.Count;
            double x_stripe = MathematicLibrary.Divide(sum, count);

            sum = 0;
            foreach (var num in values)
            {
                sum += MathematicLibrary.Multiply(num, num);
            }

            double part_a = MathematicLibrary.Multiply(count, MathematicLibrary.Multiply(x_stripe, x_stripe));
            double part_b = MathematicLibrary.Sub(sum, part_a);
            double before_sqrt = MathematicLibrary.Divide(part_b, MathematicLibrary.Sub(count, 1));
            double after_sqrt = MathematicLibrary.Sqrt(before_sqrt, 2);
            
            Console.WriteLine("{0}", after_sqrt);
            Thread.Sleep(10000);

            return 0;
        }
    }
}

/*** Koniec súboru StandardDeviation.cs ***/
