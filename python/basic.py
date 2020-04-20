import threading
import time
def basic(name):
	print(name)

thread_1 = threading.Thread(None,basic,"t1",args = ("thread_1",))
thread_2 = threading.Thread(None,basic,"t2", args = ("thread_2",))
thread_1.start()
time.sleep(2)

thread_2.start()
