from urllib.parse import urlencode
import requests
import re
import os

save_dir='d:/download/壁纸/'
 
def  baidtu_uncomplie(url):
    res = ''
    c = ['_z2C$q', '_z&e3B', 'AzdH3F']
    d= {'w':'a', 'k':'b', 'v':'c', '1':'d', 'j':'e', 'u':'f', '2':'g', 'i':'h', 't':'i', '3':'j', 'h':'k', 's':'l', '4':'m', 'g':'n', '5':'o', 'r':'p', 'q':'q', '6':'r', 'f':'s', 'p':'t', '7':'u', 'e':'v', 'o':'w', '8':'1', 'd':'2', 'n':'3', '9':'4', 'c':'5', 'm':'6', '0':'7', 'b':'8', 'l':'9', 'a':'0', '_z2C$q':':', '_z&e3B':'.', 'AzdH3F':'/'}
    if(url==None or 'http' in url):
        #print(url)
        return url
    else:
        j= url
        for m in c:
            j=j.replace(m,d[m])
        for char in j:
            if re.match('^[a-w\d]+$',char):
                char = d[char]
            res= res+char
        #print(res)
        return res
 
def get_page(offset,search):
    params = {
        'tn': 'resultjson_com',
        'ipn': 'rj',
        'ct':'201326592',
        'is':'',
        'fp': 'result',
        'queryWord': search,
        'cl': '2',
        'lm': '-1',
        'ie': 'utf-8',
        'oe': 'utf-8',
        'adpicid':'',
        'st': '-1',
        'z':'',
        'ic': '0',
        'word': search,
        's':'',
        'se':'',
        'tab':'',
        'width':'',
        'height':'',
        'face': '0',
        'istype': '2',
        'qc':'',
        'nc': '1',
        'fr':'',
        'expermode':'',
        'pn': offset*30,
        'rn': '30',
        'gsm': '1e',
        '1537355234668':'',
    }
    url = 'https://image.baidu.com/search/acjson?' + urlencode(params)
    try:
        response = requests.get(url)
        if response.status_code == 200:
            return response.json()
    except requests.ConnectionError as e:
        print('Error', e.args)
 
def get_images(json,file):
    if json.get('data'):
        for item in json.get('data'):
            if item.get('fromPageTitle'):
                title = item.get('fromPageTitle')
            else:
                title='noTitle'
            url = baidtu_uncomplie(item.get('objURL'))
            if url is not None:
                file.write(url)
                file.write('\n')
            image = url
            if(image):
                yield {
                    'image': image,
                    'title': title
                }
 
def save_image(item,count,all_cnt):
    try:
        response = requests.get(item.get('image'))
        if response.status_code == 200:
            '''file_path = save_dir+'{0}.{1}'.format(str(count), 'jpg')
            if not os.path.exists(file_path):
                with open(file_path, 'wb') as f:
                    f.write(response.content)
                print(str(count)+'.jpg'+' 下载成功')
            else:
                print('Already Downloaded', file_path)'''
            while True:
            	file_path = save_dir+'{0}.{1}'.format(str(count), 'jpg')
            	if not os.path.exists(file_path):
            		break
            	count+=1
            with open(file_path, 'wb') as f:
                f.write(response.content)
            print(str(count)+'.jpg'+' 下载成功')
            all_cnt+=1
    except requests.ConnectionError:
        print('Failed to Save Image')
    return count,all_cnt
 
def main(pageIndex,count,max,file,keyword,all_cnt):
    json = get_page(pageIndex,keyword)
    for image in get_images(json,file):
        count,all_cnt = save_image(image, count,all_cnt)
        #print(count)
        count += 1
        if(all_cnt>MAX_COUNT):
            return -1,all_cnt
    return count,all_cnt

if __name__=='__main__':
    if not os.path.exists(save_dir):
        os.mkdir(save_dir)
    count=1
    all_count=1
    MAX_COUNT=200
    word = input('请输入检索信息：')
    if word:
        pass
    else:
        word = '猫'
    file = open("bdurl.txt","w")
    for i in range(1,20):
        count,all_count=main(i,count,MAX_COUNT,file,word,all_count)
        if(count<0):
            break
    file.close()
    print('total:',all_count-1)