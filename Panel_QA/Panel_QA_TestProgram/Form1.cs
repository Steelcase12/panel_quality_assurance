using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MYopencv;

namespace Panel_QA_TestProgram
{
    public partial class Form1 : Form
    {
        MYPanel newPanel;
        public Form1()
        {
            InitializeComponent();
        }

        private void goBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel = new MYPanel();
                newPanel.ShowImage(inputBox.Text, "My Image");
                newPanel = null;
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void redBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel = new MYPanel();
                newPanel.MaskWithColor(inputBox.Text, "red");
                warningLabel.Text = "";
                newPanel = null;
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void blueBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel = new MYPanel();
                newPanel.MaskWithColor(inputBox.Text, "blue");
                warningLabel.Text = "";
                newPanel = null;
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void panelBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel = new MYPanel();
                newPanel.MaskWithColor(inputBox.Text, "panel");
                warningLabel.Text = "";
                newPanel = null;
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void detectEdgesBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel = new MYPanel();
                newPanel.DetectEdges(inputBox.Text);
                warningLabel.Text = "";
                newPanel = null;
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void calibrateBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel = new MYPanel();
                newPanel.CalibrateCamera(inputBox.Text);
                warningLabel.Text = "";
                newPanel = null;
            } else {
                warningLabel.Text = "You must enter a path to an file";
            }
        }

        private void calibrateNoOutputBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "")
            {
                newPanel = new MYPanel();
                newPanel.CalibrateCameraNoOutput(inputBox.Text);
                warningLabel.Text = "";
                newPanel = null;
            }
            else
            {
                warningLabel.Text = "You must enter a path to an file";
            }
        }

        private void classifierBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "" && classifierBox.Text != "") {
                newPanel = new MYPanel();
                newPanel.CascadeClassify(inputBox.Text, classifierBox.Text);
                warningLabel.Text = "";
                newPanel = null;
            } else {
                warningLabel.Text = "You must enter a path to an file";
            }
        }
    }
}
