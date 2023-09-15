# 簡介
MalwareBazaar 是一個收集和共享惡意軟件樣本的公共存儲庫。它的運作原理是，通過共享有關惡意軟件的知識，網絡安全社區可以更好地理解、預測和減輕威脅。用戶可以上傳、下載和分析樣​​本，使其成為世界各地研究人員和分析師的中心。

![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/Malware_bazzar.png)

每個樣本都會有如下圖的資料
![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/Malware_bazzar_sample.png)


# 使用方式
MalwareBazaar 提供了 API 以提供使用者大量下載惡意程式的樣本，其使用方式如下:
1. **註冊帳戶：** 首先，您需要在 MalwareBazaar 的網站上註冊一個帳戶。完成註冊後，即可獲得一個 API 密鑰。
2. **API 請求：** 使用 Python 或其他程式語言，您可以發送 HTTP 請求到 MalwareBazaar 的 API。

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

本次下載的樣本都是64位元的elf檔(詳見 ``tags = ['elf', '64']`` )
