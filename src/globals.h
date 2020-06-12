unsigned long genratorTrunedONAt = 0;
unsigned long wapdaTunredONAt = 0;
unsigned long genratorTrunedOFFAt = 0;
unsigned long wapdaTunredOFFAt = 0;



unsigned long startPinTrunedONAt = 0;
unsigned long stopPinTunredONAt = 0;
unsigned long startPinTrunedOFFAt = 0;
unsigned long stopPinTunredOFFAt = 0;


bool genratorState = false;
bool wapdaState = false;
bool automaticStartEnabled = false;





int slipTime = 4000;
int maxNumberOfSlips = 4;
int Slips =1; // current slips number
int waitTimeBetweenSlips = 4000;

int voltageT = 35;


int wapdaPin = 34;
int genratorPin = 35;
int startPin = 22;
int stopPin = 23;