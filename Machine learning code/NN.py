# -*- coding: utf-8 -*-
"""
Created on Mon Jul 10 17:09:48 2023

@author: Eason
"""

import tensorflow as tf
from tensorflow.keras.layers import Dense, Input , Flatten, Dropout
from tensorflow.keras.callbacks import EarlyStopping, ReduceLROnPlateau
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn import metrics
import openpyxl
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.metrics import confusion_matrix,precision_score, recall_score
from sklearn.metrics import roc_curve, auc
import seaborn as sns

def build_generator(input_shape):
    inputs = Input(input_shape,name="input")

    
    c1 = Dense(64,activation='relu',name="layer_1")(inputs)
    c6 = Dropout(0.15)(c1)
    c7 = Dense(256,activation='relu',name="layer_2")(c6)
    c2 = Dense(128,activation='relu',name="layer_3")(c7)
    c3 = Dense(64,activation='relu',name="layer_4")(c2)
    c8 = Dropout(0.15)(c3)
    c4 = Dense(32,activation='relu',name="layer_5")(c8)
    c5 = Flatten()(c4)
    # Output layer
    outputs = Dense(2, activation='softmax',name="output")(c5)
    
    
    model = tf.keras.Model(inputs=[inputs], outputs=[outputs])
    
    model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=0.005, beta_1=0.6, clipnorm=0.01, epsilon=0.001), loss="binary_crossentropy", metrics=['accuracy'])
    model.summary()
    return model

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

def one_hot(arr,num_label):
    ret = []
    temp = [0 for i in range(num_label)]
    
    for i in range(len(arr)):
        temp[int(arr[i])] = 1
        ret.append(temp)
        temp = [0 for i in range(num_label)]
        
    return np.array(ret)

shuffle_loc = 'C:/Users/88696/Desktop/shuffled_report.xlsx'
test_loc = 'C:/Users/88696/Desktop/課程/四上課程/資專/xlsx file/Main_dynamic_report.xlsx'
test = openxl(test_loc)


shuffle_sheet = openxl1(shuffle_loc)
idx = int(0.7*len(shuffle_sheet))
X_limit = -3
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



X = np.array(X)
X = np.expand_dims(X,axis=2)
y = one_hot(np.array(y),2)

X_train = np.array(X_train)
X_train = np.expand_dims(X_train,axis=2)
y_train = one_hot(np.array(y_train),2)

X_test = np.array(X_test)
X_test = np.expand_dims(X_test,axis=2)
y_test = one_hot(np.array(y_test),2)

early_stopping = EarlyStopping(monitor='val_loss', patience=16, verbose=1)
reduce_lr = ReduceLROnPlateau(monitor='val_loss', factor=0.5, patience=3, verbose=1)
callbacks = [early_stopping, reduce_lr]



Agent = build_generator((np.shape(X)[1],1))
history = Agent.fit(X_train, y_train, epochs=50, batch_size=16, verbose=1, validation_data=(X_test, y_test), callbacks=callbacks)

# Plot training & validation accuracy values
plt.figure(figsize=(12, 4))
plt.subplot(1, 2, 1)
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('Model accuracy')
plt.ylabel('Accuracy')
plt.xlabel('Epoch')
plt.legend(['Train', 'Test'], loc='upper left')

# Plot training & validation loss values
plt.subplot(1, 2, 2)
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Model loss')
plt.ylabel('Loss')
plt.xlabel('Epoch')
plt.legend(['Train', 'Test'], loc='upper left')
plt.show()

# Compute confusion matrix
y_pred = Agent.predict(X_test)
y_pred = np.argmax(y_pred, axis=1)
y_test_label = np.argmax(y_test, axis=1)
cm = confusion_matrix(y_test_label, y_pred)

# Visualize the confusion matrix using seaborn
plt.figure(figsize=(10,7))
sns.heatmap(cm, annot=True, fmt='d')
plt.xlabel('Predicted')
plt.ylabel('Truth')
plt.title('Confusion Matrix')
plt.show()

# Compute the ROC curve
y_score = Agent.predict(X_test)[:, 1]
fpr, tpr, _ = roc_curve(y_test_label, y_score)
roc_auc = auc(fpr, tpr)

# Plot the ROC curve
plt.figure()
lw = 2
plt.plot(fpr, tpr, color='darkorange', lw=lw, label='ROC curve (area = %0.2f)' % roc_auc)
plt.plot([0, 1], [0, 1], color='navy', lw=lw, linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('Receiver Operating Characteristic')
plt.legend(loc="lower right")
plt.show()

