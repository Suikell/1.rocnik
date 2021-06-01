//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		Ovládanie kalkulačky
//
// $NoKeywords: $ivs_project_2 $GUI.cs
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Author:     Karolína Radačovská <xradac00@stud.fit.vutbr.cz>
// $Date:       $2021-04-09
//============================================================================//
/**
 * @file	GUI.cs
 * @author	Iveta Snášelová
 * @author  Karolína Radačovská
 * 
 * @brief	Ovládanie kalkulačky
 */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StarCalculator
{   
    /**
	* Trieda pre ovládanie komponentov kalkulačky
	*/
    public partial class GUI : Form
    {
        static bool move_form = false;
        static bool is_result = false;
        static bool star_falling = false;
        /**
        * Pomocná funkcia pre zmazanie obsahu textboxu po zobrazení výsledku
        */
        public void test_result()
        {
            if (is_result)
            {
                screen.Text = "";
                is_result = false;
            }
        }

        /**
        * Funkcia pre ošetrovanie chybných stavov pri operátoroch
        */
        public void error_handling()
        {
            star_falling = true;
            screen.Text = "MATH ERROR";
        }

        /**
        * Funkcie pre povolenie dôležitých vlastností komponentov
        */
        public GUI()
        {
            InitializeComponent();
            KeyPreview = true;
            btn_hint.Focus();
            log_man.Visible = false;
            sqrt_man.Visible = false;
        }

        /**
        * Funkcia zaisťuje, že hviezdy padajú v pozadí
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void Form1_Load(object sender, EventArgs e)
        {
            falling_star.SendToBack();
            star_1.SendToBack();
            star_2.SendToBack();
            star_3.SendToBack();
            star_4.SendToBack();
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 0 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_0(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '0';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 1 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_1(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '1';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 2 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_2(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '2';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 3 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_3(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '3';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 4 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_4(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '4';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 5 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_5(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '5';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 6 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_6(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '6';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 7 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_7(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '7';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 8 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_8(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '8';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla 9 z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_9(object sender, EventArgs e)
        {
            test_result();
            screen.Text += '9';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla + z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_plus(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "" || screen.Text.Last() == '-') { }
            else if (screen.Text.Last() != '+' && char.IsDigit(screen.Text.Last()))
                screen.Text += '+';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla y√x z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_sqrt(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "") { }
            else if (screen.Text.Last() != '√' && char.IsDigit(screen.Text.Last()))
                screen.Text += '√';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla . z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_decimal_point(object sender, EventArgs e)
        {
            test_result();
            if (screen.Text == "") { }
            else if (screen.Text.Last() != '.' && char.IsDigit(screen.Text.Last()))
                screen.Text += '.';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla = z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_equal(object sender, EventArgs e)
        {
            is_result = false;
            int error_code = 0;
            string expression = screen.Text;
            string text = OperatorPriority.Priority(expression, ref error_code).ToString();
            if (error_code != 0)
                error_handling();
            else
                screen.Text = text;
            is_result = true;
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla / z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_divide(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "") { }
            else if (screen.Text.Last() != '/' && char.IsDigit(screen.Text.Last()))
                screen.Text += '/';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla * z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_multiply(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "") { }
            else if (screen.Text.Last() != '*' && char.IsDigit(screen.Text.Last()))
                screen.Text += '*';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla - z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_minus(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "")
            {
                screen.Text += '-';
                return;
            }
            char ch = screen.Text.Last();
            if (ch == '+')
            {
                btn_DEL(this, e);
                screen.Text += '-';
            }
            else if (ch == '-')
            {
                btn_DEL(this, e);
                screen.Text += '+';
            }
            else
                screen.Text += '-';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla x^y z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_power(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "") { }
            else if (screen.Text.Last() != '^' && char.IsDigit(screen.Text.Last()))
                screen.Text += '^';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla x! z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_factorial(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "") { }
            else if (screen.Text.Last() != '!' && char.IsDigit(screen.Text.Last()))
                screen.Text += '!';
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla a log x z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_log(object sender, EventArgs e)
        {
            is_result = false;
            if (screen.Text == "") { }
            else if (screen.Text.Last() != 'g' && char.IsDigit(screen.Text.Last()))
                screen.Text += "log";
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla CE z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_CE(object sender, EventArgs e)
        {
            screen.Text = "";
        }

        /**
        * Funkcia slúži pre ovládanie tlačidla DEL z kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_DEL(object sender, EventArgs e)
        {
            if(screen.Text == "") { }
            else if (screen.Text.Last() == 'g')
                screen.Text = screen.Text.Substring(0, screen.Text.Length - 3);
            else
                screen.Text = screen.Text.Substring(0, screen.Text.Length - 1);
        }

        /**
        * Funkcia slúži pre ovládanie tlačidel z klávesnice
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param e Inštancia triedy, špeciálna pre ovladanie klávesnice. Obsahuje parametre, ktoré majú byť události pridané.
        */
        private void form_keyboard(object sender, KeyPressEventArgs e)
        {
            // Podmienka pre výpis jediného čísla po stlačení klávesy
            if (screen.Focused == true)
                return;

            // Podmienky pre ošetrenie hodnôt z klávesnice
            if (e.KeyChar == '=')
                btn_equal(sender, e);
            else if (e.KeyChar == 8) // backspace je reprezentovaný ako 8
                btn_DEL(sender, e);
            else if (e.KeyChar >= '0' && e.KeyChar <= '9')
            {
                test_result();
                screen.Text += e.KeyChar;
            }
            else
            {
                // Volanie rozličných metód na základe vybraného vstupu z klávesnice
                switch (e.KeyChar)
                {
                    case '+': btn_plus(this, new EventArgs()); break;
                    case '-': btn_minus(this, new EventArgs()); break;
                    case '/': btn_divide(this, new EventArgs()); break;
                    case '*': btn_multiply(this, new EventArgs()); break;
                    case '^': btn_power(this, new EventArgs()); break;
                    case '!': btn_factorial(this, new EventArgs()); break;
                    case '√': btn_sqrt(this, new EventArgs()); break;
                    case '.': btn_decimal_point(this, new EventArgs()); break;
                    case 'l': btn_log(this, new EventArgs()); break;
                    default: MessageBox.Show("Stlačená neplatná klávesa."); break;
                }
            }
        }

        /**
        * Funkcia prepisuje defaultnú implementáciu šípok a klávesy enter
        *
        * @param msg Správa preávaná odkazom, ktorá predstavuje okno so správou k spracovaniu
        * @param keyData Výraz typu Keys, ktorý reprezentuje kľúč procesu
        */
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            /// podmienka pre neakceptovanie šípok ako vstupy z klávesnice
            if (keyData == Keys.Left || keyData == Keys.Right || keyData == Keys.Up || keyData == Keys.Down)
            {
                MessageBox.Show("Stlačená neplatná klávesa!");
                return true;
            }
            /// podmienka pre vyhodnotenie klávesy enter ako rovná sa
            if (keyData == Keys.Enter)
            {
                btn_equal(this, new EventArgs());
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        /**
        * Funkcia pre zobrazenie rychlej nápovedy pri tlačidle a log x
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void log_enter(object sender, EventArgs e)
        {
            log_man.Visible = true;
        }

        /**
        * Funkcia pre skrytie rychlej nápovedy pri tlačidle a log x
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void log_leave(object sender, EventArgs e)
        {
            log_man.Visible = false;
        }

        /**
        * Funkcia pre zobrazenie rychlej nápovedy pri tlačidle y√x
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void sqrt_enter(object sender, EventArgs e)
        {
            sqrt_man.Visible = true;
        }

        /**
        * Funkcia pre skrytie rychlej nápovedy pri tlačidle y√x
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void sqrt_leave(object sender, EventArgs e)
        {
            sqrt_man.Visible = false;
        }

        /**
        * Funkcia slúži pre uzatvorenie okna aplikacie kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /**
        * Funkcia pre minimalizáciu kalkulačky
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_minimize_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        /**
        * Funkcie pre možnost posunutia kalkulačky po ploche obrazovky.
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param e Inštancia triedy, špeciálna pre ovladanie myši. Obsahuje parametre, ktoré majú byť události pridané.
        */
        static Point cursor_position;
        static Point form_position;
        private void form_take(object sender, MouseEventArgs e)
        {
            move_form = true;
            cursor_position = Cursor.Position;
            form_position = this.Location;
        }

        private void form_move(object sender, MouseEventArgs e)
        {
            if (move_form)
            {
                Point new_ = Point.Subtract(Cursor.Position, new Size(cursor_position));
                this.Location = Point.Add(form_position, new Size(new_));
            }
        }
        private void form_let(object sender, MouseEventArgs e)
        {
            move_form = false;
        }
        /**
         * Konec funkcií pre posunutie kalkulačky
         */


        /**
        * Funkcia zaisťuje padanie hviezd pri matematickej chybe
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void timer1_Tick(object sender, EventArgs e)
        {

            if (star_falling)
            {
                falling_star.Top += 5;
                star_1.Top += 5;
                star_2.Top += 5;
                star_3.Top += 5;
                star_4.Top += 5;
            }

            if (falling_star.Top > this.Bottom)
            {
                falling_star.Top = 145;
                star_1.Top = 2;
                star_2.Top = 12;
                star_3.Top = 140;
                star_4.Top = 130;
                star_falling = false;
            }
            Refresh();
        }

        /**
        * Funkcia pre zobrazenie nápovedy
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_hint_Click(object sender, EventArgs e)
        {
            Help hint_f = new Help();
            hint_f.ShowDialog();
        }
    }
}

/*** Koniec súboru GUI.cs ***/
