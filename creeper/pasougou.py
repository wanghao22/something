import requests
import json
import urllib
import os

def getSogouImag(category,tag,length,path):
    n = length
    cate = category
    imgs = requests.get('http://pic.sogou.com/pics/channel/getAllRecomPicByTag.jsp?category='+cate+'&tag='+tag+'&start=0&len='+str(n)+'&width=1920&height=1080')
    jd = json.loads(imgs.text)
    jd = jd['all_items']
    imgs_url = []
    for j in jd:
        ori = j['ori_pic_url']
        if ori is None:
            imgs_url.append(j['bthumbUrl'])
        else:
            imgs_url.append(ori)
    m = 1
    tmp = m
    txt = open("url.txt","w");
    for img_url in imgs_url:
            while True:
                full_path = path+str(tmp)+'.jpg'
                if not os.path.exists(full_path):
                    break
                tmp+=1
            txt.write(img_url)
            txt.write("\n")
            print('***** '+str(tmp)+'.jpg *****'+'   Downloading...')
            urllib.request.urlretrieve(img_url,full_path)
            m = m + 1
            if m>length:
                break
    txt.close();
    print('Download complete!',m-1,'Files')

if __name__=='__main__':
    word = input('请输入检索信息：')
    if word:
        pass
    else:
        word = '游戏'
    getSogouImag('壁纸',word,50,'d:/download/壁纸/')