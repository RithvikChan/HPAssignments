# -*- coding: utf-8 -*-
"""Untitled2.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1dOKPmWrb6hKZyz0nxMOwjS3jciFfNsSl
"""

import threading
import random
queue = []

def insert(data1, data2, lock):
    global queue
    lock.acquire() 
    queue.append((data1,data2)) 
    print("INSERTING", (data1,data2))
    print(queue)
    lock.release()
def delete(lock):
    global queue 
    lock.acquire()
    maxim = 0    
    for i in queue:
      if i[1] > maxim:
        toremove = i
        maxim = i[1]
    print("DELETING ITEM", toremove) 
    queue.remove(toremove) 
    lock.release()

lock = threading.Lock()
t1 = threading.Thread(target = insert, args = ("A",1,lock,))
t3 = threading.Thread(target = insert, args = ("B",2,lock,))
t2 = threading.Thread(target = delete, args = (lock,))
t4 = threading.Thread(target = insert, args = ("C",5,lock,))
t5 = threading.Thread(target = insert, args = ("D",3,lock,))
t6 = threading.Thread(target = delete, args = (lock,))
t1.start()
t2.start()
t3.start()
t4.start()
t5.start()
t6.start()

