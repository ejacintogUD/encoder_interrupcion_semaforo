/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "InterruptIn.h"
#include "PinNames.h"
#include "Semaphore.h"
#include "Thread.h"
#include "cmsis_os2.h"
#include "mbed.h"
#include "mbed_rtx_conf.h"
#include "net_sleep.h"
//define

//prototipos
void ISR_interrupt_pin(void);
void antirebote_interrupt(void);

//Tareas y herramientas del sistema operativo 
Thread hilo_antirebote(osPriorityNormal, OS_STACK_SIZE);
Semaphore s_boton(0);

//Pines 
InterruptIn btn (D3);

//Variables globales 



int main()
{
    
    btn.rise(ISR_interrupt_pin);
    hilo_antirebote.start(antirebote_interrupt);
    printf("arranque programa\n\r");
    while (true) {
    }
}

void ISR_interrupt_pin (void)
{
    s_boton.release(); //Instruccion atomica para evitar choques entre interrupciones
}

void antirebote_interrupt (void)
{
    bool Q0;
    int i;
    while(true)
    {
        s_boton.acquire();
        Q0 = btn;
        wait_us(10000); //esperar tiempo rebote
        if (btn==Q0) //&&  btn==0)
        {printf("flanco bajada %u \n\r", i++);}

    }
}