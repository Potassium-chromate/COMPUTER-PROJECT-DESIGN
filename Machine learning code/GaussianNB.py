# -*- coding: utf-8 -*-
"""
Created on Sat Jul  8 14:08:10 2023

@author: Eason
"""

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn import metrics
import openpyxl
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import confusion_matrix
from sklearn.metrics import roc_curve, auc


def openxl(loc): 
    workbook = openpyxl.load_workbook(loc)
    sheet = workbook.worksheets[0]
    
    sheet_list = [row for row in sheet.values]
    
    return pd.DataFrame([row[1:] for row in sheet_list[1:]], columns=sheet_list[0][1:])

sbin_loc = "C:/Users/88696/Desktop/四上課程/資專/xlsx file/sbin_report.xlsx"
bin_loc = "C:/Users/88696/Desktop/四上課程/資專/xlsx file/bin_report.xlsx"
linux_loc = "C:/Users/88696/Desktop/四上課程/資專/xlsx file/linux_report.xlsx"
MalwareBazaar_loc = "C:/Users/88696/Desktop/四上課程/資專/xlsx file/MalwareBazaar_report.xlsx"

sbin_sheet = openxl(sbin_loc)
bin_sheet = openxl(bin_loc)
linux_sheet = openxl(linux_loc)
MalwareBazaar_sheet = openxl(MalwareBazaar_loc)

X = bin_sheet.append(sbin_sheet)
X = X.append(linux_sheet)
X = X.append(MalwareBazaar_sheet)
X = X.astype(float)

label = [0 for i in range(len(sbin_sheet)+len(bin_sheet))]
temp = [1 for i in range(len(linux_sheet)+len(MalwareBazaar_sheet))]
label.extend(temp)

data = {'Is_Malware':label}
y = pd.DataFrame(label)
y = y.astype(float)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=1)

clf = GaussianNB()
clf = clf.fit(X_train, y_train)

y_pred = clf.predict(X)
y_probs = clf.predict_proba(X_test)

# Compute ROC curve and ROC area for each class
fpr, tpr, _ = roc_curve(y_test, y_probs[:, 1])
roc_auc = auc(fpr, tpr)

print("Accuracy:", metrics.accuracy_score(y, y_pred))

# Create confusion matrix
cm = confusion_matrix(y, y_pred)

# Visualize the confusion matrix using seaborn
plt.figure(figsize=(10,7))
sns.heatmap(cm, annot=True, fmt='d')
plt.xlabel('Predicted')
plt.ylabel('Truth')
plt.title('Confusion Matrix')
plt.show()

# Plot the ROC curve
plt.figure()
lw = 2
plt.plot(fpr, tpr, color='darkorange', lw=lw, label='ROC curve (area = %0.2f)' % roc_auc)
plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.legend(loc="lower right")
plt.show()


