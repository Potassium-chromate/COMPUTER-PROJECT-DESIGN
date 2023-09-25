# 簡介
在上一篇介紹了 example_1 的動態分析，這次我們一樣是用 wireshark 來做分析
*  **樣本資料:**
    + sha256: 0b2a20aa35ad78f835614ae31a25b50c646aeb7bc7df3699b9b0d7c235cb8a22
    + 64 bit 
    + elf 



# 分析
再先前的靜態分析中，我們已經看到攻擊者的 ip 為 `37.49.230.128` ，引此這次我們直接搜尋 `37.49.230.128`。
可以看到圖中不停出現`[TCP Retransmission] 55000 -> 9834`，當發送方在特定時間範圍內沒有收到其發送的資料包的確認 (ACK) 時，通常會發生這種情況，導致發送方認為資料包可能在傳輸過程中遺失。

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2_dyn_analysis_2.png)

`9834 -> 55008 [RST, ACK] Seq=1 Ack=1 Win=64240 Len=0`代表 TCP 封包從通訊埠9834發送到另一個通訊埠55008，並設定了RST（重設）和ACK（確認）信號。

其中:
- **RST（重置）：** 此信號用於重置連接。
- **ACK（確認）：** 此信號用於確認資料包的接收。
- **len = 0 :** 發送者沒有要傳送的 payload ，但需要通知另一方某件事，例如成功接收數據，或連接失敗。

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2_dyn_analysis_3.png)

可以看到在收到 RST 訊號之後，我們的通訊埠確實改變了 (55000 變成 45400)

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2_dyn_analysis_4.png)

在接下來數以千計的數據傳輸中，他一直重複上述的步驟，不斷重新連接。

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2_dyn_analysis_1.png)

最後，值得一提的是，在瀏覽整個Wireshark檔案時，我們發現攻擊者似乎也利用了`34.160.144.191`和`35.201.103.21`進行攻擊。而且，這兩個IP地址發出的封包是一模一樣的。我們目前的推測是，這可能是攻擊者在被發現後，為了確保能夠繼續保持連線而採取的策略。

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2_dyn_analysis_5.png)

# 結論
惡意軟體經常出於各種原因嘗試與遠端伺服器建立連接，例如接收命令、竊取資料或下載額外的有效負載。如果惡意軟體連續發送`[RST, ACK]`資料包，我們猜測可能是遇到以下幾種情況：

1. **連線被阻止：** 
    惡意軟體的連線嘗試可能會被防火牆、入侵防禦系統 (IPS) 或某些其他安全機制阻止，從而導致連線重複重置時出現連續的資料包`[RST, ACK]`。
   
3. **Non-Responsive Server：**
    惡意軟體嘗試連接的伺服器可能未按預期回應，有可能該伺服器被查水表而導致關閉。
   
5. **躲避策略 :**
    病毒可能會檢測到它處於一個可能受到監控的虛擬機或沙盒環境中，因此它可能無法發動攻擊。因此，連續生成的[RST, ACK]封包可能是這種規避策略的一部分。
