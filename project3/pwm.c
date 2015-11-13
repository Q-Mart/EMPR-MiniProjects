#include "pwm.h"

void pwmInit(int base, int channel){
  /*Initialise the pwm controller
   * @param base: Your base time for channel 0
   * @param channel: The channel you wish to activat
   */

  PINSEL_CFG_Type pinCfg;
  PWM_TIMERCFG_Type PWMCfgDat;
  PWM_MATCHCFG_Type PWMMatchCfgDat;
  PWMCfgDat.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;
  PWMCfgDat.PrescaleValue = 1;
  PWM_Init(LPC_PWM1, PWM_MODE_TIMER, (void*) &PWMCfgDat);

  pinCfg.Funcnum = 1;
  pinCfg.OpenDrain = 0;
  pinCfg.Pinmode = 0;
  pinCfg.Portnum = 2;
  pinCfg.Pinnum = 5;
  PINSEL_ConfigPin(&pinCfg);

  PWM_MatchUpdate(LPC_PWM1, 0, base, PWM_MATCH_UPDATE_NOW);
  PWMMatchCfgDat.IntOnMatch = DISABLE;
  PWMMatchCfgDat.MatchChannel = 0;
  PWMMatchCfgDat.ResetOnMatch = ENABLE;
  PWMMatchCfgDat.StopOnMatch = DISABLE;
  PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfgDat);

  PWM_ChannelConfig(LPC_PWM1, channel, PWM_CHANNEL_SINGLE_EDGE);

  PWMMatchCfgDat.IntOnMatch = DISABLE;
  PWMMatchCfgDat.MatchChannel = channel;
  PWMMatchCfgDat.ResetOnMatch = DISABLE;
  PWMMatchCfgDat.StopOnMatch = DISABLE;
  PWM_ConfigMatch(LPC_PWM1, &PWMMatchCfgDat);
  PWM_ChannelCmd(LPC_PWM1, channel, ENABLE);

  PWM_ResetCounter(LPC_PWM1);
  PWM_CounterCmd(LPC_PWM1, ENABLE);
  PWM_Cmd(LPC_PWM1, ENABLE);
}

void pwmSetValue(int channel, float val, int base){
  /*Set the value for the match register
   * @param channel: The channel to wish to change the MR for
   * @param val: The percentage of base time you wish to have a pulse width
   * @param base: your channel 0 base time
   */

  PWM_MatchUpdate(LPC_PWM1, channel, val*base, PWM_MATCH_UPDATE_NOW);
}

void pwmDisable(){
  PWM_CounterCmd(LPC_PWM1, DISABLE);
  PWM_Cmd(LPC_PWM1, DISABLE);
}
