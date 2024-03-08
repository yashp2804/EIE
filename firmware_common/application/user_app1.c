/*!*********************************************************************************************************************
@file user_app1.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
  PWMAudioSetFrequency(BUZZER1,131);
  
  //initialize all unused LEDs to off
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN );
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_pfStateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */
static void UserApp1SM_Idle(void)
{
  //game location
  static u16 game_state = 0;
  //timer 
  static u32 timer = 0;
  //led output array
  static u32 array[] = {0, 0, 0, 0};
  //user input button array
  static u32 user_array[] = {0, 0, 0, 0};
  //cycles and counts through array
  static u16 array_count = 0;
  //run user start menu
  static u16 run_menu = 0;
  //i 4 for loop
  static u8 array_compare = 0;
  //correct array counter
  static u32 correct_counter = 0;
  //random number
  static u16 rand_num = 0;
  //loop count
  static u16 i=0;
  
  
  static u16 button0pressed =0;
 
  static u16 loops = 0;
  loops ++;
  if (loops == 65400){
    loops=0;
  }
  
  LcdCommand(LCD_CLEAR_CMD);
  LcdMessage(LINE1_START_ADDR, "Press 0");
  
  if (game_state == 0 ){
    
    
    if( WasButtonPressed(BUTTON0) || button0pressed == 1)
    {
      ButtonAcknowledge(BUTTON0);
      button0pressed = 1;
      
      srand(1103515245 * loops + 12345);
      rand_num = rand()%4;
     
      //tunrs on first pair/ turns off
     
      if(rand_num == 3){
        
        //set sound
        PWMAudioSetFrequency(BUZZER1, 1175);
        PWMAudioSetFrequency(BUZZER2, 587);
        
        while(timer < 200000 )
        {
          LedOn(RED);
          LedOn(ORANGE);
          PWMAudioOn(BUZZER1);
          PWMAudioOn(BUZZER2);
          timer++;
        }
        LedOff(RED);
        LedOff(ORANGE);
        PWMAudioOff(BUZZER1);
        PWMAudioOff(BUZZER2);
      
        array[i] = 3;
        i++;
        timer = 0;
       }
    
    //tunrs on second pair/ turns off
      if(rand_num == 1){
        
        //set sound 
        PWMAudioSetFrequency(BUZZER1, 880);
        PWMAudioSetFrequency(BUZZER2, 440);
        
        while(timer < 200000 )
        {
          LedOn(CYAN);
          LedOn(BLUE);
          PWMAudioOn(BUZZER1);
          PWMAudioOn(BUZZER2);
          timer++;
        }
        LedOff(CYAN);
        LedOff(BLUE);
        PWMAudioOff(BUZZER1);
        PWMAudioOff(BUZZER2);
    
        array[i] = 1;
        timer = 0;
        i++;
      }
    
    //tunrs on third pair/ turns off
      if(rand_num == 2){
        
        //set sound 
        PWMAudioSetFrequency(BUZZER1, 740);
        PWMAudioSetFrequency(BUZZER2, 370);
        
        while(timer < 200000 )
        {
          LedOn(YELLOW);
          LedOn(GREEN);
          PWMAudioOn(BUZZER1);
          PWMAudioOn(BUZZER2);
          timer++;
        }
        LedOff(YELLOW);
        LedOff(GREEN);
        PWMAudioOff(BUZZER1);
        PWMAudioOff(BUZZER2);
      
        array[i] = 2;
        timer = 0;
        i++;
      }
      
      //turns on fourth pair/ turns off
      if(rand_num == 0){
        
        //set sound 
        PWMAudioSetFrequency(BUZZER1, 131);
        PWMAudioSetFrequency(BUZZER2, 65);
        
        while(timer < 200000 )
        {
          LedOn(WHITE);
          LedOn(PURPLE);
          PWMAudioOn(BUZZER1);
          PWMAudioOn(BUZZER2);
          timer++;
        }
        LedOff(WHITE);
        LedOff(PURPLE);
        PWMAudioOff(BUZZER1);
        PWMAudioOff(BUZZER2);
      
        array[i] = 0;
        timer = 0;
        i++;
      }
      
      //go to next game state
      if(i >= 4){
      game_state = 1;
      }
    }
    
  }
  
  
  //user input 
  if(game_state == 1 && array_count < 4){
    
    if( WasButtonPressed(BUTTON0) )
    {
      ButtonAcknowledge(BUTTON0);
      user_array[array_count] = 0;
      array_count++;
    }
    
    if( WasButtonPressed(BUTTON1) )
    {
      ButtonAcknowledge(BUTTON1);
      user_array[array_count] = 1;
      array_count++;
    }
    
    if( WasButtonPressed(BUTTON2) )
    {
      ButtonAcknowledge(BUTTON2);
      user_array[array_count] = 2;
      array_count++;
    }
    
    if( WasButtonPressed(BUTTON3) )
    {
      ButtonAcknowledge(BUTTON3);
      user_array[array_count] = 3;
      array_count++;
    }
    
    
  }
  
  if (game_state ==1 && array_count >=4){
    
    static u8 j=0;
    
    if (array[j] != user_array[j]){
      LedOn(RED);
    }
    
    if(j==3 && array[j] == user_array[j]){
      LedOn(GREEN);
    }
    
    else{
      j++;
    }
  }

     
  
  
    
  
} /* end UserApp1SM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
