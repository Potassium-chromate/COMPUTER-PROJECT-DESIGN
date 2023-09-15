# 簡介
MalwareBazaar 是一個收集和共享惡意軟件樣本的公共存儲庫。它的運作原理是，通過共享有關惡意軟件的知識，網絡安全社群可以更好地理解、預測和減輕威脅。用戶可以上傳、下載和分析樣​​本，使其成為世界各地研究人員和分析師的中心。而在本次中，我們從 MalwareBazaar 上下載1000樣本作為機器學習樣本的一部分。

![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/Malware_bazzar.png)

每個樣本都會有如下圖的資料

![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/Malware_bazzar_sample.png)

在下方的 **Intelligence** 中有各家防毒軟體對於該樣本的分析，有些甚至會給出關於該惡意程式的相關訊息

![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/Malware_bazzar_intelligence.png)


# 使用方式
MalwareBazaar 提供了 API 以提供使用者大量下載惡意程式的樣本，其使用方式如下:
1. **註冊帳戶：** 首先，您需要在 MalwareBazaar 的網站上註冊一個帳戶。完成註冊後，即可獲得一個 API 密鑰。
2. **API 請求樣本資料：** 使用 Python 或其他程式語言，發送 HTTP 請求到 MalwareBazaar 的 API，已獲得惡意程式的SHA256 digest。

```
import requests
import pandas as pd

tags = ['elf', '64']  # List of tags you want to query

results = []
df = pd.DataFrame(results)

for tag in tags:
    data = {
        'query': 'get_taginfo',
        'tag': tag,
        'limit': '1000'
    }

    response = requests.post('https://mb-api.abuse.ch/api/v1/', data=data)
    results.append(response.json())

df = pd.DataFrame(response.json()['data'])

df.to_excel("C:/Users/88696/Desktop/query_result.xlsx", index=False, header=True)
```
將獲得的 response 存進 Excel，可見其包含許多資訊如:sha256 digest 等等

![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/Malware_bazzar_sample_excel.png)

本次下載的樣本都是64位元的elf檔(詳見 ``tags = ['elf', '64']`` )

3. **API 下載樣本：** 把下載到的1000個樣本的sha256 digest存進 txt 檔中，最後在虛擬機中利用 Bash 腳本讀取該 txt 檔內的 digest 並大量下載樣本
```
#!/bin/bash

while read hash; do
    wget -O "$hash.zip" --post-data "query=get_file&sha256_hash=$hash" https://mb-api.abuse.ch/api/v1/
done < 1000_hashes.txt
```

