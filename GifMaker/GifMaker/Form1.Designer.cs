namespace GifMaker
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
            this.img_show = new System.Windows.Forms.PictureBox();
            this.select_files = new System.Windows.Forms.Button();
            this.gif_excude = new System.Windows.Forms.Button();
            this.img_list = new System.Windows.Forms.ListView();
            this.delete_files = new System.Windows.Forms.Button();
            this.outpath = new System.Windows.Forms.TextBox();
            this.Set_output = new System.Windows.Forms.Button();
            this.gif_decode = new System.Windows.Forms.Button();
            this.files_clear = new System.Windows.Forms.Button();
            this.gif_delay = new System.Windows.Forms.TextBox();
            this.Loop_Flag = new System.Windows.Forms.CheckBox();
            this.decode_pro = new System.Windows.Forms.ProgressBar();
            this.LOAD_FROM_URL = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.img_show)).BeginInit();
            this.SuspendLayout();
            // 
            // img_show
            // 
            this.img_show.Location = new System.Drawing.Point(194, 13);
            this.img_show.Name = "img_show";
            this.img_show.Size = new System.Drawing.Size(485, 485);
            this.img_show.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.img_show.TabIndex = 1;
            this.img_show.TabStop = false;
            // 
            // select_files
            // 
            this.select_files.Location = new System.Drawing.Point(686, 13);
            this.select_files.Name = "select_files";
            this.select_files.Size = new System.Drawing.Size(136, 38);
            this.select_files.TabIndex = 2;
            this.select_files.Text = "添加文件";
            this.select_files.UseVisualStyleBackColor = true;
            this.select_files.Click += new System.EventHandler(this.select_files_Click);
            // 
            // gif_excude
            // 
            this.gif_excude.Location = new System.Drawing.Point(686, 121);
            this.gif_excude.Name = "gif_excude";
            this.gif_excude.Size = new System.Drawing.Size(136, 38);
            this.gif_excude.TabIndex = 3;
            this.gif_excude.Text = "导出gif文件";
            this.gif_excude.UseVisualStyleBackColor = true;
            this.gif_excude.Click += new System.EventHandler(this.gif_excude_Click);
            // 
            // img_list
            // 
            this.img_list.Location = new System.Drawing.Point(13, 13);
            this.img_list.Name = "img_list";
            this.img_list.Size = new System.Drawing.Size(174, 485);
            this.img_list.TabIndex = 0;
            this.img_list.UseCompatibleStateImageBehavior = false;
            this.img_list.View = System.Windows.Forms.View.Details;
            this.img_list.ItemSelectionChanged += new System.Windows.Forms.ListViewItemSelectionChangedEventHandler(this.img_list_ItemSelectionChanged);
            // 
            // delete_files
            // 
            this.delete_files.Location = new System.Drawing.Point(686, 68);
            this.delete_files.Name = "delete_files";
            this.delete_files.Size = new System.Drawing.Size(136, 38);
            this.delete_files.TabIndex = 4;
            this.delete_files.Text = "删除";
            this.delete_files.UseVisualStyleBackColor = true;
            this.delete_files.Click += new System.EventHandler(this.delete_files_Click);
            // 
            // outpath
            // 
            this.outpath.Location = new System.Drawing.Point(686, 470);
            this.outpath.Name = "outpath";
            this.outpath.ReadOnly = true;
            this.outpath.Size = new System.Drawing.Size(136, 28);
            this.outpath.TabIndex = 5;
            // 
            // Set_output
            // 
            this.Set_output.Location = new System.Drawing.Point(686, 426);
            this.Set_output.Name = "Set_output";
            this.Set_output.Size = new System.Drawing.Size(136, 38);
            this.Set_output.TabIndex = 6;
            this.Set_output.Text = "设置输出目录";
            this.Set_output.UseVisualStyleBackColor = true;
            this.Set_output.Click += new System.EventHandler(this.Set_output_Click);
            // 
            // gif_decode
            // 
            this.gif_decode.Location = new System.Drawing.Point(686, 382);
            this.gif_decode.Name = "gif_decode";
            this.gif_decode.Size = new System.Drawing.Size(136, 38);
            this.gif_decode.TabIndex = 7;
            this.gif_decode.Text = "gif转图像";
            this.gif_decode.UseVisualStyleBackColor = true;
            this.gif_decode.Click += new System.EventHandler(this.gif_decode_Click);
            // 
            // files_clear
            // 
            this.files_clear.Location = new System.Drawing.Point(686, 174);
            this.files_clear.Name = "files_clear";
            this.files_clear.Size = new System.Drawing.Size(136, 38);
            this.files_clear.TabIndex = 8;
            this.files_clear.Text = "清空";
            this.files_clear.UseVisualStyleBackColor = true;
            this.files_clear.Click += new System.EventHandler(this.files_clear_Click);
            // 
            // gif_delay
            // 
            this.gif_delay.Location = new System.Drawing.Point(685, 228);
            this.gif_delay.Name = "gif_delay";
            this.gif_delay.Size = new System.Drawing.Size(137, 28);
            this.gif_delay.TabIndex = 9;
            this.gif_delay.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.gif_delay_KeyPress);
            // 
            // Loop_Flag
            // 
            this.Loop_Flag.AutoSize = true;
            this.Loop_Flag.Location = new System.Drawing.Point(685, 272);
            this.Loop_Flag.Name = "Loop_Flag";
            this.Loop_Flag.Size = new System.Drawing.Size(106, 22);
            this.Loop_Flag.TabIndex = 10;
            this.Loop_Flag.Text = "是否循环";
            this.Loop_Flag.UseVisualStyleBackColor = true;
            // 
            // decode_pro
            // 
            this.decode_pro.Location = new System.Drawing.Point(686, 341);
            this.decode_pro.Name = "decode_pro";
            this.decode_pro.Size = new System.Drawing.Size(136, 35);
            this.decode_pro.TabIndex = 11;
            // 
            // LOAD_FROM_URL
            // 
            this.LOAD_FROM_URL.Location = new System.Drawing.Point(685, 297);
            this.LOAD_FROM_URL.Name = "LOAD_FROM_URL";
            this.LOAD_FROM_URL.Size = new System.Drawing.Size(136, 38);
            this.LOAD_FROM_URL.TabIndex = 12;
            this.LOAD_FROM_URL.Text = "加载网络图片";
            this.LOAD_FROM_URL.UseVisualStyleBackColor = true;
            this.LOAD_FROM_URL.Click += new System.EventHandler(this.LOAD_FROM_URL_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(834, 510);
            this.Controls.Add(this.LOAD_FROM_URL);
            this.Controls.Add(this.decode_pro);
            this.Controls.Add(this.Loop_Flag);
            this.Controls.Add(this.gif_delay);
            this.Controls.Add(this.files_clear);
            this.Controls.Add(this.gif_decode);
            this.Controls.Add(this.Set_output);
            this.Controls.Add(this.outpath);
            this.Controls.Add(this.delete_files);
            this.Controls.Add(this.gif_excude);
            this.Controls.Add(this.select_files);
            this.Controls.Add(this.img_show);
            this.Controls.Add(this.img_list);
            this.Name = "Form1";
            this.Text = "Gif小工具";
            ((System.ComponentModel.ISupportInitialize)(this.img_show)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.PictureBox img_show;
        private System.Windows.Forms.Button select_files;
        private System.Windows.Forms.Button gif_excude;
        private System.Windows.Forms.ListView img_list;
        private System.Windows.Forms.Button delete_files;
        private System.Windows.Forms.TextBox outpath;
        private System.Windows.Forms.Button Set_output;
        private System.Windows.Forms.Button gif_decode;
        private System.Windows.Forms.Button files_clear;
        private System.Windows.Forms.TextBox gif_delay;
        private System.Windows.Forms.CheckBox Loop_Flag;
        private System.Windows.Forms.ProgressBar decode_pro;
        private System.Windows.Forms.Button LOAD_FROM_URL;
    }
}

