import os
import sys
import requests
client_id = "6GeC8cV4tsgfm3BvrI6Q"
client_secret = "jKbayzSuQ9"
url = "https://openapi.naver.com/v1/vision/face"
files = {'image': open('go3.png', 'rb')}
headers = {'X-Naver-Client-Id': client_id, 'X-Naver-Client-Secret': client_secret }
response = requests.post(url,  files=files, headers=headers)
rescode = response.status_code

if(rescode==200):
    print (response.text)
else:
    print("Error Code:" + rescode)