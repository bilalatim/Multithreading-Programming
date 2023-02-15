Main: Thread0 Thread5 Thread10 Thread_opt
Thread0:
		g++ thread0.cpp -o thread0
Thread5:
		g++ thread5.cpp -o thread5 -pthread 
Thread10: 
		g++ thread10.cpp -o thread10 -pthread 
Thread_opt:
		g++ thread_opt.cpp -o thread_opt -pthread
