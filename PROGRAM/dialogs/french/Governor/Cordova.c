#include "SD\TEXT\DIALOGS\Quest_Governor.h"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = DLG_TEXT_GUB[356];
			link.l1 = DLG_TEXT_GUB[355];
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";			
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}