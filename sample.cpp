#include "wav.hpp"
#include <cmath>
#include <cstdio>

void SaveWavFile(const char *filename);

int main(void) {
  wav::stream ws;
  ws.save_to_file("test.wav");
}
