﻿namespace Panel_QA_TestProgram
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.blueBtn = new System.Windows.Forms.Button();
            this.redBtn = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.warningLabel = new System.Windows.Forms.Label();
            this.panelBtn = new System.Windows.Forms.Button();
            this.detectEdgesBtn = new System.Windows.Forms.Button();
            this.inputBox = new System.Windows.Forms.TextBox();
            this.viewWithCalibrationBtn = new System.Windows.Forms.Button();
            this.goBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.batchCalibrateBtn = new System.Windows.Forms.Button();
            this.pixelsToLengthBtn = new System.Windows.Forms.Button();
            this.calibrateBtn = new System.Windows.Forms.Button();
            this.loadCalibrationBtn = new System.Windows.Forms.Button();
            this.featuresCheckBox = new System.Windows.Forms.CheckBox();
            this.featureDetectionBtn = new System.Windows.Forms.Button();
            this.featureTemplateLabel = new System.Windows.Forms.Label();
            this.featureTemplateBox = new System.Windows.Forms.TextBox();
            this.calibrationPath = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.calibrateNoOutputBtn = new System.Windows.Forms.Button();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.label3 = new System.Windows.Forms.Label();
            this.imagePath = new System.Windows.Forms.TextBox();
            this.colorGroupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.detectTagBtn = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.label3 = new System.Windows.Forms.Label();
            this.settingsInput = new System.Windows.Forms.TextBox();
            this.settingsBtn = new System.Windows.Forms.Button();
            this.tabPage2.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.colorGroupBox1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.blueBtn);
            this.tabPage2.Controls.Add(this.redBtn);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Controls.Add(this.settingsBtn);
            this.tabPage2.Controls.Add(this.settingsInput);
            this.tabPage2.Controls.Add(this.label3);
            this.tabPage2.Controls.Add(this.warningLabel);
            this.tabPage2.Controls.Add(this.panelBtn);
            this.tabPage2.Controls.Add(this.detectEdgesBtn);
            this.tabPage2.Controls.Add(this.inputBox);
            this.tabPage2.Controls.Add(this.viewWithCalibrationBtn);
            this.tabPage2.Controls.Add(this.goBtn);
            this.tabPage2.Controls.Add(this.label1);
            this.tabPage2.Controls.Add(this.batchCalibrateBtn);
            this.tabPage2.Controls.Add(this.pixelsToLengthBtn);
            this.tabPage2.Controls.Add(this.calibrateBtn);
            this.tabPage2.Controls.Add(this.loadCalibrationBtn);
            this.tabPage2.Controls.Add(this.featuresCheckBox);
            this.tabPage2.Controls.Add(this.featureDetectionBtn);
            this.tabPage2.Controls.Add(this.featureTemplateLabel);
            this.tabPage2.Controls.Add(this.featureTemplateBox);
            this.tabPage2.Controls.Add(this.calibrationPath);
            this.tabPage2.Controls.Add(this.label4);
            this.tabPage2.Controls.Add(this.calibrateNoOutputBtn);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(648, 318);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Settings";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // blueBtn
            // 
            this.blueBtn.Location = new System.Drawing.Point(192, 131);
            this.blueBtn.Name = "blueBtn";
            this.blueBtn.Size = new System.Drawing.Size(75, 23);
            this.blueBtn.TabIndex = 69;
            this.blueBtn.Text = "Blue";
            this.blueBtn.UseVisualStyleBackColor = true;
            this.blueBtn.Click += new System.EventHandler(this.blueBtn_Click);
            // 
            // redBtn
            // 
            this.redBtn.Location = new System.Drawing.Point(111, 131);
            this.redBtn.Name = "redBtn";
            this.redBtn.Size = new System.Drawing.Size(75, 23);
            this.redBtn.TabIndex = 68;
            this.redBtn.Text = "Red";
            this.redBtn.UseVisualStyleBackColor = true;
            this.redBtn.Click += new System.EventHandler(this.redBtn_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 131);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 13);
            this.label2.TabIndex = 67;
            this.label2.Text = "Detect Color:";
            // 
            // warningLabel
            // 
            this.warningLabel.AutoSize = true;
            this.warningLabel.Location = new System.Drawing.Point(286, 220);
            this.warningLabel.Name = "warningLabel";
            this.warningLabel.Size = new System.Drawing.Size(56, 13);
            this.warningLabel.TabIndex = 66;
            this.warningLabel.Text = "StPaQuAs";
            // 
            // panelBtn
            // 
            this.panelBtn.Location = new System.Drawing.Point(273, 131);
            this.panelBtn.Name = "panelBtn";
            this.panelBtn.Size = new System.Drawing.Size(102, 23);
            this.panelBtn.TabIndex = 65;
            this.panelBtn.Text = "Panel";
            this.panelBtn.UseVisualStyleBackColor = true;
            this.panelBtn.Click += new System.EventHandler(this.panelBtn_Click);
            // 
            // detectEdgesBtn
            // 
            this.detectEdgesBtn.Location = new System.Drawing.Point(509, 126);
            this.detectEdgesBtn.Name = "detectEdgesBtn";
            this.detectEdgesBtn.Size = new System.Drawing.Size(118, 23);
            this.detectEdgesBtn.TabIndex = 64;
            this.detectEdgesBtn.Text = "Canny Edges";
            this.detectEdgesBtn.UseVisualStyleBackColor = true;
            this.detectEdgesBtn.Click += new System.EventHandler(this.detectEdgesBtn_Click);
            // 
            // inputBox
            // 
            this.inputBox.Location = new System.Drawing.Point(111, 90);
            this.inputBox.Name = "inputBox";
            this.inputBox.Size = new System.Drawing.Size(281, 20);
            this.inputBox.TabIndex = 60;
            // 
            // viewWithCalibrationBtn
            // 
            this.viewWithCalibrationBtn.Location = new System.Drawing.Point(509, 87);
            this.viewWithCalibrationBtn.Name = "viewWithCalibrationBtn";
            this.viewWithCalibrationBtn.Size = new System.Drawing.Size(118, 23);
            this.viewWithCalibrationBtn.TabIndex = 63;
            this.viewWithCalibrationBtn.Text = "View With Calibration";
            this.viewWithCalibrationBtn.UseVisualStyleBackColor = true;
            this.viewWithCalibrationBtn.Click += new System.EventHandler(this.viewWithCalibrationBtn_Click);
            // 
            // goBtn
            // 
            this.goBtn.Location = new System.Drawing.Point(401, 87);
            this.goBtn.Name = "goBtn";
            this.goBtn.Size = new System.Drawing.Size(105, 23);
            this.goBtn.TabIndex = 62;
            this.goBtn.Text = "Show Image";
            this.goBtn.UseVisualStyleBackColor = true;
            this.goBtn.Click += new System.EventHandler(this.goBtn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 101);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 13);
            this.label1.TabIndex = 61;
            this.label1.Text = "Image Path:";
            // 
            // batchCalibrateBtn
            // 
            this.batchCalibrateBtn.Location = new System.Drawing.Point(509, 45);
            this.batchCalibrateBtn.Name = "batchCalibrateBtn";
            this.batchCalibrateBtn.Size = new System.Drawing.Size(118, 27);
            this.batchCalibrateBtn.TabIndex = 59;
            this.batchCalibrateBtn.Text = "Batch Calibrate";
            this.batchCalibrateBtn.UseVisualStyleBackColor = true;
            this.batchCalibrateBtn.Click += new System.EventHandler(this.batchCalibrateBtn_Click);
            // 
            // pixelsToLengthBtn
            // 
            this.pixelsToLengthBtn.Location = new System.Drawing.Point(401, 125);
            this.pixelsToLengthBtn.Name = "pixelsToLengthBtn";
            this.pixelsToLengthBtn.Size = new System.Drawing.Size(105, 23);
            this.pixelsToLengthBtn.TabIndex = 56;
            this.pixelsToLengthBtn.Text = "Pixels to Length";
            this.pixelsToLengthBtn.UseVisualStyleBackColor = true;
            this.pixelsToLengthBtn.Click += new System.EventHandler(this.pixelsToLengthBtn_Click);
            // 
            // calibrateBtn
            // 
            this.calibrateBtn.Location = new System.Drawing.Point(399, 19);
            this.calibrateBtn.Name = "calibrateBtn";
            this.calibrateBtn.Size = new System.Drawing.Size(107, 23);
            this.calibrateBtn.TabIndex = 50;
            this.calibrateBtn.Text = "Calibrate";
            this.calibrateBtn.UseVisualStyleBackColor = true;
            this.calibrateBtn.Click += new System.EventHandler(this.calibrateBtn_Click);
            // 
            // loadCalibrationBtn
            // 
            this.loadCalibrationBtn.Location = new System.Drawing.Point(401, 45);
            this.loadCalibrationBtn.Name = "loadCalibrationBtn";
            this.loadCalibrationBtn.Size = new System.Drawing.Size(105, 27);
            this.loadCalibrationBtn.TabIndex = 55;
            this.loadCalibrationBtn.Text = "Load Calibration";
            this.loadCalibrationBtn.UseVisualStyleBackColor = true;
            this.loadCalibrationBtn.Click += new System.EventHandler(this.loadCalibrationBtn_Click);
            // 
            // featuresCheckBox
            // 
            this.featuresCheckBox.AutoSize = true;
            this.featuresCheckBox.Location = new System.Drawing.Point(402, 187);
            this.featuresCheckBox.Name = "featuresCheckBox";
            this.featuresCheckBox.Size = new System.Drawing.Size(128, 17);
            this.featuresCheckBox.TabIndex = 54;
            this.featuresCheckBox.Text = "Part Exceeds Feature";
            this.featuresCheckBox.UseVisualStyleBackColor = true;
            // 
            // featureDetectionBtn
            // 
            this.featureDetectionBtn.Location = new System.Drawing.Point(532, 184);
            this.featureDetectionBtn.Name = "featureDetectionBtn";
            this.featureDetectionBtn.Size = new System.Drawing.Size(98, 23);
            this.featureDetectionBtn.TabIndex = 53;
            this.featureDetectionBtn.Text = "Detect Features";
            this.featureDetectionBtn.UseVisualStyleBackColor = true;
            this.featureDetectionBtn.Click += new System.EventHandler(this.featureDetectionBtn_Click);
            // 
            // featureTemplateLabel
            // 
            this.featureTemplateLabel.AutoSize = true;
            this.featureTemplateLabel.Location = new System.Drawing.Point(6, 189);
            this.featureTemplateLabel.Name = "featureTemplateLabel";
            this.featureTemplateLabel.Size = new System.Drawing.Size(93, 13);
            this.featureTemplateLabel.TabIndex = 52;
            this.featureTemplateLabel.Text = "Feature Template:";
            // 
            // featureTemplateBox
            // 
            this.featureTemplateBox.Location = new System.Drawing.Point(114, 186);
            this.featureTemplateBox.Name = "featureTemplateBox";
            this.featureTemplateBox.Size = new System.Drawing.Size(281, 20);
            this.featureTemplateBox.TabIndex = 51;
            this.featureTemplateBox.Text = "C:\\CPE 495 496\\panel_quality_assurance\\resources\\Glue_Booth\\qr_steelcase.png";
            // 
            // calibrationPath
            // 
            this.calibrationPath.Location = new System.Drawing.Point(111, 19);
            this.calibrationPath.Name = "calibrationPath";
            this.calibrationPath.Size = new System.Drawing.Size(281, 20);
            this.calibrationPath.TabIndex = 49;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 19);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(84, 13);
            this.label4.TabIndex = 48;
            this.label4.Text = "Calibration Path:";
            // 
            // calibrateNoOutputBtn
            // 
            this.calibrateNoOutputBtn.Location = new System.Drawing.Point(509, 19);
            this.calibrateNoOutputBtn.Name = "calibrateNoOutputBtn";
            this.calibrateNoOutputBtn.Size = new System.Drawing.Size(118, 23);
            this.calibrateNoOutputBtn.TabIndex = 47;
            this.calibrateNoOutputBtn.Text = "Calibrate No Output";
            this.calibrateNoOutputBtn.UseVisualStyleBackColor = true;
            this.calibrateNoOutputBtn.Click += new System.EventHandler(this.calibrateNoOutputBtn_Click);
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.imagePath);
            this.tabPage1.Controls.Add(this.colorGroupBox1);
            this.tabPage1.Controls.Add(this.detectTagBtn);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(648, 318);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Main";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 24);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Image Path:";
            // 
            // imagePath
            // 
            this.imagePath.Location = new System.Drawing.Point(94, 21);
            this.imagePath.Name = "imagePath";
            this.imagePath.Size = new System.Drawing.Size(350, 20);
            this.imagePath.TabIndex = 4;
            // 
            // colorGroupBox1
            // 
            this.colorGroupBox1.Controls.Add(this.radioButton1);
            this.colorGroupBox1.Controls.Add(this.radioButton2);
            this.colorGroupBox1.Location = new System.Drawing.Point(94, 57);
            this.colorGroupBox1.Name = "colorGroupBox1";
            this.colorGroupBox1.Size = new System.Drawing.Size(126, 37);
            this.colorGroupBox1.TabIndex = 3;
            this.colorGroupBox1.TabStop = false;
            this.colorGroupBox1.Text = "Color";
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Checked = true;
            this.radioButton1.Location = new System.Drawing.Point(13, 14);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(45, 17);
            this.radioButton1.TabIndex = 1;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "Red";
            this.radioButton1.UseVisualStyleBackColor = true;
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(65, 14);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(46, 17);
            this.radioButton2.TabIndex = 2;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "Blue";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // detectTagBtn
            // 
            this.detectTagBtn.Location = new System.Drawing.Point(242, 57);
            this.detectTagBtn.Name = "detectTagBtn";
            this.detectTagBtn.Size = new System.Drawing.Size(202, 37);
            this.detectTagBtn.TabIndex = 0;
            this.detectTagBtn.Text = "Detect Tag";
            this.detectTagBtn.UseVisualStyleBackColor = true;
            this.detectTagBtn.Click += new System.EventHandler(this.detectTagBtn_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(4, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(656, 344);
            this.tabControl1.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 228);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(67, 13);
            this.label3.TabIndex = 67;
            this.label3.Text = "Settings File:";
            // 
            // settingsInput
            // 
            this.settingsInput.Location = new System.Drawing.Point(114, 221);
            this.settingsInput.Name = "settingsInput";
            this.settingsInput.Size = new System.Drawing.Size(281, 20);
            this.settingsInput.TabIndex = 68;
            // 
            // settingsBtn
            // 
            this.settingsBtn.Location = new System.Drawing.Point(401, 219);
            this.settingsBtn.Name = "settingsBtn";
            this.settingsBtn.Size = new System.Drawing.Size(100, 23);
            this.settingsBtn.TabIndex = 69;
            this.settingsBtn.Text = "Read Settings";
            this.settingsBtn.UseVisualStyleBackColor = true;
            this.settingsBtn.Click += new System.EventHandler(this.settingsBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(663, 316);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Panels Test Program";
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.colorGroupBox1.ResumeLayout(false);
            this.colorGroupBox1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.Button calibrateBtn;
        private System.Windows.Forms.Button loadCalibrationBtn;
        private System.Windows.Forms.CheckBox featuresCheckBox;
        private System.Windows.Forms.Button featureDetectionBtn;
        private System.Windows.Forms.Label featureTemplateLabel;
        private System.Windows.Forms.TextBox featureTemplateBox;
        private System.Windows.Forms.TextBox calibrationPath;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button calibrateNoOutputBtn;
        private System.Windows.Forms.Button pixelsToLengthBtn;
        private System.Windows.Forms.TextBox inputBox;
        private System.Windows.Forms.Button viewWithCalibrationBtn;
        private System.Windows.Forms.Button goBtn;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button batchCalibrateBtn;
        private System.Windows.Forms.Button detectEdgesBtn;
        private System.Windows.Forms.Button panelBtn;
        private System.Windows.Forms.Label warningLabel;
        private System.Windows.Forms.Button blueBtn;
        private System.Windows.Forms.Button redBtn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button detectTagBtn;
        private System.Windows.Forms.GroupBox colorGroupBox1;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox imagePath;
        private System.Windows.Forms.TextBox settingsInput;
        private System.Windows.Forms.Label settingsLabel;
        private System.Windows.Forms.Button settingsBtn;
    }
}

