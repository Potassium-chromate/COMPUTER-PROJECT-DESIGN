# 簡介
Wireshark 是一種廣泛認可和使用的開源封包分析器。它允許用戶捕獲和互動式瀏覽電腦網路上運行的流量。以下是對 Wireshark 主要功能的詳細介紹：
* **即時資料擷取：** Wireshark 可以從各種網路介面擷取即時資料包資料。
* **過濾：** 用戶可以過濾捕獲的數據，以將視野範圍縮小到感興趣的特定資料包。
* **顏色分類：** 為了更輕鬆地分析，Wireshark 可以根據資料包的類型和狀態對資料包進行顏色分類。
*  **樣本資料:**
    + sha256: 0a3f63fe58f542939154ba9633ac7d2fc18dd5efba1649af729e2c84f0920dcc 
    + 64 bit 
    + elf 

# 使用步驟
* 首先先在 host kernel 上運行 wireshark 
![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/wireshark_setup_2.png)
* 接著在虛擬機中執行目標惡意程式
  
![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/wireshark_setup_1.png)
* 在上方的搜尋欄輸入 `ip.addr == 140.116.103.33` (可以換成任何想找的ip)

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/wireshark_setup_3.png)


# 分析
我們先前已經透過IDA Pro分析出了整個病毒大致的運作流程，藉由以下的動態分析來觀察其行為是否與靜態分析的結果相同

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_1_dyn_analysis.png)

1. 在第一次允許資料傳輸中，它向`45.56.96.91`（攻擊者IP）發送了訊息，並使用了TCP的SACK選項。
2. 第二行是因第一次傳輸失敗而進行的重傳。
3. 第三和第四行是攻擊者對前兩次傳輸的反應。
4. 然後14到19行是攻擊者的傳輸，它發送了建立與TLSv1.2（加密）連接所需的數據，並持續重傳成功為止。

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2_dyn_analysis.png)

1. 當成功發送「應用資料」後，受感染的裝置會傳送「Client Hello」（開始建立連接，47行），它會不斷重傳直到伺服器回應連接（編號53行）。
2. 當進行 handshake 時，連線便成功建立了（編號56行）。


# 細節分析
## initConnection()
對著原本 pseudocode 中的`initConnection()`點兩下，即可看到該子程式的 pseudocode 

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/initConnection_%E7%B4%B0%E7%AF%80.png)
此時可一窺其運作細節，此時可看到其中有個名為commServer的可疑數組

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/commServer_%E7%B4%B0%E7%AF%80.png)

可以發現攻擊者的ip是 `45.56.96.91:23`
在之後的動態分析中，我們能從 wireshark 中看到該惡意程式確實訪問了`45.56.96.91:23`，甚至還能觀察到訪問其他ip地址





