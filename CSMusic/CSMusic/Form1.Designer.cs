namespace CSMusic
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
            this.Bt_Play = new System.Windows.Forms.Button();
            this.Music_list = new System.Windows.Forms.ListBox();
            this.Music_Add = new System.Windows.Forms.Button();
            this.Music_Voice = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.Music_Length = new System.Windows.Forms.TrackBar();
            this.Music_Length_Start = new System.Windows.Forms.Label();
            this.Music_Length_End = new System.Windows.Forms.Label();
            this.Music_Pause = new System.Windows.Forms.Button();
            this.CB_Play_State = new System.Windows.Forms.ComboBox();
            this.Music_Now = new System.Windows.Forms.TextBox();
            this.Last_one = new System.Windows.Forms.Button();
            this.Next_one = new System.Windows.Forms.Button();
            this.Music_Dir = new System.Windows.Forms.TextBox();
            this.Select_Music_Dir = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Music_Voice)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Music_Length)).BeginInit();
            this.SuspendLayout();
            // 
            // Bt_Play
            // 
            this.Bt_Play.Location = new System.Drawing.Point(689, 12);
            this.Bt_Play.Name = "Bt_Play";
            this.Bt_Play.Size = new System.Drawing.Size(83, 33);
            this.Bt_Play.TabIndex = 0;
            this.Bt_Play.Text = "播放";
            this.Bt_Play.UseVisualStyleBackColor = true;
            this.Bt_Play.Click += new System.EventHandler(this.Bt_Play_Click);
            // 
            // Music_list
            // 
            this.Music_list.FormattingEnabled = true;
            this.Music_list.ItemHeight = 18;
            this.Music_list.Location = new System.Drawing.Point(13, 13);
            this.Music_list.Name = "Music_list";
            this.Music_list.Size = new System.Drawing.Size(184, 364);
            this.Music_list.TabIndex = 1;
            this.Music_list.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.Music_list_MouseDoubleClick);
            // 
            // Music_Add
            // 
            this.Music_Add.Location = new System.Drawing.Point(689, 111);
            this.Music_Add.Name = "Music_Add";
            this.Music_Add.Size = new System.Drawing.Size(83, 33);
            this.Music_Add.TabIndex = 2;
            this.Music_Add.Text = "结束";
            this.Music_Add.UseVisualStyleBackColor = true;
            this.Music_Add.Click += new System.EventHandler(this.Music_Add_Click);
            // 
            // Music_Voice
            // 
            this.Music_Voice.Location = new System.Drawing.Point(721, 328);
            this.Music_Voice.Name = "Music_Voice";
            this.Music_Voice.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.Music_Voice.Size = new System.Drawing.Size(69, 122);
            this.Music_Voice.TabIndex = 3;
            this.Music_Voice.Scroll += new System.EventHandler(this.Music_Voice_Scroll);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(718, 442);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 18);
            this.label1.TabIndex = 4;
            this.label1.Text = "0";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(718, 320);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 18);
            this.label2.TabIndex = 5;
            this.label2.Text = "100";
            // 
            // Music_Length
            // 
            this.Music_Length.Location = new System.Drawing.Point(86, 381);
            this.Music_Length.Name = "Music_Length";
            this.Music_Length.Size = new System.Drawing.Size(483, 69);
            this.Music_Length.TabIndex = 6;
            this.Music_Length.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Music_Length_MouseDown);
            this.Music_Length.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Music_Length_MouseUp);
            // 
            // Music_Length_Start
            // 
            this.Music_Length_Start.AutoSize = true;
            this.Music_Length_Start.Location = new System.Drawing.Point(12, 381);
            this.Music_Length_Start.Name = "Music_Length_Start";
            this.Music_Length_Start.Size = new System.Drawing.Size(80, 18);
            this.Music_Length_Start.TabIndex = 7;
            this.Music_Length_Start.Text = "00:00:00";
            // 
            // Music_Length_End
            // 
            this.Music_Length_End.AutoSize = true;
            this.Music_Length_End.Location = new System.Drawing.Point(565, 381);
            this.Music_Length_End.Name = "Music_Length_End";
            this.Music_Length_End.Size = new System.Drawing.Size(80, 18);
            this.Music_Length_End.TabIndex = 8;
            this.Music_Length_End.Text = "00:00:00";
            // 
            // Music_Pause
            // 
            this.Music_Pause.Location = new System.Drawing.Point(689, 61);
            this.Music_Pause.Name = "Music_Pause";
            this.Music_Pause.Size = new System.Drawing.Size(83, 33);
            this.Music_Pause.TabIndex = 9;
            this.Music_Pause.Text = "暂停";
            this.Music_Pause.UseVisualStyleBackColor = true;
            this.Music_Pause.Click += new System.EventHandler(this.Music_Pause_Click);
            // 
            // CB_Play_State
            // 
            this.CB_Play_State.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CB_Play_State.FormattingEnabled = true;
            this.CB_Play_State.Items.AddRange(new object[] {
            "顺序播放",
            "随机播放",
            "重复播放",
            "循环播放"});
            this.CB_Play_State.Location = new System.Drawing.Point(669, 276);
            this.CB_Play_State.Name = "CB_Play_State";
            this.CB_Play_State.Size = new System.Drawing.Size(121, 26);
            this.CB_Play_State.TabIndex = 10;
            this.CB_Play_State.SelectedIndexChanged += new System.EventHandler(this.CB_Play_State_SelectedIndexChanged);
            // 
            // Music_Now
            // 
            this.Music_Now.Location = new System.Drawing.Point(219, 13);
            this.Music_Now.Name = "Music_Now";
            this.Music_Now.ReadOnly = true;
            this.Music_Now.Size = new System.Drawing.Size(426, 28);
            this.Music_Now.TabIndex = 11;
            this.Music_Now.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // Last_one
            // 
            this.Last_one.Location = new System.Drawing.Point(689, 152);
            this.Last_one.Name = "Last_one";
            this.Last_one.Size = new System.Drawing.Size(83, 33);
            this.Last_one.TabIndex = 12;
            this.Last_one.Text = "上一首";
            this.Last_one.UseVisualStyleBackColor = true;
            this.Last_one.Click += new System.EventHandler(this.Last_one_Click);
            // 
            // Next_one
            // 
            this.Next_one.Location = new System.Drawing.Point(689, 199);
            this.Next_one.Name = "Next_one";
            this.Next_one.Size = new System.Drawing.Size(83, 33);
            this.Next_one.TabIndex = 13;
            this.Next_one.Text = "下一首";
            this.Next_one.UseVisualStyleBackColor = true;
            this.Next_one.Click += new System.EventHandler(this.Next_one_Click);
            // 
            // Music_Dir
            // 
            this.Music_Dir.Location = new System.Drawing.Point(219, 349);
            this.Music_Dir.Multiline = true;
            this.Music_Dir.Name = "Music_Dir";
            this.Music_Dir.ReadOnly = true;
            this.Music_Dir.Size = new System.Drawing.Size(278, 33);
            this.Music_Dir.TabIndex = 14;
            this.Music_Dir.Text = "D:\\Music";
            // 
            // Select_Music_Dir
            // 
            this.Select_Music_Dir.Location = new System.Drawing.Point(513, 349);
            this.Select_Music_Dir.Name = "Select_Music_Dir";
            this.Select_Music_Dir.Size = new System.Drawing.Size(113, 33);
            this.Select_Music_Dir.TabIndex = 15;
            this.Select_Music_Dir.Text = "选择文件夹";
            this.Select_Music_Dir.UseVisualStyleBackColor = true;
            this.Select_Music_Dir.Click += new System.EventHandler(this.Select_Music_Dir_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(802, 462);
            this.Controls.Add(this.Select_Music_Dir);
            this.Controls.Add(this.Music_Dir);
            this.Controls.Add(this.Next_one);
            this.Controls.Add(this.Last_one);
            this.Controls.Add(this.Music_Now);
            this.Controls.Add(this.CB_Play_State);
            this.Controls.Add(this.Music_Pause);
            this.Controls.Add(this.Music_Length_End);
            this.Controls.Add(this.Music_Length_Start);
            this.Controls.Add(this.Music_Length);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Music_Voice);
            this.Controls.Add(this.Music_Add);
            this.Controls.Add(this.Music_list);
            this.Controls.Add(this.Bt_Play);
            this.Name = "Form1";
            this.Text = "Soul Music";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.Music_Voice)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Music_Length)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Bt_Play;
        private System.Windows.Forms.ListBox Music_list;
        private System.Windows.Forms.Button Music_Add;
        private System.Windows.Forms.TrackBar Music_Voice;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TrackBar Music_Length;
        private System.Windows.Forms.Label Music_Length_Start;
        private System.Windows.Forms.Label Music_Length_End;
        private System.Windows.Forms.Button Music_Pause;
        private System.Windows.Forms.ComboBox CB_Play_State;
        private System.Windows.Forms.TextBox Music_Now;
        private System.Windows.Forms.Button Last_one;
        private System.Windows.Forms.Button Next_one;
        private System.Windows.Forms.TextBox Music_Dir;
        private System.Windows.Forms.Button Select_Music_Dir;
    }
}

