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
     + 詳細結果: [結果](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/dissertation%20implement/senior%20project.pptx)
     + 不同模型之比較: ![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/%E4%B8%8D%E5%90%8C%E6%A8%A1%E5%9E%8B%E4%B9%8B%E6%AF%94%E8%BC%83%E7%B5%90%E6%9E%9C.png)

6. 原論文參考文獻
   -  Misha Mehra, Jay N. Paranjape and Vinay J. Ribeiro, “Improving ML Detection of 
IoT Botnets using Comprehensive Data and Feature Sets”, 2021 13th 
International Conference on Communication Systems & Networks (COMSNETS).

      介紹: 大致與原論文相同，利用 statistic/dynamic feature 來當作訓練資料，
      跟原論文的差別在於其並未用多種不同的機器學習演算法

   -  J. Margolis, T. T. Oh, S. Jadhav, Y. H. Kim, and J. N. Kim, “An in-depth analysis of the 
mirai botnet,” in 2017 International Conference on Software Security and 
Assurance (ICSSA), Altoona, Pennsylvania, USA, 2017, pp. 6–12

      介紹: 講解惡意軟體是如何利用系統調用，如: system()，fork()….來入侵系統。
      並解釋惡意軟體在每一個階段要做的事情

   - T. N. Phu, K. H. Dang, D. N. Quoc, N. T. Dai, and N. N. Binh, “A novel framework to 
classify malware in mips architecture-based iot devices,” Security and 
Communication Networks, 2019.

      介紹: 本文介紹 F-Sandbox 是一種專門用來分析 elf 檔的工具，並提及其包含
      四個部分(沙盒控制器、虛擬機、QEMU 監視器和 INetSim/PyNetSim 服務器)
      並仔細介紹從初始化到執行的每個步驟，最後還提到該框架支援多種機器學
      習算法來執行分類任務

   - H. Nguyen, Q. Ngo, and V. Le, “Iot botnet detection approach based on psi graph 
and dgcnn classifier,” in 2018 IEEE International Conference on Information 
Communication and Signal Processing (ICICSP). Singapore: IEEE, 2018, pp. 118–122

      介紹: 本文詳細闡述了物聯網殭屍網絡惡意軟件的特徵，並提出了一種新的
      檢測方法。其中包含，使用 IDA Pro 生成 CFG，並生成 PSI 圖。最後再把 PSI
      圖轉成 adjacency lists 並餵給 DGCNN 做分類。

   - Safa Rkhouya, Khalid Chougdali, “Malware Detection Using a Machine-Learning 
Based Approach,” in 2021 International Journal of Information Technology and 
Applied Sciences.. 

      介紹: 本文提到除了常見的 Signature-based malware detection 以外，還有其
      他檢測方法，概念基本上與原論文相同，也是提取了許多標頭特徵，再利用
      機器學習的相關演算法來分類，最後在將近 13 萬個文件中取得極高的準確
      率
