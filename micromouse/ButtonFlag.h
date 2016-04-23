#pragma once
extern volatile bool buttonFlag;


#define BUTTONFLAG \
if (buttonFlag) goto BUTTON_EXIT;


#define BUTTONEXIT \
BUTTON_EXIT: