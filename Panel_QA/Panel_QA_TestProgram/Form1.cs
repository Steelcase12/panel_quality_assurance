/////////////////////////////////////////////////////////////
// File: Form.cs 
// Descripiton: 
//  This is the file which contains all of the event
//  handlers for the C# dialog Form1. The constructor
//  disallows resize and creates a new MYPanel() object.
//  The event handlers are named according to the name of
//  it's button which is set in the designer. 
//////////////////////////////////////////////////////////// 

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
            this.FormBorderStyle = FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = true;
            InitializeComponent();
            newPanel = new MYPanel();
        }

        private void goBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.ShowImage(inputBox.Text, "My Image");
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }

        private void redBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.MaskWithColor(inputBox.Text, "Red", true);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }

        private void blueBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.MaskWithColor(inputBox.Text, "Blue", true);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }

        private void panelBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.MaskWithColor(inputBox.Text, "panel", false);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }

        private void detectEdgesBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.DetectEdges(inputBox.Text, true);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }

        private void calibrateBtn_Click(object sender, EventArgs e)
        {
            if (calibrationPath.Text != "") {
                newPanel.CalibrateCamera(calibrationPath.Text);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to a file";
            }
        }

        private void calibrateNoOutputBtn_Click(object sender, EventArgs e)
        {
            if (calibrationPath.Text != "") {

                newPanel.CalibrateCameraNoOutput(calibrationPath.Text);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to a file";
            }
        }

        private void viewWithCalibrationBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.ShowImageWithCalibration(inputBox.Text, "My Image");
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }

        private void batchCalibrateBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.BatchCalibrate(inputBox.Text);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to a directory";
            }
            }

        private void featureDetectionBtn_Click(object sender, EventArgs e)
            {
            if (featureImageBox.Text != "" && featureTemplateBox.Text != "")
            {
                newPanel.DetectFeatures(featureImageBox.Text, featureTemplateBox.Text, featuresCheckBox.Checked, featureRotatedCheckBox.Checked);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to a file AND a template";
            }
        }

        private void pixelsToLengthBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "")
            {
                newPanel.PixelsToLength(inputBox.Text);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            }
            else
            {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }

        private void loadCalibrationBtn_Click(object sender, EventArgs e)
        {
            if (calibrationPath.Text != "")
            {
                newPanel.LoadCalibration(calibrationPath.Text);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            }
            else
            {
                toolStripStatusLabel1.Text = "You must enter a path to a file";
            }
        }

        private void detectTagBtn_Click(object sender, EventArgs e)
        {
            if (imagePath.Text != "")
            {
                if (radioButton1.Checked)
                {
                    newPanel.MaskWithColor(imagePath.Text, radioButton1.Text, false);
                } else if (radioButton2.Checked){
                    newPanel.MaskWithColor(imagePath.Text, radioButton2.Text, false);
                }
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            }
            else
            {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }      
    
        private void settingsBtn_Click(object sender, EventArgs e)
        {
            if (settingsInput.Text != "") {
                newPanel.ReadSettings(settingsInput.Text);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            } else {
                toolStripStatusLabel1.Text = "You must enter a path to a settings file";
            }
        }

        private void dimensionsBtn_Click(object sender, EventArgs e)
        {
            if (imagePath.Text != "")
            {
                newPanel.DetectEdges(imagePath.Text, false);
                toolStripStatusLabel1.Text = "StPaQuAs - Ready";
            }
            else
            {
                toolStripStatusLabel1.Text = "You must enter a path to an image";
            }
        }
    }
}
