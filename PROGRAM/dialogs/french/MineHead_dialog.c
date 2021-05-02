#include "SD\TEXT\DIALOGS\MineHead_dialog.h"
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(DLG_TEXT_BASE[0],DLG_TEXT_BASE[1],DLG_TEXT_BASE[2]), 
					LinkRandPhrase(DLG_TEXT_BASE[3]+ GetSexPhrase(DLG_TEXT_BASE[4],DLG_TEXT_BASE[5]) +DLG_TEXT_BASE[6]+ GetSexPhrase(DLG_TEXT_BASE[7],"") +" !", DLG_TEXT_BASE[8],DLG_TEXT_BASE[9]+ GetSexPhrase(DLG_TEXT_BASE[10],DLG_TEXT_BASE[11]) +DLG_TEXT_BASE[12]));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple(DLG_TEXT_BASE[13], DLG_TEXT_BASE[14]), 
					RandPhraseSimple(DLG_TEXT_BASE[15] + GetWorkTypeOfMan(npchar, "") + DLG_TEXT_BASE[16], DLG_TEXT_BASE[17]));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = DLG_TEXT_BASE[18];
				link.l1 = DLG_TEXT_BASE[19];
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+DLG_TEXT_BASE[20]+GetFullName(npchar)+DLG_TEXT_BASE[21],DLG_TEXT_BASE[22],DLG_TEXT_BASE[23]);
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = DLG_TEXT_BASE[24];
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = DLG_TEXT_BASE[25];
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = DLG_TEXT_BASE[26];
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = DLG_TEXT_BASE[27]+DLG_TEXT_BASE[28]+DLG_TEXT_BASE[29]+DLG_TEXT_BASE[30];
			link.l1 = DLG_TEXT_BASE[31];			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = DLG_TEXT_BASE[32];
			link.l1 = DLG_TEXT_BASE[33]+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день дает +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = DLG_TEXT_BASE[34];
				link.l1 = DLG_TEXT_BASE[35];
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = DLG_TEXT_BASE[36];
				link.l1 = DLG_TEXT_BASE[37]+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = DLG_TEXT_BASE[38];
			link.l1 = DLG_TEXT_BASE[39];
			link.l1.go = "slaves_g";
			link.l2 = DLG_TEXT_BASE[40];
			link.l2.go = "slaves_s";
			link.l3 = DLG_TEXT_BASE[41];
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = DLG_TEXT_BASE[42];
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = DLG_TEXT_BASE[43];
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = DLG_TEXT_BASE[44];
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = DLG_TEXT_BASE[45];
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = DLG_TEXT_BASE[46]+FindRussianQtyString(sti(location.quest.slaves.qty))+DLG_TEXT_BASE[47];
				link.l1 = DLG_TEXT_BASE[48];
				link.l1.go = "slaves_max";
				link.l2 = DLG_TEXT_BASE[49];
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+DLG_TEXT_BASE[50];
			link.l1 = DLG_TEXT_BASE[51];
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = DLG_TEXT_BASE[52];
			link.l1 = DLG_TEXT_BASE[53];
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info(DLG_TEXT_BASE[54]);
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
