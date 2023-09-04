### ObjectBus
C++ test task - Dev 2

ENG
Design and implement the ObjectsBus data bus based on the standard C++ library. By data, we mean C++ objects.
Requirements for the data bus:
- The data bus should be typed and support objects of one type.
- The data bus should be implemented as a circular buffer of finite size.
- The size (number of elements) should be set as an argument.
- The data bus should support multi-threaded writing.
- The data bus should support multi-threaded reading.
- Provide a class or method to write data (object) to the data bus.

Develop an auxiliary class for reading data from the data bus, which should contain the following methods:
StartReading - performs a search for the last added item in the data bus.
ReadNext - reads the next item. The method returns the next item if it has already been added. The method waits for a new item to be added if all previous items have already been read. The method throws an exception if the reading is too slow, and the reading lags behind the writing process for more than the size of the data bus.
StopReading - stops reading new data. Calling this method should interrupt any waiting in the ReadNext method.
Choose the names of interfaces, classes, and functions at your discretion.
