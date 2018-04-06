///////////////////////////////////////////////////////////////////
//  DarkRAT.h Version 1.2									     //
//  by Paul Chin  (Feb 26, 2010)								 //    
//  Last Updated: March 2, 2010									 //
//  Forum Post:													 //			
//  http://forum.thegamecreators.com/?m=forum_view&t=166159&b=22 //
//	                                                             // 
//   Dependency:  DarkForm.h                                     //
//                                                               //
//  * Free to modify and use for any purpose *					 //
///////////////////////////////////////////////////////////////////

#ifndef DARKRAT_H
#define DARKRAT_H

#include "DarkForm.h"

//---------  DESKTOP ------------
class Desktop
{
public:
	Desktop(){};
	Desktop(int _xLeft,int _yTop,int _width,int _height, int _interval);	
	void update();
	void startDesktopCapture();	
	void stopDesktopCapture();
	void bmp2jpeg();
	void getDesktopImage();
	void showDesktopImage();
private:
	int xLeft,yTop,xRight,yBottom,width,height;
	bool isCapture;
	int interval,counter;

	int maxX,maxY;
	bool isLoadJpeg;
};
Desktop::Desktop(int _xLeft,int _yTop,int _width,int _height, int _interval){
	xLeft = _xLeft;
	yTop = _yTop;
	width = _width;
	height = _height;
	xRight = xLeft + width;
	yBottom = yTop + height;
	isCapture = false;
	interval = _interval;
	counter = 0;
	//Get screen size 
	maxX = GetSystemMetrics(SM_CXSCREEN);
	maxY = GetSystemMetrics(SM_CYSCREEN);
}
void Desktop::update(){	
	dbInk(dbRGB(255,255,255),dbRGB(255,255,255));
	dbBox(xLeft,yTop,xRight,yBottom);
	counter++; 	
	if(isCapture && counter>interval) {	
		getDesktopImage(); 	dbWait(10);	
		bmp2jpeg();		    dbWait(10);		
		showDesktopImage();	dbWait(5);		
		counter=0;
	}	
}
void Desktop::startDesktopCapture(){
	isCapture = true;	
	counter = 0;
}
void Desktop::stopDesktopCapture(){
	isCapture = false;	
	counter = 0;
	if(dbSpriteExist(200)) dbDeleteSprite(200);
    if(dbImageExist(100))  dbDeleteImage(100);
}

//capture desktop image and save to same folder as desktop.bmp
void Desktop::getDesktopImage(){
	    char filename[]="desktop.bmp";
		//Simulate PrintScreen keypress
		keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
        keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
        HBITMAP h;
        
        OpenClipboard(NULL);
		h = (HBITMAP)GetClipboardData(CF_BITMAP);
        CloseClipboard();
        HDC hdc=NULL;
    
		FILE *fp=NULL;
		LPVOID pBuf=NULL;
		BITMAPINFO bmpInfo;
		BITMAPFILEHEADER bmpFileHeader;
		
		do {
            hdc=GetDC(NULL);
			ZeroMemory(&bmpInfo,sizeof(BITMAPINFO));
			bmpInfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
			GetDIBits(hdc,h,0,0,NULL,&bmpInfo,DIB_RGB_COLORS);
			if(bmpInfo.bmiHeader.biSizeImage<=0)
                bmpInfo.bmiHeader.biSizeImage=bmpInfo.bmiHeader.biWidth*abs(bmpInfo.bmiHeader.biHeight)*(bmpInfo.bmiHeader.biBitCount+7)/8;
			if((pBuf = malloc(bmpInfo.bmiHeader.biSizeImage))==NULL){
				MessageBox( NULL, "Unable to Allocate Bitmap Memory", "Error", MB_OK|MB_ICONERROR);
				break;
			}

			bmpInfo.bmiHeader.biCompression=BI_RGB;
			GetDIBits(hdc,h,0,bmpInfo.bmiHeader.biHeight,pBuf, &bmpInfo, DIB_RGB_COLORS);
			if((fp = fopen(filename,"wb"))==NULL)   {
                MessageBox( NULL, "Unable to Create Bitmap File", "Error", MB_OK|MB_ICONERROR);
				break;
			}
			bmpFileHeader.bfReserved1=0;
			bmpFileHeader.bfReserved2=0;
			bmpFileHeader.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+bmpInfo.bmiHeader.biSizeImage;
			bmpFileHeader.bfType='MB';
			bmpFileHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);
			fwrite(&bmpFileHeader,sizeof(BITMAPFILEHEADER),1,fp);
			fwrite(&bmpInfo.bmiHeader,sizeof(BITMAPINFOHEADER),1,fp);
			fwrite(pBuf,bmpInfo.bmiHeader.biSizeImage,1,fp);
        }while(false);
        
		if(hdc)ReleaseDC(NULL,hdc);
        if(pBuf) free(pBuf);
        if(fp)fclose(fp);
}
void Desktop::showDesktopImage(){
	if(dbImageExist(100)==1) dbDeleteImage(100);
	dbLoadImage("desktop.jpg",100); //not bmp
	if(dbImageExist(100)==1) {
		if(dbSpriteExist(200)==1) dbDeleteSprite(200);
		dbSprite(200,xLeft,yTop,100);
		dbStretchSprite(200,(width*100)/maxX,(height*100)/maxY);		
	}

}
void Desktop::bmp2jpeg(){
	if(dbImageExist(100)==1) dbDeleteImage(100);
	dbLoadImage("desktop.bmp",100);//load bmp save to jpg
	if(dbImageExist(100)==1) dbSaveImage("desktop.jpg",100);
}


//---------  NET CONNECTOR ------------
#define SIZE 32 //number of commands
class NetConnector
{
public:
	NetConnector(Textarea* _taDisplay,Textarea* _taWho,Picturebox* _picturebox);
	NetConnector(Textarea* _taDisplay,Textarea* _taWho,Desktop *_desktop);
	void findTcpipConnectionNumber();
	void checkIncomingMessages();
	int startServer(char *servername);
	int connect(char *IP, char* username);
	void update();
	void disconnect();
	void sendCommand(int _command);
	void addCommand(int _command, char* _program_to_run); 
	void addCommand(int _command, char* _program_to_run,char* _commandLine_Param); 
	void addCommand(int _command, char* _program_to_run,char* _commandLine_Param,char* _cmdFolder); 
	void runCommand(int _command); //locally (used if running as server)
private:
	char playerName[32];
	int numberOfPlayers;	
	bool isConnected;
	int counter;
	char prevMsg[128];          //used by checkIncomingMessages()
	Textarea *taDisplay, *taWho; //used by checkIncomingMessages()
	int tcpIpNumber;
	int msgcheckInterval;
    bool isServer;
	//Desktop capture networking
	Desktop *desktop;
	void sendDesktopImage();
	bool isDesktopCapture;
	Picturebox* picturebox;
    char commands[SIZE][128]; // eg.  1 notepad, 2 IE, 3 paint, 4 soundfile, upto 31
	                          // first array index denotes command number, what is stored is command name
	char cmdParam[SIZE][128];
	char cmdFolder[SIZE][128];
};
//Client constructor
NetConnector::NetConnector(Textarea* _taDisplay,Textarea* _taWho,Picturebox* _picturebox){
	memset(playerName,0,sizeof(playerName));
	isConnected = false;
	counter = 0;
	memset(prevMsg,0,sizeof(prevMsg));
	taDisplay = _taDisplay;
	taWho = _taWho;	
	tcpIpNumber = 0;   
	msgcheckInterval = 100;
	isDesktopCapture = false; //no *_desktop in constructor
	isServer = false;
	picturebox = _picturebox;
}
//Server constructor
NetConnector::NetConnector(Textarea* _taDisplay,Textarea* _taWho,Desktop *_desktop){
	memset(playerName,0,sizeof(playerName));
	isConnected = false;
	counter = 0;
	memset(prevMsg,0,sizeof(prevMsg));
	taDisplay = _taDisplay;
	taWho = _taWho;	
	tcpIpNumber = 0;   
	msgcheckInterval = 100;
    isServer = true;
	//desktop capture networking
	desktop = _desktop;
	isDesktopCapture = true; //because *_desktop in constructor
	memset(commands,NULL,sizeof(commands));
	memset(cmdParam,NULL,sizeof(cmdParam));
	memset(cmdFolder,NULL,sizeof(cmdFolder));
}
void NetConnector::findTcpipConnectionNumber(){
	int FLAG = 0;
    dbPerformChecklistForNetConnections();
	for(int x=1; x<=dbChecklistQuantity(); x++){
		char* service = dbChecklistString(x);
		if(strcmp(dbLeft(service,15),"Internet TCP/IP")==0){        
            FLAG = x;        
		}
	}
	tcpIpNumber = FLAG;
}
void NetConnector::checkIncomingMessages(){	
	dbGetNetMessage();
	if(dbNetMessageExists()==0) return;
	if(dbNetMessageExists()!=0 && dbNetMessageType()==3){//3 is string	
		char *msg = dbNetMessageString();
		if(strcmp(prevMsg,msg)!=0){
			strcpy(prevMsg,msg);
			strcpy(prevMsg,msg);
			dbSendNetMessageString(0,msg);
			taDisplay->appendText(msg);
			isConnected=true;
			if(taWho==NULL) return;

			//Displays the players in the room
			dbPerformChecklistForNetPlayers();
			numberOfPlayers = dbChecklistQuantity();
			taWho->clear();
			for(int x=1; x<=numberOfPlayers; x++){				
				taWho->appendText(dbChecklistString(x));
			} 
		}
	}else if(dbNetMessageExists()!=0 && !isServer && dbNetMessageType()==5){//5 is image
		if(dbImageExist(400)==1) dbDeleteImage(400);
		dbNetMessageImage(400); 
		BOXPOINTS boxpts = picturebox->getBoxpoints();
		int xleft = boxpts.xLeft;
		int ytop  = boxpts.yTop;
		int bWidth = boxpts.width;
		int bHeight = boxpts.height;
		
		//Create sprite
		if(dbSpriteExist(200)==1) dbDeleteSprite(200);
		dbSprite(200,xleft,ytop,400);
		dbSizeSprite(200,bWidth,bHeight);
	}else if(dbNetMessageExists()!=0 && dbNetMessageType()==1){//1 is integer
		int cmdNumber = dbNetMessageInteger();
		if(cmdNumber == 0) {
			dbFreeNetGame();
			isConnected=false;			
		}
		if(cmdNumber>0 && cmdNumber<SIZE){
			runCommand(cmdNumber);
			char cmdAck[32]={0};
			sprintf(cmdAck,"Command [%s ] received",commands[cmdNumber]);
			dbSendNetMessageString(0,cmdAck);
		}
	}
}
int NetConnector::startServer(char *servername){
	findTcpipConnectionNumber();
	strcpy(playerName,servername);
	taDisplay->appendText("Creating net session.");
	dbSleep(200);			
	dbSetNetConnection(tcpIpNumber," ");
	dbCreateNetGame("Sample Net Session",playerName,64,2);	

	int isExist = dbNetGameExists ( );
	
	if(isExist==1) isServer = true;
	
    return isExist; //1 (exist) or 0 (not exist)
}
int NetConnector::connect(char *IP, char* username){
	findTcpipConnectionNumber();
	strcpy(playerName,username);
	char ip[64]={0};
	if(strcmp(IP,"")==0) strcpy(ip,"127.0.0.1");
	else                 strcpy(ip,IP);
	
	taDisplay->appendText("Connecting to net session at: ");
	taDisplay->appendText(ip);
	
	dbSetNetConnection(tcpIpNumber,ip);
	dbPerformChecklistForNetSessions();
	int numberOfGames = dbChecklistQuantity();
	if(numberOfGames==0){
		taDisplay->appendText("No session found at that address.");
		return 0; //Cannot connect
	}
	dbJoinNetGame(1,playerName);
	int isExist = dbNetGameExists ( );
	if(isExist==1){
		taDisplay->appendText("Connected to session");
		isConnected=true;
		isServer = false;
	}

	//Broadcast incoming message
	char c[32] = {0};
	sprintf(c,"%s has joined",playerName);
	dbSendNetMessageString(0,c);
	return 1; //connected
}
void NetConnector::update(){
	counter++; if(counter>10000) counter=0;
	if(counter%msgcheckInterval==0){ //slow down checking of new msg
		checkIncomingMessages();
		
	}
	if(isConnected && counter%(msgcheckInterval+101)==0 && isDesktopCapture && isServer){
		desktop->getDesktopImage(); dbWait(10);
		desktop->bmp2jpeg();        dbWait(10);
		if(dbImageExist(300)==1) dbDeleteImage(300);
		dbLoadImage("desktop.jpg",300);
		if(dbImageExist(300)==1) {
			dbSendNetMessageImage(0,300,1); 
			dbDeleteImage(300);
		}
	}

}
void NetConnector::disconnect(){
	dbSendNetMessageInteger(0,0); //2nd param 0 is to disconnect
	dbFreeNetGame();
}
void NetConnector::sendCommand(int _command){//used by client
	dbSendNetMessageInteger(0,_command); //2nd param should be designed by programmer
}
void NetConnector::addCommand(int _command,char* _program_to_run){
	if(_command <= 0 && _command >= SIZE) return; //only 31 commands
	strcpy(commands[_command],_program_to_run);
}
void NetConnector::addCommand(int _command, char* _program_to_run,char* _commandLine_Param){
	if(_command <= 0 && _command >= SIZE) return; //only 31 commands
	strcpy(commands[_command],_program_to_run);
	strcpy(cmdParam[_command],_commandLine_Param);
}
void NetConnector::addCommand(int _command, char* _program_to_run,char* _commandLine_Param,char* _cmdFolder){
	if(_command <= 0 && _command >= SIZE) return; //only 31 commands
	strcpy(commands[_command],_program_to_run);
	strcpy(cmdParam[_command],_commandLine_Param);
	strcpy(cmdFolder[_command],_cmdFolder);
}
void NetConnector::runCommand(int _command){
	dbExecuteFile(commands[_command],cmdParam[_command],cmdFolder[_command]);
}
#endif
	