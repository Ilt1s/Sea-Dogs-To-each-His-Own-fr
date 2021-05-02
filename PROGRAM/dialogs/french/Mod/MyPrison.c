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
        case "PrisonRoom_A":  
			dialog.text = DLG_TEXT_BASE[968];
			link.l1 =DLG_TEXT_BASE[969];
			link.l1.go = "exit";						 
			if (GetPrisonerQty() > 0)
            {
			link.l2 = DLG_TEXT_BASE[975];
			link.l2.go = "sell_prisoner";
            }
			if (npchar.prisoner >= 1)
        	{		
			link.l4 = DLG_TEXT_BASE[992];
			link.l4.go = "Prisoner_Back";	
			}
            break;

		case "sell_prisoner":
			if (npchar.prisoner >= 5)
        	{		
			dialog.text = DLG_TEXT_BASE[986];
			link.l1 =DLG_TEXT_BASE[987];
			link.l1.go = "exit";
			}			
			else		          		   
			{		
			dialog.text = DLG_TEXT_BASE[977];
			qty = 1;
				for(i=0; i < GetPassengersQuantity(pchar); i++)
				{
				cn = GetPassenger(pchar,i);
					if(cn != -1)
					{
					offref = GetCharacter(cn);
						if(CheckAttribute(offref,"prisoned"))
						{
							if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
							{
							attrLoc = "l"+qty;
							link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
							link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
							qty++;
							}
						}
					}
				}
			link.l99 = DLG_TEXT_BASE[978];
			link.l99.go = "exit";
			}			      						
			break;	

		case "sell_prisoner_2":
			offref = GetCharacter(sti(npchar.GenQuest.GetPrisonerIdx));
			attrLoc =  DLG_TEXT_BASE[979] + GetFullName(offref) + "...";                     
			dialog.text = attrLoc;	
			link.l1 = DLG_TEXT_BASE[980] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Prison";
			link.l3 = DLG_TEXT_BASE[978];
			link.l3.go = "exit";
			break;			

		case "Prison":
			DialogExit();
			i=1;
			while(i!=0)
			{
				if(CheckAttribute(npchar, "cell"+i)) i++;
				else
				{
				attrLoc = "cell"+i;
				npchar.(attrLoc) = true;
				npchar.prisoner = sti(npchar.prisoner)+1;
				offref = GetCharacter(sti(npchar.GenQuest.GetPrisonerIdx));
				offref.Dialog.Filename = "Mod\MyOwn_Guards.c";
				offref.dialog.currentnode = "Prison_Node_Man";
				offref.money = "0";			
				ChangeCharacterAddressGroup(offref,"MyOwn_Prison","prison","prison"+i);
				LAi_SetGroundSitType(offref);
				ReleasePrisoner(offref); 
				LAi_SetImmortal(offref, true);				
				DeleteAttribute(offref, "LifeDay");	
				offref.id = "MyPrisonner"+i;
				i=0;
				}
			}
			break;	

		case "Prisoner_Back":													
			dialog.text = DLG_TEXT_BASE[991];
			link.l1 = DLG_TEXT_BASE[978];
			link.l1.go = "exit";
			qty = 2;
			for(i=1; i <= 5; i++)
			{
				if(CheckAttribute(npchar,"cell"+i))
				{
				offref = CharacterFromID("MyPrisonner"+i);
				attrLoc = "l"+qty;
				link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
				link.(attrLoc).go = "GetMyPrisonerIdx_" + offref.index;
				qty++;					
				}
			}			
			break;	

		case "BackPrison":
			rCharacter = GetCharacter(sti(npchar.GenQuest.GetMyPrisonerIdx));	
			i = 1;
			while(i!=0)
			{
				if(rCharacter.id == "MyPrisonner"+i) 
				{
				DeleteAttribute(npchar, "cell"+i); 
				i=0;
				}
				else i++;
			}	
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
            SetCharToPrisoner(rCharacter);
			LAi_SetImmortal(rCharacter, false);
			npchar.prisoner = sti(npchar.prisoner)-1;
			dialog.text = DLG_TEXT_BASE[1639]+GetFullName(rCharacter)+" sur votre vaiseau.";
			link.l1 = DLG_TEXT_BASE[1640];
			link.l1.go = "exit";			
			break;				
	}
	
}
