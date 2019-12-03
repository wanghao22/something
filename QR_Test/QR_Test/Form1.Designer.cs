namespace QR_Test
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.QR_make = new System.Windows.Forms.Button();
            this.QR_show = new System.Windows.Forms.PictureBox();
            this.QR_Save = new System.Windows.Forms.Button();
            this.img_name = new System.Windows.Forms.TextBox();
            this.img_type = new System.Windows.Forms.ComboBox();
            this.QR_class = new System.Windows.Forms.ComboBox();
            this.QR_Decode = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.QR_show)).BeginInit();
            this.SuspendLayout();
            // 
            // QR_make
            // 
            this.QR_make.Location = new System.Drawing.Point(557, 46);
            this.QR_make.Name = "QR_make";
            this.QR_make.Size = new System.Drawing.Size(111, 48);
            this.QR_make.TabIndex = 0;
            this.QR_make.Text = "生成二维码";
            this.QR_make.UseVisualStyleBackColor = true;
            this.QR_make.Click += new System.EventHandler(this.QR_make_Click);
            // 
            // QR_show
            // 
            this.QR_show.Location = new System.Drawing.Point(13, 13);
            this.QR_show.Name = "QR_show";
            this.QR_show.Size = new System.Drawing.Size(538, 450);
            this.QR_show.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.QR_show.TabIndex = 1;
            this.QR_show.TabStop = false;
            // 
            // QR_Save
            // 
            this.QR_Save.Cursor = System.Windows.Forms.Cursors.Default;
            this.QR_Save.Location = new System.Drawing.Point(558, 101);
            this.QR_Save.Name = "QR_Save";
            this.QR_Save.Size = new System.Drawing.Size(111, 48);
            this.QR_Save.TabIndex = 2;
            this.QR_Save.Text = "保存图片";
            this.QR_Save.UseVisualStyleBackColor = true;
            this.QR_Save.Click += new System.EventHandler(this.QR_Save_Click);
            // 
            // img_name
            // 
            this.img_name.Location = new System.Drawing.Point(558, 174);
            this.img_name.Name = "img_name";
            this.img_name.Size = new System.Drawing.Size(110, 28);
            this.img_name.TabIndex = 3;
            // 
            // img_type
            // 
            this.img_type.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.img_type.FormattingEnabled = true;
            this.img_type.Items.AddRange(new object[] {
            "jpg",
            "png",
            "bmp"});
            this.img_type.Location = new System.Drawing.Point(558, 223);
            this.img_type.Name = "img_type";
            this.img_type.Size = new System.Drawing.Size(110, 26);
            this.img_type.TabIndex = 4;
            // 
            // QR_class
            // 
            this.QR_class.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.QR_class.FormattingEnabled = true;
            this.QR_class.Items.AddRange(new object[] {
            "文字",
            "网址",
            "Wifi",
            "书签",
            "一次性验证码",
            "电话",
            "邮箱",
            "短信",
            "WhatsAppMessage",
            "地图",
            "联系人",
            "日历事件"});
            this.QR_class.Location = new System.Drawing.Point(558, 13);
            this.QR_class.Name = "QR_class";
            this.QR_class.Size = new System.Drawing.Size(110, 26);
            this.QR_class.TabIndex = 5;
            // 
            // QR_Decode
            // 
            this.QR_Decode.Location = new System.Drawing.Point(558, 266);
            this.QR_Decode.Name = "QR_Decode";
            this.QR_Decode.Size = new System.Drawing.Size(111, 48);
            this.QR_Decode.TabIndex = 6;
            this.QR_Decode.Text = "解析二维码";
            this.QR_Decode.UseVisualStyleBackColor = true;
            this.QR_Decode.Click += new System.EventHandler(this.QR_Decode_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(680, 471);
            this.Controls.Add(this.QR_Decode);
            this.Controls.Add(this.QR_class);
            this.Controls.Add(this.img_type);
            this.Controls.Add(this.img_name);
            this.Controls.Add(this.QR_Save);
            this.Controls.Add(this.QR_show);
            this.Controls.Add(this.QR_make);
            this.Name = "Form1";
            this.Text = "二维码小工具";
            ((System.ComponentModel.ISupportInitialize)(this.QR_show)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button QR_make;
        private System.Windows.Forms.PictureBox QR_show;
        private System.Windows.Forms.Button QR_Save;
        private System.Windows.Forms.TextBox img_name;
        private System.Windows.Forms.ComboBox img_type;
        private System.Windows.Forms.ComboBox QR_class;
        private System.Windows.Forms.Button QR_Decode;
    }
}

