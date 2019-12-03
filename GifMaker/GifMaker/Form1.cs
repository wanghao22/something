using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Gif;
using Gif.Components;
using System.IO;

namespace GifMaker
{
    public partial class Form1 : Form
    {
        delegate void SetTrackBarValue(int val);
        delegate void SetTrackBarState(bool flag);
        string[] files;
        string outgif;
        string giffile;
        Random rd = new Random();
        List<string> urls = new List<string>();
        bool m_decode_flag;
        BackgroundWorker m_bkwork;
        public Form1()
        {
            InitializeComponent();
            img_list.Columns.Add("名称", 120, HorizontalAlignment.Left);
            img_show.BackColor = Color.White;
            //获取exe所在的目录
            outpath.Text = System.Environment.CurrentDirectory+"\\img";
            gif_delay.Text = "30";
            decode_pro.Visible = false;
            LoadNetUrl("url.txt", ref urls);
            m_decode_flag = false;
            //初始化背后事件
            this.m_bkwork = new BackgroundWorker();
            this.m_bkwork.WorkerSupportsCancellation = true;
            this.m_bkwork.DoWork += BgWorker1_DoWork;
        }

        /// <summary>
        /// 只获取文件名称
        /// </summary>
        /// <param name="fullpath"></param>
        /// <returns></returns>
        protected string OnlyGetName(string fullpath)
        {
            int a = fullpath.LastIndexOf('/');
            int b = fullpath.LastIndexOf('\\');
            int c = Math.Max(a, b);
            return fullpath.Remove(0, c + 1);
        }

        /// <summary>
        /// 添加文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void select_files_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Multiselect = true;//该值确定是否可以选择多个文件
            dialog.Title = "请选择文件";
            dialog.Filter = "jpg file(*.jpg)|*.jpg|png file(*.png)|*.png|bmp file(*.bmp)|*.bmp|所有文件(*.*)|*.*";
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                // file = dialog.FileName;
                if (files == null)
                {
                    files = dialog.FileNames;
                }
                else
                {
                    var temp1 = (string[])files.Clone();
                    var temp2 = dialog.FileNames;
                    if (files != null)
                        files = null;
                    files = new string[temp1.Length + temp2.Length];
                    for (int i = 0; i < temp1.Length + temp2.Length; i++)
                    {
                        if (i < temp1.Length)
                            files[i] = temp1[i];
                        else
                            files[i] = temp2[i - temp1.Length];
                    }
                }
                //files = dialog.FileNames;
            }
            else
                return;
            ListShow();
        }

        /// <summary>
        /// 当列表的选择项更改的时候所做的操作
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void img_list_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            if (img_list.SelectedItems.Count == 0) return;
            else
            {
                int k = img_list.SelectedItems[0].Index;
                img_show.Image = Image.FromFile(files[k]);
            }
        }

        /// <summary>
        /// 删除所选择的文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void delete_files_Click(object sender, EventArgs e)
        {
            int s = img_list.SelectedItems.Count;
            if (s == 0) return;
            else
            {
                for (int i = s - 1; i >= 0; i--)
                {
                    int k = img_list.SelectedItems[i].Index;
                    //IMG_SHOW.Image = MatToBitmap(imgs[k]);
                    //string site = img_list.SelectedItems[i].Text;
                    files = Delfile(files, k);
                    img_list.Items.RemoveAt(k);
                }
            }
        }

        /// <summary>
        /// 把选择的文件显示到控件上
        /// </summary>
        private void ListShow()
        {
            img_list.Items.Clear();
            for(int i = 0;i<files.Length;i++)
                img_list.Items.Add(OnlyGetName(files[i]));
        }

        /// <summary>
        /// 删除arr中第index个元素
        /// </summary>
        /// <param name="arr">原数组</param>
        /// <param name="index">要删除的元素下标</param>
        /// <returns>更改后的数组</returns>
        private string[] Delfile(string[] arr,int index)
        {
            var temp = new string[arr.Length - 1];
            for(int i = 0;i<arr.Length; i++)
            {
                if (i < index)
                    temp[i] = arr[i];
                else if (i == index)
                    continue;
                else
                    temp[i - 1] = arr[i];
            }
            return temp;
        }

        /// <summary>
        /// 导出gif
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void gif_excude_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();
            dialog.Title = "请选择文件";
            dialog.Filter = "gif file(*.gif)|*.gif";
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                outgif = dialog.FileName;
            }
            else
                return;
            //MessageBox.Show(file);
            try
            {
                //ImgsToGif(files, outgif, 30, true);
                Thread nk = new Thread(ThreadImgsToGif);
                nk.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        /// <summary>
        /// 合成gif线程
        /// </summary>
        public void ThreadImgsToGif()
        {
            int delay = Convert.ToInt32(gif_delay.Text);
            ImgsToGif(files, outgif, delay, Loop_Flag.Checked);
        }

        /// <summary>
        /// 解析gif线程
        /// </summary>
        public void ThreadGifToImg()
        {
            GifToPngs(giffile, outpath.Text, "png");
        }

        /// <summary>
        /// 把directory文件夹里的png文件生成为gif文件，放在giffile
        /// </summary>
        /// <param name="imgfiles">图像文件</param>
        /// <param name="giffile">gif保存路径</param>
        /// <param name="time">每帧的时间/ms</param>
        /// <param name="repeat">是否重复</param>
        public void ImgsToGif(string[] imgfiles, string giffile, int time, bool repeat)
        {
            if (imgfiles == null) 
            {
                var ex = new NullReferenceException();
                throw ex;
            }
            var encode = new AnimatedGifEncoder();
            encode.Start(giffile);
            //每帧播放时间
            encode.SetDelay(time);
            //-1：不重复，0：重复
            encode.SetRepeat(repeat ? 0 : -1);
            
            for (int i = 0, count = imgfiles.Length; i < count; i++)
            {
                encode.AddFrame(Image.FromFile(imgfiles[i]));
            }
            encode.Finish();
            MessageBox.Show("gif生成完成");
        }
        
        /// <summary>
        /// 把Gif文件转成Png文件，放在directory目录下
        /// </summary>
        /// <param name="giffile">gif文件</param>
        /// <param name="directory">输出目录</param>
        /// <param name="type">输出类型</param>
        /// <returns></returns>
        public void GifToPngs(string giffile, string directory, string type)
        {
            if (type != "jpg" && type != "png" && type != "bmp")
            {
                var ex = new NullReferenceException();
                throw ex;
            }
            var gifDecoder = new GifDecoder();
            directory += "\\";
            if (!Directory.Exists(directory))
            {
                Directory.CreateDirectory(directory);
            }
            //读取
            gifDecoder.Read(giffile);
            for (int i = 0, count = gifDecoder.GetFrameCount(); i < count; i++)
            {
                Image frame = gifDecoder.GetFrame(i);  // frame i
                frame.Save(directory + "\\" + i.ToString("d3") + "." + type);
            }
            MessageBox.Show("gif解析完成");
        }

        /// <summary>
        /// 设置输出目录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Set_output_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dlg = new FolderBrowserDialog();
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                outpath.Text = dlg.SelectedPath;
            }
        }

        /// <summary>
        /// 解析gif按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void gif_decode_Click(object sender, EventArgs e)
        {
            if (!m_decode_flag)
            {
                m_decode_flag = true;
                OpenFileDialog dialog = new OpenFileDialog();
                dialog.Multiselect = false;//该值确定是否可以选择多个文件
                dialog.Title = "请选择文件";
                dialog.Filter = "gif file(*.gif)|*.gif";
                if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
                {
                    giffile = dialog.FileName;
                }
                else
                    return;
                try
                {
                    //Thread nk = new Thread(ThreadGifToImg);
                    //nk.Start();
                    if (!this.m_bkwork.IsBusy)
                        m_bkwork.RunWorkerAsync();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
            else
            {
                MessageBox.Show("gif正在解析中\n请等待解析完成后\n再进行下一次操作！");
            }
        }

        /// <summary>
        /// 清空按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void files_clear_Click(object sender, EventArgs e)
        {
            files = null;
            img_list.Items.Clear();
        }

        /// <summary>
        /// 只允许输入数字和删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void gif_delay_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar != '\b')//这是允许输入退格键
            {
                if ((e.KeyChar < '0') || (e.KeyChar > '9'))//这是允许输入0-9数字
                {
                    e.Handled = true;
                }
            }
        }

        /// <summary>
        /// 背后事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BgWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            var type = "png";
            var gifDecoder = new GifDecoder();
            var directory = outpath.Text;
            directory += "\\";
            if (!Directory.Exists(directory))
            {
                Directory.CreateDirectory(directory);
            }
            //读取
            gifDecoder.Read(giffile);
            SetTrackBarFlg(true);
            for (int i = 0, count = gifDecoder.GetFrameCount(); i < count; i++)
            {
                Image frame = gifDecoder.GetFrame(i);  // frame i
                frame.Save(directory + "\\" + i.ToString("d3") + "." + type);
                var t = (i + 1) * 100 / count;
                SetTrackBarVal(t);
                Thread.Sleep(200);
            }
            SetTrackBarFlg(false);
            m_decode_flag = false;
            MessageBox.Show("gif解析完成");
        }

        /// <summary>
        /// 异步设置进度条的数值
        /// </summary>
        /// <param name="val"></param>
        void SetTrackBarVal(int val)
        {
            try
            {
                if (this.decode_pro.InvokeRequired)
                {
                    SetTrackBarValue d = new SetTrackBarValue(SetTrackBarVal);
                    this.Invoke(d, new object[] { val });
                }
                else
                {
                    this.decode_pro.Value = val;
                }
            }
            catch { };
        }

        /// <summary>
        /// 异步设置进度条的状态
        /// </summary>
        /// <param name="flag"></param>
        void SetTrackBarFlg(bool flag)
        {
            try
            {
                if (this.decode_pro.InvokeRequired)
                {
                    SetTrackBarState d = new SetTrackBarState(SetTrackBarFlg);
                    this.Invoke(d, new object[] { flag });
                }
                else
                {
                    this.decode_pro.Visible = flag;
                }
            }
            catch { };
        }

        /// <summary>
        /// 加载网络图像
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void LOAD_FROM_URL_Click(object sender, EventArgs e)
        {
            int index = rd.Next(0, urls.Count - 1);
            //img_show.LoadAsync(urls[0]);//异步
            img_show.Load(urls[index]);//同步
            //img_show.Image.Save("D:\\1122\\22.png");
        }

        void LoadNetUrl(string urlfiel,ref List<string> urls)
        {
            using (FileStream fs = new FileStream(urlfiel, FileMode.Open))
            {
                using (StreamReader sw = new StreamReader(fs, Encoding.Default))
                {
                    while (!sw.EndOfStream)
                    {
                        string lineInfo = sw.ReadLine();
                        urls.Add(lineInfo);
                    }
                }
            }
        }
    }
}
