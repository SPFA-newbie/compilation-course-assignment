push ebp
mov ebp, esp
push FFFFFFFFh
push FFFFFFFFh
mov eax, 100
push eax
mov eax, 1
push eax
jmp MAIN
FUNCTION_HEAD_1:
mov [ebp-8], esp
push ecx
mov ecx, esp
push ecx
mov ecx, esp
mov eax, [ebp-8]
mov eax, [eax+8]
push eax
mov eax, 0
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
cmp eax, ebx
jge CMP_T_1
mov eax, 0
jmp CMP_F_1
CMP_T_1:
mov eax, FFh
CMP_F_1:
nop
pop ecx
mov esp, ecx
pop ecx
test eax, FFh
jz ELSE_1
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
jmp IF_END_1
ELSE_1:
mov eax, [ebp-8]
mov eax, [eax+8]
neg eax
mov esp, [ebp-8]
pop ecx
pop ebx
mov [ebp-8], ebx
mov esp, [ebp-4]
pop ebx
mov [ebp-4], ebx
mov eip, ecx
IF_END_1:
nop
mov esp, ecx
pop ecx
FUNCTION_END_1:
jmp ERROR_TAG
MAIN:
mov [ebp-8], esp
mov eax, 0
push eax
mov eax, 0
push eax
push ecx
mov ecx, esp
FOR_HEAD_1:
push ecx
mov ecx, esp
mov eax, [ebp-8]
mov eax, [eax-8]
push eax
mov eax, [ebp-12]
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
cmp eax, ebx
je CMP_T_2
mov eax, 0
jmp CMP_F_2
CMP_T_2:
mov eax, FFh
CMP_F_2:
nop
pop ecx
mov esp, ecx
pop ecx
test eax, FFh
jz FOR_END_1
push ecx
mov ecx, esp
push ecx
mov ecx, esp
push ecx
mov ecx, esp
mov eax, [ebp-8]
mov eax, [eax-8]
push eax
mov eax, 2
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
cdp
idiv ebx
mov eax, edx
pop ecx
mov esp, ecx
pop ecx
push eax
mov eax, 1
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
cmp eax, ebx
je CMP_T_3
mov eax, 0
jmp CMP_F_3
CMP_T_3:
mov eax, FFh
CMP_F_3:
nop
pop ecx
mov esp, ecx
pop ecx
test eax, FFh
jz ELSE_2
push ecx
mov ecx, esp
mov eax, [ebp-8]
mov eax, [eax-4]
push eax
mov eax, [ebp-8]
mov eax, [eax-8]
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
sub eax, ebx
pop ecx
mov esp, ecx
pop ecx
mov ebx, [ebp-8]
mov [ebx-4], eax
jmp IF_END_2
ELSE_2:
push ecx
mov ecx, esp
mov eax, [ebp-8]
mov eax, [eax-4]
push eax
mov eax, [ebp-16]
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
sub eax, ebx
pop ecx
mov esp, ecx
pop ecx
mov ebx, [ebp-8]
mov [ebx-4], eax
IF_END_2:
nop
push ecx
mov ecx, esp
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
mov eax, [ebp-16]
neg eax
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
add eax, ebx
pop ecx
mov esp, ecx
pop ecx
mov ebx, [ebp-8]
mov [ebx-4], eax
WHILE_HEAD_1:
push ecx
mov ecx, esp
mov eax, [ebp-16]
push eax
mov eax, [ebp-12]
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
cmp eax, ebx
jl CMP_T_4
mov eax, 0
jmp CMP_F_4
CMP_T_4:
mov eax, FFh
CMP_F_4:
nop
pop ecx
mov esp, ecx
pop ecx
test eax, FFh
jz WHILE_END_1
mov ebx, [ebp-4]
push ebx
mov [ebp-4], esp
push ecx
mov ecx, esp
mov eax, [ebp-16]
push eax
mov eax, [ebp-8]
mov eax, [eax-4]
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
add eax, ebx
pop ecx
mov esp, ecx
pop ecx
push eax
mov eax, [ebp-8]
push eax
push eip
jmp FUNCTION_HEAD_1
mov [ebp-16], eax
jmp WHILE_HEAD_1
WHILE_END_1:
nop
mov esp, ecx
pop ecx
push ecx
mov ecx, esp
mov eax, [ebp-8]
mov eax, [eax-8]
push eax
mov eax, 1
push eax
push ecx
sub ecx, 4
mov eax, [ecx]
sub ecx, 4
mov ebx, [ecx]
add eax, ebx
pop ecx
mov esp, ecx
pop ecx
mov ebx, [ebp-8]
mov [ebx-8], eax
jmp FOR_HEAD_1
FOR_END_1:
nop
mov esp, ecx
pop ecx
jmp PROGRAM_END
ERROR_TAG:
nop
PROGRAM_END:
pop eax
pop eax
pop ebp
