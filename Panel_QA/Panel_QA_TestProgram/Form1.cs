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
            newPanel = new MYPanel();
        }

        private void goBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.ShowImage(inputBox.Text, "My Image");
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void redBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.MaskWithColor(inputBox.Text, "red");
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void blueBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.MaskWithColor(inputBox.Text, "blue");
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void panelBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.MaskWithColor(inputBox.Text, "panel");
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void detectEdgesBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.DetectEdges(inputBox.Text);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void calibrateBtn_Click(object sender, EventArgs e)
        {
            if (calibrationPath.Text != "") {
                newPanel.CalibrateCamera(calibrationPath.Text);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to a file";
            }
        }

        private void calibrateNoOutputBtn_Click(object sender, EventArgs e)
        {
            if (calibrationPath.Text != "") {

                newPanel.CalibrateCameraNoOutput(calibrationPath.Text);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to a file";
            }
        }

        private void classifierBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "" && classifierBox.Text != "") {
                newPanel.CascadeClassify(inputBox.Text, classifierBox.Text);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to a file";
            }
        }

        private void viewWithCalibrationBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.ShowImageWithCalibration(inputBox.Text, "My Image");
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void calibrateFisheyeNoOutputBtn_Click(object sender, EventArgs e)
        {
            if (calibrationPath.Text != "") {
                newPanel.CalibrateCameraFisheyeNoOutput(calibrationPath.Text);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to a file";
            }
        }

        private void drawOnBoardBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.DrawOnBoard(inputBox.Text);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void batchCalibrateBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.BatchCalibrate(inputBox.Text);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to a directory";
            }
            }

        private void featureDetectionBtn_Click(object sender, EventArgs e)
            {
            if (inputBox.Text != "" && featureTemplateBox.Text != "") {
                newPanel.DetectFeatures(inputBox.Text, featureTemplateBox.Text, featuresCheckBox.Checked);
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to a file AND a template";
            }
        }

        private void perspectiveBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "") {
                newPanel.Perspective(inputBox.Text, comboBox1.SelectedItem.ToString());
                warningLabel.Text = "";
            } else {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

        private void rectificationBtn_Click(object sender, EventArgs e)
        {
            if (inputBox.Text != "")
            {
                newPanel.Rectification(inputBox.Text, comboBox1.SelectedItem.ToString());
                warningLabel.Text = "";
            }
            else
            {
                warningLabel.Text = "You must enter a path to an image";
            }
        }

    }
}
