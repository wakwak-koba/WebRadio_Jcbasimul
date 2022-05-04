/*
 * https://twitter.com/wakwak_koba/
 */

#ifndef _WAKWAK_KOBA_AUDIOFILESOURCE_JCBASIMUL_HPP_
#define _WAKWAK_KOBA_AUDIOFILESOURCE_JCBASIMUL_HPP_

#include <HTTPClient.h>
#include <AudioFileSource.h>
#include <Arduino_JSON.h>
#include "SimpleRingBuffer.hpp"
#include "WebSocketsClientFn.hpp"

class AudioFileSourceWebSockets : public AudioFileSource {
  public:
    AudioFileSourceWebSockets(uint16_t _buffSize) : buffer(_buffSize) {
      Init();
    }
    
    AudioFileSourceWebSockets(uint8_t *_buffer, uint16_t _buffSize) : buffer(_buffer, _buffSize) {
      Init();
    }
    
    virtual bool close() override {
      wss.disconnect();
      return true;
    }

    virtual bool isOpen() override {
      return wss.isConnected();
    }

    virtual uint32_t getSize() override {
      return buffer.available();
    }

    virtual bool loop() override {
      wss.loop();
      return true;
    }

    virtual uint32_t read(void *data, uint32_t length) override {
      auto start = millis();
      while(buffer.available() < 1 && millis() - start < timeout)
        wss.loop();
      return readNonBlock((uint8_t *)data, length);
    }

    virtual uint32_t readNonBlock(void *data, uint32_t length) override {
      auto rLen = buffer.read((uint8_t *)data, length);
      if(length && rLen < length)
        cb.st(STATUS_TOO_SLOW, PSTR("receive is too slow.."));
      return rLen;
    }

    virtual void setTimeout(uint16_t _timeout) {
      timeout = _timeout;
    }
    
    enum { STATUS_TOO_SLOW=10 };
    
  protected:   
    virtual bool waitConnect() {
      if(wss.isConnected())
        return true;

//    cb.st(STATUS_CONNECTING, PSTR("Attempting to connect"));
      auto st = millis();
      while(!wss.isConnected() && millis() - st < timeout)
        wss.loop();

      return wss.isConnected();
    }
    
    virtual void onConnect() { ; }
    
    virtual void onBinary(uint8_t * payload, size_t length) {
      buffer.write(payload, length);
    }

  private:
    void Init() {
      setTimeout(5000);
      wss.onConnect = [&]() {
        onConnect();
      };
      wss.onBinary = [&](uint8_t * payload, size_t length) {
        onBinary(payload, length);
      };
    }

  protected:
    WebSocketsClientFn  wss;   
    SimpleRingBuffer<uint8_t> buffer;
    uint16_t timeout;  
};

class AudioFileSourceJcbasimul : public AudioFileSourceWebSockets {
  public:
    AudioFileSourceJcbasimul(uint16_t buffSize = 8000) : AudioFileSourceWebSockets(buffSize), saveURL(nullptr), token(nullptr) {
      Init();
    }

    AudioFileSourceJcbasimul(uint8_t *buffer, uint16_t buffSize) : AudioFileSourceWebSockets(buffer, buffSize), saveURL(nullptr), token(nullptr) {
      Init();
    }

    ~AudioFileSourceJcbasimul() {
      deInit();
    }

    virtual bool open(const char *url) override {
      deInit();
      buffer.init();

      char* host = nullptr;
      char* path = nullptr;
      int port;

      auto https = new HTTPClient();
      auto client = new WiFiClientSecure();
      client->setInsecure();
      
      if (https->begin(*client, url)) {
        auto httpCode = https->GET();
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          auto payload = https->getString();
          auto jo = JSON.parse(payload.c_str());

          char schema[strlen(jo["location"]) + 1];
          host = new char[strlen(jo["location"]) + 1];
          path = new char[strlen(jo["location"]) + 1];
          
          if( sscanf(jo["location"], "%[^:]://%[^:]:%hu%s", schema, host, &port, path) == 4 ) {
            token = new char[strlen(jo["token"]) + 1];
            strcpy(token, jo["token"]);
            saveURL = new char[strlen(url) + 1];
            strcpy(saveURL, url);
          }
        }   
        https->end();
      }
      delete client;
      delete https;

      if(token)
        wss.beginSSL(host, port, path, SSL_FINGERPRINT_NULL, "listener.fmplapla.com");

      if(path)
        delete []path;
      if(host)
        delete []host;

      if(token)
        return waitConnect();
      else
        return false;
    }
    
  protected:
    virtual void onConnect() override {
      if(token) {
        wss.sendTXT(token);
        delete []token;
        token = nullptr;
      }
    }
    
    virtual void onBinary(uint8_t * payload, size_t length) override {
      auto f = buffer.free();
      auto segnum = payload[26];
      while(f < length && segnum > 0) {
        length -= payload[26 + segnum] + 1;
        segnum --;
      }
      if(!segnum)
        length = 0;

      auto segdel = payload[26] - segnum;
      if(segdel > 0) {
        payload[26] = segnum;
        memmove(&payload[segdel], payload, 26 + segnum);
        payload += segdel;
      }
      
      AudioFileSourceWebSockets::onBinary(payload, length);
    }
    
  private:
    void Init() {
      saveURL = nullptr;
      token = nullptr;
      wss.setExtraHeaders("Origin: https://www.jcbasimul.com");
    }
    
    void deInit() {
      if(token) {
        delete []token;
        token = nullptr;
      }
      if(saveURL) {
        delete []saveURL;
        token = nullptr;
      }
    }
    
  private:
    char *saveURL;
    char *token;
};

#endif
