/*
 * https://twitter.com/wakwak_koba/
 */

#ifndef _WAKWAK_KOBA_SIMPLE_RINGBUFFER_HPP_
#define _WAKWAK_KOBA_SIMPLE_RINGBUFFER_HPP_

template <typename T>
class SimpleRingBuffer {
  public:
    SimpleRingBuffer(uint16_t _buffSize = 6000) : buffSize(_buffSize), writeMode(0), deallocateBuffer(true) {
      buffer = new T[buffSize];
      init();
    }

    SimpleRingBuffer(uint8_t *_buffer, uint16_t _buffSize) : buffSize(_buffSize), buffer(_buffer), writeMode(0), deallocateBuffer(false) {
      init();
    }

    ~SimpleRingBuffer() {
      if(deallocateBuffer)
        delete []buffer;
    }

    void init() {
      readPtr = 0;
      writePtr = 0;
    }
    
    uint16_t available() {
      if (readPtr > writePtr)
        return buffSize + writePtr - readPtr;
      else
        return            writePtr - readPtr;
    }

    uint16_t free() {
      return buffSize - available() - 1;
    }
    
    uint16_t write(T *payload, uint16_t length) {
      if (!payload || !length || length > buffSize) return 0;

      auto f = free();
      if (length > f) {
        if (writeMode == 2)
          readPtr = (readPtr + length - f) % buffSize;
        else {
          if (writeMode == 1)
            length = f;
          if (!length || !writeMode)
            return 0;
        }
      }

      auto bytesAvail = std::min(length, (uint16_t)(buffSize - writePtr));
      memcpy(&buffer[writePtr], &payload[0         ], sizeof(T) * bytesAvail);
      memcpy(&buffer[0       ], &payload[bytesAvail], sizeof(T) * (length - bytesAvail));
      writePtr = (writePtr + length) % buffSize;

      return length;
    }

    uint16_t read(T *data, uint16_t length) {
      if (!data || !length) return 0;

      length = std::min(length, available());
      auto bytesAvail = std::min(length, (uint16_t)(buffSize - readPtr));
      memcpy(&data[0         ], &buffer[readPtr], sizeof(T) * bytesAvail);
      memcpy(&data[bytesAvail], &buffer[0      ], sizeof(T) * (length - bytesAvail));
      readPtr = (readPtr + length) % buffSize;

      return length;
    }

  private:
    T *buffer;
    uint16_t buffSize;
    uint16_t readPtr;
    uint16_t writePtr;
    uint8_t writeMode;     // 空きが足りないときの挙動 0:writeしない 1:空きの分だけ 2:先頭を削除して強制挿入
    bool deallocateBuffer;
};

#endif
