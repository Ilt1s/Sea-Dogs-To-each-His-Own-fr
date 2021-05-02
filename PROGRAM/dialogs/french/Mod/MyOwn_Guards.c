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
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
	
	switch (Dialog.CurrentNode)
	{	
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			//AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "CitizenNotBlade":		
     		dialog.text = DLG_TEXT_BASE[972];
			link.l1 =DLG_TEXT_BASE[973];
			link.l1.go = "exit";					
            break;			
		
		            case "First time":    
	                    NextDiag.TempNode = "First time"; 	
 	                    {
				    switch (rand(3))
                        {
                        case 0 :
         			    dialog.text = DLG_TEXT_BASE[950]; // <------ 
				        link.l1 =DLG_TEXT_BASE[951];
				        link.l1.go = "exit";	
                        break;    				
                        case 1 :
                        dialog.text = DLG_TEXT_BASE[952]; //<------
				        link.l1 =DLG_TEXT_BASE[953];
				        link.l1.go = "exit";
                        break;
                        case 2 :
      			        dialog.text = DLG_TEXT_BASE[954]; //<------
				        link.l1 =DLG_TEXT_BASE[955];
				        link.l1.go = "exit";	
                        break;   	
                        case 3 :
                        dialog.text = DLG_TEXT_BASE[956]; //<------
				        link.l1 =DLG_TEXT_BASE[957];
				        link.l1.go = "exit";
                        break;						
	                    }							
	                    }	
                        break;
						
		
		            case "PlantationGuard":    
	                    NextDiag.TempNode = "PlantationGuard"; 	
 	                    {
				    switch (rand(2))
                        {
                        case 0 :
         			    dialog.text = DLG_TEXT_BASE[1524]; // <------ 
				        link.l1 =DLG_TEXT_BASE[1525];
				        link.l1.go = "exit";	
                        break;    				
                        case 1 :
                        dialog.text = DLG_TEXT_BASE[1526]; //<------
				        link.l1 =DLG_TEXT_BASE[1527];
				        link.l1.go = "exit";
                        break;
                        case 2 :
      			        dialog.text = DLG_TEXT_BASE[1528]; //<------
				        link.l1 =DLG_TEXT_BASE[1529];
				        link.l1.go = "exit";	
                        break;   					
	                    }							
	                    }	
                        break;	

		            case "My_PlantationSlave":    
	                    NextDiag.TempNode = "My_PlantationSlave"; 	
 	                    {
				    switch (rand(2))
                        {
                        case 0 :
         			    dialog.text = DLG_TEXT_BASE[1530]; // <------ 
				        link.l1 =DLG_TEXT_BASE[1531];
				        link.l1.go = "exit";	
                        break;    				
                        case 1 :
                        dialog.text = DLG_TEXT_BASE[1532]; //<------
				        link.l1 =DLG_TEXT_BASE[1533];
				        link.l1.go = "exit";
                        break;
                        case 2 :
      			        dialog.text = DLG_TEXT_BASE[1534]; //<------
				        link.l1 =DLG_TEXT_BASE[1535];
				        link.l1.go = "exit";	
                        break;   					
	                    }							
	                    }	
                        break;								
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		            case "TortureShack":    
	                    NextDiag.TempNode = "TortureShack"; 				
 	                    {
				    switch (rand(3))
                        {
                        case 0 :
         			    dialog.text = DLG_TEXT_BASE[958]; // <------ 
				        link.l1 =DLG_TEXT_BASE[959];
				        link.l1.go = "exit";	
                        break;    				
                        case 1 :
                        dialog.text = DLG_TEXT_BASE[960]; //<------
				        link.l1.go = "exit";
                        break;
                        case 2 :
      			        dialog.text = DLG_TEXT_BASE[960]; //<------
				        link.l1.go = "exit";	
                        break;   	
                        case 3 :
                        dialog.text = DLG_TEXT_BASE[961]; //<------
				        link.l1 =DLG_TEXT_BASE[962];
				        link.l1.go = "exit";
                        break;						
	                    }							
	                    }			
                        break;						
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                   case "CashRoom_A": // 
				        NextDiag.TempNode = "CashRoom_A";
  			            dialog.text = DLG_TEXT_BASE[963];
				        link.l1 =DLG_TEXT_BASE[964];
				        link.l1.go = "exit";	
				        link.l2 =DLG_TEXT_BASE[965]; //  
				        link.l2.go = "CashRoom_Work";							
                        break;
						
                  case "CashRoom_Work": // 
  			            dialog.text = DLG_TEXT_BASE[966];
				        link.l1 =DLG_TEXT_BASE[967];
				        link.l1.go = "exit";						
	                	break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    case "PrisonRoom_A":  
					    cCharacter = CharacterFromID("TortureRoomMan");
						dCharacter = CharacterFromID("Testo");
				        NextDiag.TempNode = "PrisonRoom_A";
                    if (GetCharacterItem(npchar, "Pirate_Note_IK") >= 1 || GetCharacterItem(npchar, "Pirate_Note_IL") >= 1 )//
	                    {			
						sTemp = (GetCharacterItem(npchar, "Pirate_Note_IK"));
						bTemp = (GetCharacterItem(npchar, "Pirate_Note_IL"));
 			            dialog.text = DLG_TEXT_BASE[1588]+sTemp+DLG_TEXT_BASE[1589]+bTemp+DLG_TEXT_BASE[1591];
				        link.l1 =DLG_TEXT_BASE[1590];
				        link.l1.go = "exit";	
						TakenItems(npchar, "Pirate_Note_IK", -5);
						TakenItems(npchar, "Pirate_Note_IL", -3);
                        }
					   else
                        {
  			            dialog.text = DLG_TEXT_BASE[968];
				        link.l1 =DLG_TEXT_BASE[969];
				        link.l1.go = "exit";	
                    if (GetPrisonerQty() > 0)
                        {
				        link.l2 = DLG_TEXT_BASE[975];
				        link.l2.go = "sell_prisoner";
                        }
					if (GetCharacterItem(Pchar, "QstWifeOnShip") >= 1 || GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1 || GetCharacterItem(Pchar, "Pirate_Note_E") >= 1 || GetCharacterItem(Pchar, "Pirate_Note_EG") >= 1 || GetCharacterItem(Pchar, "Pirate_Note_K") >= 1 || GetCharacterItem(Pchar, "Pirate_Note_M") >= 1)  
               	        {	
						link.l3 =DLG_TEXT_BASE[976];
				        link.l3.go = "DamselInPrison";								
                        }	
			        if (GetCharacterItem(NPchar, "Pirate_Note_FS") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FT") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FU") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FV") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FW") >= 1 )
				        {		
				        link.l4 =DLG_TEXT_BASE[992];
				        link.l4.go = "Prisoner_Back";											
						}	
			        if (GetCharacterItem(NPchar, "Pirate_Note_FY") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FZ") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_GB") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FX") >= 1)
				        {		
				        link.l5 =DLG_TEXT_BASE[1004];
				        link.l5.go = "PrisonerGirl_Back";											
						}	
			        if (GetCharacterItem(dCharacter, "Pirate_Note_FN") >= 1 && sti(GetCharacterItem(NPchar, "Pirate_Note_FY") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FZ") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_GB") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FX") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FS") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FT") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FU") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FV") >= 1 || GetCharacterItem(NPchar, "Pirate_Note_FW") >= 1))
				        {		
				        link.l6 =DLG_TEXT_BASE[1039];
				        link.l6.go = "PrisonerToDonjon";											
						}
						}						
                        break;

		case "PrisonerToDonjon":
			dialog.text = DLG_TEXT_BASE[1040];
			link.l1 = DLG_TEXT_BASE[978];
			link.l1.go = "exit"; //	
        if (GetCharacterIndex("MyGirlPrisonner_9A") != -1) 
	        {
			aCharacter = CharacterFromID("MyGirlPrisonner_9A"); //TEST
			link.l2 = GetFullName(aCharacter)+ "...";
			link.l2.go = "GirlPrisonner_9A_toDonjon";		
		    }	
        if (GetCharacterIndex("MyGirlPrisonner_9B") != -1) 
	        {
			bCharacter = CharacterFromID("MyGirlPrisonner_9B"); //TEST
			link.l3 = GetFullName(bCharacter)+ "...";
			link.l3.go = "GirlPrisonner_9B_toDonjon";		
		    }	
        if (GetCharacterIndex("MyGirlPrisonner_9C") != -1) 
	        {
			cCharacter = CharacterFromID("MyGirlPrisonner_9C"); //   TEST                 
			link.l4 = GetFullName(cCharacter)+ "...";
			link.l4.go = "GirlPrisonner_9C_toDonjon";		
		    }								
        if (GetCharacterItem(NPchar, "Pirate_Note_FX") >= 1) //TEST
	        {
			chr = CharacterFromID("MyGirlPrisonner_6");
			link.l6 = GetFullName(chr)+ "...";
			link.l6.go = "GirlSlave_toDonjon";						
	        }
        if (GetCharacterItem(NPchar, "Pirate_Note_FS") >= 1) 
			{		
			rCharacter = CharacterFromID("MyPrisonner_1");			
			link.l8 = GetFullName(rCharacter) + "...";
			link.l8.go = "Prison_1_toDonjon";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FT") >= 1) 
			{				
			aCharacter = CharacterFromID("MyPrisonner_2");
			link.l9 = GetFullName(aCharacter) + "...";
			link.l9.go = "Prison_2_toDonjon";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FU") >= 1) 
			{		
			bCharacter = CharacterFromID("MyPrisonner_3");
			link.l10 = GetFullName(bCharacter) + "...";
			link.l10.go = "Prison_3_toDonjon";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FV") >= 1) 
			{		
			cCharacter = CharacterFromID("MyPrisonner_4");
			link.l11 = GetFullName(cCharacter) + "...";
			link.l11.go = "Prison_4_toDonjon";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FW") >= 1) 
			{	
			dCharacter = CharacterFromID("MyPrisonner_5");
			link.l12 = GetFullName(dCharacter) + "...";
			link.l12.go = "Prison_5_toDonjon";											
			}					
            break;	
						
		case "PrisonerGirl_Back":		   
			dialog.text = DLG_TEXT_BASE[1002];
			link.l1 = DLG_TEXT_BASE[978];
			link.l1.go = "exit"; //	
     if (GetCharacterIndex("MyGirlPrisonner_9A") != -1) 
	        {
			aCharacter = CharacterFromID("MyGirlPrisonner_9A"); //test ok
			link.l2 = GetFullName(aCharacter)+ "...";
			link.l2.go = "TakeBackGirlPrisonner_9A";		
		    }	
    if (GetCharacterIndex("MyGirlPrisonner_9B") != -1) 
	        {
			bCharacter = CharacterFromID("MyGirlPrisonner_9B"); //test ok
			link.l3 = GetFullName(bCharacter)+ "...";
			link.l3.go = "TakeBackGirlPrisonner_9B";		
		    }	
    if (GetCharacterIndex("MyGirlPrisonner_9C") != -1) 
	        {
			cCharacter = CharacterFromID("MyGirlPrisonner_9C"); //test ok                    
			link.l4 = GetFullName(cCharacter)+ "...";
			link.l4.go = "TakeBackGirlPrisonner_9C";		
		    }								
        if (GetCharacterItem(NPchar, "Pirate_Note_FY") >= 1) //test ok
	        {                    
			ch = CharacterFromID("MoorsWife");
			link.l5 = GetFullName(ch)+ "...";
			link.l5.go = "TakeBackMoorsWo_A";							                    				
	        }	
        if (GetCharacterItem(NPchar, "Pirate_Note_FX") >= 1) //test ok
	        {
			chr = CharacterFromID("MyGirlPrisonner_6");
			link.l6 = GetFullName(chr)+ "...";
			link.l6.go = "TakeBackGirlSlave_A";						
	        }	
        if (GetCharacterItem(NPchar, "Pirate_Note_FZ") >= 1) //test ok
            {
		    rCharacter = CharacterFromID("MyGirlPrisonner_8");		
			link.l7 = GetFullName(rCharacter)+ "...";
			link.l7.go = "TakeBackLewWife_A";
	        }				
            break;						
						
		case "DamselInPrison":	
	       if (GetCharacterItem(NPchar, "Pirate_Note_GA") >= 6)
	        {
			dialog.text = DLG_TEXT_BASE[999];
			link.l1 = DLG_TEXT_BASE[1000];
			link.l1.go = "exit"; //					
	        }	
           else
	        {		   
			dialog.text = DLG_TEXT_BASE[993];
			link.l1 = DLG_TEXT_BASE[978];
			link.l1.go = "exit"; //	
        if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1)
	        {
			sld = CharacterFromID("Rapt_Girl");
			link.l2 = GetFullName(sld)+ "...";
			link.l2.go = "SellRapt_Girl_A";						
	        }	
        if (GetCharacterItem(Pchar, "Pirate_Note_E") >= 1 || GetCharacterItem(Pchar, "Pirate_Note_EG") >= 1 )
	        {                    
			ch = CharacterFromID("MoorsWife");
			link.l3 = GetFullName(ch)+ "...";
			link.l3.go = "SellMoorsWo_A";							                    				
	        }	
        if (GetCharacterItem(Pchar, "Pirate_Note_K") >= 1 || GetCharacterItem(Pchar, "Pirate_Note_M") >= 1)
	        {
			chr = CharacterFromID("GirlSlave");
			link.l4 = GetFullName(chr)+ "...";
			link.l4.go = "SellGirlSlave_A";						
	        }	
	        }			
            break;
////////////////////////////////////////////////////////////////////////////////				
		case "SellMoorsWo_A":
        if (GetCharacterItem(NPchar, "Pirate_Note_FY") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[997];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {
	        sld = CharacterFromID("MoorsWife");
       		dialog.text = DLG_TEXT_BASE[994]+GetFullName(sld)+DLG_TEXT_BASE[995];
           	link.l1 =DLG_TEXT_BASE[996];
		    link.l1.go = "SellMoorsWo_B";
            }			
            break;

		case "SellMoorsWo_B":           
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");								
			sld = CharacterFromID("MoorsWife");
			{
 	        RemovePassenger(pchar, sld); 
            ChangeCharacterAddressGroup(sld, "MyOwn_Prison", "goto", "goto9");
			LAi_SetLoginTime(sld, 0.0, 24.0);
			sld.dialog.currentnode = "Trick_C";
			LAi_SetCitizenType(sld);						
            }		
			TakenItems(Pchar, "Pirate_Note_E",-1);
			TakenItems(Pchar, "Pirate_Note_EG",-1);
			TakenItems(NPchar, "Pirate_Note_FY",1);
			TakenItems(NPchar, "Pirate_Note_GA",1);
            OfficersReaction("bad");
            break;			
	
		case "TakeBackMoorsWo_A":           
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");								
			sld = CharacterFromID("MoorsWife");
			{
 	        AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
            ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto2");
			LAi_SetLoginTime(sld, 0.0, 24.0);
			sld.dialog.currentnode = "WifeDeck_A_A";
			LAi_SetCitizenType(sld);						
            }		
			TakenItems(Pchar, "Pirate_Note_E",1);
			TakenItems(NPchar, "Pirate_Note_FY",-1);
			TakenItems(NPchar, "Pirate_Note_GA",-1);
            break;	
		
////////////////////////////////////////////////////////////////////////////////				
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////										
								
		case "SellRapt_Girl_A":
        if (GetCharacterItem(NPchar, "Pirate_Note_GB") >= 3) 
			{				
       		dialog.text = DLG_TEXT_BASE[997];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {
	        rCharacter = CharacterFromID("Rapt_Girl");
       		dialog.text = DLG_TEXT_BASE[994]+GetFullName(rCharacter)+DLG_TEXT_BASE[995];
           	link.l1 =DLG_TEXT_BASE[996];
		    link.l1.go = "SellRapt_Girl_B";
            }			
            break;

		case "SellRapt_Girl_B":           
   		    NextDiag.CurrentNode = NextDiag.TempNode;
	    	TakenItems(NPchar, "Pirate_Note_GA",1);
            TakenItems(NPchar, "Pirate_Note_GB", 1);
			TakenItems(Pchar, "Pirate_Note_GB",-1);
			
			PChar.quest.PrisonQst.win_condition.l1            = "Timer";
            PChar.quest.PrisonQst.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 5);
            PChar.quest.PrisonQst.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.PrisonQst.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.PrisonQst.function	= "PrisonQst";				
			
            OfficersReaction("bad");			
			DialogExit();
			DoReloadCharacterToLocation("MyOwn_Prison", "reload", "reload1")
			AddDialogExitQuest("MainHeroFightModeOff");			
 			rCharacter = CharacterFromID("Rapt_Girl");
    if (GetCharacterIndex("MyGirlPrisonner_9A") != -1) 
	       {	
        if (GetCharacterIndex("MyGirlPrisonner_9B") != -1) 
	        {		
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_9C", rCharacter.model, "woman", "woman", rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Woman";
			ch.reputation = rCharacter.reputation;
			//DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "goto";
	        ch.location.locator = "goto9";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);	
	        RemovePassenger(pchar, rCharacter); 
            LAi_KillCharacter(rCharacter); 			
		    }	
           else
		    {
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_9B", rCharacter.model, "woman", "woman", rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Woman";
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "goto";
	        ch.location.locator = "goto9";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);	
	        RemovePassenger(pchar, rCharacter); 
            LAi_KillCharacter(rCharacter); 			
			}		
		    }	
           else
		    {	
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_9A", rCharacter.model, "woman", "woman", rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Woman";
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "goto";
	        ch.location.locator = "goto9";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        RemovePassenger(pchar, rCharacter); 
            LAi_KillCharacter(rCharacter); 	 		
		    }			
            break;	
			
		case "TakeBackGirlPrisonner_9A":   
       if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1003];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");								
			rCharacter = CharacterFromID("MyGirlPrisonner_9A");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.rank 	= 3;
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
	    	TakenItems(NPchar, "Pirate_Note_GA",-1);
            TakenItems(NPchar, "Pirate_Note_GB",-1);
			DoReloadCharacterToLocation("MyOwn_Prison", "goto", "goto13")
            }			
            break;		

		case "TakeBackGirlPrisonner_9B":   
       if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1003];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");								
			rCharacter = CharacterFromID("MyGirlPrisonner_9B");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.rank 	= 3;
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
	    	TakenItems(NPchar, "Pirate_Note_GA",-1);
            TakenItems(NPchar, "Pirate_Note_GB",-1);
			DoReloadCharacterToLocation("MyOwn_Prison", "goto", "goto13")
            }			
            break;	

		case "TakeBackGirlPrisonner_9C":   
       if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1003];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");								
			rCharacter = CharacterFromID("MyGirlPrisonner_9C");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.rank 	= 3;
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
	    	TakenItems(NPchar, "Pirate_Note_GA",-1);
            TakenItems(NPchar, "Pirate_Note_GB",-1);
			DoReloadCharacterToLocation("MyOwn_Prison", "goto", "goto13")
            }			
            break;		

		case "GirlPrisonner_9A_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
        if (GetCharacterItem(cCharacter, "Pirate_Note_GC") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[997];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {			
       		dialog.text = DLG_TEXT_BASE[1035];
           	link.l1 =DLG_TEXT_BASE[1036];
		    link.l1.go = "GirlPrisonner_9A_toDonjon_B";
            }				
            break;	

		case "GirlPrisonner_9A_toDonjon_B":           
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
	        rCharacter = CharacterFromID("MyGirlPrisonner_9A");
			cCharacter = CharacterFromID("TortureRoomMan");
	        {		
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_9D", rCharacter.model, "woman", "woman", rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
			ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison3";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);	
		    }		
	    	TakenItems(NPchar, "Pirate_Note_GA",-1);
            TakenItems(NPchar, "Pirate_Note_GB",-1);
	    	TakenItems(cCharacter, "Pirate_Note_GC",1);
            TakenItems(cCharacter, "Pirate_Note_GB", 1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            OfficersReaction("bad");
            DoReloadCharacterToLocation("MyOwn_Prison", "goto", "goto13")			
            break;	

		case "GirlPrisonner_9B_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
        if (GetCharacterItem(cCharacter, "Pirate_Note_GC") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[997];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {			
       		dialog.text = DLG_TEXT_BASE[1035];
           	link.l1 =DLG_TEXT_BASE[1036];
		    link.l1.go = "GirlPrisonner_9B_toDonjon_B";
            }				
            break;	

		case "GirlPrisonner_9B_toDonjon_B":           
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
	        rCharacter = CharacterFromID("MyGirlPrisonner_9B");
			cCharacter = CharacterFromID("TortureRoomMan");
	        {		
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_9D", rCharacter.model, "woman", "woman", rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
			ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison3";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);	
		    }		
	    	TakenItems(NPchar, "Pirate_Note_GA",-1);
            TakenItems(NPchar, "Pirate_Note_GB",-1);
	    	TakenItems(cCharacter, "Pirate_Note_GC",1);
            TakenItems(cCharacter, "Pirate_Note_GB", 1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            OfficersReaction("bad");
			DoReloadCharacterToLocation("MyOwn_Prison", "goto", "goto13")
            break;	

		case "GirlPrisonner_9C_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
        if (GetCharacterItem(cCharacter, "Pirate_Note_GC") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[997];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {			
       		dialog.text = DLG_TEXT_BASE[1035];
           	link.l1 =DLG_TEXT_BASE[1036];
		    link.l1.go = "GirlPrisonner_9C_toDonjon_B";
            }				
            break;	

		case "GirlPrisonner_9C_toDonjon_B":           
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
	        rCharacter = CharacterFromID("MyGirlPrisonner_9C");
			cCharacter = CharacterFromID("TortureRoomMan");
	        {		
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_9D", rCharacter.model, "woman", "woman", rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
			ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison3";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);	
		    }		
	    	TakenItems(NPchar, "Pirate_Note_GA",-1);
            TakenItems(NPchar, "Pirate_Note_GB",-1);
	    	TakenItems(cCharacter, "Pirate_Note_GC",1);
            TakenItems(cCharacter, "Pirate_Note_GB", 1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            OfficersReaction("bad");
			DoReloadCharacterToLocation("MyOwn_Prison", "goto", "goto13")
            break;					
////////////////////////////////////////////////////////////////////////////////				
		case "SellGirlSlave_A":
       if (GetCharacterItem(NPchar, "Pirate_Note_FX") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[997];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {
	        sld = CharacterFromID("GirlSlave");
       		dialog.text = DLG_TEXT_BASE[994]+GetFullName(sld)+DLG_TEXT_BASE[995];
           	link.l1 =DLG_TEXT_BASE[996];
			link.l1.go = "SellGirlSlave_B";
            }			
            break;

		case "SellGirlSlave_B":           
  		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");		
			sld = CharacterFromID("GirlSlave");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_6", sld.model, "woman", "woman", sld.rank, sld.nation, -1, true));	
	        ch.name 	= sld.name;
	        ch.lastname = sld.lastname;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Woman";
			ch.reputation = sld.reputation;

			//DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "goto";
	        ch.location.locator = "goto9";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 									            
	        RemovePassenger(pchar, sld);  
			TakenItems(Pchar, "Pirate_Note_K",-1);
			TakenItems(Pchar, "Pirate_Note_M",-1);
			TakenItems(NPchar, "Pirate_Note_FX",1);
			TakenItems(NPchar, "Pirate_Note_GA",1);
            OfficersReaction("bad");
			DoQuestFunctionDelay("FreeGirlSlave_B_B", 3.0);
            break;	

		case "TakeBackGirlSlave_A":   
       if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1003];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");								
			rCharacter = CharacterFromID("MyGirlPrisonner_6");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.rank 	= 3;
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);	
			TakenItems(NPchar, "Pirate_Note_FX",-1);
			TakenItems(NPchar, "Pirate_Note_GA",-1);
            }			
            break;	

		case "GirlSlave_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
        if (GetCharacterItem(cCharacter, "Pirate_Note_GC") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[997];
           	link.l1 =DLG_TEXT_BASE[1001];
			link.l1.go = "exit";
            }			
           else		
            {			
       		dialog.text = DLG_TEXT_BASE[1035];
           	link.l1 =DLG_TEXT_BASE[1036];
		    link.l1.go = "GirlSlave_toDonjon_B";
            }				
            break;	

		case "GirlSlave_toDonjon_B":           
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
	        rCharacter = CharacterFromID("MyGirlPrisonner_6");
			cCharacter = CharacterFromID("TortureRoomMan");
	        {		
	        ch = GetCharacter(NPC_GenerateCharacter("MyGirlPrisonner_6B", rCharacter.model, "woman", "woman", rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
			ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison3";
            ch.money = "0";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);	
		    }		
			TakenItems(NPchar, "Pirate_Note_FX",-1);
			TakenItems(NPchar, "Pirate_Note_GA",-1);
	    	TakenItems(cCharacter, "Pirate_Note_GC",1);
            TakenItems(cCharacter, "Pirate_Note_FX", 1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            break;					
////////////////////////////////////////////////////////////////////////////////
			
		case "Prisoner_Back":													
			dialog.text = DLG_TEXT_BASE[991];
			link.l1 = DLG_TEXT_BASE[978];
			link.l1.go = "exit"; //			
        if (GetCharacterItem(NPchar, "Pirate_Note_FS") >= 1) 
			{		
			rCharacter = CharacterFromID("MyPrisonner_1");			
			link.l2 = GetFullName(rCharacter) + "...";
			link.l2.go = "BackPrison_1";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FT") >= 1) 
			{				
			aCharacter = CharacterFromID("MyPrisonner_2");
			link.l3 = GetFullName(aCharacter) + "...";
			link.l3.go = "BackPrison_2";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FU") >= 1) 
			{		
			bCharacter = CharacterFromID("MyPrisonner_3");
			link.l4 = GetFullName(bCharacter) + "...";
			link.l4.go = "BackPrison_3";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FV") >= 1) 
			{		
			cCharacter = CharacterFromID("MyPrisonner_4");
			link.l5 = GetFullName(cCharacter) + "...";
			link.l5.go = "BackPrison_4";											
			}	
       if (GetCharacterItem(NPchar, "Pirate_Note_FW") >= 1) 
			{	
			dCharacter = CharacterFromID("MyPrisonner_5");
			link.l6 = GetFullName(dCharacter) + "...";
			link.l6.go = "BackPrison_5";											
			}			
		break;		

		case "BackPrison_1":
			rCharacter = CharacterFromID("MyPrisonner_1");		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");		
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
            SetCharToPrisoner(rCharacter);	
			TakenItems(NPchar, "Pirate_Note_FS", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);
		break;	
		
		case "Prison_1_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
		rCharacter = CharacterFromID("MyPrisonner_1");
 		if (GetCharacterItem(cCharacter, "Pirate_Note_GD") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "exit";
            }			
           else		
            {					
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");				
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_6", rCharacter.model, "man", rCharacter.model.animation, rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison4";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 		
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            TakenItems(cCharacter, "Pirate_Note_GD", 1);
			TakenItems(NPchar, "Pirate_Note_FS", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);			
            }	
		break;	
		
		case "BackPrison_2":
			aCharacter = CharacterFromID("MyPrisonner_2");	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");		
            ChangeCharacterAddressGroup(aCharacter, "none", "", "");
            SetCharToPrisoner(aCharacter);	
			TakenItems(NPchar, "Pirate_Note_FT", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);
		break;	

		case "Prison_2_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
		rCharacter = CharacterFromID("MyPrisonner_2");
 		if (GetCharacterItem(cCharacter, "Pirate_Note_GD") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "exit";
            }			
           else		
            {					
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");				
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_6", rCharacter.model, "man", rCharacter.model.animation, rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison4";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 		
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            TakenItems(cCharacter, "Pirate_Note_GD", 1);
			TakenItems(NPchar, "Pirate_Note_FT", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);			
            }	
		break;			
		
		case "BackPrison_3":
			bCharacter = CharacterFromID("MyPrisonner_3");	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");		
            ChangeCharacterAddressGroup(bCharacter, "none", "", "");
            SetCharToPrisoner(bCharacter);	
			TakenItems(NPchar, "Pirate_Note_FU", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);
		break;	

		case "Prison_3_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
		rCharacter = CharacterFromID("MyPrisonner_3");
 		if (GetCharacterItem(cCharacter, "Pirate_Note_GD") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "exit";
            }			
           else		
            {					
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");				
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_6", rCharacter.model, "man", rCharacter.model.animation, rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison4";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 		
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            TakenItems(cCharacter, "Pirate_Note_GD", 1);
			TakenItems(NPchar, "Pirate_Note_FU", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);			
            }	
		break;			
		
		case "BackPrison_4":
			cCharacter = CharacterFromID("MyPrisonner_4");	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");		
            ChangeCharacterAddressGroup(cCharacter, "none", "", "");
            SetCharToPrisoner(cCharacter);	
			TakenItems(NPchar, "Pirate_Note_FV", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);
		break;	

		case "Prison_4_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
		rCharacter = CharacterFromID("MyPrisonner_4");
 		if (GetCharacterItem(cCharacter, "Pirate_Note_GD") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "exit";
            }			
           else		
            {					
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");				
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_6", rCharacter.model, "man", rCharacter.model.animation, rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison4";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 		
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            TakenItems(cCharacter, "Pirate_Note_GD", 1);
			TakenItems(NPchar, "Pirate_Note_FV", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);			
            }	
		break;			

		case "BackPrison_5":
			dCharacter = CharacterFromID("MyPrisonner_5");	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");		
            ChangeCharacterAddressGroup(dCharacter, "none", "", "");
            SetCharToPrisoner(dCharacter);	
			TakenItems(NPchar, "Pirate_Note_FW", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);
		break;			
	
		case "Prison_5_toDonjon":
		cCharacter = CharacterFromID("TortureRoomMan");
		rCharacter = CharacterFromID("MyPrisonner_5");
 		if (GetCharacterItem(cCharacter, "Pirate_Note_GD") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "exit";
            }			
           else		
            {					
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");				
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_6", rCharacter.model, "man", rCharacter.model.animation, rCharacter.rank, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\My_TortureRoom.c";
            ch.dialog.currentnode = rCharacter.dialog.currentnode;	
			ch.reputation = rCharacter.reputation;
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_TortureRoom";
	        ch.location.group = "prison";
	        ch.location.locator = "prison4";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 		
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");			
			LAi_KillCharacter(rCharacter);
            TakenItems(cCharacter, "Pirate_Note_GD", 1);
			TakenItems(NPchar, "Pirate_Note_FW", -1);
			TakenItems(NPchar, "Pirate_Note_FP", -1);			
            }	
		break;	
	
 		case "sell_prisoner":
		if (GetCharacterItem(sld, "Pirate_Note_FP") >= 5 )
            {		
 			dialog.text = DLG_TEXT_BASE[986];
			link.l1 =DLG_TEXT_BASE[987];
			link.l1.go = "exit";
            }			
           else		
            {		   
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
			
            }						
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  DLG_TEXT_BASE[979] + GetFullName(offref) + "...";
                        
			dialog.text = attrLoc;	
			link.l1 = DLG_TEXT_BASE[980] + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = DLG_TEXT_BASE[978];
			link.l3.go = "exit";
		break;

		case "sell_prisoner_3":
			dialog.text = DLG_TEXT_BASE[981];
			link.l1 = DLG_TEXT_BASE[978];
			link.l1.go = "exit"; //			
			link.l2 = DLG_TEXT_BASE[982];
			link.l2.go = "Prison1"; //cell 1
			link.l3 = DLG_TEXT_BASE[983];
			link.l3.go = "Prison2"; //cell 2
			link.l4 = DLG_TEXT_BASE[984];
			link.l4.go = "Prison3"; //cell 3
			link.l5 = DLG_TEXT_BASE[985];
			link.l5.go = "Prison4"; //cell 4
			link.l6 = DLG_TEXT_BASE[988];
			link.l6.go = "Prison5"; //cell 5			
		break;						
		
		case "Prison1":	
		if (GetCharacterItem(NPchar, "Pirate_Note_FS") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "sell_prisoner_3";
            }			
           else		
            {					
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");			
			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));            
         	offref.location = "";
			
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_1", offref.model, "man", "man", offref.rank, offref.nation, -1, true));	
	        ch.name 	= offref.name;
	        ch.lastname = offref.lastname;
			ch.City = offref.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Man";
			ch.reputation = offref.reputation;

            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "prison";
	        ch.location.locator = "prison1";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 			
			
        	ReleasePrisoner(offref); // освободили пленника	
            TakenItems(NPchar, "Pirate_Note_FP", 1);	
			TakenItems(NPchar, "Pirate_Note_FS", 1);
			
			PChar.quest.PrisonQst.win_condition.l1            = "Timer";
            PChar.quest.PrisonQst.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.PrisonQst.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.PrisonQst.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.PrisonQst.function	= "PrisonQst";				
            }			
		break;	

		case "Prison2":	
		if (GetCharacterItem(NPchar, "Pirate_Note_FT") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "sell_prisoner_3";
            }			
           else		
            {	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");
			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));            
         	offref.location = "";
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_2", offref.model, "man", "man", offref.rank, offref.nation, -1, true));	
	        ch.name 	= offref.name;
	        ch.lastname = offref.lastname;
			ch.City = offref.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Man";
			ch.reputation = offref.reputation;

            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "prison";
	        ch.location.locator = "prison2";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 			
        	ReleasePrisoner(offref); // освободили пленника	
			TakenItems(NPchar, "Pirate_Note_FP", 1);	
            TakenItems(NPchar, "Pirate_Note_FT", 1);	
			
			PChar.quest.PrisonQst.win_condition.l1            = "Timer";
            PChar.quest.PrisonQst.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.PrisonQst.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.PrisonQst.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.PrisonQst.function	= "PrisonQst";					
            }			
		break;	

		case "Prison3":	
		if (GetCharacterItem(NPchar, "Pirate_Note_FU") >= 1 )
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "sell_prisoner_3";
            }			
           else		
            {		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");
			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));            
         	offref.location = "";
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_3", offref.model, "man", "man", offref.rank, offref.nation, -1, true));	
	        ch.name 	= offref.name;
	        ch.lastname = offref.lastname;
			ch.City = offref.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Man";
			ch.reputation = offref.reputation;

            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "prison";
	        ch.location.locator = "prison3";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 			
        	ReleasePrisoner(offref); // освободили пленника	
			TakenItems(NPchar, "Pirate_Note_FP", 1);
			TakenItems(NPchar, "Pirate_Note_FU", 1);
			
			PChar.quest.PrisonQst.win_condition.l1            = "Timer";
            PChar.quest.PrisonQst.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.PrisonQst.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.PrisonQst.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.PrisonQst.function	= "PrisonQst";					
            }				
		break;	

		case "Prison4":		
		if (GetCharacterItem(NPchar, "Pirate_Note_FV") >= 1 )	
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "sell_prisoner_3";
            }			
           else		
            {	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");
			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));            
      	    offref.location = "";
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_4", offref.model, "man", "man", offref.rank, offref.nation, -1, true));	
	        ch.name 	= offref.name;
	        ch.lastname = offref.lastname;
			ch.City = offref.City;			
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Man";
			ch.reputation = offref.reputation;

            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "prison";
	        ch.location.locator = "prison4";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 			
		    ReleasePrisoner(offref); // освободили пленника	
			TakenItems(NPchar, "Pirate_Note_FP", 1);
			TakenItems(NPchar, "Pirate_Note_FV", 1);
			
			PChar.quest.PrisonQst.win_condition.l1            = "Timer";
            PChar.quest.PrisonQst.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.PrisonQst.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.PrisonQst.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.PrisonQst.function	= "PrisonQst";					
            }				
		break;	

		case "Prison5":	
		if (GetCharacterItem(NPchar, "Pirate_Note_FW") >= 1 )		
            {		
 			dialog.text = DLG_TEXT_BASE[989];
			link.l1 =DLG_TEXT_BASE[990];
			link.l1.go = "sell_prisoner_3";
            }			
           else		
            {		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
			OfficersReaction("bad");
			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));            
         	offref.location = "";			
            {
	        ch = GetCharacter(NPC_GenerateCharacter("MyPrisonner_5", offref.model, "man", "man", offref.rank, offref.nation, -1, true));	
	        ch.name 	= offref.name;
	        ch.lastname = offref.lastname;
			ch.City = offref.City;
            ch.greeting = "Gr_Ransack";
	        ch.Dialog.Filename = "Pirate\MyOwn_Guards.c";
            ch.dialog.currentnode = "Prison_Node_Man";
			ch.reputation = offref.reputation;

            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "MyOwn_Prison";
	        ch.location.group = "prison";
	        ch.location.locator = "prison5";
            ch.money = "0";
	        LAi_SetGroundSitType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
	        } 			
        	ReleasePrisoner(offref); // освободили пленника	
			TakenItems(NPchar, "Pirate_Note_FP", 1);
			TakenItems(NPchar, "Pirate_Note_FW", 1);
			
			PChar.quest.PrisonQst.win_condition.l1            = "Timer";
            PChar.quest.PrisonQst.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
            PChar.quest.PrisonQst.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            PChar.quest.PrisonQst.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            PChar.quest.PrisonQst.function	= "PrisonQst";					
            }			
		break;	
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

      case "Prison_Node_Man": // 
			NextDiag.TempNode = "Prison_Node_Man";	
		    dialog.text = DLG_TEXT_BASE[1016];
			link.l1 = DLG_TEXT_BASE[1017];
			link.l1.go = "exit";				
            break;	
		
	    case "Prison_Node_Woman":  
		    NextDiag.TempNode = "Prison_Node_Woman";	
       		dialog.text = DLG_TEXT_BASE[998];
			link.l1 =DLG_TEXT_BASE[1011];			
			link.l1.go = "exit";					
            break;	
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////*********************brothel dialogue*********************//////////////////////////////////////////////		
	    case "Brothel_GirlPrisonner_A":  //LewWife
		    NextDiag.TempNode = "Brothel_GirlPrisonner_A";	
			aCharacter = CharacterFromID("Testo");
       		//dialog.text = DLG_TEXT_BASE[1041];
dialog.text = npchar.id;
			link.l1 =DLG_TEXT_BASE[1046];			
			link.l1.go = "exit";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_GirlPrisonner_A";	
       if (pchar.location == "MyOwn_Manor_Brothel") 
			{				
			link.l3 =DLG_TEXT_BASE[1326]; //
			link.l3.go = "GirlPrisonner_ToYard";	
			}
          else	
			{				
			link.l3 =DLG_TEXT_BASE[1327]; //
			link.l3.go = "GirlPrisonnerToBrothelFW";	
			}				
        if (GetCharacterItem(aCharacter, "Pirate_Note_FB") >= 1) 
			{				
			link.l4 =DLG_TEXT_BASE[1047]; //My BedRoom
			link.l4.go = "GirlPrisonner_ToMyBedRoom";	
			}		  
        if (GetCharacterItem(aCharacter, "Pirate_Note_FR") >= 1) 
			{				
			link.l5 =DLG_TEXT_BASE[1048]; // Team morale
			link.l5.go = "GirlPrisonner_Morale";	
			}
	if (GetCharacterItem(aCharacter, "Pirate_Note_LZ") >= 1)
	{
	sld = CharacterFromID("MonBarmen");
 	if (GetCharacterItem(sld, "Pirate_Note_LX") == 0)
	{
	link.l6 ="Tu vas aller aider а la taverne."; // Team morale
	link.l6.go = "Tavern";
	}
	}
        break;
	    case "Tavern":  
			DialogExit();
			LAi_SetWaitressType(npchar);
			ChangeCharacterAddressGroup(npchar, "MyOwn_Tavern", "goto", "goto4");
			sld = CharacterFromID("MonBarmen");
			TakenItems(sld, "Pirate_Note_LX", +1);
			bCharacter = CharacterFromID("Testo");
	    		TakenItems(bCharacter, "Pirate_Note_GA",-1);
			if (npchar.id != "MyGirlPrisonner_6X")
			{
            		TakenItems(bCharacter, "Pirate_Note_GB",-1);
			}
			npchar.dialog.currentnode = "Tavern1";
			npchar.id = "Maserveuse";		
            break;
	    case "Tavern1":
      			dialog.text ="Que me voulez vous ?";  
			link.l5 ="Continue ton travail.";
			link.l5.go = "Tavern2";		
            break;
	    case "Tavern2":
			DialogExit();
			npchar.dialog.currentnode = "Tavern1";						
            break;
			
	    case "MaServeuseGood":
			chrDisableReloadToLocation = false;
      		dialog.text = "Capitaine, j'ai cru entendre dire, que vous cherchiez quelqu'un pour travailler ?";
           	link.l1 ="C'est exact, il me faut quelqu'un pour gerer ma taverne dans mon manoir, bien sur vous serez nouris et logee.";
			link.l1.go = "MaServeuseGood1";					
            break;

	    case "MaServeuseGood1":
      		dialog.text = "C'est une offre interessante, mais j'aimerais un suplement de " +(sti(PChar.rank)*1000)+ "  piastres, pour accepter.";
           	link.l1 ="Trop chere pour ma bourse.";
			link.l1.go = "MaServeuseGood2";
           	link.l2 ="Bienvenue dans l'equipe..";
			link.l2.go = "MaServeuseGood3";				
            break;	

	    case "MaServeuseGood2":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "none", "goto", "goto1");
            break;

	    case "MaServeuseGood3":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, "MyOwn_Tavern", "goto", "goto4");
			sld = CharacterFromID("MonBarmen");
			TakenItems(sld, "Pirate_Note_LX", +1);
			npchar.dialog.currentnode = "Tavern1";
			npchar.id = "Maserveuse";
			LAi_SetWaitressType(npchar);
            break;			

		case "GirlPrisonner_ToMyBedRoom"://LewWife
		    aCharacter = CharacterFromID("Testo");		
        if (GetCharacterItem(aCharacter, "Pirate_Note_GE") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1052];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {    		
			NextDiag.CurrentNode = "GirlPrisonner_BedRoom_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Bedroom", "goto", "goto7");
            }				
		break;	

	    case "GirlPrisonner_BedRoom_A":  //LewWife
		    NextDiag.TempNode = "GirlPrisonner_BedRoom_A";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1041];
			link.l1 =DLG_TEXT_BASE[1046];			
			link.l1.go = "exit";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_GirlPrisonner_A";  
			link.l3 =DLG_TEXT_BASE[1053];//<---------------------have fun
			link.l3.go = "GirlPrisonner_HaveFun";	
       if (GetCharacterItem(aCharacter, "Pirate_Note_FI") >= 1)//<----To brothel
			{				
			link.l4 =DLG_TEXT_BASE[1054];			
			link.l4.go = "GirlPrisonnerToBrothel";		
            }							
		break;
		
		 case "GirlPrisonner_HaveFun": 
DialogExit();
AddDialogExitQuestFunction("SexWithHostess_fack");
npchar.dialog.currentnode = "Sexend";




	/*	    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
			
			//iTemp = makeint(pchar.hp)+10
            AddCharacterHealth(pchar, 25);
			//LAi_SetHP(pchar,pchar.hp ,iTemp);
            TakenItems(Pchar, "Pinion",1);
			TakenItems(aCharacter, "Pirate_Note_FZ", -1);
			TakenItems(aCharacter, "Pirate_Note_GA",-1);
			TakenItems(aCharacter, "Pirate_Note_GE", -1);
			TakenItems(aCharacter, "QstWifeOnShip",-1);			
            DoQuestCheckDelay("Kill_GirlPrisonner_8X", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);	*/		
		   





 break;				
		






		case "GirlPrisonner_ToYard":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_GirlPrisonner_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");					
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor", "goto", "goto"+(rand(9)+1));			
		break;	

		case "GirlPrisonnerToBrothelFW":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_GirlPrisonner_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");					
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");			
		break;
		
		case "GirlPrisonnerToBrothel":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_GirlPrisonner_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",-1);		
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");			
		break;		
		
		case "TakeBack_GirlPrisonner_A":   
        if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1050];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");		
			aCharacter = CharacterFromID("Testo");
			rCharacter = CharacterFromID("MyGirlPrisonner_8X");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
			TakenItems(aCharacter, "Pirate_Note_FZ", -1);
			TakenItems(aCharacter, "Pirate_Note_GA",-1);
			TakenItems(aCharacter, "QstWifeOnShip",-1);
			TakenItems(aCharacter, "Pirate_Note_GE",-1);
       if (npchar.location == "MyOwn_Bedroom")	
            {	   
            TakenItems(aCharacter, "Pirate_Note_GE",-1);			
            }			
            }			
            break;
			
		 case "GirlPrisonner_Morale": 
		    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
            AddCrewMorale(Pchar, 100);
            ChangeCrewExp(pchar, "Sailors", 60);
	        ChangeCrewExp(pchar, "Cannoners", 60);
	        ChangeCrewExp(pchar, "Soldiers", 60);
            TakenItems(Pchar, "Pinion",1);
			TakenItems(aCharacter, "Pirate_Note_FZ", -1);
			TakenItems(aCharacter, "Pirate_Note_GA",-1);
			TakenItems(aCharacter, "QstWifeOnShip",-1);			
            DoQuestCheckDelay("Kill_GirlPrisonner_8X", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);			
		    break;			
        ////**************************************************************
	    case "Brothel_GirlSlave_A":  
		    NextDiag.TempNode = "Brothel_GirlSlave_A";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1042];
			link.l1 =DLG_TEXT_BASE[1046];			
			link.l1.go = "exit";
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_GirlSlave_A";
       if (pchar.location == "MyOwn_Manor_Brothel") 
			{				
			link.l3 =DLG_TEXT_BASE[1326]; //
			link.l3.go = "GirlSlave_ToYard";	
			}
          else	
			{				
			link.l3 =DLG_TEXT_BASE[1327]; //
			link.l3.go = "GirlSlaveToBrothelFW";	
			}			
        if (GetCharacterItem(aCharacter, "Pirate_Note_FB") >= 1) 
			{				
			link.l4 =DLG_TEXT_BASE[1047]; //My BedRoom
			link.l4.go = "GirlSlave_ToMyBedRoom";	
			}
        if (GetCharacterItem(aCharacter, "Pirate_Note_FR") >= 1) 
			{				
			link.l5 =DLG_TEXT_BASE[1048]; // Team morale
			link.l5.go = "GirlSlave_Morale";	
			}
	if (GetCharacterItem(aCharacter, "Pirate_Note_LZ") >= 1)
	{
	sld = CharacterFromID("MonBarmen");
 	if (GetCharacterItem(sld, "Pirate_Note_LX") == 0)
	{
	link.l6 ="Tu vas aller aider а la taverne."; // Team morale
	link.l6.go = "Tavern";
	}
	}			
            break;	
			
		case "GirlSlave_ToMyBedRoom"://GirlSlave
		    aCharacter = CharacterFromID("Testo");		
        if (GetCharacterItem(aCharacter, "Pirate_Note_GE") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1052];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {    		
			NextDiag.CurrentNode = "GirlSlave_BedRoom_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Bedroom", "goto", "goto7");
            }				
		break;	

	    case "GirlSlave_BedRoom_A":  //GirlSlave
		    NextDiag.TempNode = "GirlSlave_BedRoom_A";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1041];
			link.l1 =DLG_TEXT_BASE[1133];			
			link.l1.go = "exitSetCitizen";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_GirlSlave_A";  
			link.l3 =DLG_TEXT_BASE[1053];//<---------------------have fun
			link.l3.go = "GirlSlave_HaveFun";	
       if (GetCharacterItem(aCharacter, "Pirate_Note_FI") >= 1)//<----To brothel
			{				
			link.l4 =DLG_TEXT_BASE[1054];			
			link.l4.go = "GirlSlaveToBrothel";		
            }							
		break;
		
		 case "GirlSlave_HaveFun": 
DialogExit();
AddDialogExitQuestFunction("SexWithHostess_fack");
npchar.dialog.currentnode = "Sexend";
		/*    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
			
			//iTemp = makeint(pchar.hp)+10
            AddCharacterHealth(pchar, 25);
			//LAi_SetHP(pchar,pchar.hp ,iTemp);
            TakenItems(Pchar, "Pinion",1);
			TakenItems(aCharacter, "Pirate_Note_FX",-1);
			TakenItems(aCharacter, "Pirate_Note_GA",-1);	
			TakenItems(aCharacter, "Pirate_Note_GE", -1);
            DoQuestCheckDelay("Kill_GirlPrisonner_6X", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);	*/		
		    break;

		case "GirlSlaveToBrothel":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_GirlSlave_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",-1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto2");
			LAi_SetCitizenType(npchar);
		break;	

		case "GirlSlaveToBrothelFW":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_GirlSlave_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto2");
			LAi_SetCitizenType(npchar);
		break;		
		
		case "GirlSlave_ToYard":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_GirlSlave_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor", "goto", "goto"+(rand(7)+1));
			LAi_SetCitizenType(npchar);
		break;					
						
		case "TakeBack_GirlSlave_A":   
        if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1050];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");		
			aCharacter = CharacterFromID("Testo");
			rCharacter = CharacterFromID("MyGirlPrisonner_6X");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
	    	TakenItems(aCharacter, "Pirate_Note_FX",-1);
			TakenItems(aCharacter, "Pirate_Note_GA",-1);
			TakenItems(aCharacter, "Pirate_Note_GE",-1);
        if (npchar.location == "MyOwn_Bedroom")	
            {	   
            TakenItems(aCharacter, "Pirate_Note_GE",-1);			
            }				
            }			
            break;			

		 case "GirlSlave_Morale": 
		    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
            AddCrewMorale(Pchar, 100);
            ChangeCrewExp(pchar, "Sailors", 60);
	        ChangeCrewExp(pchar, "Cannoners", 60);
	        ChangeCrewExp(pchar, "Soldiers", 60);
            TakenItems(Pchar, "Pinion",1);
			TakenItems(aCharacter, "Pirate_Note_FX",-1);
			TakenItems(aCharacter, "Pirate_Note_GA",-1);		
            DoQuestCheckDelay("Kill_GirlPrisonner_6X", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);			
		    break;				
			
        ////*****************************************************************
	    case "Brothel_Rapt_Girl_9E":  
		    NextDiag.TempNode = "Brothel_Rapt_Girl_9E";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1043];
			link.l1 =DLG_TEXT_BASE[1046];			
			link.l1.go = "exit";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_Rapt_Girl_9E";	
       if (pchar.location == "MyOwn_Manor_Brothel") 
			{				
			link.l3 =DLG_TEXT_BASE[1326]; //
			link.l3.go = "Rapt_Girl_9E_ToYard";	
			}
          else	
			{				
			link.l3 =DLG_TEXT_BASE[1327]; //
			link.l3.go = "Rapt_Girl_9EToBrothelFY";	
			}				
        if (GetCharacterItem(aCharacter, "Pirate_Note_FB") >= 1) 
			{				
			link.l4 =DLG_TEXT_BASE[1047]; //My BedRoom
			link.l4.go = "Rapt_Girl_9E_ToMyBedRoom";	
			}	
        if (GetCharacterItem(aCharacter, "Pirate_Note_FR") >= 1) 
			{				
			link.l5 =DLG_TEXT_BASE[1048]; // Team morale
			link.l5.go = "Rapt_Girl_9E_Morale";	
			}
	if (GetCharacterItem(aCharacter, "Pirate_Note_LZ") >= 1)
	{
	sld = CharacterFromID("MonBarmen");
 	if (GetCharacterItem(sld, "Pirate_Note_LX") == 0)
	{
	link.l6 ="Tu vas aller aider а la taverne."; // Team morale
	link.l6.go = "Tavern";
	}
	}			
            break;	
			
		case "Rapt_Girl_9E_ToMyBedRoom"://GirlSlave
		    aCharacter = CharacterFromID("Testo");		
        if (GetCharacterItem(aCharacter, "Pirate_Note_GE") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1052];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {    		
			NextDiag.CurrentNode = "Rapt_Girl_9E_BedRoom_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Bedroom", "goto", "goto7");
            }				
		break;	

	    case "Rapt_Girl_9E_BedRoom_A":  //GirlSlave
		    NextDiag.TempNode = "Rapt_Girl_9E_BedRoom_A";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1041];
			link.l1 =DLG_TEXT_BASE[1133];			
			link.l1.go = "exitSetCitizen";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_Rapt_Girl_9E";  
			link.l3 =DLG_TEXT_BASE[1053];//<---------------------have fun
			link.l3.go = "Rapt_Girl_9E_HaveFun";	
       if (GetCharacterItem(aCharacter, "Pirate_Note_FI") >= 1)//<----To brothel
			{				
			link.l4 =DLG_TEXT_BASE[1054];			
			link.l4.go = "Rapt_Girl_9EToBrothel";		
            }							
		break;
		
		 case "Rapt_Girl_9E_HaveFun":
DialogExit();
AddDialogExitQuestFunction("SexWithHostess_fack"); 
npchar.dialog.currentnode = "Sexend";
		/*    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);			
            AddCharacterHealth(pchar, 25);
            TakenItems(Pchar, "Pinion",1);
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);	
			TakenItems(aCharacter, "Pirate_Note_GE", -1);
            DoQuestCheckDelay("Kill_Rapt_Girl_9E", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);	*/		
		    break;				
		
		case "Rapt_Girl_9EToBrothel":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9E";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE", -1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");
			LAi_SetCitizenType(npchar);
		break;	

	    case "Rapt_Girl_9E_ToYard":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9E";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor", "goto", "goto"+(rand(7)+1));
			LAi_SetCitizenType(npchar);
		break;				
		
	    case "Rapt_Girl_9EToBrothelFY":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9E";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");
			LAi_SetCitizenType(npchar);
		break;				
			
		case "TakeBack_Rapt_Girl_9E":   
        if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1050];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");		
			aCharacter = CharacterFromID("Testo");
			rCharacter = CharacterFromID("MyGirlPrisonner_9E");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);
			TakenItems(aCharacter, "Pirate_Note_GE",-1);
        if (npchar.location == "MyOwn_Bedroom")	
            {	   
            TakenItems(aCharacter, "Pirate_Note_GE",-1);			
            }					
            }			
            break;					
			
		case "Rapt_Girl_9E_Morale": 
		    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
            AddCrewMorale(Pchar, 100);
            ChangeCrewExp(pchar, "Sailors", 60);
	        ChangeCrewExp(pchar, "Cannoners", 60);
	        ChangeCrewExp(pchar, "Soldiers", 60);
            TakenItems(Pchar, "Pinion",1);
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);	
            DoQuestCheckDelay("Kill_Rapt_Girl_9E", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);			
		    break;				

	    case "Brothel_Rapt_Girl_9F":  
		    NextDiag.TempNode = "Brothel_Rapt_Girl_9F";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1044];
			link.l1 =DLG_TEXT_BASE[1046];			
			link.l1.go = "exit";
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_Rapt_Girl_9F";	
      if (pchar.location == "MyOwn_Manor_Brothel") 
			{				
			link.l3 =DLG_TEXT_BASE[1326]; //
			link.l3.go = "Rapt_Girl_9F_ToYard";	
			}
          else	
			{				
			link.l3 =DLG_TEXT_BASE[1327]; //
			link.l3.go = "Rapt_Girl_9FToBrothelFY";	
			}			
        if (GetCharacterItem(aCharacter, "Pirate_Note_FB") >= 1) 
			{				
			link.l4 =DLG_TEXT_BASE[1047]; //My BedRoom
			link.l4.go = "Rapt_Girl_9F_ToMyBedRoom";	
			}
        if (GetCharacterItem(aCharacter, "Pirate_Note_FR") >= 1) 
			{				
			link.l5 =DLG_TEXT_BASE[1048]; // Team morale
			link.l5.go = "Rapt_Girl_9F_Morale";	
			}
	if (GetCharacterItem(aCharacter, "Pirate_Note_LZ") >= 1)
	{
	sld = CharacterFromID("MonBarmen");
 	if (GetCharacterItem(sld, "Pirate_Note_LX") == 0)
	{
	link.l6 ="Tu vas aller aider а la taverne."; // Team morale
	link.l6.go = "Tavern";
	}
	}			
            break;	

		case "Rapt_Girl_9F_ToMyBedRoom"://GirlSlave
		    aCharacter = CharacterFromID("Testo");		
        if (GetCharacterItem(aCharacter, "Pirate_Note_GE") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1052];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {    		
			NextDiag.CurrentNode = "Rapt_Girl_9F_BedRoom_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Bedroom", "goto", "goto7");
            }				
		break;	

	    case "Rapt_Girl_9F_BedRoom_A":  //GirlSlave
		    NextDiag.TempNode = "Rapt_Girl_9F_BedRoom_A";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1041];
			link.l1 =DLG_TEXT_BASE[1133];			
			link.l1.go = "exitSetCitizen";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_Rapt_Girl_9F";  
			link.l3 =DLG_TEXT_BASE[1053];//<---------------------have fun
			link.l3.go = "Rapt_Girl_9F_HaveFun";	
       if (GetCharacterItem(aCharacter, "Pirate_Note_FI") >= 1)//<----To brothel
			{				
			link.l4 =DLG_TEXT_BASE[1054];			
			link.l4.go = "Rapt_Girl_9FToBrothel";		
            }							
		break;
		
		 case "Rapt_Girl_9F_HaveFun":
DialogExit();
AddDialogExitQuestFunction("SexWithHostess_fack");
npchar.dialog.currentnode = "Sexend"; 
		  /*  aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);			
            AddCharacterHealth(pchar, 25);
            TakenItems(Pchar, "Pinion",1);
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);	
			TakenItems(aCharacter, "Pirate_Note_GE", -1);
            DoQuestCheckDelay("Kill_Rapt_Girl_9F", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);	*/		
		    break;	
			
		case "Rapt_Girl_9F_ToYard":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9F";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor", "goto", "goto"+(rand(6)+1));
			LAi_SetCitizenType(npchar);
		break;			

		case "Rapt_Girl_9FToBrothelFY":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9F";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");
			LAi_SetCitizenType(npchar);
		break;		
		
		case "Rapt_Girl_9FToBrothel":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9F";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE", -1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");
			LAi_SetCitizenType(npchar);
		break;		
			
		case "TakeBack_Rapt_Girl_9F":   
        if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1050];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");		
			aCharacter = CharacterFromID("Testo");
			rCharacter = CharacterFromID("MyGirlPrisonner_9F");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);
			TakenItems(aCharacter, "Pirate_Note_GE",-1);
        if (npchar.location == "MyOwn_Bedroom")	
            {	   
            TakenItems(aCharacter, "Pirate_Note_GE",-1);			
            }					
            }			
            break;					

		case "Rapt_Girl_9F_Morale": 
		    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
            AddCrewMorale(Pchar, 100);
            ChangeCrewExp(pchar, "Sailors", 60);
	        ChangeCrewExp(pchar, "Cannoners", 60);
	        ChangeCrewExp(pchar, "Soldiers", 60);
            TakenItems(Pchar, "Pinion",1);
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);	
            DoQuestCheckDelay("Kill_Rapt_Girl_9F", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);			
		    break;					
			
	    case "Brothel_Rapt_Girl_9G":  
		    NextDiag.TempNode = "Brothel_Rapt_Girl_9G";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1045];
			link.l1 =DLG_TEXT_BASE[1046];			
			link.l1.go = "exit";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_Rapt_Girl_9G";	
     if (pchar.location == "MyOwn_Manor_Brothel") 
			{				
			link.l3 =DLG_TEXT_BASE[1326]; //
			link.l3.go = "Rapt_Girl_9G_ToYard";	
			}
          else	
			{				
			link.l3 =DLG_TEXT_BASE[1327]; //
			link.l3.go = "Rapt_Girl_9GToBrothelFY";	
			}				
        if (GetCharacterItem(aCharacter, "Pirate_Note_FB") >= 1) 
			{				
			link.l4 =DLG_TEXT_BASE[1047]; //My BedRoom
			link.l4.go = "Rapt_Girl_9G_ToMyBedRoom";	
			}
        if (GetCharacterItem(aCharacter, "Pirate_Note_FR") >= 1) 
			{				
			link.l5 =DLG_TEXT_BASE[1048]; // Team morale
			link.l5.go = "Rapt_Girl_9G_Morale";	
			}
	if (GetCharacterItem(aCharacter, "Pirate_Note_LZ") >= 1)
	{
	sld = CharacterFromID("MonBarmen");
 	if (GetCharacterItem(sld, "Pirate_Note_LX") == 0)
	{
	link.l6 ="Tu vas aller aider а la taverne."; // Team morale
	link.l6.go = "Tavern";
	}
	}			
            break;	

		case "Rapt_Girl_9G_ToMyBedRoom"://GirlSlave
		    aCharacter = CharacterFromID("Testo");		
        if (GetCharacterItem(aCharacter, "Pirate_Note_GE") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1052];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {    		
			NextDiag.CurrentNode = "Rapt_Girl_9G_BedRoom_A";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Bedroom", "goto", "goto7");
            }				
		break;	

	    case "Rapt_Girl_9G_BedRoom_A":  //GirlSlave
		    NextDiag.TempNode = "Rapt_Girl_9G_BedRoom_A";	
			aCharacter = CharacterFromID("Testo");
       		dialog.text = DLG_TEXT_BASE[1041];
			link.l1 =DLG_TEXT_BASE[1133];			
			link.l1.go = "exitSetCitizen";	
			link.l2 =DLG_TEXT_BASE[1049];			
			link.l2.go = "TakeBack_Rapt_Girl_9G";  
			link.l3 =DLG_TEXT_BASE[1053];//<---------------------have fun
			link.l3.go = "Rapt_Girl_9G_HaveFun";	
       if (GetCharacterItem(aCharacter, "Pirate_Note_FI") >= 1)//<----To brothel
			{				
			link.l4 =DLG_TEXT_BASE[1054];			
			link.l4.go = "Rapt_Girl_9GToBrothel";		
            }							
		break;
		
		 case "Rapt_Girl_9G_HaveFun":
DialogExit();
AddDialogExitQuestFunction("SexWithHostess_fack");
npchar.dialog.currentnode = "Sexend"; 
		/*    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
            AddCharacterHealth(pchar, 25);						
            TakenItems(Pchar, "Pinion",1);
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);
			TakenItems(aCharacter, "Pirate_Note_GE", -1);
            DoQuestCheckDelay("Kill_Rapt_Girl_9G", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);	*/		
		    break;	
			
		case "Rapt_Girl_9G_ToYard":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9G";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor", "goto", "goto"+(rand(7)+1));
			LAi_SetCitizenType(npchar);
		break;			

		case "Rapt_Girl_9GToBrothelFY":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9G";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");
			LAi_SetCitizenType(npchar);
		break;				
		
		case "Rapt_Girl_9GToBrothel":		
		    aCharacter = CharacterFromID("Testo");
			NextDiag.CurrentNode = "Brothel_Rapt_Girl_9G";
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");			
		    TakenItems(aCharacter, "Pirate_Note_GE",-1);
            ChangeCharacterAddressGroup(npchar, "MyOwn_Manor_Brothel", "goto", "goto3");
			LAi_SetCitizenType(npchar);
		break;					
			
		case "TakeBack_Rapt_Girl_9G":   
        if (GetCharacterItem(Pchar, "Pirate_Note_GB") >= 1) 
			{				
       		dialog.text = DLG_TEXT_BASE[1050];
           	link.l1 =DLG_TEXT_BASE[1051];
			link.l1.go = "exit";
            }			
           else		
            {       
   		    NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");		
			aCharacter = CharacterFromID("Testo");
			rCharacter = CharacterFromID("MyGirlPrisonner_9G");
            {
	        ch = GetCharacter(NPC_GenerateCharacter("Rapt_Girl", rCharacter.model, "woman", "woman", 3, rCharacter.nation, -1, true));	
	        ch.name 	= rCharacter.name;
	        ch.lastname = rCharacter.lastname;
			ch.City = rCharacter.City;
            ch.greeting = "Enc_RapersGirl_1";
	        ch.Dialog.Filename = "special_4\Rapt_Dialogue.c";
            ch.dialog.currentnode = "GirlDeck_A_A";
			ch.reputation = rCharacter.reputation;
			DeleteAttribute(ch, "items");
            RemoveCharacterEquip(ch, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(ch, GUN_ITEM_TYPE);
	        ch.location	= "My_Deck";
	        ch.location.group = "goto";
	        ch.location.locator = "goto2";
	        ch.SaveItemsForDead = true; // сохранять на трупе вещи
	        ch.DontClearDead = true; // не убирать труп через 200с
            ch.money = "1";
	        LAi_SetCitizenType(ch);
	        LAi_SetLoginTime(ch, 0.0, 24.0);
            LAi_NoRebirthEnable(ch);
		  	AddPassenger(pchar, ch, false);
		    SetCharacterRemovable(ch, false);
	        } 
			TakenItems(Pchar, "Pirate_Note_GB",1);
            ChangeCharacterAddressGroup(rCharacter, "none", "", "");
			rCharacter.LifeDay = 0; 	
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);
			TakenItems(aCharacter, "Pirate_Note_GE",-1);
        if (npchar.location == "MyOwn_Bedroom")	
            {	   
            TakenItems(aCharacter, "Pirate_Note_GE",-1);			
            }					
            }			
            break;				

		case "Rapt_Girl_9G_Morale": 
		    aCharacter = CharacterFromID("Testo");
       		DialogExit();
            ChangeCharacterAddressGroup(npchar, "Estate", "goto", "goto3");					
            ChangeCharacterReputation(pchar, -100);
            OfficersReaction("bad");
            AddCharacterExpToSkill(Pchar, "Leadership", 250);
            AddCrewMorale(Pchar, 100);
            ChangeCrewExp(pchar, "Sailors", 60);
	        ChangeCrewExp(pchar, "Cannoners", 60);
	        ChangeCrewExp(pchar, "Soldiers", 60);
            TakenItems(Pchar, "Pinion",1);
	    	TakenItems(aCharacter, "Pirate_Note_GA",-1);
            TakenItems(aCharacter, "Pirate_Note_GB", -1);	
            DoQuestCheckDelay("Kill_Rapt_Girl_9G", 1.0);
			DoQuestCheckDelay("PlayBadSex_1", 1.0);			
		    break;		

		case "exitSetCitizen":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
			LAi_SetCitizenType(npchar);
		    break;


		case "Sexend":
       		dialog.text = "Pitiй je n'en peux plus...";
			link.l1 ="Trиs bien retourne au bordel.";			
			link.l1.go = "Sexend1";
		    break;
		case "sexend1":
            		ChangeCharacterAddressGroup(npchar, "Myown_manor_brothel", "goto", "goto6");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
			LAi_SetCitizenType(npchar);
		if (npchar.id == "MyGirlPrisonner_6X")
			{
			npchar.dialog.currentnode = "Brothel_GirlSlave_A";
			}
		if (npchar.id == "MyGirlPrisonner_9E")
			{
			npchar.dialog.currentnode = "Brothel_Rapt_Girl_9E";
			}
		if (npchar.id == "MyGirlPrisonner_9F")
			{
			npchar.dialog.currentnode = "Brothel_Rapt_Girl_9F";
			}
		if (npchar.id == "MyGirlPrisonner_9G")
			{
			npchar.dialog.currentnode = "Brothel_Rapt_Girl_9G";
			}
		    aCharacter = CharacterFromID("Testo");			
		    TakenItems(aCharacter, "Pirate_Note_GE",-1);
		    break;

			

	}
	
}
