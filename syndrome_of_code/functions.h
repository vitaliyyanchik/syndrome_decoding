#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void EnterCode(short* code, int all_bits);
int ControlBitsCounter(int all_bits);
void CalculateSyndrome(short* code, int all_bits, short* syndrome, int control_bits);
int FindError(short* syndrome, int control_bits);
void CorrectCode(short* code, int all_bits, short* syndrome, int control_bits);
void PrintCode(short* code, int all_bits);
void CustomCode(short* code, int all_bits);

#endif //FUNCTIONS_H