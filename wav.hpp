/*
MIT License

Copyright (c) 2019 - present H. Watanabe

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once

#include <cmath>
#include <iostream>
#include <vector>

namespace wav {

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

const int WAVE_FORMAT_PCM = 1;
typedef struct {
  WORD wFormatTag;
  WORD nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD nBlockAlign;
  WORD wBitsPerSample;
  WORD cbSize;
} WAVEFORMATEX;

struct stream {
  std::vector<BYTE> bWave;
  const DWORD SRATE = 11025; // Sampling Rate (11025Hz)
  const DWORD dwFmtSize = 16;

  stream() {
    const int totalsec = 2; // Length of Data [sec]
    const double Pi = M_PI;
    double f = (double)440.0 / (double)SRATE; //(440.0Hz)
    int size = SRATE * totalsec;
    for (int i = 0; i < size; i++) {
      double phase = (double)i * f * Pi * 2.0;
      BYTE c = static_cast<BYTE>(sin(phase) * 128 + 128);
      bWave.push_back(c);
    }
  }

  void save_to_file(const char *filename) {
    WAVEFORMATEX wfe;
    DWORD dwWaveSize = bWave.size();
    const DWORD dwFileSize = dwWaveSize + 36; // Size of File

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
      std::cerr << "Failed to open " << filename << std::endl;
      return;
    }

    fwrite("RIFF", sizeof(BYTE), 4, fp);
    fwrite(&dwFileSize, sizeof(DWORD), 1, fp);
    fwrite("WAVE", sizeof(BYTE), 4, fp);

    wfe.wFormatTag = WAVE_FORMAT_PCM; // Fileformat (PCM)
    wfe.nChannels = 1;
    wfe.nSamplesPerSec = SRATE;
    wfe.nAvgBytesPerSec = SRATE;
    wfe.wBitsPerSample = 8;
    wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;

    fwrite("fmt ", sizeof(BYTE), 4, fp);
    fwrite(&dwFmtSize, sizeof(DWORD), 1, fp);
    fwrite(&wfe, 1, 16, fp);
    fwrite("data", sizeof(BYTE), 4, fp);
    fwrite(&dwWaveSize, sizeof(DWORD), 1, fp);
    fwrite(bWave.data(), sizeof(BYTE), dwWaveSize, fp);
    fclose(fp);
  }
};
} // namespace wav
