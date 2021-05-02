#include "SD\TEXT\DIALOGS\Quest_Store.h"
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[0],
                          DLG_TEXT_STR[1], DLG_TEXT_STR[2],
                          DLG_TEXT_STR[3], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[4] + NPChar.name + DLG_TEXT_STR[5], DLG_TEXT_STR[6],
                      DLG_TEXT_STR[7], DLG_TEXT_STR[8], npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = DLG_TEXT_STR[9]+npchar.name+DLG_TEXT_STR[10];
				link.l1.go = "tieyasal";
			}
			// Addon 2016-1 Jason пиратская линейка
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_start")
			{
				link.l1 = ""+npchar.name+DLG_TEXT_STR[203];
				link.l1.go = "mtraxx";
			}
			if(CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "pasq_win")
			{
				link.l1 = ""+npchar.name+DLG_TEXT_STR[204];
				link.l1.go = "mtraxx_5";
			}
			// ACKMOD
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = DLG_TEXT_STR[123];
				link.l1.go = "BlueBird_1";
			}
			if (pchar.questTemp.BlueBird == "weWon")
			{
				link.l1 = DLG_TEXT_STR[124];
				link.l1.go = "BlueBird_3";
			}			
		break;
				
		// город май€
		case "tieyasal":
			dialog.text = DLG_TEXT_STR[11];
			link.l1 = DLG_TEXT_STR[12];
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[125], 
				DLG_TEXT_STR[126], 
				DLG_TEXT_STR[127],
                DLG_TEXT_STR[128], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[129], 
				DLG_TEXT_STR[130],
                DLG_TEXT_STR[131], 
				DLG_TEXT_STR[132], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "BlueBird_2":
			dialog.text = DLG_TEXT_STR[133];
			link.l1 = DLG_TEXT_STR[134];
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "2");
		break;

		case "BlueBird_3":
			dialog.text = NPCStringReactionRepeat(DLG_TEXT_STR[135], 
				DLG_TEXT_STR[136], 
				DLG_TEXT_STR[137],
                DLG_TEXT_STR[138], "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(DLG_TEXT_STR[139], 
				DLG_TEXT_STR[140],
                DLG_TEXT_STR[141], 
				DLG_TEXT_STR[142], npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			pchar.quest.Mtraxx_PasqualeLate.over = "yes";
            dialog.text = DLG_TEXT_STR[205];
			link.l1 = DLG_TEXT_STR[206];
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
			string sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")));
            dialog.text = DLG_TEXT_STR[207]+sTemp+DLG_TEXT_STR[208];
			link.l1 = DLG_TEXT_STR[209];
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
			int i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
			int n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
            dialog.text = ""+sti(pchar.questTemp.Mtraxx.Crdn.degN)+" "+i+DLG_TEXT_STR[210]+sti(pchar.questTemp.Mtraxx.Crdn.degW)+" "+n+DLG_TEXT_STR[211];
			link.l1 = DLG_TEXT_STR[212];
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = DLG_TEXT_STR[213];
			link.l1 = "...";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_convoy";
		   i = sti(pchar.questTemp.Mtraxx.Crdn.minN2)-10;
           n = sti(pchar.questTemp.Mtraxx.Crdn.minW2)-10;
		   AddQuestRecord("Roger_4", "3");
		   AddQuestUserData("Roger_4", "sShip", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.Mtraxx.Crdn.Ship), "Name")+ "Gen")));
		   AddQuestUserData("Roger_4", "sdegN", sti(pchar.questTemp.Mtraxx.Crdn.degN));
		   AddQuestUserData("Roger_4", "sminN", i);
		   AddQuestUserData("Roger_4", "sdegW", sti(pchar.questTemp.Mtraxx.Crdn.degW));
		   AddQuestUserData("Roger_4", "sminW", n);
		   SetFunctionTimerCondition("Mtraxx_PasqualeTimeConvoy", 0, 0, 6, false);
		   SetFunctionTimerCondition("Mtraxx_PasqualeConvoyOver", 0, 0, 7, false);
		break;
		
		case "mtraxx_5":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_EBONY);
			if (iTotalTemp < 1)
			{
				dialog.text = DLG_TEXT_STR[214];
				link.l1 = "Hmm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < makeint(sti(pchar.questTemp.Mtraxx.Crdn.Ebony)/4))
			{
				dialog.text = DLG_TEXT_STR[215];
				link.l1 = "Hmm...";
				link.l1.go = "mtraxx_6";
				break;
			}
			if (iTotalTemp < sti(pchar.questTemp.Mtraxx.Crdn.Ebony)-20)
			{
				dialog.text = DLG_TEXT_STR[216]+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.Crdn.Ebony))+DLG_TEXT_STR[217];
				link.l1 = DLG_TEXT_STR[218];
				link.l1.go = "mtraxx_7";
				break;
			}
            dialog.text = DLG_TEXT_STR[219]+FindRussianQtyString(iTotalTemp)+DLG_TEXT_STR[220];
			link.l1 = DLG_TEXT_STR[221];
			link.l1.go = "mtraxx_10";
		break;
		
		case "mtraxx_6":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_angry";
		   DoQuestReloadToLocation("Pirates_town", "reload", "reload6", "");
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_7":
            dialog.text = DLG_TEXT_STR[222];
			link.l1 = DLG_TEXT_STR[223];
			link.l1.go = "mtraxx_8";
		break;
		
		case "mtraxx_8":
			AddMoneyToCharacter(pchar, iTotalTemp*100);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = DLG_TEXT_STR[224];
			link.l1 = DLG_TEXT_STR[225];
			link.l1.go = "mtraxx_9";
		break;
		
		case "mtraxx_9":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_fail";
		   AddQuestRecord("Roger_4", "8");
		   CloseQuestHeader("Roger_4");
		   QuestSetCurrentNode("Terrax", "mtraxx_34");
		break;
		
		case "mtraxx_10":
            dialog.text = DLG_TEXT_STR[226];
			link.l1 = DLG_TEXT_STR[227]+npchar.name+DLG_TEXT_STR[228];
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
			AddMoneyToCharacter(pchar, iTotalTemp*150);
			RemoveCharacterGoods(pchar, GOOD_EBONY, iTotalTemp);
            dialog.text = DLG_TEXT_STR[229];
			link.l1 = DLG_TEXT_STR[230];
			link.l1.go = "mtraxx_12";
		break;
		
		case "mtraxx_12":
           DialogExit();
		   pchar.questTemp.Mtraxx = "pasq_complete";
		   AddQuestRecord("Roger_4", "9");
		   pchar.quest.mtr_pasq_fin.win_condition.l1 = "location";
		   pchar.quest.mtr_pasq_fin.win_condition.l1.location = "Pirates_town";
		   pchar.quest.mtr_pasq_fin.function = "Mtraxx_PasqualeJeffry";
		   bDisableFastReload = true;
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}