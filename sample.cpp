#include "wav.hpp"
#include <cmath>
#include <cstdio>

void SaveWavFile(const char *filename);

int main(void) {
  wav::SaveWavFile("test.wav");
}
