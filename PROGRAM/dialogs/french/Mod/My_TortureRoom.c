// boal 25/04/04 общий диалог мэры
#include "SD\DIALOGS\russian\Rumours\Common_rumours.c"  //homo 25/06/06
#include "SD\TEXT\DIALOGS\Mod\Pirates.h"
void ProcessDialogEvent()
{
    ref NPChar,mainChr, sld,ch,chr,aCharacter,bCharacter,cCharacter,dCharacter;
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
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
	 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
										
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       case "TortureRoom_A": // 				        												
			NextDiag.TempNode = "TortureRoom_A";
  			dialog.text = DLG_TEXT_BASE[968];
			link.l1 =DLG_TEXT_BASE[969];
			link.l1.go = "exit";	
            if (GetPrisonerQty() > 0)
            {
			link.l2 = DLG_TEXT_BASE[1033];
			link.l2.go = "sell_prisoner";
            }
            if (npchar.prisoner >= 1) 
			{
			link.l3 =DLG_TEXT_BASE[992];
			link.l3.go = "Prisoner_Back";
			}
        break;
							
////////////////////////////////////////////////////////////////////////////////
		case "sell_prisoner":
			if (npchar.prisoner >= 2)
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
					sld = GetCharacter(cn);
						if(CheckAttribute(sld,"prisoned"))
						{
							if(sti(sld.prisoned)==true && GetRemovable(sld)) // ставим только фантомов
							{
							attrLoc = "l"+qty;
							link.(attrLoc)    = GetFullName(sld) + " - " + NationNameMan(sti(sld.nation)) + ".";
							link.(attrLoc).go = "GetPrisonerIdx_" + sld.index;
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
            sld = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  DLG_TEXT_BASE[979] + GetFullName(sld) + "...";                       
			dialog.text = attrLoc;	
			link.l1 = DLG_TEXT_BASE[980] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "DonjonPrison_1";
			link.l2 = DLG_TEXT_BASE[978];
			link.l2.go = "exit";
		break;
						
		case "DonjonPrison_1":	
			DialogExit();
			sld = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
	        sld.Dialog.Filename = "Mod\My_TortureRoom.c";
            sld.dialog.currentnode = "Prison_Node_Man";
			sld.money = "0";
			LAi_SetGroundSitType(sld);
			ReleasePrisoner(sld); 
			LAi_SetImmortal(sld, true);				
			DeleteAttribute(sld, "LifeDay");	
			npchar.prisoner = sti(npchar.prisoner)+1;				
		if (CheckAttribute(npchar, "cell2"))
			{	
			npchar.cell1 = true;
			ChangeCharacterAddressGroup(sld,"MyOwn_TortureRoom","prison","prison3");			
			sld.id = "MyPrisonnerTorture1";
            }			
            else		
            {	
			npchar.cell2 = true;			
			ChangeCharacterAddressGroup(sld,"MyOwn_TortureRoom","prison","prison4");
            sld.id = "MyPrisonnerTorture2";	
            }			
		break;	
		
		case "Prisoner_Back":													
			dialog.text = DLG_TEXT_BASE[991];
			link.l1 = DLG_TEXT_BASE[978];
			link.l1.go = "exit"; //		
        if (CheckAttribute(npchar, "cell1")) 
			{		
			sld = CharacterFromID("MyPrisonnerTorture1");			
			link.l2 = GetFullName(sld) + "...";
			link.l2.go = "BackPrison_1";											
			}				
        if (CheckAttribute(npchar, "cell2")) 
			{		
			sld = CharacterFromID("MyPrisonnerTorture2");			
			link.l3 = GetFullName(sld) + "...";
			link.l3.go = "BackPrison_2";											
			}			
		break;	

		case "BackPrison_1":
			DialogExit();	
			sld = CharacterFromID("MyPrisonnerTorture1");			
            ChangeCharacterAddressGroup(sld, "none", "", "");
            SetCharToPrisoner(sld);	
			LAi_SetImmortal(sld, false);			
			DeleteAttribute(npchar, "cell1");
			npchar.prisoner = sti(npchar.prisoner)-1;			
		break;	
		
		case "BackPrison_2":
			DialogExit();	
			sld = CharacterFromID("MyPrisonnerTorture2");
            ChangeCharacterAddressGroup(sld, "none", "", "");
            SetCharToPrisoner(sld);	
			LAi_SetImmortal(sld, false);			
			DeleteAttribute(npchar, "cell2");
			npchar.prisoner = sti(npchar.prisoner)-1;			
		break;
	
        case "Prison_Node_Man": // 
			NextDiag.TempNode = "Prison_Node_Man";	
		    dialog.text = DLG_TEXT_BASE[1016];
			link.l1 = DLG_TEXT_BASE[1017];
			link.l1.go = "exit";	
			link.l2 =DLG_TEXT_BASE[1012];
			link.l2.go = "IsBaseCity";					
        break;	

		case "IsBaseCity":			
		    dialog.text = DLG_TEXT_BASE[1016];
			link.l1 = DLG_TEXT_BASE[1017];
			link.l1.go = "exit";						
        break;		
	}
	
}
