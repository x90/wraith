#ifndef _ENCRYPTEDSTREAM_H
#define _ENCRYPTEDSTREAM_H 1

namespace bd {
  class String;
}
#include <iostream>
#include <bdlib/src/Stream.h>
#include <bdlib/src/String.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ENC_AES_256_ECB 	1
#define ENC_AES_256_CBC		2
#define ENC_BASE64_BROKEN	4
#define ENC_BASE64		8
#define ENC_KEEP_NEWLINES	16
#define ENC_NO_HEADER		32

#define ENC_DEFAULT 		(ENC_AES_256_ECB)

class EncryptedStream : public bd::Stream {
  private:
        bd::String key;
        void apply_filters(bd::String& buf, const char enc_flags) const;
        void unapply_filters(bd::String& buf, const char enc_flags) const;

  protected:

  public:
        EncryptedStream(const char* keyStr) : Stream(), key(bd::String(keyStr)) {};
        EncryptedStream(bd::String& keyStr) : Stream(), key(keyStr) {};
        EncryptedStream(EncryptedStream& stream) : Stream(stream), key(stream.key) {};

        virtual int loadFile(const int fd);
        virtual int loadFile(const char* fname) { return bd::Stream::loadFile(fname); }

        virtual int writeFile(const int fd, const char enc_flags) const;
        virtual int writeFile(const int fd) const { return writeFile(fd, ENC_DEFAULT); }
        int writeFile(const char* fname, mode_t mode = (S_IRUSR|S_IWUSR)) const { return bd::Stream::writeFile(fname, mode); }
};
#endif
