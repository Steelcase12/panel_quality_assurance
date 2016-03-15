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
            this.calibrateBtn = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.classifierBox = new System.Windows.Forms.TextBox();
            this.classifierBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // inputBox
            // 
            this.inputBox.Location = new System.Drawing.Point(94, 42);
            this.inputBox.Name = "inputBox";
            this.inputBox.Size = new System.Drawing.Size(191, 20);
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
            this.goBtn.Location = new System.Drawing.Point(291, 42);
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
            this.label2.Location = new System.Drawing.Point(24, 129);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Detect Color:";
            // 
            // redBtn
            // 
            this.redBtn.Location = new System.Drawing.Point(94, 124);
            this.redBtn.Name = "redBtn";
            this.redBtn.Size = new System.Drawing.Size(75, 23);
            this.redBtn.TabIndex = 4;
            this.redBtn.Text = "Red";
            this.redBtn.UseVisualStyleBackColor = true;
            this.redBtn.Click += new System.EventHandler(this.redBtn_Click);
            // 
            // blueBtn
            // 
            this.blueBtn.Location = new System.Drawing.Point(175, 124);
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
            this.warningLabel.Location = new System.Drawing.Point(170, 181);
            this.warningLabel.Name = "warningLabel";
            this.warningLabel.Size = new System.Drawing.Size(0, 13);
            this.warningLabel.TabIndex = 6;
            // 
            // detectEdgesBtn
            // 
            this.detectEdgesBtn.Location = new System.Drawing.Point(94, 171);
            this.detectEdgesBtn.Name = "detectEdgesBtn";
            this.detectEdgesBtn.Size = new System.Drawing.Size(87, 23);
            this.detectEdgesBtn.TabIndex = 7;
            this.detectEdgesBtn.Text = "Canny Edges";
            this.detectEdgesBtn.UseVisualStyleBackColor = true;
            this.detectEdgesBtn.Click += new System.EventHandler(this.detectEdgesBtn_Click);
            // 
            // panelBtn
            // 
            this.panelBtn.Location = new System.Drawing.Point(256, 124);
            this.panelBtn.Name = "panelBtn";
            this.panelBtn.Size = new System.Drawing.Size(75, 23);
            this.panelBtn.TabIndex = 8;
            this.panelBtn.Text = "Panel";
            this.panelBtn.UseVisualStyleBackColor = true;
            this.panelBtn.Click += new System.EventHandler(this.panelBtn_Click);
            // 
            // calibrateNoOutputBtn
            // 
            this.calibrateNoOutputBtn.Location = new System.Drawing.Point(210, 171);
            this.calibrateNoOutputBtn.Name = "calibrateNoOutputBtn";
            this.calibrateNoOutputBtn.Size = new System.Drawing.Size(75, 23);
            this.calibrateNoOutputBtn.TabIndex = 9;
            this.calibrateNoOutputBtn.Text = "Calibrate";
            this.calibrateNoOutputBtn.UseVisualStyleBackColor = true;
            this.calibrateNoOutputBtn.Click += new System.EventHandler(this.calibrateNoOutputBtn_Click);
            // 
            // calibrateBtn
            // 
            this.calibrateBtn.Location = new System.Drawing.Point(0, 0);
            this.calibrateBtn.Name = "calibrateBtn";
            this.calibrateBtn.Size = new System.Drawing.Size(75, 23);
            this.calibrateBtn.TabIndex = 0;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(24, 86);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Classifier";
            // 
            // classifierBox
            // 
            this.classifierBox.Location = new System.Drawing.Point(94, 83);
            this.classifierBox.Name = "classifierBox";
            this.classifierBox.Size = new System.Drawing.Size(191, 20);
            this.classifierBox.TabIndex = 12;
            this.classifierBox.Text = "C:\\CPE 495 496\\Haar_Example\\opencv-haar-classifier-training\\classifier\\cascade.xm" +
    "l";
            // 
            // classifierBtn
            // 
            this.classifierBtn.Location = new System.Drawing.Point(291, 81);
            this.classifierBtn.Name = "classifierBtn";
            this.classifierBtn.Size = new System.Drawing.Size(75, 23);
            this.classifierBtn.TabIndex = 13;
            this.classifierBtn.Text = "Detect";
            this.classifierBtn.UseVisualStyleBackColor = true;
            this.classifierBtn.Click += new System.EventHandler(this.classifierBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(390, 223);
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
        private System.Windows.Forms.Button calibrateBtn;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox classifierBox;
        private System.Windows.Forms.Button classifierBtn;
    }
}

