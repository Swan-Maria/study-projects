#include <iostream>

int main() 
{
    int var_a = 5;
    int ebx = 0;

    // mov eax, [var_a]
    int eax = var_a;

    // cmp eax, 10
    // jne ElseBlock
    if (eax != 10) goto ElseBlock;

    // add ebx, 1
    ebx += 1;

    // jmp EndIf
    goto EndIf;

    // ElseBlock:
ElseBlock:
    // sub ebx, 1
    ebx -= 1;

    // EndIf:
EndIf:
    std::cout << "result ebx: " << ebx << std::endl;

    return 0;
}
