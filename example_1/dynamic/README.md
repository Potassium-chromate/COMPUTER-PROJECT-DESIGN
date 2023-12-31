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

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_1_dyn_analysis_1.png)

1. 在第一次允許資料傳輸中，它向`45.56.96.91`（攻擊者IP）發送了訊息，並使用了TCP的SACK選項。
2. 第二行是因第一次傳輸失敗而進行的重傳。
3. 第三和第四行是攻擊者對前兩次傳輸的反應。
4. 然後14到19行是攻擊者的傳輸，它發送了建立與TLSv1.2（加密）連接所需的數據，並持續重傳成功為止。


![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_1_dyn_analysis_2.png)

1. 當成功發送「應用資料」後，受感染的裝置會傳送「Client Hello」（開始建立連接，47行），它會不斷重傳直到伺服器回應連接（編號53行）。
2. 當進行 handshake 時，連線便成功地建立了（編號56行）。


![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_1_dyn_analysis_3.png)

1. 在第61行中，它會更改cipher spec（建立新的連線），這樣電腦就無法偵測到裝置中存在的異常連線。這種情況會在特定的時間周期內發生，以確保其隱藏性。


![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_1_dyn_analysis_4.png)

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_1_dyn_analysis_5.png)

1. 在接下來數以千計的數據傳輸中，它會不斷地從受感染的設備中提取數據，但由於這些數據已加密，所以我們無法查看。

# 結論
在完成動態與靜態分析後，可以發現，要獲得一個全面且深入的病毒分析結果，兩者的結合是不可或缺的。靜態分析讓我們深入了解病毒的內部結構和程式邏輯，但它的局限性在於無法完全捕捉到病毒在執行時的動態行為。例如，我們在靜態分析中難以發現病毒如何更改cipher spec。反之，若是僅依賴動態分析，我們可能會錯過病毒的整體架構和某些隱藏的功能。

不過，靜態分析的優勢在於它能夠提供一個宏觀的視角，讓我們初步識別出攻擊者的IP。這一資訊在後續的動態分析中，特別是使用wireshark時，變得尤為重要。當面對大量的網絡數據時，已知的攻擊者IP可以幫助我們迅速鎖定與病毒相關的網絡活動，從而更有效地追踪和分析其行為。總之，動態與靜態分析各有所長，但它們的結合能夠為我們提供一個全面且深入的病毒分析視角。


