/////////////////////////////////////////////////////////////
// File: Program.cs 
// Descripiton: 
//  This is the entry point for the C# project. It starts
//  the application by creating an instance of Form1().
//  See Form1.cs for more details.
//////////////////////////////////////////////////////////// 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Panel_QA_TestProgram
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
