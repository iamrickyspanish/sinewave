#include "voice.h"
#include <stdio.h>

int main () {
    printf ("test sigpath\n\n");
    voice sp = voice_create ();
    printf ("newly initialized sigpath: output should be 0\n\n");
    if (voice_out (sp) != 0) {
        printf ("FAIL, expected 0, received: %i \n\n", voice_out (sp));
        return 1;
    }
    printf ("CHECK \n\n");

    return 0;
}
