namespace Panel_QA_TestProgram
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
            if (disposing && (components != null))
            {
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
            this.inputBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.goBtn = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.redBtn = new System.Windows.Forms.Button();
            this.blueBtn = new System.Windows.Forms.Button();
            this.warningLabel = new System.Windows.Forms.Label();
            this.detectEdgesBtn = new System.Windows.Forms.Button();
            this.panelBtn = new System.Windows.Forms.Button();
            this.calibrateNoOutputBtn = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.classifierBox = new System.Windows.Forms.TextBox();
            this.classifierBtn = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.calibrationPath = new System.Windows.Forms.TextBox();
            this.calibrateBtn = new System.Windows.Forms.Button();
            this.viewWithCalibrationBtn = new System.Windows.Forms.Button();
            this.calibrateFisheyeNoOutputBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // inputBox
            // 
            this.inputBox.Location = new System.Drawing.Point(132, 42);
            this.inputBox.Name = "inputBox";
            this.inputBox.Size = new System.Drawing.Size(281, 20);
            this.inputBox.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(24, 45);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Image Path:";
            // 
            // goBtn
            // 
            this.goBtn.Location = new System.Drawing.Point(419, 40);
            this.goBtn.Name = "goBtn";
            this.goBtn.Size = new System.Drawing.Size(75, 23);
            this.goBtn.TabIndex = 2;
            this.goBtn.Text = "Show Image";
            this.goBtn.UseVisualStyleBackColor = true;
            this.goBtn.Click += new System.EventHandler(this.goBtn_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(24, 216);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Detect Color:";
            // 
            // redBtn
            // 
            this.redBtn.Location = new System.Drawing.Point(132, 211);
            this.redBtn.Name = "redBtn";
            this.redBtn.Size = new System.Drawing.Size(75, 23);
            this.redBtn.TabIndex = 4;
            this.redBtn.Text = "Red";
            this.redBtn.UseVisualStyleBackColor = true;
            this.redBtn.Click += new System.EventHandler(this.redBtn_Click);
            // 
            // blueBtn
            // 
            this.blueBtn.Location = new System.Drawing.Point(213, 211);
            this.blueBtn.Name = "blueBtn";
            this.blueBtn.Size = new System.Drawing.Size(75, 23);
            this.blueBtn.TabIndex = 5;
            this.blueBtn.Text = "Blue";
            this.blueBtn.UseVisualStyleBackColor = true;
            this.blueBtn.Click += new System.EventHandler(this.blueBtn_Click);
            // 
            // warningLabel
            // 
            this.warningLabel.AutoSize = true;
            this.warningLabel.Location = new System.Drawing.Point(208, 268);
            this.warningLabel.Name = "warningLabel";
            this.warningLabel.Size = new System.Drawing.Size(0, 13);
            this.warningLabel.TabIndex = 6;
            // 
            // detectEdgesBtn
            // 
            this.detectEdgesBtn.Location = new System.Drawing.Point(132, 258);
            this.detectEdgesBtn.Name = "detectEdgesBtn";
            this.detectEdgesBtn.Size = new System.Drawing.Size(87, 23);
            this.detectEdgesBtn.TabIndex = 7;
            this.detectEdgesBtn.Text = "Canny Edges";
            this.detectEdgesBtn.UseVisualStyleBackColor = true;
            this.detectEdgesBtn.Click += new System.EventHandler(this.detectEdgesBtn_Click);
            // 
            // panelBtn
            // 
            this.panelBtn.Location = new System.Drawing.Point(294, 211);
            this.panelBtn.Name = "panelBtn";
            this.panelBtn.Size = new System.Drawing.Size(75, 23);
            this.panelBtn.TabIndex = 8;
            this.panelBtn.Text = "Panel";
            this.panelBtn.UseVisualStyleBackColor = true;
            this.panelBtn.Click += new System.EventHandler(this.panelBtn_Click);
            // 
            // calibrateNoOutputBtn
            // 
            this.calibrateNoOutputBtn.Location = new System.Drawing.Point(500, 90);
            this.calibrateNoOutputBtn.Name = "calibrateNoOutputBtn";
            this.calibrateNoOutputBtn.Size = new System.Drawing.Size(121, 23);
            this.calibrateNoOutputBtn.TabIndex = 9;
            this.calibrateNoOutputBtn.Text = "Calibrate No Output";
            this.calibrateNoOutputBtn.UseVisualStyleBackColor = true;
            this.calibrateNoOutputBtn.Click += new System.EventHandler(this.calibrateNoOutputBtn_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 173);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(51, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Classifier:";
            // 
            // classifierBox
            // 
            this.classifierBox.Location = new System.Drawing.Point(132, 170);
            this.classifierBox.Name = "classifierBox";
            this.classifierBox.Size = new System.Drawing.Size(281, 20);
            this.classifierBox.TabIndex = 12;
            this.classifierBox.Text = "C:\\CPE 495 496\\Haar_Example\\opencv-haar-classifier-training\\classifier\\cascade.xm" +
    "l";
            // 
            // classifierBtn
            // 
            this.classifierBtn.Location = new System.Drawing.Point(419, 168);
            this.classifierBtn.Name = "classifierBtn";
            this.classifierBtn.Size = new System.Drawing.Size(75, 23);
            this.classifierBtn.TabIndex = 13;
            this.classifierBtn.Text = "Detect";
            this.classifierBtn.UseVisualStyleBackColor = true;
            this.classifierBtn.Click += new System.EventHandler(this.classifierBtn_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(27, 92);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(84, 13);
            this.label4.TabIndex = 14;
            this.label4.Text = "Calibration Path:";
            // 
            // calibrationPath
            // 
            this.calibrationPath.Location = new System.Drawing.Point(132, 92);
            this.calibrationPath.Name = "calibrationPath";
            this.calibrationPath.Size = new System.Drawing.Size(281, 20);
            this.calibrationPath.TabIndex = 15;
            // 
            // calibrateBtn
            // 
            this.calibrateBtn.Location = new System.Drawing.Point(419, 90);
            this.calibrateBtn.Name = "calibrateBtn";
            this.calibrateBtn.Size = new System.Drawing.Size(75, 23);
            this.calibrateBtn.TabIndex = 16;
            this.calibrateBtn.Text = "Calibrate";
            this.calibrateBtn.UseVisualStyleBackColor = true;
            this.calibrateBtn.Click += new System.EventHandler(this.calibrateBtn_Click);
            // 
            // viewWithCalibrationBtn
            // 
            this.viewWithCalibrationBtn.Location = new System.Drawing.Point(500, 40);
            this.viewWithCalibrationBtn.Name = "viewWithCalibrationBtn";
            this.viewWithCalibrationBtn.Size = new System.Drawing.Size(121, 23);
            this.viewWithCalibrationBtn.TabIndex = 17;
            this.viewWithCalibrationBtn.Text = "View With Calibration";
            this.viewWithCalibrationBtn.UseVisualStyleBackColor = true;
            this.viewWithCalibrationBtn.Click += new System.EventHandler(this.viewWithCalibrationBtn_Click);
            // 
            // calibrateFisheyeNoOutputBtn
            // 
            this.calibrateFisheyeNoOutputBtn.Location = new System.Drawing.Point(500, 119);
            this.calibrateFisheyeNoOutputBtn.Name = "calibrateFisheyeNoOutputBtn";
            this.calibrateFisheyeNoOutputBtn.Size = new System.Drawing.Size(121, 34);
            this.calibrateFisheyeNoOutputBtn.TabIndex = 18;
            this.calibrateFisheyeNoOutputBtn.Text = "Calibrate Fisheye\r\nNo Output";
            this.calibrateFisheyeNoOutputBtn.UseVisualStyleBackColor = true;
            this.calibrateFisheyeNoOutputBtn.Click += new System.EventHandler(this.calibrateFisheyeNoOutputBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(702, 388);
            this.Controls.Add(this.calibrateFisheyeNoOutputBtn);
            this.Controls.Add(this.viewWithCalibrationBtn);
            this.Controls.Add(this.calibrateBtn);
            this.Controls.Add(this.calibrationPath);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.classifierBtn);
            this.Controls.Add(this.classifierBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.calibrateNoOutputBtn);
            this.Controls.Add(this.panelBtn);
            this.Controls.Add(this.detectEdgesBtn);
            this.Controls.Add(this.warningLabel);
            this.Controls.Add(this.blueBtn);
            this.Controls.Add(this.redBtn);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.goBtn);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.inputBox);
            this.Name = "Form1";
            this.Text = "Panels Test Program";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox inputBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button goBtn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button redBtn;
        private System.Windows.Forms.Button blueBtn;
        private System.Windows.Forms.Label warningLabel;
        private System.Windows.Forms.Button detectEdgesBtn;
        private System.Windows.Forms.Button panelBtn;
        private System.Windows.Forms.Button calibrateNoOutputBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox classifierBox;
        private System.Windows.Forms.Button classifierBtn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox calibrationPath;
        private System.Windows.Forms.Button calibrateBtn;
        private System.Windows.Forms.Button viewWithCalibrationBtn;
        private System.Windows.Forms.Button calibrateFisheyeNoOutputBtn;
    }
}

