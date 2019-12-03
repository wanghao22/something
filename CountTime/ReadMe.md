# CountTime

> how to use thread.

1. AfxBeginThread()

* > Start the thread.
  >
  > `CWinThread* m_thred_countdown = AfxBeginThread(CountThread2_, this);`

2. CreateThread()

* > Start the thread.
  >
  > ```c++
  > DWORD m_thred_count_dw;
  > HANDLE m_thred_count = ::CreateThread(NULL, 0, CountThread__, (LPVOID)this, 0, &m_thred_count_dw);
  > ```

3. TerminateThread()

* > End the Thread.
  >
  > ``` c++
  > TerminateThread(m_thred_countdown->m_hThread, m_thred_countdown->m_nThreadID);
  > TerminateThread(m_thred_count, m_thred_count_dw);
  > ```
