# 基本資料
- ([論文原文](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/dissertation%20implement/thesis-2023-02-03-chh-ykc-0938.pdf))
- 論文作者: 黃志翔 
- 指導教授: 張燕光
- 日期: 2023/01

# 摘要 
本文介紹了一種基於機器學習和深度學習的方法來偵測物聯網殭屍網路散佈的惡意軟體。作者使用了三種方法來訓練模型，分別是動態分析、靜態分析和圖像分析。在動態分析中，作者使用了Cuckoo Sandbox來模擬惡意軟體的執行環境，並使用Python腳本來提取特徵值。在靜態分析中，作者使用了Linux內建的指令分析可執行可鏈接文件，並使用Python腳本將所有特徵值整理成一個CSV檔案。在圖像分析中，作者將可執行可鏈接文件轉換成二維灰階圖片，並使用深度學習進行分析。在本文中，作者使用了多種機器學習和深度學習模型，包括K-最近鄰算法、決策樹、隨機森林、支持向量機、多層感知器等。

# 訓練方法
1. 資料蒐集:
   - ELF 檔案總數：4804
   - 良性：1551（來自 Ubuntu 20.04 作業系統的 /bin 和 /sbin 目錄）
   - 惡意：3253 個（2778 個來自 VirusTotal 和 475 個 Linux 惡意軟體檔案）
   - 有問題的文件：46 個物聯網殭屍網路文件

2. 特徵提取：
   - 靜態特徵：ELF 檔案的特徵，如program headers的數量、section headers的數量、檔案大小等。
   - 系統呼叫特徵：系統呼叫如execve、read、write等，是程式向作業系統請求的操作

3. 機器學習模型：
   - 決策樹、邏輯迴歸、隨機森林、高斯樸素貝葉斯、SVM、KNN。
   - 此外，ELF 檔案被轉換為灰階影像以供 CNN 分析。

4. 實驗設置：
   - 訓練集：70%（3330個文件）
   - 測試集：30%（1428 個檔案）
   - 使用如以下表格中的27個特徵作為機器學習的輸入，進行迴歸分析的訓練

| execve| read | close | ... | Size of .data Section |
| ---- | ---- |---- |---- |---- |
| 2| 8 | 13 | ... | 1 |

5. 結果
   - 論文
![image](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/%E8%AB%96%E6%96%87%E7%B5%90%E6%9E%9C.png)
   - 實作
