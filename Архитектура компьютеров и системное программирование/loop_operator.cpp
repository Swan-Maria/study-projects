#include <iostream>

int main() 
{
    // mov ecx, 10
    unsigned int ecx = 10;

    // LoopStart:
LoopStart:
    // cmp ecx, 0
    // je LoopEnd
    if (ecx == 0) goto LoopEnd;

    // dec ecx
    ecx--;

    // jmp LoopStart
    goto LoopStart;

    // LoopEnd:
LoopEnd:
    std::cout << "result ecx: " << ecx << std::endl;

    return 0;
}
