import requests
import urllib
import json
import os


path = 'D:/1122/爬虫/Music/'
MAX_COUNT=200
word = input('请输入检索信息：')
if word:
    pass
else:
    word = '中华粘土娘'
res1 = requests.get('https://c.y.qq.com/soso/fcgi-bin/client_search_cp?&t=0&aggr=1&cr=1&catZhida=1&lossless=0&flag_qc=0&p=1&n='+str(MAX_COUNT)+'&w='+word)
jm1 = json.loads(res1.text.strip('callback()[]'))
jm1 = jm1['data']['song']['list']
mids = []
songmids = []
srcs = []
songnames = []
singers = []
for j in jm1:
    try:
        mids.append(j['media_mid'])
        songmids.append(j['songmid'])
        songnames.append(j['songname'])
        singers.append(j['singer'][0]['name'])
    except:
        print('wrong')

MAX_COUNT=min(len(mids),MAX_COUNT)
for n in range(0,MAX_COUNT):
    res2 = requests.get('https://c.y.qq.com/base/fcgi-bin/fcg_music_express_mobile3.fcg?&jsonpCallback=MusicJsonCallback&cid=205361747&songmid='+songmids[n]+'&filename=C400'+mids[n]+'.m4a&guid=6612300644')
    jm2 = json.loads(res2.text)
    vkey = jm2['data']['items'][0]['vkey']
    srcs.append('http://dl.stream.qqmusic.qq.com/C400'+mids[n]+'.m4a?vkey='+vkey+'&guid=6612300644&uin=0&fromtag=66')

x = len(srcs)
print("choose what to Download:")
nums = []
t = 0
step = 10
while t<x-1:
    for m in range(t,t+step):
        if(m<x):
            print(m,' '+songnames[m]+' - '+singers[m]+'.mp3')
    while True:
        op = input('input index:')
        if op == 'n' or op == 'N':
            t+=step
            break
        elif op == 'q' or op == 'Q':
            t = x+1
            break
        else:
            ccc = int(op)
            if ccc >=0 and ccc<=x-1:
                nums.append(ccc)
if len(nums) == 0:
    print("None")
else:
    print(nums)

print('For '+word+' Start download...')    
file=open('musicurl.txt','w')
count = 0
#for m in range(0,x):
for m in nums:
    print(str(m)+'***** '+songnames[m]+' - '+singers[m]+'.mp3 *****'+' Downloading...')
    try:
        full_path = path+songnames[m]+' - '+singers[m]+'.mp3'
        if os.path.exists(full_path):
            idx = 1
            while True:
                full_path = path+songnames[m]+' - '+singers[m]+str(idx)+'.mp3'
                if not os.path.exists(full_path):
                    break
                idx+=1
        file.write(srcs[m])
        file.write('\n')
        urllib.request.urlretrieve(srcs[m],full_path)
        count+=1
    except:
        print('Download wrong~')
file.close()
print('For ['+word+'] Download complete '+str(count)+'files !')