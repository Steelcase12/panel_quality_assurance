using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Panels;

namespace Panel_QA_TestProgram
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void goBtn_Click(object sender, EventArgs e)
        {
            Panels.Panel newPanel = new Panels.Panel();
            newPanel.ShowMessage(inputBox.Text);
            newPanel = null;
        }
    }
}
