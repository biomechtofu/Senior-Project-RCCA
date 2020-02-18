/**
 ******************************************************************************
 * @file    main.cpp
 * @author  Davide Aliprandi, STMicroelectronics
 * @version V1.0.0
 * @date    October 14th, 2015
 * @brief   mbed test application for the STMicroelectronics X-NUCLEO-IHM01A1
 *          Motor Control Expansion Board: control of 2 motors.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Includes ------------------------------------------------------------------*/

/* mbed specific header files. */
#include "mbed.h"

/* Helper header files. */
#include "DevSPI.h"

/* Component specific header files. */
#include "L6474.h"


/* Definitions ---------------------------------------------------------------*/

/* Number of steps. */
#define STEPS 3200

/* Delay in milliseconds. */
#define DELAY_1 2000
#define DELAY_2 6000
#define DELAY_3 8000

/* Speed in pps (Pulses Per Second).
   In Full Step mode: 1 pps = 1 step/s).
   In 1/N Step Mode:  N pps = 1 step/s). */
#define SPEED_1 2400
#define SPEED_2 1200


/* Variables -----------------------------------------------------------------*/

/* Motor Control Component. */
L6474 *motor1;
L6474 *motor2;


/* Main ----------------------------------------------------------------------*/

int main()
{
    /*----- Initialization. -----*/

    /* Initializing SPI bus. */
    DevSPI dev_spi(D11, D12, D13);

    /* Initializing Motor Control Components. */
    motor1 = new L6474(D2, D8, D7, D9, D10, dev_spi);
    motor2 = new L6474(D2, D8, D4, D3, D10, dev_spi);
    if (motor1->init() != COMPONENT_OK) {
        exit(EXIT_FAILURE);
    }
    if (motor2->init() != COMPONENT_OK) {
        exit(EXIT_FAILURE);
    }

    /* Printing to the console. */
    printf("Motor Control Application Example for 2 Motors\r\n\n");


    /*----- Moving. -----*/

    /* Printing to the console. */
    printf("--> Moving forward: M1 %d steps, M2 %d steps.\r\n", STEPS >> 1, STEPS);

    /* Moving N steps in the forward direction. */
    motor1->move(StepperMotor::FWD, STEPS >> 1);
    motor2->move(StepperMotor::FWD, STEPS);

    /* Waiting while the motor is active. */
    motor1->wait_while_active();
    motor2->wait_while_active();

    /* Getting current position. */
    int position1 = motor1->get_position();
    int position2 = motor2->get_position();
    
    /* Printing to the console. */
    printf("    Position: M1 %d, M2 %d.\r\n", position1, position2);

    /* Waiting 2 seconds. */
    wait_ms(DELAY_1);

    
    /*----- Moving. -----*/
    
    /* Printing to the console. */
    printf("--> Moving backward: M1 %d steps, M2 %d steps.\r\n", STEPS >> 1, STEPS);

    
    /* Moving N steps in the backward direction. */
    motor1->move(StepperMotor::BWD, STEPS >> 1);
    motor2->move(StepperMotor::BWD, STEPS);
    
    /* Waiting while the motor is active. */
    motor1->wait_while_active();
    motor2->wait_while_active();

    /* Getting current position. */
    position1 = motor1->get_position();
    position2 = motor2->get_position();
    
    /* Printing to the console. */
    printf("    Position: M1 %d, M2 %d.\r\n", position1, position2);
    printf("--> Setting Home.\r\n");

    /* Setting the current position to be the home position. */
    motor1->set_home();
    motor2->set_home();

    /* Waiting 2 seconds. */
    wait_ms(DELAY_1);


    /*----- Going to a specified position. -----*/

    /* Printing to the console. */
    printf("--> Going to position: M1 %d, M2 %d.\r\n", STEPS, STEPS >> 1);
    
    /* Requesting to go to a specified position. */
    motor1->go_to(STEPS);
    motor2->go_to(STEPS >> 1);
    
    /* Waiting while the motor is active. */
    motor1->wait_while_active();
    motor2->wait_while_active();

    /* Getting current position. */
    position1 = motor1->get_position();
    position2 = motor2->get_position();
    
    /* Printing to the console. */
    printf("    Position: M1 %d, M2 %d.\r\n", position1, position2);
    
    /* Waiting 2 seconds. */
    wait_ms(DELAY_1);

    
    /*----- Going Home. -----*/

    /* Printing to the console. */
    printf("--> Going Home.\r\n");
    
    /* Requesting to go to home. */
    motor1->go_home();
    motor2->go_home();
    
    /* Waiting while the motor is active. */
    motor1->wait_while_active();
    motor2->wait_while_active();

    /* Getting current position. */
    position1 = motor1->get_position();
    position2 = motor2->get_position();

    /* Printing to the console. */
    printf("    Position: M1 %d, M2 %d.\r\n", position1, position2);

    /* Waiting 2 seconds. */
    wait_ms(DELAY_1);


    /*----- Running. -----*/

    /* Printing to the console. */
    printf("--> M1 running backward, M2 running forward.\r\n");

    /* Requesting to run backward. */
    motor1->run(StepperMotor::BWD);
    motor2->run(StepperMotor::FWD);

    /* Waiting until delay has expired. */
    wait_ms(DELAY_2);

    /* Getting current speed. */
    int speed1 = motor1->get_speed();
    int speed2 = motor2->get_speed();

    /* Printing to the console. */
    printf("    Speed: M1 %d, M2 %d.\r\n", speed1, speed2);

    /*----- Increasing the speed while running. -----*/

    /* Printing to the console. */
    printf("--> Increasing the speed while running.\r\n");

    /* Increasing the speed. */
    motor1->set_max_speed(SPEED_1);
    motor2->set_max_speed(SPEED_1);

    /* Waiting until delay has expired. */
    wait_ms(DELAY_2);

    /* Getting current speed. */
    speed1 = motor1->get_speed();
    speed2 = motor2->get_speed();

    /* Printing to the console. */
    printf("    Speed: M1 %d, M2 %d.\r\n", speed1, speed2);


    /*----- Decreasing the speed while running. -----*/

    /* Printing to the console. */
    printf("--> Decreasing the speed while running.\r\n");

    /* Decreasing the speed. */
    motor1->set_max_speed(SPEED_2);
    motor2->set_max_speed(SPEED_2);

    /* Waiting until delay has expired. */
    wait_ms(DELAY_3);

    /* Getting current speed. */
    speed1 = motor1->get_speed();
    speed2 = motor2->get_speed();

    /* Printing to the console. */
    printf("    Speed: M1 %d, M2 %d.\r\n", speed1, speed2);


    /*----- Requiring hard-stop while running. -----*/

    /* Printing to the console. */
    printf("--> Requiring hard-stop while running.\r\n");

    /* Requesting to immediatly stop. */
    motor1->hard_stop();
    motor2->hard_stop();

    /* Waiting while the motor is active. */
    motor1->wait_while_active();
    motor2->wait_while_active();

    /* Waiting 2 seconds. */
    wait_ms(DELAY_1);


    /*----- Infinite Loop. -----*/

    /* Printing to the console. */
    printf("--> Infinite Loop...\r\n");

    /* Setting the current position to be the home position. */
    motor1->set_home();
    motor2->set_home();

    /* Infinite Loop. */
    while(true) {
        /* Requesting to go to a specified position. */
        motor1->go_to(STEPS >> 1);
        motor2->go_to(- (STEPS >> 1));

        /* Waiting while the motor is active. */
        motor1->wait_while_active();
        motor2->wait_while_active();

        /* Requesting to go to a specified position. */
        motor1->go_to(- (STEPS >> 1));
        motor2->go_to(STEPS >> 1);

        /* Waiting while the motor is active. */
        motor1->wait_while_active();
        motor2->wait_while_active();
    }
}
