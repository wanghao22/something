using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NAudio.CoreAudioApi;
using System.Threading;
using NAudio.Wave;
using System.IO;

namespace CSMusic
{
    public partial class Form1 : Form
    {
        delegate void SetTrackBarCallback(int val);
        delegate void SetTextCallback(string str);
        delegate int GetTrackBarCallback();
        WaveOut waveOutDevice;
        AudioFileReader mp3;
        bool play_flag = false;
        bool pause_flag = false;
        bool trackbar_flag = true;
        BackgroundWorker bkwork;
        List<string> fullName;
        List<string> name;
        int select;
        Random rng;
        PlayState play_state;
        List<int> hostry;
        /// <summary>
        /// 初始化
        /// </summary>
        public Form1()
        {
            InitializeComponent();
            waveOutDevice = new WaveOut();
            //LoadFormTxt();
            Music_Voice.SetRange(0, 100);
            Music_Length.SetRange(0, 100);
            Music_Voice.Value = 50;
            waveOutDevice.Volume = 0.5f;
            play_flag = false;
            //初始化背后事件
            this.bkwork = new BackgroundWorker();
            this.bkwork.WorkerSupportsCancellation = true;
            this.bkwork.DoWork += BgWorker1_DoWork;
            fullName = new List<string>();
            name = new List<string>();
            rng = new Random();
            CB_Play_State.SelectedIndex = 1;
            //play_state = PlayState.random_play;
            LoadAllMusic(Music_Dir.Text);
            hostry = new List<int>();
        }

        /// <summary>
        /// 播放按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Bt_Play_Click(object sender, EventArgs e)
        {
            try
            {
                select = Music_list.SelectedIndex;
                PlayMusic(select);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        
        /// <summary>
        /// 结束播放
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Music_Add_Click(object sender, EventArgs e)
        {
            pause_flag = true;
            if (play_flag)
            {
                waveOutDevice.Stop();
                waveOutDevice.Dispose();
                waveOutDevice = new WaveOut();
            }
            play_flag = false;
            Music_Length_End.Text = "00:00:00";
        }

        /// <summary>
        /// 调节音量
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Music_Voice_Scroll(object sender, EventArgs e)
        {
            waveOutDevice.Volume = (float)Music_Voice.Value / 100f;
        }

        /// <summary>
        /// 双击播放音乐
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Music_list_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            try
            {
                select = Music_list.SelectedIndex;
                PlayMusic(select);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        /// <summary>
        /// 播放音乐主函数
        /// </summary>
        /// <param name="filename"></param>
        private void PlayMusic(string filename)
        {
            pause_flag = false;
            if (play_flag)
            {
                waveOutDevice.Stop();
                waveOutDevice.Dispose();
                waveOutDevice = new WaveOut();
                play_flag = false;
            }
            mp3 = null;
            GC.Collect();
            GC.WaitForPendingFinalizers();
            mp3 = new AudioFileReader(filename);
            //Music_Length_End.Text = GetStringFromTimeSpan(mp3.TotalTime);
            SetEndTime(GetStringFromTimeSpan(mp3.TotalTime));
            waveOutDevice.Init(mp3);
            waveOutDevice.Play();
            play_flag = true;
            if (!this.bkwork.IsBusy)
                bkwork.RunWorkerAsync();
        }
        private void PlayMusic(int index)
        {
            if (index < 0 || index > fullName.Count)
                return;
            string file = fullName[index];
            SetPlayNow(name[index]);
            PlayMusic(file);
            this.hostry.Add(index);
        }

        /// <summary>
        /// 当鼠标在音乐滑块处弹起时的操作
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Music_Length_MouseUp(object sender, MouseEventArgs e)
        {
            if (play_flag)
            {
                var val = Music_Length.Value;
                var count = mp3.TotalTime.TotalSeconds;
                var maxl = (int)count * val / 100;
                int hour = maxl / (60 * 60);
                maxl = maxl % (60 * 60);
                int mint = maxl / 60;
                int sec = maxl % 60;
                TimeSpan pan = new TimeSpan(hour, mint, sec);
                mp3.CurrentTime = pan;
                trackbar_flag = true;
            }
        }

        /// <summary>
        /// 把int类型转为对应位数的string
        /// </summary>
        /// <param name="val"></param>
        /// <param name="zoom"></param>
        /// <returns></returns>
        private string Int2String(int val,int zoom)
        {
            string val_s = Convert.ToString(val);
            if (val_s.Length == zoom)
                return val_s;
            else if (val_s.Length > zoom)
                throw new OverflowException();
            else
            {
                string result = "";
                for (int i = 0; i < zoom - val_s.Length; i++)
                    result += "0";
                result += val_s;
                return result;
            }
            throw new Exception("Unkown Error!");
        }
        
        /// <summary>
        /// 背后事件（线程）的工作
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BgWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            while (play_flag)
            {
                while (!pause_flag)
                {
                    if (trackbar_flag)
                    {
                        TimeSpan tc = mp3.CurrentTime;
                        var t = (int)tc.TotalSeconds;
                        var t1 = (int)mp3.TotalTime.TotalSeconds;
                        if (t == t1)
                        {
                            play_flag = false;
                            PlayNext(play_state);
                        }
                        var val = 100 * t / t1;
                        SetTrackBar(val);
                        SetText(GetStringFromTimeSpan(tc));
                    }
                    else
                    {
                        var val = this.GetTraackBar();
                        var count = mp3.TotalTime.TotalSeconds;
                        var maxl = (int)count * val / 100;
                        int hour = maxl / (60 * 60);
                        maxl = maxl % (60 * 60);
                        int mint = maxl / 60;
                        int sec = maxl % 60;
                        TimeSpan pan = new TimeSpan(hour, mint, sec);
                        SetText(GetStringFromTimeSpan(pan));
                    }
                }
                Thread.Sleep(20);
            }
            SetText("00:00:00");
            SetTrackBar(0);
        }

        /// <summary>
        /// 异步设置滑块的值
        /// </summary>
        /// <param name="val"></param>
        private void SetTrackBar(int val)
        {
            try
            {
                if (this.Music_Length.InvokeRequired)
                {

                    //Music_LengthCallback d = new Music_LengthCallback(SetTrackBar);
                    SetTrackBarCallback d = new SetTrackBarCallback(SetTrackBar);
                    this.Invoke(d, new object[] { val });
                }
                else
                {
                    this.Music_Length.Value = val;
                }
            }
            catch{ };
        }

        /// <summary>
        /// 异步获取滑块的值
        /// </summary>
        /// <returns></returns>
        private int GetTraackBar()
        {
            try
            {
                if (this.Music_Length.InvokeRequired)
                {

                    //Music_LengthCallback d = new Music_LengthCallback(SetTrackBar);
                    GetTrackBarCallback d = new GetTrackBarCallback(GetTraackBar);
                    int result = (int)this.Invoke(d);
                    return result;
                }
                else
                {
                    return this.Music_Length.Value;
                }
            }
            catch { };
            return -1;
        }

        /// <summary>
        /// 异步设置当前时间控件
        /// </summary>
        /// <param name="str"></param>
        private void SetText(string str)
        {
            try
            {
                if (this.Music_Length.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(SetText);
                    this.Invoke(d, new object[] { str });
                }
                else
                {
                    this.Music_Length_Start.Text = str;
                }
            }
            catch { };
        }

        /// <summary>
        /// 异步设置当前选择的项
        /// </summary>
        /// <param name="val"></param>
        private void SetSelectIndex(int val)
        {
            try
            {
                if (this.Music_Length.InvokeRequired)
                {

                    //Music_LengthCallback d = new Music_LengthCallback(SetTrackBar);
                    SetTrackBarCallback d = new SetTrackBarCallback(SetSelectIndex);
                    this.Invoke(d, new object[] { val });
                }
                else
                {
                    this.Music_list.SelectedIndex = val;
                }
            }
            catch { };
        }

        /// <summary>
        /// 异步设置结束时间
        /// </summary>
        /// <param name="str"></param>
        private void SetEndTime(string str)
        {
            try
            {
                if (this.Music_Length.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(SetEndTime);
                    this.Invoke(d, new object[] { str });
                }
                else
                {
                    this.Music_Length_End.Text = str;
                }
            }
            catch { };
        }

        /// <summary>
        /// 设置显示当前播放的音乐名称
        /// </summary>
        /// <param name="str"></param>
        private void SetPlayNow(string str)
        {
            try
            {
                if (this.Music_Length.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(SetPlayNow);
                    this.Invoke(d, new object[] { str });
                }
                else
                {
                    this.Music_Now.Text = str;
                }
            }
            catch { };
        }

        /// <summary>
        /// TimeSpan转为string
        /// </summary>
        /// <param name="d"></param>
        /// <returns></returns>
        private string GetStringFromTimeSpan(TimeSpan d)
        {
            int maxl = (int)d.TotalSeconds;
            int hour = maxl / (60 * 60);
            maxl = maxl % (60 * 60);
            int mint = maxl / 60;
            int sec = maxl % 60;
            string str = Int2String(hour, 2) + ":" +
                Int2String(mint, 2) + ":" + Int2String(sec, 2);
            return str;
        }
        
        /// <summary>
        /// 窗口关闭时所执行的操作
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult result = MessageBox.Show("确认退出吗?", "操作提示", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            if (result == DialogResult.OK)
            {
                play_flag = false;
                //Application.Exit();
                e.Cancel = false;
            }
            else
            {
                e.Cancel = true;
            }
            //play_flag = false;
        }

        /// <summary>
        /// 当鼠标在音乐滑块处按下时的操作
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Music_Length_MouseDown(object sender, MouseEventArgs e)
        {
            trackbar_flag = false;
        }

        /// <summary>
        /// 在指定的文件夹中搜索mp3文件
        /// </summary>
        /// <param name="folder"></param>
        /// <param name="result"></param>
        private void SerchMP3InFolder(string folder, ref List<string> result)
        {
            try
            {
                //在指定目录及子目录下查找文件,在list中列出子目录及文件
                DirectoryInfo Dir = new DirectoryInfo(folder);
                DirectoryInfo[] DirSub = Dir.GetDirectories();
                if (DirSub.Length <= 0)
                {
                    foreach (FileInfo f in Dir.GetFiles("*.mp3", SearchOption.TopDirectoryOnly)) //查找文件
                    {
                        //listBox1.Items.Add(Dir+f.ToString()); //listBox1中填加文件名
                        result.Add(Dir + @"\" + f.ToString());
                    }
                }
                int t = 1;
                foreach (DirectoryInfo d in DirSub)//查找子目录 
                {
                    SerchMP3InFolder(Dir + @"\" + d.ToString(), ref result);
                    //result.Add(Dir + @"\" + d.ToString());
                    if (t == 1)
                    {
                        foreach (FileInfo f in Dir.GetFiles("*.mp3", SearchOption.TopDirectoryOnly)) //查找文件
                        {
                            result.Add(Dir + @"\" + f.ToString());
                        }
                        t = t + 1;
                    }
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        /// <summary>
        /// 暂停按钮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Music_Pause_Click(object sender, EventArgs e)
        {
            if (play_flag)
            {
                pause_flag = !pause_flag;
                if (pause_flag)
                    waveOutDevice.Pause();
                else
                    waveOutDevice.Resume();
            }
        }

        /// <summary>
        /// 加载所有音乐文件
        /// </summary>
        /// <param name="folder"></param>
        private void LoadAllMusic(string folder)
        {
            fullName.Clear();
            name.Clear();
            SerchMP3InFolder(folder, ref fullName);
            for (int i = 0; i < fullName.Count; i++)
                name.Add(Path.GetFileNameWithoutExtension(fullName[i]));
            Music_list.Items.Clear();
            for (int i = 0; i < name.Count; i++)
                Music_list.Items.Add(name[i]);
        }

        /// <summary>
        /// 播放下一个
        /// </summary>
        /// <param name="state"></param>
        private void PlayNext(PlayState state)
        {
            switch(state)
            {
                case(PlayState.order_play):
                    select++;
                    if (select == fullName.Count)
                    {
                        select--;
                        return;
                    }
                    //var willplay = fullName[select];
                    SetSelectIndex(select);
                    PlayMusic(select);
                    break;
                case (PlayState.random_play):
                    select = rng.Next(0,fullName.Count);
                    //var willplay2 = fullName[select];
                    SetSelectIndex(select);
                    PlayMusic(select);
                    break;
                case (PlayState.repet_play):
                    //var willplay3 = fullName[select];
                    PlayMusic(select);
                    break;
                case (PlayState.loop_play):
                    select++;
                    if (select == fullName.Count)
                        select = 0;
                    //var willplay1 = fullName[select];
                    SetSelectIndex(select);
                    PlayMusic(select);
                    break;
                default:
                    break;
            }
        }

        /// <summary>
        /// 设置播放顺序
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CB_Play_State_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch(CB_Play_State.SelectedIndex)
            {
                case 0:
                    play_state = PlayState.order_play;
                    break;
                case 1:
                    play_state = PlayState.random_play;
                    break;
                case 2:
                    play_state = PlayState.repet_play;
                    break;
                case 3:
                    play_state = PlayState.random_play;
                    break;
                default:
                    break;
            }
        }

        /// <summary>
        /// 播放下一个
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Next_one_Click(object sender, EventArgs e)
        {
            PlayNext(play_state);
        }

        private void Last_one_Click(object sender, EventArgs e)
        {
            var last = hostry.Count;
            if (last < 2)
                return;
            select = hostry[last - 2];
            hostry.Remove(last - 1);
            hostry.Remove(last - 2);
            if (select < 0 || select > fullName.Count)
                return;
            string file = fullName[select];
            SetPlayNow(name[select]);
            PlayMusic(file);
        }

        private void Select_Music_Dir_Click(object sender, EventArgs e)
        {
            var dlg = new FolderBrowserDialog();
            dlg.Description = "请选择音乐文件夹";
            if(dlg.ShowDialog()==DialogResult.OK)
            {
                Music_Dir.Text = dlg.SelectedPath;
            }
            LoadAllMusic(Music_Dir.Text);
        }
    }

    enum PlayState
    {
        order_play,
        random_play,
        repet_play,
        loop_play
    }
}
