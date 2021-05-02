// boal 25/04/04 общий диалог мэры
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "SD\TEXT\DIALOGS\Mod\Pirates.h"
void ProcessDialogEvent()
{
    ref NPChar,mainChr, sld,ch,chr,rCharacter,aCharacter,bCharacter,cCharacter,dCharacter;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

        ref mc = GetMainCharacter(); 

    ref offref;
    //int iColony;	
    int i, cn, iRank, iColony, iTest, qty, iTemp, aTemp;
	//int iTest;	
    //iTest = FindColony(NPChar.City); // город 
    ref rColony;	
    string sGroup;		
    //int qty;
    string attrLoc, QuestName, sTemp, bTemp;
	bool   bOk;
 	
 	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	npchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
  	if (findsubstr(attrLoc, "GetMyPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	npchar.GenQuest.GetMyPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "BackPrison";
 	}	
	
	switch (Dialog.CurrentNode)
	{	
		case "Exit":
			npchar.dialog.currentnode = "PrisonRoom_A";
			DialogExit();
			//AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "CitizenNotBlade":		
     		dialog.text = DLG_TEXT_BASE[972];
			link.l1 =DLG_TEXT_BASE[973];
			link.l1.go = "exit";					
        break;			

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "MyTavern":		
     		dialog.text = "Bienvenue capitaine, je vous sers quelque chose ?";
			link.l1 = "Non rien pour l'instant";
			link.l1.go = "exit";					
        break;	

	}
	
}
