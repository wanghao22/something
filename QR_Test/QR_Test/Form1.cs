using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using QRCoder;
using static QRCoder.PayloadGenerator;
using ThoughtWorks.QRCode;
using ThoughtWorks.QRCode.Codec;
using ThoughtWorks.QRCode.Codec.Data;
using OpenCvSharp;
using OpenCvSharp.Extensions;
using xdQR;

namespace QR_Test
{
    public partial class Form1 : Form
    {
        Bitmap QR;
        QR_Creat QRC = new QR_Creat();
        QR_Creat_Mat QRCM = new QR_Creat_Mat();
        public Form1()
        {
            InitializeComponent();
            QR_show.BackColor = Color.Black;
            img_type.SelectedIndex = 0;
            QR_class.SelectedIndex = 0;
        }
        

        /// <summary>
        /// 静态文字
        /// </summary>
        protected void QR_text()
        {
            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode("扫我干嘛？", QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(10);
            //Mat src = BitmapConverter.ToMat(QR);
            //Cv2.Resize(src, src, new OpenCvSharp.Size(300, 300));
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 网上链接
        /// </summary>
        protected void QR_url()
        {
            Url url = new Url("https://github.com/wanghao22");
            //string lol = "https://www.baidu.com";//也行
            string lol = url.ToString();
            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(lol, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4, Color.DarkRed, Color.PaleGreen, true);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// wifi
        /// </summary>
        protected void QR_wifi()
        {
            WiFi generator = new WiFi("Wifi_Name", "Wifi_Password", WiFi.Authentication.WPA);
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4, Color.Red, Color.Green, (Bitmap)Bitmap.FromFile("D:\\1122\\02\\NG\\1 (1).jpg"));
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 书签
        /// </summary>
        protected void QR_bookmark()
        {
            //Bookmark generator = new Bookmark("http://code-bude.net", "Blog of QRCoder's father");
            Bookmark generator = new Bookmark("http://www.baidu.com", "百度");
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 一次性验证码
        /// </summary>
        protected void QR_OneTimePassword()
        {
            OneTimePassword generator = new OneTimePassword()
            {
                Secret = "pwq6 5q55",
                Issuer = "Google",
                Label = "test@google.com",
            };
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 电话
        /// </summary>
        protected void QR_Phonenumber()
        {
            PhoneNumber generator = new PhoneNumber("18342963066");
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 邮箱
        /// </summary>
        protected void QR_Mail()
        {
            Mail generator = new Mail("wanghao@shsaimo.cn", "康康这个!", "这个邮件来自扫描二维码!",
                encoding:Mail.MailEncoding.MATMSG);
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(3);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 短信
        /// </summary>
        protected void QR_SMS()
        {
            SMS generator = new SMS("15001853310", "This message from QR!",encoding:SMS.SMSEncoding.SMSTO);
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// WhatsAppMessage
        /// </summary>
        protected void QR_WhatsAppMsg()
        {
            WhatsAppMessage generator = new WhatsAppMessage("你好约翰，你怎么看QR码？");
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 地理位置
        /// </summary>
        protected void QR_Geolocation()
        {
            //Geolocation generator = new Geolocation("51.26118", "6.6717");
            Geolocation generator = new Geolocation("30.6717", "121.26118");
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 联系人
        /// </summary>
        protected void QR_ContactData()
        {
            ContactData generator = new ContactData(ContactData.ContactOutputType.VCard3, 
                "浩", "王", mobilePhone: "13120659173",workPhone:"18342963066",phone:"13020110635",
                email:"wanghao@shsaimo.cn",birthday:new DateTime(1996,08,13));
            string payload = generator.ToString();
            
            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(3);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }
        
        /// <summary>
        /// 日历事件
        /// </summary>
        protected void QR_Calendarevents()
        {
            CalendarEvent generator = new CalendarEvent("生日", "参加QRcoder的第四年", "上海", 
                new DateTime(2019, 10, 13), new DateTime(2019, 10, 13), true);
            string payload = generator.ToString();

            QRCodeGenerator qrGenerator = new QRCodeGenerator();
            QRCodeData qrCodeData = qrGenerator.CreateQrCode(payload, QRCodeGenerator.ECCLevel.Q);
            QRCode qrCode = new QRCode(qrCodeData);
            QR = qrCode.GetGraphic(4);
            QR_show.Image = QR.GetThumbnailImage(300, 300, null, IntPtr.Zero);
        }

        private void QR_make_Click(object sender, EventArgs e)
        {
            switch (QR_class.SelectedIndex)
            {
                case 0:
                    //QR_text();
                    QR_show.Image = QRC.QR_text("想偷我票？\n没门！");
                    Mat temp = QRCM.QR_text("想偷我票？\n没门！");
                    Cv2.ImShow("QR", temp);
                    break;
                case 1:
                    QR_url();
                    //QR_show.Image = QRC.QR_url("www.baidu.com");
                    break;
                case 2:
                    QR_wifi();
                    break;
                case 3:
                    QR_bookmark();
                    break;
                case 4:
                    QR_OneTimePassword();
                    break;
                case 5:
                    QR_Phonenumber();
                    break;
                case 6:
                    QR_Mail();
                    break;
                case 7:
                    QR_SMS();
                    break;
                case 8:
                    QR_WhatsAppMsg();
                    break;
                case 9:
                    QR_Geolocation();
                    break;
                case 10:
                    QR_ContactData();
                    break;
                case 11:
                    QR_Calendarevents();
                    break;
                default:
                    break;
            }
        }

        private void QR_Save_Click(object sender, EventArgs e)
        {
            QR_Savepic(name:img_name.Text, img:QR_show.Image, path:"D:\\1122\\");
        }

        /// <summary>
        /// 返回二维码图片
        /// </summary>
        public Bitmap Encode(string text)
        {
            try
            {
                var qrCodeEncoder = new QRCodeEncoder();
                qrCodeEncoder.QRCodeVersion = 5;
                qrCodeEncoder.QRCodeEncodeMode = QRCodeEncoder.ENCODE_MODE.BYTE;
                qrCodeEncoder.QRCodeErrorCorrect = QRCodeEncoder.ERROR_CORRECTION.M;
                qrCodeEncoder.QRCodeScale = 4;
                return qrCodeEncoder.Encode(text);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return null;
            }
        }

        /// <summary>
        /// 返回二维码定义的字符串
        /// </summary>
        public string Decode(Bitmap image)
        {
            try
            {
                var qrCodeBitmapImage = new QRCodeBitmapImage(image);
                var qrCodeDecoder = new QRCodeDecoder();
                //qrCodeDecoder.decode(qrCodeBitmapImage, Encoding.ASCII);
                return qrCodeDecoder.decode(qrCodeBitmapImage, Encoding.UTF8);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return null;
            }
        }

        /// <summary>
        /// 返回二维码定义的字符串
        /// </summary>
        public string Decode(string path)
        {
            return Decode(new Bitmap(path));
        }

        private void QR_Decode_Click(object sender, EventArgs e)
        {
            if (QR_show.Image != null)
            {
                var temp = Decode(new Bitmap(QR_show.Image));
                if (temp != null)
                    MessageBox.Show(temp);
            }
            else
                MessageBox.Show("先生成图片！");
        }

        private void QR_Savepic(Image img, string name, string path = null)
        {
            string fullname;
            if (path == null)
                fullname = img_name.Text;
            else
                fullname = DirAddSubdir(path, name);
            if (name.Length < 1)
            {
                MessageBox.Show("请输入文件名");
                return;
            }
            if (img == null)
            {
                MessageBox.Show("图像为空");
                return;
            }
            string type = (string)img_type.SelectedItem;
            fullname = fullname + "." + type;
            //MessageBox.Show(fullname);
            try
            {
                img.Save(fullname);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                return;
            }
        }

        private string DirAddSubdir(string dir,string subdir)
        {
            int a = dir.LastIndexOf('\\');
            int b = dir.LastIndexOf('/');
            int c = Math.Max(a, b);
            if (c != dir.Length - 1)
                dir = dir + "\\" + subdir;
            else
                dir = dir + subdir;
            return dir;
        }
    }
}
