首先，先下載limon sandbox
```
git clone https://github.com/.../limon_sandbox.git
```
之後到limon的資料夾應該會看到以下畫面
![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/limon.png)


之後可以利用以下腳本將讀取所有樣本的靜態特徵
```
#!/bin/bash

DIR="/home/eason/MalwareBazaar_Database/"
OUTPUT_DIR="/home/eason/analysis_results/"

mkdir -p "$OUTPUT_DIR"


for FILE in "$DIR"*
do

  BASENAME=$(basename "$FILE")
  

  FILE_OUTPUT_DIR="$OUTPUT_DIR$BASENAME"
  mkdir -p "$FILE_OUTPUT_DIR"

  
  OUTPUT_FILE="$FILE_OUTPUT_DIR/result.txt"

  # Use Limon to analyze the file and store the result in the output file
  echo "Analyzing file: $FILE" > "$OUTPUT_FILE"
  sudo python2 /home/eason/Limon/limon.py "$FILE" >> "$OUTPUT_FILE" 2>&1
  echo "Finished analyzing file: $FILE" >> "$OUTPUT_FILE"
done

```

輸出的每個會長這樣，而黃框內的部分就是我們所需的靜態特徵
![](https://github.com/Potassium-chromate/COMPUTER-PROJECT-DESIGN/blob/main/picture/static.png)
