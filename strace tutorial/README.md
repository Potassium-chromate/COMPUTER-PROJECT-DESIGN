假設我們已經將所有樣本的elf檔放到同一個資料夾底下，之後可以利用以下腳本將讀取所有樣本的動態特徵。

```
#!/bin/bash

read -p "Enter the file_dir: " f_dir
read -p "Enter the report_dir: " r_dir

num_files=$(ls -1q "$f_dir" | wc -l)
echo "There are $num_files files in the directory."

echo "Starting in 3 seconds..."
sleep 3

for file in $f_dir/*
do
  s
  
  if [ -f "$file" ]; then
    filename=$(basename -- "$file")
    echo "Tracing $file"
    chmod +x "$file"
    
    timeout --kill-after=5s 15s strace -f -o "${r_dir}/${filename}_report.txt" "$file" || echo "Tracing $file took too long and was terminated"
  fi
  
done


```
`Enter the file_dir`填入樣本的elf檔的資料夾。
`Enter the report_dir` 填入樣本分析報告的資料夾。
![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/strace.png)

每個樣本的分析結果會下圖
![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/strace_report.png)

之後再想辦法用python從一千多個txt檔中把動態特徵取出
