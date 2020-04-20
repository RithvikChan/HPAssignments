# -*- coding: utf-8 -*-
"""Untitled1.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1sNzoyFzuyHsVH99cMMFqlHAEd4d9pRBi
"""

import threading
import random
balance = 1000
minbalance = 100
def deposit(amount, lock):
  global balance
  lock.acquire()
  print("Depositing", amount)
  balance += amount
  print("TOTAL:", balance)
  lock.release()

def withdraw(amount, lock):
  global balance
  lock.acquire()
  if(balance - amount > minbalance):
    print("Withdrawing", amount)
    balance -= amount
    print("TOTAL:", balance)
  lock.release()

lock = threading.Lock()
t1 = threading.Thread(target = deposit, args = (random.randint(100,1000),lock,))
t2 = threading.Thread(target = deposit, args = (random.randint(100,1000),lock,))
t3 = threading.Thread(target = withdraw, args = (random.randint(100,1000),lock,))
t4 = threading.Thread(target = deposit, args = (random.randint(100,1000),lock,))
t5 = threading.Thread(target = withdraw, args = (random.randint(100,1000),lock,))
t6 = threading.Thread(target = deposit, args = (random.randint(100,1000),lock,))

t1.start()
t2.start()
t3.start()
t4.start()
t5.start()
t6.start()



