//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Účel:		Nápoveda
//
// $NoKeywords: $ivs_project_2 $Help.cs
// $Author:     Iveta Snášelová <xsnase07@stud.fit.vutbr.cz>
// $Date:       $2021-04-18
//============================================================================//
/**
 * @file	Help.cs
 * @author	Iveta Snášelová
 * 
 * @brief	Ovládanie Nápovedy
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
	* Trieda pre ovládanie komponentov nápovedy
	*/
    public partial class Help : Form
    {
        static bool move_form = false;

        /**
        * Funkcie pre povolenie dôležitých vlastností komponentov
        */
        public Help()
        {
            InitializeComponent();

            panel1.AutoScroll = false;
            panel1.HorizontalScroll.Enabled = false;
            panel1.HorizontalScroll.Visible = false;
            panel1.HorizontalScroll.Maximum = 0;
            panel1.AutoScroll = true;
        }

        /**
        * Funkcia pre uzatvorenie okna nápovedy
        *
        * @param sender Posiela požiadavku na spracovanie danej akcie
        * @param Inštancia triedy, obsahuje parametre, ktoré majú byť události pridané.
        */
        private void btn_close_Click(object sender, EventArgs e)
        {
            this.Close();
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
    }
}
