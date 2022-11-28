push ebp
mov ebp, esp
push FFFFFFFFh
push FFFFFFFFh
mov eax, 1
push eax
jmp MAIN
FUNCTION_HEAD_1:
mov [ebp-8], esp
push ecx
mov ecx, esp
mov eax, [ebp-8]
mov eax, [eax+8]
neg eax
mov ebx, [ebp-8]
mov [ebx+8], eax
mov eax, [ebp-8]
mov eax, [eax+8]
mov esp, [ebp-8]
pop ecx
pop ebx
mov [ebp-8], ebx
mov esp, [ebp-4]
pop ebx
mov [ebp-4], ebx
mov eip, ecx
mov esp, ecx
pop ecx
FUNCTION_END_1:
jmp ERROR_TAG
MAIN:
mov [ebp-8], esp
mov eax, 2
push eax
mov eax, 0
push eax
push ecx
mov ecx, esp
push ecx
mov ecx, esp
mov eax, [ebp-12]
push eax
mov ebx, [ebp-4]
push ebx
mov [ebp-4], esp
mov eax, [ebp-8]
mov eax, [eax-4]
push eax
mov eax, [ebp-8]
push eax
push eip
jmp FUNCTION_HEAD_1
push eax
mov eax, 1
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
add eax, ebx
sub ecx, 4
mov ebx, [ecx]
add eax, ebx
pop ecx
mov esp, ecx
pop ecx
mov ebx, [ebp-8]
mov [ebx-8], eax
mov esp, ecx
pop ecx
jmp PROGRAM_END
ERROR_TAG:
nop
PROGRAM_END:
pop eax
pop eax
pop ebp