# -*- coding: utf-8 -*-
"""
Created on Sat Jul  8 14:08:10 2023

@author: Eason
"""

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
import openpyxl
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import confusion_matrix, precision_score, recall_score
from sklearn.metrics import roc_curve, auc


def openxl(loc): 
    workbook = openpyxl.load_workbook(loc)
    sheet = workbook.worksheets[0]
    
    sheet_list = [row for row in sheet.values]
    
    return pd.DataFrame([row[1:] for row in sheet_list[1:]], columns=sheet_list[0][1:])
def openxl1(loc): 
    workbook = openpyxl.load_workbook(loc)
    sheet = workbook.worksheets[0]
    
    # Read the sheet into a DataFrame without headers
    data = sheet.values
    data = list(data)
    
    # Convert to DataFrame
    df = pd.DataFrame(data)
    
    return df

shuffle_loc = 'C:/Users/88696/Desktop/shuffled_report.xlsx'
test_loc = 'C:/Users/88696/Desktop/課程/四上課程/資專/xlsx file/Main_dynamic_report.xlsx'
test = openxl(test_loc)


shuffle_sheet = openxl1(shuffle_loc)
idx = int(0.7*len(shuffle_sheet))
X_limit = -1
X = shuffle_sheet.iloc[:, :X_limit]
y = shuffle_sheet.iloc[:, -1]
X_train = shuffle_sheet.iloc[:idx, :X_limit]
y_train = shuffle_sheet.iloc[:idx, -1]
X_test = shuffle_sheet.iloc[idx+1:, :X_limit]
y_test = shuffle_sheet.iloc[idx+1:, -1]
if(X_limit == -1):
    test = test.iloc[:, :]
elif(X_limit == -3):
    test = test.iloc[:, :-2]

# Create Decision Tree Classifier
clf = KNeighborsClassifier(n_neighbors=3)


clf = clf.fit(X_train, y_train)


y_pred = clf.predict(X_test) #
y_probs = clf.predict_proba(X_test)

fpr, tpr, _ = roc_curve(y_test, y_probs[:, 1])
roc_auc = auc(fpr, tpr)

print("Accuracy:", metrics.accuracy_score(y_test, y_pred)) #
precision = precision_score(y_test, y_pred)
recall = recall_score(y_test, y_pred)
print("Precision:", precision)
print("Recall:", recall)

# Create confusion matrix
cm = confusion_matrix(y_test, y_pred) #

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

#test_pred = clf.predict(Test)


