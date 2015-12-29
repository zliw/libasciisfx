#include <math.h>
#include "oscillator.h"

struct Oscillator newSinusOscillator() {
    struct Oscillator oscillator;
    oscillator.wave = newBufferWithFrames(1024);

    float *data = oscillator.wave.data;
    float length = (float) oscillator.wave.length;
    uint32_t i;

    for (i = 0; i < oscillator.wave.length; i++) {
        data[i] = sinf(((float) i) / length * 2 * M_PI);
    }

    return oscillator;
}

uint32_t renderOscillatorToBuffer(struct Oscillator self,
                                  struct Buffer buffer) {

    if (buffer.length == 0) {
        return 0;
    }

    if (buffer.data == NULL) {
        return 0;
    }

    //frequencyBuffer.render()

    //let frequency = frequencyBuffer.buffer.floatChannelData[0]
    //let volumes = frequencyBuffer.volumeBuffer.buffer.floatChannelData[0]
    uint32_t i;
    float phase = 0.0;
    float volume = 1.0;
    float value;
    float f = 220.0;

    for (i = 0; i < buffer.length; i++) {
        //f = frequency[i];
        if (f == 0) {
            buffer.data[i] = 0;
        }
        else {
            phase +=  self.wave.length * f / SAMPLE_RATE;
            // let volume = volumes[i]
            value = volume * self.wave.data[((int) phase) % self.wave.length];
            buffer.data[i] = value;
        }
    }

    return 1;
}

void deleteOscillator(struct Oscillator *oscillator) {
    deleteBuffer(&oscillator->wave);
}
